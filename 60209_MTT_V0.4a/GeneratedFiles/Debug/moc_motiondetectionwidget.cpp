/****************************************************************************
** Meta object code from reading C++ file 'motiondetectionwidget.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.2.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../GUI/motiondetectionwidget.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'motiondetectionwidget.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.2.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_MotionDetectionWidget_t {
    QByteArrayData data[9];
    char stringdata[123];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    offsetof(qt_meta_stringdata_MotionDetectionWidget_t, stringdata) + ofs \
        - idx * sizeof(QByteArrayData) \
    )
static const qt_meta_stringdata_MotionDetectionWidget_t qt_meta_stringdata_MotionDetectionWidget = {
    {
QT_MOC_LITERAL(0, 0, 21),
QT_MOC_LITERAL(1, 22, 10),
QT_MOC_LITERAL(2, 33, 0),
QT_MOC_LITERAL(3, 34, 7),
QT_MOC_LITERAL(4, 42, 10),
QT_MOC_LITERAL(5, 53, 21),
QT_MOC_LITERAL(6, 75, 21),
QT_MOC_LITERAL(7, 97, 11),
QT_MOC_LITERAL(8, 109, 12)
    },
    "MotionDetectionWidget\0updateInfo\0\0"
    "_source\0onOpenFile\0on_playButton_clicked\0"
    "on_stopButton_clicked\0updateFrame\0"
    "onUpdateInfo\0"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_MotionDetectionWidget[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       6,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       1,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    1,   44,    2, 0x06,

 // slots: name, argc, parameters, tag, flags
       4,    0,   47,    2, 0x0a,
       5,    0,   48,    2, 0x08,
       6,    0,   49,    2, 0x08,
       7,    0,   50,    2, 0x08,
       8,    1,   51,    2, 0x08,

 // signals: parameters
    QMetaType::Void, QMetaType::QString,    3,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::QString,    3,

       0        // eod
};

void MotionDetectionWidget::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        MotionDetectionWidget *_t = static_cast<MotionDetectionWidget *>(_o);
        switch (_id) {
        case 0: _t->updateInfo((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 1: _t->onOpenFile(); break;
        case 2: _t->on_playButton_clicked(); break;
        case 3: _t->on_stopButton_clicked(); break;
        case 4: _t->updateFrame(); break;
        case 5: _t->onUpdateInfo((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        void **func = reinterpret_cast<void **>(_a[1]);
        {
            typedef void (MotionDetectionWidget::*_t)(QString );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&MotionDetectionWidget::updateInfo)) {
                *result = 0;
            }
        }
    }
}

const QMetaObject MotionDetectionWidget::staticMetaObject = {
    { &QWidget::staticMetaObject, qt_meta_stringdata_MotionDetectionWidget.data,
      qt_meta_data_MotionDetectionWidget,  qt_static_metacall, 0, 0}
};


const QMetaObject *MotionDetectionWidget::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *MotionDetectionWidget::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_MotionDetectionWidget.stringdata))
        return static_cast<void*>(const_cast< MotionDetectionWidget*>(this));
    return QWidget::qt_metacast(_clname);
}

int MotionDetectionWidget::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 6)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 6;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 6)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 6;
    }
    return _id;
}

// SIGNAL 0
void MotionDetectionWidget::updateInfo(QString _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}
QT_END_MOC_NAMESPACE
