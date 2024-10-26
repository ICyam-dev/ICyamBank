-- Table "user" pour les informations de l'utilisateur / "user" table for user information
CREATE TABLE user (
    id_user INTEGER PRIMARY KEY AUTOINCREMENT,   -- Identifiant unique de l'utilisateur / Unique identifier for the user
    folder_name TEXT NOT NULL,                    -- Nom du dossier de l'utilisateur / User folder name
    folder_desc TEXT,                             -- Description du dossier de l'utilisateur / User folder description
    first_name TEXT,                              -- Prénom de l'utilisateur / User's first name
    last_name TEXT,                               -- Nom de famille de l'utilisateur / User's last name
    phone TEXT,                                   -- Numéro de téléphone de l'utilisateur / User's phone number
    email TEXT,                                   -- Adresse email de l'utilisateur / User's email address
    addr1 TEXT,                                   -- Adresse principale de l'utilisateur (ligne 1) / User's main address (line 1)
    addr2 TEXT,                                   -- Adresse supplémentaire de l'utilisateur (ligne 2) / User's additional address (line 2)
    addr3 TEXT,                                   -- Autre adresse de l'utilisateur (ligne 3) / User's other address (line 3)
    default_currency TEXT,                        -- Devise par défaut de l'utilisateur / User's default currency
    language TEXT DEFAULT 'fr',                   -- Langue de l'application pour l'utilisateur / Application language for the user
    theme TEXT DEFAULT 'light',                   -- Thème d'interface pour l'utilisateur (clair ou sombre) / User's interface theme (light or dark)
    is_deleted INTEGER DEFAULT 0                  -- Utilisateur supprimé (soft delete) / Soft delete flag for the user
);

-- Table "bank" pour les informations de banque / "bank" table for bank information
CREATE TABLE bank (
    id_bank INTEGER PRIMARY KEY AUTOINCREMENT,    -- Identifiant unique de la banque / Unique bank ID
    bank_name TEXT NOT NULL,                      -- Nom de la banque / Bank name
    address_line1 TEXT,                           -- Adresse ligne 1 / Address line 1
    address_line2 TEXT,                           -- Adresse ligne 2 / Address line 2
    address_line3 TEXT,                           -- Adresse ligne 3 / Address line 3
    phone TEXT,                                   -- Téléphone de la banque / Bank phone
    email TEXT,                                   -- Email de la banque / Bank email
    website TEXT,                                 -- Site web de la banque / Bank website
    icon_url TEXT,                                -- Lien vers l'icône de la banque / Bank icon URL
    contact_name TEXT,                            -- Nom du contact à la banque / Bank contact name
    contact_phone TEXT,                           -- Téléphone du contact à la banque / Bank contact phone
    contact_email TEXT,                           -- Email du contact à la banque / Bank contact email
    id_user INTEGER,                              -- Lien avec l'utilisateur / Link to the user
    is_deleted INTEGER DEFAULT 0,                 -- Banque supprimée (soft delete) / Soft delete flag for the bank
    FOREIGN KEY (id_user) REFERENCES user(id_user) ON DELETE CASCADE -- Contrainte de clé étrangère pour id_user / Foreign key constraint for id_user
);

-- Table "type_account" pour les types de comptes bancaires / "type_account" table for bank account types
CREATE TABLE type_account (
    id_type INTEGER PRIMARY KEY AUTOINCREMENT,    -- Identifiant unique du type de compte / Unique account type ID
    name_type TEXT NOT NULL,                      -- Nom du type de compte / Account type name
    description TEXT,                             -- Description du type de compte / Account type description
    is_deleted INTEGER DEFAULT 0                  -- Type de compte supprimé (soft delete) / Soft delete flag for the account type
);

-- Table "group_account" pour les groupes de comptes / "group_account" table for account groups
CREATE TABLE group_account (
    id_group INTEGER PRIMARY KEY AUTOINCREMENT,   -- Identifiant unique du groupe de comptes / Unique account group ID
    name_group TEXT NOT NULL,                     -- Nom du groupe de comptes / Account group name
    description TEXT,                             -- Description du groupe de comptes / Account group description
    id_user INTEGER,                              -- Lien avec l'utilisateur / Link to the user
    is_deleted INTEGER DEFAULT 0,                 -- Groupe de compte supprimé (soft delete) / Soft delete flag for the account group
    FOREIGN KEY (id_user) REFERENCES user(id_user) ON DELETE CASCADE -- Contrainte de clé étrangère pour id_user / Foreign key constraint for id_user
);

