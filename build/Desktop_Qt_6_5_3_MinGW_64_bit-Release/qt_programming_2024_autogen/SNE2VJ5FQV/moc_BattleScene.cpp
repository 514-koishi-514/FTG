/****************************************************************************
** Meta object code from reading C++ file 'BattleScene.h'
**
** Created by: The Qt Meta Object Compiler version 68 (Qt 6.5.3)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../../../src/Scenes/BattleScene.h"
#include <QtGui/qtextcursor.h>
#include <QtCore/qmetatype.h>

#if __has_include(<QtCore/qtmochelpers.h>)
#include <QtCore/qtmochelpers.h>
#else
QT_BEGIN_MOC_NAMESPACE
#endif


#include <memory>

#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'BattleScene.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 68
#error "This file was generated using the moc from 6.5.3. It"
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
struct qt_meta_stringdata_CLASSBattleSceneENDCLASS_t {};
static constexpr auto qt_meta_stringdata_CLASSBattleSceneENDCLASS = QtMocHelpers::stringData(
    "BattleScene",
    "update",
    "",
    "onBulletFired",
    "Weapon*",
    "weapon",
    "firePos",
    "isRight",
    "fromCharacterName",
    "fromPlayerID"
);
#else  // !QT_MOC_HAS_STRING_DATA
struct qt_meta_stringdata_CLASSBattleSceneENDCLASS_t {
    uint offsetsAndSizes[20];
    char stringdata0[12];
    char stringdata1[7];
    char stringdata2[1];
    char stringdata3[14];
    char stringdata4[8];
    char stringdata5[7];
    char stringdata6[8];
    char stringdata7[8];
    char stringdata8[18];
    char stringdata9[13];
};
#define QT_MOC_LITERAL(ofs, len) \
    uint(sizeof(qt_meta_stringdata_CLASSBattleSceneENDCLASS_t::offsetsAndSizes) + ofs), len 
Q_CONSTINIT static const qt_meta_stringdata_CLASSBattleSceneENDCLASS_t qt_meta_stringdata_CLASSBattleSceneENDCLASS = {
    {
        QT_MOC_LITERAL(0, 11),  // "BattleScene"
        QT_MOC_LITERAL(12, 6),  // "update"
        QT_MOC_LITERAL(19, 0),  // ""
        QT_MOC_LITERAL(20, 13),  // "onBulletFired"
        QT_MOC_LITERAL(34, 7),  // "Weapon*"
        QT_MOC_LITERAL(42, 6),  // "weapon"
        QT_MOC_LITERAL(49, 7),  // "firePos"
        QT_MOC_LITERAL(57, 7),  // "isRight"
        QT_MOC_LITERAL(65, 17),  // "fromCharacterName"
        QT_MOC_LITERAL(83, 12)   // "fromPlayerID"
    },
    "BattleScene",
    "update",
    "",
    "onBulletFired",
    "Weapon*",
    "weapon",
    "firePos",
    "isRight",
    "fromCharacterName",
    "fromPlayerID"
};
#undef QT_MOC_LITERAL
#endif // !QT_MOC_HAS_STRING_DATA
} // unnamed namespace

Q_CONSTINIT static const uint qt_meta_data_CLASSBattleSceneENDCLASS[] = {

 // content:
      11,       // revision
       0,       // classname
       0,    0, // classinfo
       4,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags, initial metatype offsets
       1,    0,   38,    2, 0x09,    1 /* Protected */,
       3,    5,   39,    2, 0x08,    2 /* Private */,
       3,    4,   50,    2, 0x28,    8 /* Private | MethodCloned */,
       3,    3,   59,    2, 0x28,   13 /* Private | MethodCloned */,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void, 0x80000000 | 4, QMetaType::QPointF, QMetaType::Bool, QMetaType::QString, QMetaType::Int,    5,    6,    7,    8,    9,
    QMetaType::Void, 0x80000000 | 4, QMetaType::QPointF, QMetaType::Bool, QMetaType::QString,    5,    6,    7,    8,
    QMetaType::Void, 0x80000000 | 4, QMetaType::QPointF, QMetaType::Bool,    5,    6,    7,

       0        // eod
};

Q_CONSTINIT const QMetaObject BattleScene::staticMetaObject = { {
    QMetaObject::SuperData::link<Scene::staticMetaObject>(),
    qt_meta_stringdata_CLASSBattleSceneENDCLASS.offsetsAndSizes,
    qt_meta_data_CLASSBattleSceneENDCLASS,
    qt_static_metacall,
    nullptr,
    qt_incomplete_metaTypeArray<qt_meta_stringdata_CLASSBattleSceneENDCLASS_t,
        // Q_OBJECT / Q_GADGET
        QtPrivate::TypeAndForceComplete<BattleScene, std::true_type>,
        // method 'update'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'onBulletFired'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<Weapon *, std::false_type>,
        QtPrivate::TypeAndForceComplete<const QPointF &, std::false_type>,
        QtPrivate::TypeAndForceComplete<bool, std::false_type>,
        QtPrivate::TypeAndForceComplete<const QString &, std::false_type>,
        QtPrivate::TypeAndForceComplete<const int &, std::false_type>,
        // method 'onBulletFired'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<Weapon *, std::false_type>,
        QtPrivate::TypeAndForceComplete<const QPointF &, std::false_type>,
        QtPrivate::TypeAndForceComplete<bool, std::false_type>,
        QtPrivate::TypeAndForceComplete<const QString &, std::false_type>,
        // method 'onBulletFired'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<Weapon *, std::false_type>,
        QtPrivate::TypeAndForceComplete<const QPointF &, std::false_type>,
        QtPrivate::TypeAndForceComplete<bool, std::false_type>
    >,
    nullptr
} };

void BattleScene::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<BattleScene *>(_o);
        (void)_t;
        switch (_id) {
        case 0: _t->update(); break;
        case 1: _t->onBulletFired((*reinterpret_cast< std::add_pointer_t<Weapon*>>(_a[1])),(*reinterpret_cast< std::add_pointer_t<QPointF>>(_a[2])),(*reinterpret_cast< std::add_pointer_t<bool>>(_a[3])),(*reinterpret_cast< std::add_pointer_t<QString>>(_a[4])),(*reinterpret_cast< std::add_pointer_t<int>>(_a[5]))); break;
        case 2: _t->onBulletFired((*reinterpret_cast< std::add_pointer_t<Weapon*>>(_a[1])),(*reinterpret_cast< std::add_pointer_t<QPointF>>(_a[2])),(*reinterpret_cast< std::add_pointer_t<bool>>(_a[3])),(*reinterpret_cast< std::add_pointer_t<QString>>(_a[4]))); break;
        case 3: _t->onBulletFired((*reinterpret_cast< std::add_pointer_t<Weapon*>>(_a[1])),(*reinterpret_cast< std::add_pointer_t<QPointF>>(_a[2])),(*reinterpret_cast< std::add_pointer_t<bool>>(_a[3]))); break;
        default: ;
        }
    }
}

const QMetaObject *BattleScene::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *BattleScene::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_CLASSBattleSceneENDCLASS.stringdata0))
        return static_cast<void*>(this);
    return Scene::qt_metacast(_clname);
}

int BattleScene::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = Scene::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 4)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 4;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 4)
            *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType();
        _id -= 4;
    }
    return _id;
}
QT_WARNING_POP
