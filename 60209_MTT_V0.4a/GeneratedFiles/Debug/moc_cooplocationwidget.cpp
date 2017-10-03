/****************************************************************************
** Meta object code from reading C++ file 'cooplocationwidget.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.2.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../GUI/cooplocationwidget.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'cooplocationwidget.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.2.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_CoopLocationWidget_t {
    QByteArrayData data[15];
    char stringdata[311];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    offsetof(qt_meta_stringdata_CoopLocationWidget_t, stringdata) + ofs \
        - idx * sizeof(QByteArrayData) \
    )
static const qt_meta_stringdata_CoopLocationWidget_t qt_meta_stringdata_CoopLocationWidget = {
    {
QT_MOC_LITERAL(0, 0, 18),
QT_MOC_LITERAL(1, 19, 10),
QT_MOC_LITERAL(2, 30, 0),
QT_MOC_LITERAL(3, 31, 7),
QT_MOC_LITERAL(4, 39, 11),
QT_MOC_LITERAL(5, 51, 12),
QT_MOC_LITERAL(6, 64, 28),
QT_MOC_LITERAL(7, 93, 28),
QT_MOC_LITERAL(8, 122, 31),
QT_MOC_LITERAL(9, 154, 31),
QT_MOC_LITERAL(10, 186, 27),
QT_MOC_LITERAL(11, 214, 27),
QT_MOC_LITERAL(12, 242, 20),
QT_MOC_LITERAL(13, 263, 21),
QT_MOC_LITERAL(14, 285, 24)
    },
    "CoopLocationWidget\0updateInfo\0\0_source\0"
    "updateFrame\0onUpdateInfo\0"
    "on_loadVideoButton_1_clicked\0"
    "on_loadVideoButton_2_clicked\0"
    "on_loadDetectorButton_1_clicked\0"
    "on_loadDetectorButton_2_clicked\0"
    "on_loadPoseButton_1_clicked\0"
    "on_loadPoseButton_2_clicked\0"
    "on_runButton_clicked\0on_stopButton_clicked\0"
    "on_loadMapButton_clicked\0"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_CoopLocationWidget[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
      12,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       1,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    1,   74,    2, 0x06,

 // slots: name, argc, parameters, tag, flags
       4,    0,   77,    2, 0x08,
       5,    1,   78,    2, 0x08,
       6,    0,   81,    2, 0x08,
       7,    0,   82,    2, 0x08,
       8,    0,   83,    2, 0x08,
       9,    0,   84,    2, 0x08,
      10,    0,   85,    2, 0x08,
      11,    0,   86,    2, 0x08,
      12,    0,   87,    2, 0x08,
      13,    0,   88,    2, 0x08,
      14,    0,   89,    2, 0x08,

 // signals: parameters
    QMetaType::Void, QMetaType::QString,    3,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void, QMetaType::QString,    3,
    QMetaType::Void,
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

void CoopLocationWidget::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        CoopLocationWidget *_t = static_cast<CoopLocationWidget *>(_o);
        switch (_id) {
        case 0: _t->updateInfo((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 1: _t->updateFrame(); break;
        case 2: _t->onUpdateInfo((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 3: _t->on_loadVideoButton_1_clicked(); break;
        case 4: _t->on_loadVideoButton_2_clicked(); break;
        case 5: _t->on_loadDetectorButton_1_clicked(); break;
        case 6: _t->on_loadDetectorButton_2_clicked(); break;
        case 7: _t->on_loadPoseButton_1_clicked(); break;
        case 8: _t->on_loadPoseButton_2_clicked(); break;
        case 9: _t->on_runButton_clicked(); break;
        case 10: _t->on_stopButton_clicked(); break;
        case 11: _t->on_loadMapButton_clicked(); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        void **func = reinterpret_cast<void **>(_a[1]);
        {
            typedef void (CoopLocationWidget::*_t)(QString );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&CoopLocationWidget::updateInfo)) {
                *result = 0;
            }
        }
    }
}

const QMetaObject CoopLocationWidget::staticMetaObject = {
    { &QWidget::staticMetaObject, qt_meta_stringdata_CoopLocationWidget.data,
      qt_meta_data_CoopLocationWidget,  qt_static_metacall, 0, 0}
};


const QMetaObject *CoopLocationWidget::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *CoopLocationWidget::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_CoopLocationWidget.stringdata))
        return static_cast<void*>(const_cast< CoopLocationWidget*>(this));
    return QWidget::qt_metacast(_clname);
}

int CoopLocationWidget::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 12)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 12;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 12)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 12;
    }
    return _id;
}

// SIGNAL 0
void CoopLocationWidget::updateInfo(QString _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}
QT_END_MOC_NAMESPACE
