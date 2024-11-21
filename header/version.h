#ifndef VERSION_H
#define VERSION_H

// Indicateur d'état de la version / Version status indicator
// 'd' -> développement, 'b' -> beta, 'r' -> release
// 'd' -> development, 'b' -> beta, 'r' -> release
#define VERSION_STATE "d"

// Numéro de version majeure et mineure / Major and minor version numbers
#define RELEASE_MAJOR "0"        // Version majeure / Major version
#define RELEASE_MINOR "0"        // Version mineure / Minor version

// Code de version basé sur l'année et le mois au format "AAMM"
// Version code based on year and month in "YYMM" format
// Exemple : 2410 signifie octobre 2024 / Example: 2410 means October 2024
#define RELEASE_CODE 2411

// Numéro de build pour suivi des modifications
// Build number for tracking incremental updates
#define BUILD_NUMBER 437

// Chaîne de version complète / Complete version string
// Format: état.version_majeure.version_mineure.année_mois.build
// Format: state.major_version.minor_version.year_month.build
#define VERSION_STRING VERSION_STATE RELEASE_MAJOR "." RELEASE_MINOR "." RELEASE_CODE "." BUILD_NUMBER

#endif // VERSION_H
