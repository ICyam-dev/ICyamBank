#ifndef VERSION_H
#define VERSION_H

// Version du projet / Project version
#define VERSION_STATE "d"        // d -> développement, b -> beta, r -> release

// Séparation du numéro de release en version majeure et mineure / Split release number into major and minor versions
#define RELEASE_MAJOR "0"        // Version majeure / Major version
#define RELEASE_MINOR "0"        // Version mineure / Minor version

// Combine RELEASE_YEAR et RELEASE_MONTH dans un code de 4 chiffres "AAMM"
#define RELEASE_CODE 2410        // Année (AA) = 24 pour 2024, Mois (MM) = 10 pour Octobre

#define BUILD_NUMBER 177         // Numéro de build / Build number

// Chaîne complète de version / Complete version string
#define VERSION_STRING VERSION_STATE RELEASE_MAJOR "." RELEASE_MINOR "." RELEASE_CODE "." BUILD_NUMBER

#endif // VERSION_H
