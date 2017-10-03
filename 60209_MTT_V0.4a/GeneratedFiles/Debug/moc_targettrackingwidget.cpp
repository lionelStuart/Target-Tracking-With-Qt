/****************************************************************************
** Meta object code from reading C++ file 'targettrackingwidget.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.2.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../GUI/targettrackingwidget.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'targettrackingwidget.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.2.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_TargetTrackingWidget_t {
    QByteArrayData data[13];
    char stringdata[193];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    offsetof(qt_meta_stringdata_TargetTrackingWidget_t, stringdata) + ofs \
        - idx * sizeof(QByteArrayData) \
    )
static const qt_meta_stringdata_TargetTrackingWidget_t qt_meta_stringdata_TargetTrackingWidget = {
    {
QT_MOC_LITERAL(0, 0, 20),
QT_MOC_LITERAL(1, 21, 10),
QT_MOC_LITERAL(2, 32, 0),
QT_MOC_LITERAL(3, 33, 7),
QT_MOC_LITERAL(4, 41, 19),
QT_MOC_LITERAL(5, 61, 10),
QT_MOC_LITERAL(6, 72, 21),
QT_MOC_LITERAL(7, 94, 21),
QT_MOC_LITERAL(8, 116, 21),
QT_MOC_LITERAL(9, 138, 12),
QT_MOC_LITERAL(10, 151, 11),
QT_MOC_LITERAL(11, 163, 12),
QT_MOC_LITERAL(12, 176, 15)
    },
    "TargetTrackingWidget\0updateInfo\0\0"
    "_source\0receiveTrackingType\0onOpenFile\0"
    "on_playButton_clicked\0on_stopButton_clicked\0"
    "on_drawButton_clicked\0receiveRects\0"
    "updateFrame\0onUpdateInfo\0initParamWidget\0"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_TargetTrackingWidget[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
      10,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       2,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    1,   64,    2, 0x06,
       4,    1,   67,    2, 0x06,

 // slots: name, argc, parameters, tag, flags
       5,    0,   70,    2, 0x0a,
       6,    0,   71,    2, 0x08,
       7,    0,   72,    2, 0x08,
       8,    0,   73,    2, 0x08,
       9,    0,   74,    2, 0x08,
      10,    0,   75,    2, 0x08,
      11,    1,   76,    2, 0x08,
      12,    1,   79,    2, 0x08,

 // signals: parameters
    QMetaType::Void, QMetaType::QString,    3,
    QMetaType::Void, QMetaType::QString,    3,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::QString,    3,
    QMetaType::Void, QMetaType::QString,    3,

       0        // eod
};

void TargetTrackingWidget::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        TargetTrackingWidget *_t = static_cast<TargetTrackingWidget *>(_o);
        switch (_id) {
        case 0: _t->updateInfo((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 1: _t->receiveTrackingType((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 2: _t->onOpenFile(); break;
        case 3: _t->on_playButton_clicked(); break;
        case 4: _t->on_stopButton_clicked(); break;
        case 5: _t->on_drawButton_clicked(); break;
        case 6: _t->receiveRects(); break;
        case 7: _t->updateFrame(); break;
        case 8: _t->onUpdateInfo((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 9: _t->initParamWidget((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        void **func = reinterpret_cast<void **>(_a[1]);
        {
            typedef void (TargetTrackingWidget::*_t)(QString );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&TargetTrackingWidget::updateInfo)) {
                *result = 0;
            }
        }
        {
            typedef void (TargetTrackingWidget::*_t)(QString );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&TargetTrackingWidget::receiveTrackingType)) {
                *result = 1;
            }
        }
    }
}

const QMetaObject TargetTrackingWidget::staticMetaObject = {
    { &QWidget::staticMetaObject, qt_meta_stringdata_TargetTrackingWidget.data,
      qt_meta_data_TargetTrackingWidget,  qt_static_metacall, 0, 0}
};


const QMetaObject *TargetTrackingWidget::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *TargetTrackingWidget::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_TargetTrackingWidget.stringdata))
        return static_cast<void*>(const_cast< TargetTrackingWidget*>(this));
    return QWidget::qt_metacast(_clname);
}

int TargetTrackingWidget::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 10)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 10;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 10)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 10;
    }
    return _id;
}

// SIGNAL 0
void TargetTrackingWidget::updateInfo(QString _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void TargetTrackingWidget::receiveTrackingType(QString _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}
QT_END_MOC_NAMESPACE
