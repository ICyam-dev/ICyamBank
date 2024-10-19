-- Table "user"
CREATE TABLE user (
    id_user INTEGER PRIMARY KEY AUTOINCREMENT,
    first_name TEXT NOT NULL,          -- Prénom de l'utilisateur
    last_name TEXT NOT NULL,           -- Nom de famille de l'utilisateur
    email TEXT,                        -- Email de l'utilisateur
    phone TEXT,                        -- Téléphone de l'utilisateur
    address TEXT,                      -- Adresse de l'utilisateur
    default_currency TEXT,             -- Devise par défaut
    language TEXT DEFAULT 'fr',        -- Langue de l'application
    theme TEXT DEFAULT 'light',        -- Thème de l'interface (clair ou sombre)
    is_deleted INTEGER DEFAULT 0       -- Utilisateur supprimé (soft delete) / Soft delete flag
);

-- Table "bank"
CREATE TABLE bank (
    id_bank INTEGER PRIMARY KEY AUTOINCREMENT,   -- Identifiant unique / Unique ID
    bank_name TEXT NOT NULL,                     -- Nom de la banque / Bank name
    address_line1 TEXT,                          -- Adresse ligne 1 / Address line 1
    address_line2 TEXT,                          -- Adresse ligne 2 / Address line 2
    address_line3 TEXT,                          -- Adresse ligne 3 / Address line 3
    phone TEXT,                                  -- Téléphone de la banque / Bank phone
    email TEXT,                                  -- Email de la banque / Bank email
    website TEXT,                                -- Site web de la banque / Bank website
    icon_url TEXT,                               -- Lien vers l'icône de la banque / Bank icon URL
    contact_name TEXT,                           -- Nom du contact à la banque / Bank contact name
    contact_phone TEXT,                          -- Téléphone du contact à la banque / Bank contact phone
    contact_email TEXT,                          -- Email du contact à la banque / Bank contact email
    is_deleted INTEGER DEFAULT 0                 -- Banque supprimée (soft delete) / Soft delete flag
);

-- Table "type_account"
CREATE TABLE type_account (
    id_type INTEGER PRIMARY KEY AUTOINCREMENT,
    name_type TEXT NOT NULL,           -- Nom du type de compte
    description TEXT,                  -- Description du type de compte
    is_deleted INTEGER DEFAULT 0       -- Type de compte supprimé (soft delete) / Soft delete flag
);

-- Table "group_account"
CREATE TABLE group_account (
    id_group INTEGER PRIMARY KEY AUTOINCREMENT,
    name_group TEXT NOT NULL,          -- Nom du groupe de comptes
    description TEXT,                  -- Description du groupe de comptes
    is_deleted INTEGER DEFAULT 0       -- Groupe de compte supprimé (soft delete) / Soft delete flag
);

-- Table "account"
CREATE TABLE account (
    id_account INTEGER PRIMARY KEY AUTOINCREMENT,
    account_number TEXT NOT NULL,      -- Numéro de compte
    id_user INTEGER NOT NULL,          -- Lien avec l'utilisateur
    id_bank INTEGER NOT NULL,          -- Lien avec la banque
    id_type INTEGER NOT NULL,          -- Lien avec le type de compte
    id_group INTEGER,                  -- Lien avec le groupe de compte
    balance REAL DEFAULT 0.0,          -- Solde actuel
    description TEXT,                  -- Description du compte
    opening_date DATE,                 -- Date d'ouverture du compte
    active BOOLEAN DEFAULT 1,          -- Compte actif ou non
    contact_name TEXT,                 -- Nom du contact à la banque
    contact_phone TEXT,                -- Téléphone du contact à la banque
    contact_email TEXT,                -- Email du contact à la banque
    icon_url TEXT,                     -- Lien vers l'icône du compte
    is_deleted INTEGER DEFAULT 0,      -- Compte supprimé (soft delete) / Soft delete flag
    FOREIGN KEY (id_user) REFERENCES user(id_user),
    FOREIGN KEY (id_bank) REFERENCES bank(id_bank),
    FOREIGN KEY (id_type) REFERENCES type_account(id_type),
    FOREIGN KEY (id_group) REFERENCES group_account(id_group)
);

