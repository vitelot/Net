/****************************************************************************
** NetIniForm meta object code from reading C++ file 'netiniform.h'
**
** Created: Thu May 16 12:20:57 2013
**      by: The Qt MOC ($Id: qt/moc_yacc.cpp   3.3.8   edited Feb 2 14:59 $)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#undef QT_NO_COMPAT
#include "../.ui/netiniform.h"
#include <qmetaobject.h>
#include <qapplication.h>

#include <private/qucomextra_p.h>
#if !defined(Q_MOC_OUTPUT_REVISION) || (Q_MOC_OUTPUT_REVISION != 26)
#error "This file was generated using the moc from 3.3.8b. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

const char *NetIniForm::className() const
{
    return "NetIniForm";
}

QMetaObject *NetIniForm::metaObj = 0;
static QMetaObjectCleanUp cleanUp_NetIniForm( "NetIniForm", &NetIniForm::staticMetaObject );

#ifndef QT_NO_TRANSLATION
QString NetIniForm::tr( const char *s, const char *c )
{
    if ( qApp )
	return qApp->translate( "NetIniForm", s, c, QApplication::DefaultCodec );
    else
	return QString::fromLatin1( s );
}
#ifndef QT_NO_TRANSLATION_UTF8
QString NetIniForm::trUtf8( const char *s, const char *c )
{
    if ( qApp )
	return qApp->translate( "NetIniForm", s, c, QApplication::UnicodeUTF8 );
    else
	return QString::fromUtf8( s );
}
#endif // QT_NO_TRANSLATION_UTF8

#endif // QT_NO_TRANSLATION

QMetaObject* NetIniForm::staticMetaObject()
{
    if ( metaObj )
	return metaObj;
    QMetaObject* parentObject = QDialog::staticMetaObject();
    static const QUMethod slot_0 = {"Save", 0, 0 };
    static const QUMethod slot_1 = {"SaveQuit", 0, 0 };
    static const QUMethod slot_2 = {"SaveRun", 0, 0 };
    static const QUMethod slot_3 = {"SaveIniFile", 0, 0 };
    static const QUMethod slot_4 = {"languageChange", 0, 0 };
    static const QMetaData slot_tbl[] = {
	{ "Save()", &slot_0, QMetaData::Public },
	{ "SaveQuit()", &slot_1, QMetaData::Public },
	{ "SaveRun()", &slot_2, QMetaData::Public },
	{ "SaveIniFile()", &slot_3, QMetaData::Public },
	{ "languageChange()", &slot_4, QMetaData::Protected }
    };
    metaObj = QMetaObject::new_metaobject(
	"NetIniForm", parentObject,
	slot_tbl, 5,
	0, 0,
#ifndef QT_NO_PROPERTIES
	0, 0,
	0, 0,
#endif // QT_NO_PROPERTIES
	0, 0 );
    cleanUp_NetIniForm.setMetaObject( metaObj );
    return metaObj;
}

void* NetIniForm::qt_cast( const char* clname )
{
    if ( !qstrcmp( clname, "NetIniForm" ) )
	return this;
    return QDialog::qt_cast( clname );
}

bool NetIniForm::qt_invoke( int _id, QUObject* _o )
{
    switch ( _id - staticMetaObject()->slotOffset() ) {
    case 0: Save(); break;
    case 1: SaveQuit(); break;
    case 2: SaveRun(); break;
    case 3: SaveIniFile(); break;
    case 4: languageChange(); break;
    default:
	return QDialog::qt_invoke( _id, _o );
    }
    return TRUE;
}

bool NetIniForm::qt_emit( int _id, QUObject* _o )
{
    return QDialog::qt_emit(_id,_o);
}
#ifndef QT_NO_PROPERTIES

bool NetIniForm::qt_property( int id, int f, QVariant* v)
{
    return QDialog::qt_property( id, f, v);
}

bool NetIniForm::qt_static_property( QObject* , int , int , QVariant* ){ return FALSE; }
#endif // QT_NO_PROPERTIES
