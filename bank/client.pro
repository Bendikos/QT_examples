QT       += core gui widgets sql network
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += main.cpp\
        widget.cpp \
    worker_log.cpp \
    worker_init.cpp \
    deal_user.cpp \
    user_init.cpp \
    user_close.cpp \
    user_save_money.cpp \
    user_getmoney.cpp \
    user_tranaccounts.cpp \
    user_lookmoney.cpp \
    user_changepassward.cpp \
    user_account_detail.cpp \
    bankbook.cpp \
    user_tranrecord.cpp \
    record.cpp

HEADERS  += widget.h \
    worker_log.h \
    worker_init.h \
    connect.h \
    deal_user.h \
    user_init.h \
    user_close.h \
    user_save_money.h \
    user_getmoney.h \
    user_tranaccounts.h \
    user_lookmoney.h \
    user_changepassward.h \
    user_account_detail.h \
    bankbook.h \
    user_tranrecord.h \
    record.h

FORMS    += widget.ui \
    logging.ui \
    init_worker.ui \
    deal_user.ui \
    user_init.ui \
    user_close.ui \
    user_save_money.ui \
    user_getmoney.ui \
    user_tranaccounts.ui \
    user_lookmoney.ui \
    user_changepassward.ui \
    user_account_detail.ui \
    bankbook.ui \
    user_tranrecord.ui \
    record.ui

RESOURCES += \
    res.qrc

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
