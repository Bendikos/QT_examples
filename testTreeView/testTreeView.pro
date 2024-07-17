QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0
SOURCES += main.cpp\
        mainwindow.cpp \
    TreeView.cpp \
    TreeModel.cpp \
    DevRoot.cpp \
    NodeBase.cpp \
    NodeAA.cpp \
    NodeBB.cpp \
    NodeAAChildA.cpp \
    NodeMac.cpp \
    NodeBBChildA.cpp \
    NodeCC.cpp \
    NodeCCChild.cpp \
    NodeCCChildChild.cpp \
#    CQTGUINetWorkTicketList.cpp \
#    QTableModelNetTicketList.cpp \
#    GUIRealTimeData.cpp \
#    TableModelRealTimeData.cpp

HEADERS  += mainwindow.h \
    TreeView.h \
    TreeModel.h \
    DevRoot.h \
    NodeBase.h \
    NodeAA.h \
    NodeBB.h \
    NodeAAChildA.h \
    NodeMac.h \
    NodeBBChildA.h \
    NodeCC.h \
    NodeCCChild.h \
    NodeCCChildChild.h \
#    CQTGUINetWorkTicketList.h \
#    QTableModelNetTicketList.h \
#    GUIRealTimeData.h \
#    TableModelRealTimeData.h

FORMS    += mainwindow.ui \
#    CQTGUINetWorkTicketList.ui \
#    GUIRealTimeData.ui

RESOURCES += \
    testTreeView.qrc


# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