-- Table "account" pour les comptes bancaires / "account" table for bank accounts
CREATE TABLE account (
    id_account INTEGER PRIMARY KEY AUTOINCREMENT,  -- Identifiant unique du compte / Unique account ID
    account_name TEXT NOT NULL,                    -- Nom du compte / Account name
    account_number TEXT NOT NULL,                  -- Numéro de compte / Account number
    id_user INTEGER NOT NULL,                      -- Lien avec l'utilisateur / Link to the user
    id_bank INTEGER NOT NULL,                      -- Lien avec la banque / Link to the bank
    id_type INTEGER NOT NULL,                      -- Lien avec le type de compte / Link to the account type
    id_devises INTEGER,                            -- Lien avec la devise du compte / Link to the account's currency
    id_group INTEGER,                              -- Lien avec le groupe de compte (facultatif) / Link to the account group (optional)
    balance REAL DEFAULT 0.0,                      -- Solde actuel du compte / Current balance of the account
    balance_in_group INTEGER,                      -- Indicateur si le solde est inclus dans le groupe / Flag if balance is included in group
    description TEXT,                              -- Description du compte / Account description
    contact_name TEXT,                             -- Nom du contact à la banque / Bank contact name
    contact_phone TEXT,                            -- Téléphone du contact à la banque / Bank contact phone
    contact_email TEXT,                            -- Email du contact à la banque / Bank contact email
    icon_url TEXT,                                 -- URL de l'icône du compte / URL for the account icon
    is_deleted INTEGER DEFAULT 0,                  -- Compte supprimé (soft delete) / Soft delete flag for the account
    FOREIGN KEY (id_user) REFERENCES user(id_user) ON DELETE CASCADE,  -- Clé étrangère vers l'utilisateur / Foreign key to user
    FOREIGN KEY (id_bank) REFERENCES bank(id_bank),                    -- Clé étrangère vers la banque / Foreign key to bank
    FOREIGN KEY (id_type) REFERENCES type_account(id_type),            -- Clé étrangère vers le type de compte / Foreign key to account type
    FOREIGN KEY (id_group) REFERENCES group_account(id_group),         -- Clé étrangère vers le groupe de compte / Foreign key to account group
    FOREIGN KEY (id_devises) REFERENCES devises(id_devises)            -- Clé étrangère vers la devise / Foreign key to currency
);

-- Table "account_documents" pour les documents liés aux comptes bancaires / "account_documents" table for documents linked to bank accounts
CREATE TABLE account_documents (
    id_document INTEGER PRIMARY KEY AUTOINCREMENT,  -- Identifiant unique du document / Unique document ID
    id_account INTEGER NOT NULL,                    -- Lien avec le compte bancaire / Link to the bank account
    document_name TEXT NOT NULL,                    -- Nom du document / Document name
    document_url TEXT NOT NULL,                     -- Lien vers le document / Document URL
    description TEXT,                               -- Description du document / Document description
    upload_date DATE DEFAULT CURRENT_DATE,          -- Date d'ajout du document / Document upload date
    is_deleted INTEGER DEFAULT 0,                   -- Document supprimé (soft delete) / Soft delete flag for the document
    FOREIGN KEY (id_account) REFERENCES account(id_account) -- Clé étrangère vers le compte / Foreign key to account
);

-- Table "contact" pour les informations de contact / "contact" table for contact information
CREATE TABLE contact (
    id_contact INTEGER PRIMARY KEY AUTOINCREMENT,   -- Identifiant unique du contact / Unique contact ID
    contact_name TEXT NOT NULL,                     -- Nom du contact / Contact name
    phone TEXT,                                     -- Téléphone du contact / Contact phone
    email TEXT,                                     -- Email du contact / Contact email
    address TEXT,                                   -- Adresse du contact / Contact address
    id_user INTEGER,                                -- Lien avec l'utilisateur / Link to the user
    is_deleted INTEGER DEFAULT 0,                   -- Contact supprimé (soft delete) / Soft delete flag for the contact
    FOREIGN KEY (id_user) REFERENCES user(id_user) ON DELETE CASCADE -- Clé étrangère vers l'utilisateur / Foreign key to user
);

