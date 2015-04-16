/****************************************************************************
** Meta object code from reading C++ file 'CalcStarApp.h'
**
** Created: Wed Mar 19 21:19:55 2014
**      by: The Qt Meta Object Compiler version 63 (Qt 4.8.4)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../CalcStarApp.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'CalcStarApp.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 63
#error "This file was generated using the moc from 4.8.4. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_CalcStarApp[] = {

 // content:
       6,       // revision
       0,       // classname
       0,    0, // classinfo
       8,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: signature, parameters, type, tag, flags
      13,   12,   12,   12, 0x0a,
      26,   12,   12,   12, 0x0a,
      39,   12,   12,   12, 0x0a,
      51,   12,   12,   12, 0x0a,
      64,   12,   12,   12, 0x0a,
      80,   12,   12,   12, 0x0a,
     107,   12,   12,   12, 0x0a,
     126,   12,   12,   12, 0x0a,

       0        // eod
};

static const char qt_meta_stringdata_CalcStarApp[] = {
    "CalcStarApp\0\0OnFileExit()\0OnTokenize()\0"
    "OnCompile()\0OnEvaluate()\0OnRunAllTests()\0"
    "OnCmdSaveVariables_Click()\0"
    "OnResetVariables()\0OnUpdateVariables()\0"
};

void CalcStarApp::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        CalcStarApp *_t = static_cast<CalcStarApp *>(_o);
        switch (_id) {
        case 0: _t->OnFileExit(); break;
        case 1: _t->OnTokenize(); break;
        case 2: _t->OnCompile(); break;
        case 3: _t->OnEvaluate(); break;
        case 4: _t->OnRunAllTests(); break;
        case 5: _t->OnCmdSaveVariables_Click(); break;
        case 6: _t->OnResetVariables(); break;
        case 7: _t->OnUpdateVariables(); break;
        default: ;
        }
    }
    Q_UNUSED(_a);
}

const QMetaObjectExtraData CalcStarApp::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject CalcStarApp::staticMetaObject = {
    { &QMainWindow::staticMetaObject, qt_meta_stringdata_CalcStarApp,
      qt_meta_data_CalcStarApp, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &CalcStarApp::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *CalcStarApp::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *CalcStarApp::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_CalcStarApp))
        return static_cast<void*>(const_cast< CalcStarApp*>(this));
    return QMainWindow::qt_metacast(_clname);
}

int CalcStarApp::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QMainWindow::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 8)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 8;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
