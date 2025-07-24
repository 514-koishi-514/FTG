/****************************************************************************
** Meta object code from reading C++ file 'Character.h'
**
** Created by: The Qt Meta Object Compiler version 68 (Qt 6.5.3)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../../../src/Items/Characters/Character.h"
#include <QtCore/qmetatype.h>

#if __has_include(<QtCore/qtmochelpers.h>)
#include <QtCore/qtmochelpers.h>
#else
QT_BEGIN_MOC_NAMESPACE
#endif


#include <memory>

#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'Character.h' doesn't include <QObject>."
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
struct qt_meta_stringdata_CLASSCharacterENDCLASS_t {};
static constexpr auto qt_meta_stringdata_CLASSCharacterENDCLASS = QtMocHelpers::stringData(
    "Character",
    "fireBullet",
    "",
    "Weapon*",
    "weapon",
    "firePos",
    "isRight",
    "fromCharacterName",
    "playerID",
    "dealMeleeDamage",
    "damage",
    "weaponID",
    "updateAnimationFrame",
    "takeMeleeDamage",
    "attackWeaponID",
    "onHealTimerTimeout"
);
#else  // !QT_MOC_HAS_STRING_DATA
struct qt_meta_stringdata_CLASSCharacterENDCLASS_t {
    uint offsetsAndSizes[32];
    char stringdata0[10];
    char stringdata1[11];
    char stringdata2[1];
    char stringdata3[8];
    char stringdata4[7];
    char stringdata5[8];
    char stringdata6[8];
    char stringdata7[18];
    char stringdata8[9];
    char stringdata9[16];
    char stringdata10[7];
    char stringdata11[9];
    char stringdata12[21];
    char stringdata13[16];
    char stringdata14[15];
    char stringdata15[19];
};
#define QT_MOC_LITERAL(ofs, len) \
    uint(sizeof(qt_meta_stringdata_CLASSCharacterENDCLASS_t::offsetsAndSizes) + ofs), len 
Q_CONSTINIT static const qt_meta_stringdata_CLASSCharacterENDCLASS_t qt_meta_stringdata_CLASSCharacterENDCLASS = {
    {
        QT_MOC_LITERAL(0, 9),  // "Character"
        QT_MOC_LITERAL(10, 10),  // "fireBullet"
        QT_MOC_LITERAL(21, 0),  // ""
        QT_MOC_LITERAL(22, 7),  // "Weapon*"
        QT_MOC_LITERAL(30, 6),  // "weapon"
        QT_MOC_LITERAL(37, 7),  // "firePos"
        QT_MOC_LITERAL(45, 7),  // "isRight"
        QT_MOC_LITERAL(53, 17),  // "fromCharacterName"
        QT_MOC_LITERAL(71, 8),  // "playerID"
        QT_MOC_LITERAL(80, 15),  // "dealMeleeDamage"
        QT_MOC_LITERAL(96, 6),  // "damage"
        QT_MOC_LITERAL(103, 8),  // "weaponID"
        QT_MOC_LITERAL(112, 20),  // "updateAnimationFrame"
        QT_MOC_LITERAL(133, 15),  // "takeMeleeDamage"
        QT_MOC_LITERAL(149, 14),  // "attackWeaponID"
        QT_MOC_LITERAL(164, 18)   // "onHealTimerTimeout"
    },
    "Character",
    "fireBullet",
    "",
    "Weapon*",
    "weapon",
    "firePos",
    "isRight",
    "fromCharacterName",
    "playerID",
    "dealMeleeDamage",
    "damage",
    "weaponID",
    "updateAnimationFrame",
    "takeMeleeDamage",
    "attackWeaponID",
    "onHealTimerTimeout"
};
#undef QT_MOC_LITERAL
#endif // !QT_MOC_HAS_STRING_DATA
} // unnamed namespace

Q_CONSTINIT static const uint qt_meta_data_CLASSCharacterENDCLASS[] = {

 // content:
      11,       // revision
       0,       // classname
       0,    0, // classinfo
       7,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       4,       // signalCount

 // signals: name, argc, parameters, tag, flags, initial metatype offsets
       1,    5,   56,    2, 0x06,    1 /* Public */,
       1,    4,   67,    2, 0x26,    7 /* Public | MethodCloned */,
       1,    3,   76,    2, 0x26,   12 /* Public | MethodCloned */,
       9,    2,   83,    2, 0x06,   16 /* Public */,

 // slots: name, argc, parameters, tag, flags, initial metatype offsets
      12,    0,   88,    2, 0x09,   19 /* Protected */,
      13,    2,   89,    2, 0x0a,   20 /* Public */,
      15,    0,   94,    2, 0x0a,   23 /* Public */,

 // signals: parameters
    QMetaType::Void, 0x80000000 | 3, QMetaType::QPointF, QMetaType::Bool, QMetaType::QString, QMetaType::Int,    4,    5,    6,    7,    8,
    QMetaType::Void, 0x80000000 | 3, QMetaType::QPointF, QMetaType::Bool, QMetaType::QString,    4,    5,    6,    7,
    QMetaType::Void, 0x80000000 | 3, QMetaType::QPointF, QMetaType::Bool,    4,    5,    6,
    QMetaType::Void, QMetaType::Int, QMetaType::Int,   10,   11,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void, QMetaType::Int, QMetaType::Int,   10,   14,
    QMetaType::Void,

       0        // eod
};

