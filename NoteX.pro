SOURCES += main.cpp \
    texteditorfunc.cpp

RESOURCES += qml.qrc
QT += quick qml widgets quickwidgets
HEADERS +=  \
    texteditorfunc.h

#qnx: target.path = /tmp/$${TARGET}/bin
#else: unix:!android: target.path = /opt/$${TARGET}/bin
#!isEmpty(target.path): INSTALLS += target

#DEFINES += QT_DEPRECATED_WARNINGS
#DEFINES += QT_NO_DEBUG_OUTPUT

DISTFILES += \
    QML_SettingUI.qml \
    main.qml