-- Table "projects" pour les projets de l'utilisateur / "projects" table for user projects
CREATE TABLE projects (
    id_project INTEGER PRIMARY KEY AUTOINCREMENT,   -- Identifiant unique du projet / Unique project ID
    project_name TEXT NOT NULL,                     -- Nom du projet / Project name
    budget REAL,                                    -- Montant budgété pour le projet / Project budget amount
    total_spent REAL DEFAULT 0.0,                   -- Montant total dépensé pour le projet / Total amount spent on project
    id_user INTEGER,                                -- Lien avec l'utilisateur / Link to the user
    is_deleted INTEGER DEFAULT 0,                   -- Projet supprimé (soft delete) / Soft delete flag for the project
    FOREIGN KEY (id_user) REFERENCES user(id_user) ON DELETE CASCADE -- Clé étrangère vers l'utilisateur / Foreign key to user
);

-- Table "transactions" pour les transactions / "transactions" table for transactions
CREATE TABLE transactions (
    id_transaction INTEGER PRIMARY KEY AUTOINCREMENT,  -- Identifiant unique de la transaction / Unique transaction ID
    id_user INTEGER NOT NULL,                          -- Lien avec l'utilisateur / Link to the user
    id_contact INTEGER NOT NULL,                       -- Lien avec le contact / Link to the contact
    date_transaction DATE NOT NULL,                    -- Date de la transaction / Transaction date
    payment_method TEXT,                               -- Moyen de paiement / Payment method
    label TEXT,                                        -- Libellé de la transaction / Transaction label
    reference TEXT,                                    -- Référence (numéro de facture ou chèque) / Reference (invoice or check number)
    amount REAL NOT NULL,                              -- Montant total de la transaction / Total transaction amount
    is_deleted INTEGER DEFAULT 0,                      -- Transaction supprimée (soft delete) / Soft delete flag for the transaction
    FOREIGN KEY (id_user) REFERENCES user(id_user) ON DELETE CASCADE,  -- Clé étrangère vers l'utilisateur / Foreign key to user
    FOREIGN KEY (id_contact) REFERENCES contact(id_contact)           -- Clé étrangère vers le contact / Foreign key to contact
);

-- Table "charge_benefit_post" pour les postes de charge et de bénéfice / "charge_benefit_post" table for expense and income categories
CREATE TABLE charge_benefit_post (
    id_post INTEGER PRIMARY KEY AUTOINCREMENT,     -- Identifiant unique du poste / Unique category ID
    category TEXT NOT NULL,                        -- Catégorie principale (ex. : Dépenses, Recettes, Hybrides) / Main category (e.g., Expenses, Income, Hybrid)
    name_post TEXT NOT NULL,                       -- Nom du poste / Category name
    parent_post INTEGER,                           -- Poste parent pour organisation hiérarchique / Parent category for hierarchical organization
    id_user INTEGER,                               -- Lien avec l'utilisateur / Link to the user
    is_deleted INTEGER DEFAULT 0,                  -- Poste supprimé (soft delete) / Soft delete flag for the category
    FOREIGN KEY (parent_post) REFERENCES charge_benefit_post(id_post),  -- Clé étrangère vers le poste parent / Foreign key to parent category
    FOREIGN KEY (id_user) REFERENCES user(id_user) ON DELETE CASCADE -- Clé étrangère vers l'utilisateur / Foreign key to user
);

-- Table "transaction_splits" pour les ventilations de transaction / "transaction_splits" table for transaction breakdowns
CREATE TABLE transaction_splits (
    id_split INTEGER PRIMARY KEY AUTOINCREMENT,   -- Identifiant unique de la ventilation / Unique split ID
    id_transaction INTEGER NOT NULL,              -- Lien avec la transaction / Link to transaction
    id_post INTEGER NOT NULL,                     -- Lien avec le poste de charge ou de bénéfice / Link to expense or income category
    id_project INTEGER,                           -- Lien avec le projet (facultatif) / Link to project (optional)
    amount REAL NOT NULL,                         -- Montant affecté à ce poste / Amount allocated to this category
    remark TEXT,                                  -- Remarque ou libellé spécifique à cette ventilation / Remark or specific label for this split
    is_deleted INTEGER DEFAULT 0,                 -- Ventilation supprimée (soft delete) / Soft delete flag for the split
    FOREIGN KEY (id_transaction) REFERENCES transactions(id_transaction),  -- Clé étrangère vers la transaction / Foreign key to transaction
    FOREIGN KEY (id_post) REFERENCES charge_benefit_post(id_post),        -- Clé étrangère vers le poste de charge / Foreign key to expense category
    FOREIGN KEY (id_project) REFERENCES projects(id_project)              -- Clé étrangère vers le projet / Foreign key to project
);