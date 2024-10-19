QT       += core gui sql  # Ajoute sql ici pour inclure Qt SQL

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

SOURCES += \
    src/databaseManager.cpp \
    src/interfaceManager.cpp \
    src/leftcolumnManager.cpp \
    src/main.cpp \
    src/mainwindow.cpp \
    src/winAbout.cpp \
    src/winAccount.cpp \
    src/winBank.cpp \
    src/winDoc.cpp \
    src/winGroup.cpp

HEADERS += \
    header/interfaceManager.h \
    header/databaseManager.h \
    header/mainwindow.h \
    header/leftcolumnManager.h \
    header/version.h \
    header/winAbout.h \
    header/winAccount.h \
    header/winBank.h \
    header/winDoc.h \
    header/winGroup.h

FORMS += \
    ui/mainwindow.ui \
    ui/winAccount.ui \
    ui/winBank.ui \
    ui/winDoc.ui \
    ui/winGroup.ui \
    ui/winabout.ui

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
    resources/ressources.qrc \
    resources/ressources.qrc \
    resources/ressources.qrc \
    resources/ressources.qrc \
    resources/ressources.qrc \
    ressources/ressources.qrc \
    ressources/ressources.qrc \
    ressources/images.qrc
