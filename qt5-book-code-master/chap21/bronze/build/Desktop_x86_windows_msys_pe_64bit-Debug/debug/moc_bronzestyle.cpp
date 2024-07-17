/****************************************************************************
** Meta object code from reading C++ file 'bronzestyle.h'
**
** Created by: The Qt Meta Object Compiler version 68 (Qt 6.7.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../../bronzestyle.h"
#include <QtCore/qmetatype.h>

#include <QtCore/qtmochelpers.h>

#include <memory>


#include <QtCore/qxptype_traits.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'bronzestyle.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 68
#error "This file was generated using the moc from 6.7.2. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

#ifndef Q_CONSTINIT
#define Q_CONSTINIT
#endif

QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
QT_WARNING_DISABLE_GCC("-Wuseless-cast")
namespace {

#ifdef QT_MOC_HAS_STRINGDATA
struct qt_meta_stringdata_CLASSBronzeStyleENDCLASS_t {};
constexpr auto qt_meta_stringdata_CLASSBronzeStyleENDCLASS = QtMocHelpers::stringData(
    "BronzeStyle",
    "standardIconImplementation",
    "",
    "StandardPixmap",
    "which",
    "const QStyleOption*",
    "option",
    "const QWidget*",
    "widget"
);
#else  // !QT_MOC_HAS_STRINGDATA
#error "qtmochelpers.h not found or too old."
#endif // !QT_MOC_HAS_STRINGDATA
} // unnamed namespace

Q_CONSTINIT static const uint qt_meta_data_CLASSBronzeStyleENDCLASS[] = {

 // content:
      12,       // revision
       0,       // classname
       0,    0, // classinfo
       2,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags, initial metatype offsets
       1,    3,   26,    2, 0x10a,    1 /* Public | MethodIsConst  */,
       1,    2,   33,    2, 0x12a,    5 /* Public | MethodCloned | MethodIsConst  */,

 // slots: parameters
    QMetaType::QIcon, 0x80000000 | 3, 0x80000000 | 5, 0x80000000 | 7,    4,    6,    8,
    QMetaType::QIcon, 0x80000000 | 3, 0x80000000 | 5,    4,    6,

       0        // eod
};

Q_CONSTINIT const QMetaObject BronzeStyle::staticMetaObject = { {
    QMetaObject::SuperData::link<QProxyStyle::staticMetaObject>(),
    qt_meta_stringdata_CLASSBronzeStyleENDCLASS.offsetsAndSizes,
    qt_meta_data_CLASSBronzeStyleENDCLASS,
    qt_static_metacall,
    nullptr,
    qt_incomplete_metaTypeArray<qt_meta_stringdata_CLASSBronzeStyleENDCLASS_t,
        // Q_OBJECT / Q_GADGET
        QtPrivate::TypeAndForceComplete<BronzeStyle, std::true_type>,
        // method 'standardIconImplementation'
        QtPrivate::TypeAndForceComplete<QIcon, std::false_type>,
        QtPrivate::TypeAndForceComplete<StandardPixmap, std::false_type>,
        QtPrivate::TypeAndForceComplete<const QStyleOption *, std::false_type>,
        QtPrivate::TypeAndForceComplete<const QWidget *, std::false_type>,
        // method 'standardIconImplementation'
        QtPrivate::TypeAndForceComplete<QIcon, std::false_type>,
        QtPrivate::TypeAndForceComplete<StandardPixmap, std::false_type>,
        QtPrivate::TypeAndForceComplete<const QStyleOption *, std::false_type>
    >,
    nullptr
} };

void BronzeStyle::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<BronzeStyle *>(_o);
        (void)_t;
        switch (_id) {
        case 0: { QIcon _r = _t->standardIconImplementation((*reinterpret_cast< std::add_pointer_t<StandardPixmap>>(_a[1])),(*reinterpret_cast< std::add_pointer_t<const QStyleOption*>>(_a[2])),(*reinterpret_cast< std::add_pointer_t<const QWidget*>>(_a[3])));
            if (_a[0]) *reinterpret_cast< QIcon*>(_a[0]) = std::move(_r); }  break;
        case 1: { QIcon _r = _t->standardIconImplementation((*reinterpret_cast< std::add_pointer_t<StandardPixmap>>(_a[1])),(*reinterpret_cast< std::add_pointer_t<const QStyleOption*>>(_a[2])));
            if (_a[0]) *reinterpret_cast< QIcon*>(_a[0]) = std::move(_r); }  break;
        default: ;
        }
    }
}

const QMetaObject *BronzeStyle::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *BronzeStyle::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_CLASSBronzeStyleENDCLASS.stringdata0))
        return static_cast<void*>(this);
    return QProxyStyle::qt_metacast(_clname);
}

int BronzeStyle::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QProxyStyle::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 2)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 2;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 2)
            *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType();
        _id -= 2;
    }
    return _id;
}
QT_WARNING_POP
