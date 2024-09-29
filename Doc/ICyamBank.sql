-- Table des groupes de comptes (Bilan, Bénéfice et Perte)
CREATE TABLE account_groups (
    id_group INTEGER PRIMARY KEY AUTOINCREMENT,
    name_group TEXT NOT NULL,
    description TEXT,
    active BOOLEAN DEFAULT 1
);

-- Table des types de comptes (Banques, Portefeuilles, Revenus, Dépenses, etc.)
CREATE TABLE account_types (
    id_type INTEGER PRIMARY KEY AUTOINCREMENT,
    id_group INTEGER NOT NULL,
    name_type TEXT NOT NULL,
    description TEXT,
    active BOOLEAN DEFAULT 1,
    FOREIGN KEY (id_group) REFERENCES account_groups(id_group)
);

-- Table des catégories de comptes définies par l'utilisateur
CREATE TABLE account_categories (
    id_category INTEGER PRIMARY KEY AUTOINCREMENT,
    id_type INTEGER NOT NULL,
    name_category TEXT NOT NULL,
    description TEXT,
    active BOOLEAN DEFAULT 1,
    FOREIGN KEY (id_type) REFERENCES account_types(id_type)
);

-- Table des comptes bancaires et autres
CREATE TABLE accounts (
    id_account INTEGER PRIMARY KEY AUTOINCREMENT,
    id_category INTEGER NOT NULL,
    name_account TEXT NOT NULL,
    balance_account REAL DEFAULT 0.0,
    id_currency INTEGER NOT NULL,
    description TEXT,
    opening_date DATE,
    active BOOLEAN DEFAULT 1,
    FOREIGN KEY (id_category) REFERENCES account_categories(id_category),
    FOREIGN KEY (id_currency) REFERENCES currencies(id_currency)
);

-- Table des devises
CREATE TABLE currencies (
    id_currency INTEGER PRIMARY KEY AUTOINCREMENT,
    code TEXT NOT NULL UNIQUE,
    symbol TEXT NOT NULL,
    name TEXT NOT NULL,
    exchange_rate REAL DEFAULT 1.0
);

-- Table des transactions
CREATE TABLE transactions (
    id_transaction INTEGER PRIMARY KEY AUTOINCREMENT,
    id_account INTEGER NOT NULL,
    id_beneficiary INTEGER,
    date_transaction DATE NOT NULL,
    amount REAL NOT NULL,
    description TEXT,
    id_currency INTEGER NOT NULL,
    status TEXT DEFAULT 'completed',
    recurrence TEXT DEFAULT 'none', -- Fréquence de l'opération (none, daily, weekly, monthly, annually)
    recurrence_end DATE, -- Date de fin de la récurrence, si applicable
    FOREIGN KEY (id_account) REFERENCES accounts(id_account),
    FOREIGN KEY (id_beneficiary) REFERENCES beneficiaries(id_beneficiary),
    FOREIGN KEY (id_currency) REFERENCES currencies(id_currency)
);

-- Table des transactions ventilées (Split transactions)
CREATE TABLE split_transactions (
    id_split INTEGER PRIMARY KEY AUTOINCREMENT,
    id_transaction INTEGER NOT NULL,
    id_account INTEGER NOT NULL,
    amount REAL NOT NULL,
    description TEXT,
    FOREIGN KEY (id_transaction) REFERENCES transactions(id_transaction),
    FOREIGN KEY (id_account) REFERENCES accounts(id_account)
);

-- Table des bénéficiaires
CREATE TABLE beneficiaries (
    id_beneficiary INTEGER PRIMARY KEY AUTOINCREMENT,
    name_beneficiary TEXT NOT NULL,
    address TEXT,
    phone TEXT,
    email TEXT
);

-- Table des paramètres utilisateur
CREATE TABLE user_settings (
    id_user INTEGER PRIMARY KEY AUTOINCREMENT,
    default_currency INTEGER NOT NULL,
    date_format TEXT NOT NULL,
    number_format TEXT NOT NULL,
    language TEXT NOT NULL,
    theme TEXT DEFAULT 'light',
    FOREIGN KEY (default_currency) REFERENCES currencies(id_currency)
);

-- Table des fichiers attachés
CREATE TABLE attachments (
    id_attachment INTEGER PRIMARY KEY AUTOINCREMENT,
    file_path TEXT NOT NULL, -- Chemin vers le fichier (PNG, JPG, PDF)
    file_type TEXT NOT NULL, -- Type de fichier (png, jpg, pdf)
    id_transaction INTEGER, -- Optionnel, fichier attaché à une transaction
    id_account INTEGER, -- Optionnel, fichier attaché à un compte
    id_user INTEGER, -- Optionnel, fichier attaché à un utilisateur
    description TEXT,
    FOREIGN KEY (id_transaction) REFERENCES transactions(id_transaction),
    FOREIGN KEY (id_account) REFERENCES accounts(id_account),
    FOREIGN KEY (id_user) REFERENCES user_settings(id_user)
);