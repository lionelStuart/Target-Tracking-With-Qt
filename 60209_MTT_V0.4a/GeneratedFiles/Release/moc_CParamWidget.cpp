/****************************************************************************
** Meta object code from reading C++ file 'CParamWidget.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.2.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../GUI/CParamWidget.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'CParamWidget.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.2.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_CParamWidget_t {
    QByteArrayData data[11];
    char stringdata[255];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    offsetof(qt_meta_stringdata_CParamWidget_t, stringdata) + ofs \
        - idx * sizeof(QByteArrayData) \
    )
static const qt_meta_stringdata_CParamWidget_t qt_meta_stringdata_CParamWidget = {
    {
QT_MOC_LITERAL(0, 0, 12),
QT_MOC_LITERAL(1, 13, 9),
QT_MOC_LITERAL(2, 23, 0),
QT_MOC_LITERAL(3, 24, 22),
QT_MOC_LITERAL(4, 47, 24),
QT_MOC_LITERAL(5, 72, 34),
QT_MOC_LITERAL(6, 107, 26),
QT_MOC_LITERAL(7, 134, 34),
QT_MOC_LITERAL(8, 169, 24),
QT_MOC_LITERAL(9, 194, 27),
QT_MOC_LITERAL(10, 222, 31)
    },
    "CParamWidget\0sendParam\0\0on_paramButton_clicked\0"
    "on_checkLBP_stateChanged\0"
    "on_ParticlesNumSlider_valueChanged\0"
    "on_checkPHash_stateChanged\0"
    "on_searchRadiusSlider_valueChanged\0"
    "on_checkHOG_stateChanged\0"
    "on_checkFixWnd_stateChanged\0"
    "on_checkMultiScale_stateChanged\0"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_CParamWidget[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       9,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       1,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    0,   59,    2, 0x06,

 // slots: name, argc, parameters, tag, flags
       3,    0,   60,    2, 0x08,
       4,    0,   61,    2, 0x08,
       5,    0,   62,    2, 0x08,
       6,    0,   63,    2, 0x08,
       7,    0,   64,    2, 0x08,
       8,    0,   65,    2, 0x08,
       9,    0,   66,    2, 0x08,
      10,    0,   67,    2, 0x08,

 // signals: parameters
    QMetaType::Void,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

void CParamWidget::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        CParamWidget *_t = static_cast<CParamWidget *>(_o);
        switch (_id) {
        case 0: _t->sendParam(); break;
        case 1: _t->on_paramButton_clicked(); break;
        case 2: _t->on_checkLBP_stateChanged(); break;
        case 3: _t->on_ParticlesNumSlider_valueChanged(); break;
        case 4: _t->on_checkPHash_stateChanged(); break;
        case 5: _t->on_searchRadiusSlider_valueChanged(); break;
        case 6: _t->on_checkHOG_stateChanged(); break;
        case 7: _t->on_checkFixWnd_stateChanged(); break;
        case 8: _t->on_checkMultiScale_stateChanged(); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        void **func = reinterpret_cast<void **>(_a[1]);
        {
            typedef void (CParamWidget::*_t)();
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&CParamWidget::sendParam)) {
                *result = 0;
            }
        }
    }
    Q_UNUSED(_a);
}

const QMetaObject CParamWidget::staticMetaObject = {
    { &QWidget::staticMetaObject, qt_meta_stringdata_CParamWidget.data,
      qt_meta_data_CParamWidget,  qt_static_metacall, 0, 0}
};


const QMetaObject *CParamWidget::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *CParamWidget::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_CParamWidget.stringdata))
        return static_cast<void*>(const_cast< CParamWidget*>(this));
    return QWidget::qt_metacast(_clname);
}

int CParamWidget::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 9)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 9;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 9)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 9;
    }
    return _id;
}

// SIGNAL 0
void CParamWidget::sendParam()
{
    QMetaObject::activate(this, &staticMetaObject, 0, 0);
}
QT_END_MOC_NAMESPACE
