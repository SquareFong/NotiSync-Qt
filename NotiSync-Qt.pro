QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    src/widgets/chatview.cpp \
    src/widgets/loginview.cpp \
    src/main.cpp \
    src/widgets/mainview.cpp \
    src/widgets/mainviewphonedetails.cpp \
    src/widgets/mainviewphonemessages.cpp \
    src/widgets/mainviewphonenotifications.cpp \
    src/widgets/messageitemwidget.cpp \
    src/widgets/messagesitemdelegate.cpp \
    src/widgets/notificationitemdelegate.cpp \
    src/core/communicationstructs.cpp \
    src/core/networkutils.cpp \
    src/core/notisyncclient.cpp \
    src/widgets/widget.cpp

HEADERS += \
    src/widgets/chatview.h \
    src/widgets/loginview.h \
    src/widgets/mainview.h \
    src/widgets/mainviewphonedetails.h \
    src/widgets/mainviewphonemessages.h \
    src/widgets/mainviewphonenotifications.h \
    src/widgets/messageitemwidget.h \
    src/widgets/notificationitemdelegate.h \
    src/widgets/messagesitemdelegate.h \
    src/core/communicationstructs.h \
    src/core/networkutils.h \
    src/core/notisyncclient.h \
    src/widgets/widget.h

FORMS += \
    loginview.ui

LIBS += -lcurl

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    icons.qrc

DISTFILES +=
