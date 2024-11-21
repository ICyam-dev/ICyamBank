QT       += core gui sql  # Ajoute sql ici pour inclure Qt SQL

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = ICyamBank

CONFIG += c++17

SOURCES += \
    src/databaseManager.cpp \
    src/main.cpp \
    src/mainWindowUpdate.cpp \
    src/mainwindow.cpp \
    src/objICyamApp.cpp \
    src/winAbout.cpp \
    src/winAccount.cpp \
    src/winBank.cpp \
    src/winCurrentUser.cpp \
    src/winDoc.cpp \
    src/winGroup.cpp \
    src/winInsertData.cpp \
    src/winUser.cpp

HEADERS += \
    header/databaseManager.h \
    header/mainWindowUpdate.h \
    header/mainwindow.h \
    header/objICyamApp.h \
    header/version.h \
    header/winAbout.h \
    header/winAccount.h \
    header/winBank.h \
    header/winCurrentUser.h \
    header/winDoc.h \
    header/winGroup.h \
    header/winUser.h \
    header/winInsertData.h

FORMS += \
    ui/mainwindow.ui \
    ui/winAccount.ui \
    ui/winBank.ui \
    ui/winCurrentUser.ui \
    ui/winDoc.ui \
    ui/winGroup.ui \
    ui/winInsertData.ui \
    ui/winUser.ui \
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
    ressources/ressources.qrc \
