QT  += core gui sql widgets multimedia

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0
SOURCES += main.cpp\
        frmmain.cpp \
    mygauge1.cpp \
    mygauge2.cpp \
    mygauge3.cpp \
    mygauge4.cpp \
    mygauge5.cpp \
    mygauge6.cpp \
    myprogressbar.cpp \
    mygauge7.cpp \
    mybattery.cpp \
    mycoolbar.cpp \
    mylcdnumber.cpp \
    myindicator.cpp \
    myvolume.cpp \
    mychart1.cpp \
    myflashlist.cpp \
    mybuttonboard.cpp \
    mysliderbutton.cpp \
    myphotoview.cpp \
    myaroundcircle.cpp \
    myprogressbar1.cpp \
    mynewled.cpp \
    mywave.cpp \
    mywave1.cpp \
    mywave2.cpp

HEADERS  += frmmain.h \
    mygauge1.h \
    mygauge2.h \
    mygauge3.h \
    mygauge4.h \
    mygauge5.h \
    mygauge6.h \
    myprogressbar.h \
    mygauge7.h \
    mybattery.h \
    mycoolbar.h \
    mylcdnumber.h \
    myindicator.h \
    myvolume.h \
    mychart1.h \
    myflashlist.h \
    mybuttonboard.h \
    mysliderbutton.h \
    myphotoview.h \
    myaroundcircle.h \
    myprogressbar1.h \
    mynewled.h \
    mywave.h \
    mywave1.h \
    mywave2.h

FORMS    += frmmain.ui

RESOURCES += \
    myResource.qrc

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
