/****************************************************************************
** Meta object code from reading C++ file 'file-reader.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.12.8)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../Qt-Files/SampleProject/file-reader.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'file-reader.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.12.8. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_FileReader_t {
    QByteArrayData data[13];
    char stringdata0[117];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_FileReader_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_FileReader_t qt_meta_stringdata_FileReader = {
    {
QT_MOC_LITERAL(0, 0, 10), // "FileReader"
QT_MOC_LITERAL(1, 11, 14), // "SigTempChanged"
QT_MOC_LITERAL(2, 26, 0), // ""
QT_MOC_LITERAL(3, 27, 4), // "temp"
QT_MOC_LITERAL(4, 32, 13), // "SigHumChanged"
QT_MOC_LITERAL(5, 46, 3), // "hum"
QT_MOC_LITERAL(6, 50, 12), // "SigIrChanged"
QT_MOC_LITERAL(7, 63, 2), // "ir"
QT_MOC_LITERAL(8, 66, 14), // "SigFullChanged"
QT_MOC_LITERAL(9, 81, 4), // "full"
QT_MOC_LITERAL(10, 86, 13), // "SigVisChanged"
QT_MOC_LITERAL(11, 100, 3), // "vis"
QT_MOC_LITERAL(12, 104, 12) // "timerHandler"

    },
    "FileReader\0SigTempChanged\0\0temp\0"
    "SigHumChanged\0hum\0SigIrChanged\0ir\0"
    "SigFullChanged\0full\0SigVisChanged\0vis\0"
    "timerHandler"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_FileReader[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
       6,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       5,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    1,   44,    2, 0x06 /* Public */,
       4,    1,   47,    2, 0x06 /* Public */,
       6,    1,   50,    2, 0x06 /* Public */,
       8,    1,   53,    2, 0x06 /* Public */,
      10,    1,   56,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
      12,    0,   59,    2, 0x08 /* Private */,

 // signals: parameters
    QMetaType::Void, QMetaType::Float,    3,
    QMetaType::Void, QMetaType::Float,    5,
    QMetaType::Void, QMetaType::Int,    7,
    QMetaType::Void, QMetaType::Int,    9,
    QMetaType::Void, QMetaType::Int,   11,

 // slots: parameters
    QMetaType::Void,

       0        // eod
};

void FileReader::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<FileReader *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->SigTempChanged((*reinterpret_cast< float(*)>(_a[1]))); break;
        case 1: _t->SigHumChanged((*reinterpret_cast< float(*)>(_a[1]))); break;
        case 2: _t->SigIrChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 3: _t->SigFullChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 4: _t->SigVisChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 5: _t->timerHandler(); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (FileReader::*)(float );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&FileReader::SigTempChanged)) {
                *result = 0;
                return;
            }
        }
        {
            using _t = void (FileReader::*)(float );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&FileReader::SigHumChanged)) {
                *result = 1;
                return;
            }
        }
        {
            using _t = void (FileReader::*)(int );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&FileReader::SigIrChanged)) {
                *result = 2;
                return;
            }
        }
        {
            using _t = void (FileReader::*)(int );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&FileReader::SigFullChanged)) {
                *result = 3;
                return;
            }
        }
        {
            using _t = void (FileReader::*)(int );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&FileReader::SigVisChanged)) {
                *result = 4;
                return;
            }
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject FileReader::staticMetaObject = { {
    &QObject::staticMetaObject,
    qt_meta_stringdata_FileReader.data,
    qt_meta_data_FileReader,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *FileReader::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *FileReader::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_FileReader.stringdata0))
        return static_cast<void*>(this);
    return QObject::qt_metacast(_clname);
}

int FileReader::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
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
void FileReader::SigTempChanged(float _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void FileReader::SigHumChanged(float _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}

// SIGNAL 2
void FileReader::SigIrChanged(int _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 2, _a);
}

// SIGNAL 3
void FileReader::SigFullChanged(int _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 3, _a);
}

// SIGNAL 4
void FileReader::SigVisChanged(int _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 4, _a);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
