--
-- Fichier généré par SQLiteStudio v3.4.4 sur mer. oct. 30 18:19:51 2024
--
-- Encodage texte utilisé : UTF-8
--
PRAGMA foreign_keys = off;
BEGIN TRANSACTION;

-- Tableau : account
CREATE TABLE IF NOT EXISTS account (
    id_account       INTEGER PRIMARY KEY AUTOINCREMENT,
    account_name     TEXT    NOT NULL,
    id_folder        INTEGER NOT NULL,
    id_bank          INTEGER NOT NULL,
    id_type          INTEGER NOT NULL,
    id_devise        INTEGER REFERENCES devise (id_devise) 
                             NOT NULL,
    id_group         INTEGER,
    account_number   TEXT,
    balance          REAL    DEFAULT 0.0,
    balance_in_group INTEGER DEFAULT (1) 
                             NOT NULL,
    description      TEXT,
    contact_name     TEXT,
    contact_phone    TEXT,
    contact_email    TEXT,
    icon_url         TEXT,
    is_deleted       INTEGER DEFAULT 0,
    FOREIGN KEY (
        id_folder
    )
    REFERENCES user (id_user),
    FOREIGN KEY (
        id_bank
    )
    REFERENCES bank (id_bank),
    FOREIGN KEY (
        id_type
    )
    REFERENCES type_account (id_type),
    FOREIGN KEY (
        id_group
    )
    REFERENCES group_account (id_group) 
);


-- Tableau : account_documents
CREATE TABLE IF NOT EXISTS account_documents (
    id_document   INTEGER PRIMARY KEY AUTOINCREMENT,
    id_account    INTEGER NOT NULL,-- Lien avec le compte bancaire
    document_name TEXT    NOT NULL,-- Nom du document
    document_url  TEXT    NOT NULL,-- Lien vers le document
    description   TEXT,-- Description du document
    upload_date   DATE    DEFAULT CURRENT_DATE,-- Date d'ajout du document
    is_deleted    INTEGER DEFAULT 0,-- Document supprimé (soft delete) / Soft delete flag
    FOREIGN KEY (
        id_account
    )
    REFERENCES account (id_account) 
);


-- Tableau : bank
CREATE TABLE IF NOT EXISTS bank (
    id_bank       INTEGER PRIMARY KEY AUTOINCREMENT,
    id_folder             NOT NULL,
    bank_name     TEXT    NOT NULL,
    address_line1 TEXT,
    address_line2 TEXT,
    address_line3 TEXT,
    phone         TEXT,
    email         TEXT,
    website       TEXT,
    icon_url      TEXT,
    contact_name  TEXT,
    contact_phone TEXT,
    contact_email TEXT,
    is_deleted    INTEGER DEFAULT 0,
    FOREIGN KEY (
        id_folder
    )
    REFERENCES user (id_user) 
);


-- Tableau : charge_benefit_post
CREATE TABLE IF NOT EXISTS charge_benefit_post (
    id_post     INTEGER PRIMARY KEY AUTOINCREMENT,
    id_folder   INTEGER NOT NULL,
    category    TEXT    NOT NULL,
    name_post   TEXT    NOT NULL,
    parent_post INTEGER,
    is_deleted  INTEGER DEFAULT 0,
    FOREIGN KEY (
        parent_post
    )
    REFERENCES charge_benefit_post (id_post),
    FOREIGN KEY (
        id_folder
    )
    REFERENCES user (id_user) 
);


-- Tableau : contact
CREATE TABLE IF NOT EXISTS contact (
    id_contact   INTEGER PRIMARY KEY AUTOINCREMENT,
    id_folder    INTEGER NOT NULL,
    contact_name TEXT    NOT NULL,
    phone        TEXT,
    email        TEXT,
    address      TEXT,
    is_deleted   INTEGER DEFAULT 0,
    FOREIGN KEY (
        id_folder
    )
    REFERENCES user (id_user) 
);