Q_CONSTINIT const QMetaObject Character::staticMetaObject = { {
    QMetaObject::SuperData::link<Item::staticMetaObject>(),
    qt_meta_stringdata_CLASSCharacterENDCLASS.offsetsAndSizes,
    qt_meta_data_CLASSCharacterENDCLASS,
    qt_static_metacall,
    nullptr,
    qt_incomplete_metaTypeArray<qt_meta_stringdata_CLASSCharacterENDCLASS_t,
        // Q_OBJECT / Q_GADGET
        QtPrivate::TypeAndForceComplete<Character, std::true_type>,
        // method 'fireBullet'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<Weapon *, std::false_type>,
        QtPrivate::TypeAndForceComplete<const QPointF &, std::false_type>,
        QtPrivate::TypeAndForceComplete<bool, std::false_type>,
        QtPrivate::TypeAndForceComplete<const QString &, std::false_type>,
        QtPrivate::TypeAndForceComplete<const int &, std::false_type>,
        // method 'fireBullet'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<Weapon *, std::false_type>,
        QtPrivate::TypeAndForceComplete<const QPointF &, std::false_type>,
        QtPrivate::TypeAndForceComplete<bool, std::false_type>,
        QtPrivate::TypeAndForceComplete<const QString &, std::false_type>,
        // method 'fireBullet'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<Weapon *, std::false_type>,
        QtPrivate::TypeAndForceComplete<const QPointF &, std::false_type>,
        QtPrivate::TypeAndForceComplete<bool, std::false_type>,
        // method 'dealMeleeDamage'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<int, std::false_type>,
        QtPrivate::TypeAndForceComplete<int, std::false_type>,
        // method 'updateAnimationFrame'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'takeMeleeDamage'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<int, std::false_type>,
        QtPrivate::TypeAndForceComplete<int, std::false_type>,
        // method 'onHealTimerTimeout'
        QtPrivate::TypeAndForceComplete<void, std::false_type>
    >,
    nullptr
} };

void Character::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<Character *>(_o);
        (void)_t;
        switch (_id) {
        case 0: _t->fireBullet((*reinterpret_cast< std::add_pointer_t<Weapon*>>(_a[1])),(*reinterpret_cast< std::add_pointer_t<QPointF>>(_a[2])),(*reinterpret_cast< std::add_pointer_t<bool>>(_a[3])),(*reinterpret_cast< std::add_pointer_t<QString>>(_a[4])),(*reinterpret_cast< std::add_pointer_t<int>>(_a[5]))); break;
        case 1: _t->fireBullet((*reinterpret_cast< std::add_pointer_t<Weapon*>>(_a[1])),(*reinterpret_cast< std::add_pointer_t<QPointF>>(_a[2])),(*reinterpret_cast< std::add_pointer_t<bool>>(_a[3])),(*reinterpret_cast< std::add_pointer_t<QString>>(_a[4]))); break;
        case 2: _t->fireBullet((*reinterpret_cast< std::add_pointer_t<Weapon*>>(_a[1])),(*reinterpret_cast< std::add_pointer_t<QPointF>>(_a[2])),(*reinterpret_cast< std::add_pointer_t<bool>>(_a[3]))); break;
        case 3: _t->dealMeleeDamage((*reinterpret_cast< std::add_pointer_t<int>>(_a[1])),(*reinterpret_cast< std::add_pointer_t<int>>(_a[2]))); break;
        case 4: _t->updateAnimationFrame(); break;
        case 5: _t->takeMeleeDamage((*reinterpret_cast< std::add_pointer_t<int>>(_a[1])),(*reinterpret_cast< std::add_pointer_t<int>>(_a[2]))); break;
        case 6: _t->onHealTimerTimeout(); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (Character::*)(Weapon * , const QPointF & , bool , const QString & , const int & );
            if (_t _q_method = &Character::fireBullet; *reinterpret_cast<_t *>(_a[1]) == _q_method) {
                *result = 0;
                return;
            }
        }
        {
            using _t = void (Character::*)(int , int );
            if (_t _q_method = &Character::dealMeleeDamage; *reinterpret_cast<_t *>(_a[1]) == _q_method) {
                *result = 3;
                return;
            }
        }
    }
}

const QMetaObject *Character::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *Character::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_CLASSCharacterENDCLASS.stringdata0))
        return static_cast<void*>(this);
    return Item::qt_metacast(_clname);
}

int Character::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = Item::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 7)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 7;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 7)
            *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType();
        _id -= 7;
    }
    return _id;
}

// SIGNAL 0
void Character::fireBullet(Weapon * _t1, const QPointF & _t2, bool _t3, const QString & _t4, const int & _t5)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))), const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t2))), const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t3))), const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t4))), const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t5))) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 3
void Character::dealMeleeDamage(int _t1, int _t2)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))), const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t2))) };
    QMetaObject::activate(this, &staticMetaObject, 3, _a);
}
QT_WARNING_POP