-- Table "account_documents"
CREATE TABLE account_documents (
    id_document INTEGER PRIMARY KEY AUTOINCREMENT,
    id_account INTEGER NOT NULL,       -- Lien avec le compte bancaire
    document_name TEXT NOT NULL,       -- Nom du document
    document_url TEXT NOT NULL,        -- Lien vers le document
    description TEXT,                  -- Description du document
    upload_date DATE DEFAULT CURRENT_DATE, -- Date d'ajout du document
    is_deleted INTEGER DEFAULT 0,      -- Document supprimé (soft delete) / Soft delete flag
    FOREIGN KEY (id_account) REFERENCES account(id_account)
);

-- Table "contact"
CREATE TABLE contact (
    id_contact INTEGER PRIMARY KEY AUTOINCREMENT,  -- Identifiant unique du contact
    contact_name TEXT NOT NULL,                   -- Nom du contact (fournisseur, client, etc.)
    phone TEXT,                                   -- Téléphone du contact
    email TEXT,                                   -- Email du contact
    address TEXT,                                 -- Adresse du contact
    is_deleted INTEGER DEFAULT 0                  -- Contact supprimé (soft delete) / Soft delete flag
);

-- Table "projects"
CREATE TABLE projects (
    id_project INTEGER PRIMARY KEY AUTOINCREMENT,  -- Identifiant unique du projet
    project_name TEXT NOT NULL,                   -- Nom du projet (ex. : Mariage, Rénovation)
    budget REAL,                                  -- Montant budgété pour le projet
    total_spent REAL DEFAULT 0.0,                 -- Montant total dépensé pour le projet
    is_deleted INTEGER DEFAULT 0                  -- Projet supprimé (soft delete) / Soft delete flag
);

-- Table "transactions"
CREATE TABLE transactions (
    id_transaction INTEGER PRIMARY KEY AUTOINCREMENT,  -- Identifiant unique de la transaction
    id_contact INTEGER NOT NULL,                      -- Lien avec le contact
    date_transaction DATE NOT NULL,                   -- Date de la transaction
    payment_method TEXT,                              -- Moyen de paiement (ex. : chèque, carte, virement)
    label TEXT,                                       -- Libellé de la transaction
    reference TEXT,                                   -- Référence (numéro de facture ou chèque)
    amount REAL NOT NULL,                             -- Montant total de la transaction
    is_deleted INTEGER DEFAULT 0,                     -- Transaction supprimée (soft delete) / Soft delete flag
    FOREIGN KEY (id_contact) REFERENCES contact(id_contact)
);

-- Table "charge_benefit_post"
CREATE TABLE charge_benefit_post (
    id_post INTEGER PRIMARY KEY AUTOINCREMENT,  -- Identifiant unique du poste
    category TEXT NOT NULL,                     -- Catégorie principale (ex. : Dépenses, Recettes, Hybrides)
    name_post TEXT NOT NULL,                    -- Nom du poste (ex. : Loyer, Salaire, Dividendes)
    parent_post INTEGER,                        -- Poste parent pour organiser hiérarchiquement (ex: Maison -> Loyer)
    is_deleted INTEGER DEFAULT 0,               -- Poste supprimé (soft delete) / Soft delete flag
    FOREIGN KEY (parent_post) REFERENCES charge_benefit_post(id_post)
);

-- Table "transaction_splits"
CREATE TABLE transaction_splits (
    id_split INTEGER PRIMARY KEY AUTOINCREMENT,  -- Identifiant unique de la ventilation
    id_transaction INTEGER NOT NULL,             -- Lien avec la transaction (clé étrangère vers transactions)
    id_post INTEGER NOT NULL,                    -- Lien avec le poste de charge ou de bénéfice
    id_project INTEGER,                          -- Lien avec le projet (clé étrangère vers projects)
    amount REAL NOT NULL,                        -- Montant affecté à ce poste
    remark TEXT,                                 -- Remarque ou libellé spécifique à cette partie de la transaction
    is_deleted INTEGER DEFAULT 0,                -- Ventilation supprimée (soft delete) / Soft delete flag
    FOREIGN KEY (id_transaction) REFERENCES transactions(id_transaction),
    FOREIGN KEY (id_post) REFERENCES charge_benefit_post(id_post),
    FOREIGN KEY (id_project) REFERENCES projects(id_project)
);