-- Tableau : devise
CREATE TABLE IF NOT EXISTS devise (
    id_devise          PRIMARY KEY
                       NOT NULL,
    devise_name   TEXT NOT NULL,
    devise_symbol TEXT
);


-- Tableau : group_account
CREATE TABLE IF NOT EXISTS group_account (
    id_group    INTEGER PRIMARY KEY AUTOINCREMENT,
    id_folder           NOT NULL,
    name_group  TEXT    NOT NULL,
    description TEXT,
    is_deleted  INTEGER DEFAULT 0,
    FOREIGN KEY (
        id_folder
    )
    REFERENCES user (id_user) 
);


-- Tableau : projects
CREATE TABLE IF NOT EXISTS projects (
    id_project   INTEGER PRIMARY KEY AUTOINCREMENT,
    id_folder    INTEGER NOT NULL,
    project_name TEXT    NOT NULL,
    budget       REAL,
    total_spent  REAL    DEFAULT 0.0,
    is_deleted   INTEGER DEFAULT 0,
    FOREIGN KEY (
        id_folder
    )
    REFERENCES user (id_user) 
);


-- Tableau : transaction_splits
CREATE TABLE IF NOT EXISTS transaction_splits (
    id_split       INTEGER PRIMARY KEY AUTOINCREMENT,-- Identifiant unique de la ventilation
    id_transaction INTEGER NOT NULL,-- Lien avec la transaction (clé étrangère vers transactions)
    id_post        INTEGER NOT NULL,-- Lien avec le poste de charge ou de bénéfice
    id_project     INTEGER,-- Lien avec le projet (clé étrangère vers projects)
    amount         REAL    NOT NULL,-- Montant affecté à ce poste
    remark         TEXT,-- Remarque ou libellé spécifique à cette partie de la transaction
    is_deleted     INTEGER DEFAULT 0,-- Ventilation supprimée (soft delete) / Soft delete flag
    FOREIGN KEY (
        id_transaction
    )
    REFERENCES transactions (id_transaction),
    FOREIGN KEY (
        id_post
    )
    REFERENCES charge_benefit_post (id_post),
    FOREIGN KEY (
        id_project
    )
    REFERENCES projects (id_project) 
);


-- Tableau : transactions
CREATE TABLE IF NOT EXISTS transactions (
    id_transaction   INTEGER PRIMARY KEY AUTOINCREMENT,
    id_account       INTEGER NOT NULL,
    id_contact       INTEGER NOT NULL,
    date_transaction DATE    NOT NULL,
    payment_method   TEXT,
    label            TEXT,
    reference        TEXT,
    amount           REAL    NOT NULL,
    is_deleted       INTEGER DEFAULT 0,
    FOREIGN KEY (
        id_contact
    )
    REFERENCES contact (id_contact),
    FOREIGN KEY (
        id_account
    )
    REFERENCES account (id_account) 
);


-- Tableau : type_account
CREATE TABLE IF NOT EXISTS type_account (
    id_type     INTEGER PRIMARY KEY AUTOINCREMENT,
    name_type   TEXT    NOT NULL,-- Nom du type de compte
    description TEXT,-- Description du type de compte
    is_deleted  INTEGER DEFAULT 0-- Type de compte supprimé (soft delete) / Soft delete flag
);


-- Tableau : user
CREATE TABLE IF NOT EXISTS user (
    id_user          INTEGER PRIMARY KEY AUTOINCREMENT,
    folder_name      TEXT    NOT NULL,
    first_name       TEXT,
    last_name        TEXT,
    email            TEXT,
    phone            TEXT,
    address          TEXT,
    default_currency TEXT,
    language         TEXT    DEFAULT 'fr',
    theme            TEXT    DEFAULT 'light',
    is_deleted       INTEGER DEFAULT 0
);


COMMIT TRANSACTION;
PRAGMA foreign_keys = on;
