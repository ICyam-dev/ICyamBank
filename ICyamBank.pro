QT       += core gui sql  # Ajoute sql ici pour inclure Qt SQL

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    src/databaseManager.cpp \
    src/main.cpp \
    src/mainwindow.cpp

HEADERS += \
    header/mainwindow.h \
    header/databaseManager.h

FORMS += \
    ui/mainwindow.ui

TRANSLATIONS += \
    languages/ICyamBank_en_US.ts \
    languages/ICyamBank_fr_FR.ts
CONFIG += lrelease
CONFIG += embed_translations

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    resources/ressources.qrc  # Correction du chemin des ressources
