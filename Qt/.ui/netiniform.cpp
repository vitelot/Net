/****************************************************************************
** Form implementation generated from reading ui file 'netiniform.ui'
**
** Created: Thu May 16 12:20:54 2013
**
** WARNING! All changes made in this file will be lost!
****************************************************************************/

#include "netiniform.h"

#include <qvariant.h>
#include <qpushbutton.h>
#include <qlabel.h>
#include <qlineedit.h>
#include <qcheckbox.h>
#include <qspinbox.h>
#include <qcombobox.h>
#include <qgroupbox.h>
#include <qradiobutton.h>
#include <qlayout.h>
#include <qtooltip.h>
#include <qwhatsthis.h>
#include <qimage.h>
#include <qpixmap.h>

#include "../netiniform.ui.h"
/*
 *  Constructs a NetIniForm as a child of 'parent', with the
 *  name 'name' and widget flags set to 'f'.
 *
 *  The dialog will by default be modeless, unless you set 'modal' to
 *  TRUE to construct a modal dialog.
 */
NetIniForm::NetIniForm( QWidget* parent, const char* name, bool modal, WFlags fl )
    : QDialog( parent, name, modal, fl )
{
    if ( !name )
	setName( "NetIniForm" );
    setSizePolicy( QSizePolicy( (QSizePolicy::SizeType)0, (QSizePolicy::SizeType)0, 0, 0, sizePolicy().hasHeightForWidth() ) );
    setMinimumSize( QSize( 700, 452 ) );
    setMaximumSize( QSize( 10000, 10000 ) );
    QPalette pal;
    QColorGroup cg;
    cg.setColor( QColorGroup::Foreground, black );
    cg.setColor( QColorGroup::Button, QColor( 170, 170, 127) );
    cg.setColor( QColorGroup::Light, QColor( 255, 255, 190) );
    cg.setColor( QColorGroup::Midlight, QColor( 212, 212, 158) );
    cg.setColor( QColorGroup::Dark, QColor( 85, 85, 63) );
    cg.setColor( QColorGroup::Mid, QColor( 113, 113, 84) );
    cg.setColor( QColorGroup::Text, black );
    cg.setColor( QColorGroup::BrightText, white );
    cg.setColor( QColorGroup::ButtonText, black );
    cg.setColor( QColorGroup::Base, white );
    cg.setColor( QColorGroup::Background, QColor( 170, 170, 127) );
    cg.setColor( QColorGroup::Shadow, black );
    cg.setColor( QColorGroup::Highlight, QColor( 0, 0, 128) );
    cg.setColor( QColorGroup::HighlightedText, white );
    cg.setColor( QColorGroup::Link, black );
    cg.setColor( QColorGroup::LinkVisited, black );
    pal.setActive( cg );
    cg.setColor( QColorGroup::Foreground, black );
    cg.setColor( QColorGroup::Button, QColor( 170, 170, 127) );
    cg.setColor( QColorGroup::Light, QColor( 255, 255, 190) );
    cg.setColor( QColorGroup::Midlight, QColor( 195, 195, 145) );
    cg.setColor( QColorGroup::Dark, QColor( 85, 85, 63) );
    cg.setColor( QColorGroup::Mid, QColor( 113, 113, 84) );
    cg.setColor( QColorGroup::Text, black );
    cg.setColor( QColorGroup::BrightText, white );
    cg.setColor( QColorGroup::ButtonText, black );
    cg.setColor( QColorGroup::Base, white );
    cg.setColor( QColorGroup::Background, QColor( 170, 170, 127) );
    cg.setColor( QColorGroup::Shadow, black );
    cg.setColor( QColorGroup::Highlight, QColor( 0, 0, 128) );
    cg.setColor( QColorGroup::HighlightedText, white );
    cg.setColor( QColorGroup::Link, QColor( 0, 0, 255) );
    cg.setColor( QColorGroup::LinkVisited, QColor( 255, 0, 255) );
    pal.setInactive( cg );
    cg.setColor( QColorGroup::Foreground, QColor( 128, 128, 128) );
    cg.setColor( QColorGroup::Button, QColor( 170, 170, 127) );
    cg.setColor( QColorGroup::Light, QColor( 255, 255, 190) );
    cg.setColor( QColorGroup::Midlight, QColor( 195, 195, 145) );
    cg.setColor( QColorGroup::Dark, QColor( 85, 85, 63) );
    cg.setColor( QColorGroup::Mid, QColor( 113, 113, 84) );
    cg.setColor( QColorGroup::Text, QColor( 128, 128, 128) );
    cg.setColor( QColorGroup::BrightText, white );
    cg.setColor( QColorGroup::ButtonText, QColor( 128, 128, 128) );
    cg.setColor( QColorGroup::Base, white );
    cg.setColor( QColorGroup::Background, QColor( 170, 170, 127) );
    cg.setColor( QColorGroup::Shadow, black );
    cg.setColor( QColorGroup::Highlight, QColor( 0, 0, 128) );
    cg.setColor( QColorGroup::HighlightedText, white );
    cg.setColor( QColorGroup::Link, QColor( 0, 0, 255) );
    cg.setColor( QColorGroup::LinkVisited, QColor( 255, 0, 255) );
    pal.setDisabled( cg );
    setPalette( pal );
    NetIniFormLayout = new QVBoxLayout( this, 11, 6, "NetIniFormLayout"); 

    layout36 = new QHBoxLayout( 0, 0, 6, "layout36"); 
    Spacer13 = new QSpacerItem( 216, 16, QSizePolicy::Expanding, QSizePolicy::Minimum );
    layout36->addItem( Spacer13 );

    TextLabel4 = new QLabel( this, "TextLabel4" );
    TextLabel4->setPaletteForegroundColor( QColor( 170, 0, 0 ) );
    TextLabel4->setPaletteBackgroundColor( QColor( 170, 170, 127 ) );
    QFont TextLabel4_font(  TextLabel4->font() );
    TextLabel4_font.setPointSize( 18 );
    TextLabel4_font.setBold( TRUE );
    TextLabel4->setFont( TextLabel4_font ); 
    TextLabel4->setFrameShape( QLabel::NoFrame );
    TextLabel4->setFrameShadow( QLabel::Plain );
    TextLabel4->setAlignment( int( QLabel::AlignCenter ) );
    layout36->addWidget( TextLabel4 );
    Spacer13_2 = new QSpacerItem( 215, 16, QSizePolicy::Expanding, QSizePolicy::Minimum );
    layout36->addItem( Spacer13_2 );
    NetIniFormLayout->addLayout( layout36 );
    Spacer26 = new QSpacerItem( 16, 16, QSizePolicy::Minimum, QSizePolicy::Expanding );
    NetIniFormLayout->addItem( Spacer26 );

    layout37 = new QHBoxLayout( 0, 0, 6, "layout37"); 

    layout36_2 = new QHBoxLayout( 0, 0, 6, "layout36_2"); 

    TextLabel1 = new QLabel( this, "TextLabel1" );
    layout36_2->addWidget( TextLabel1 );

    ProjectName = new QLineEdit( this, "ProjectName" );
    ProjectName->setEnabled( TRUE );
    ProjectName->setFrameShape( QLineEdit::LineEditPanel );
    ProjectName->setFrameShadow( QLineEdit::Sunken );
    ProjectName->setAlignment( int( QLineEdit::AlignHCenter ) );
    layout36_2->addWidget( ProjectName );
    layout37->addLayout( layout36_2 );

    layout35 = new QHBoxLayout( 0, 0, 6, "layout35"); 
    Spacer5 = new QSpacerItem( 98, 16, QSizePolicy::Expanding, QSizePolicy::Minimum );
    layout35->addItem( Spacer5 );

    ReadNetCheckBox = new QCheckBox( this, "ReadNetCheckBox" );
    layout35->addWidget( ReadNetCheckBox );
    Spacer3 = new QSpacerItem( 97, 16, QSizePolicy::Expanding, QSizePolicy::Minimum );
    layout35->addItem( Spacer3 );

    NetTypeCheckBox = new QCheckBox( this, "NetTypeCheckBox" );
    NetTypeCheckBox->setEnabled( TRUE );
    layout35->addWidget( NetTypeCheckBox );

    WeightedCheckBox = new QCheckBox( this, "WeightedCheckBox" );
    WeightedCheckBox->setEnabled( TRUE );
    layout35->addWidget( WeightedCheckBox );

    TASCheckBox = new QCheckBox( this, "TASCheckBox" );
    TASCheckBox->setEnabled( TRUE );
    layout35->addWidget( TASCheckBox );
    Spacer9 = new QSpacerItem( 50, 16, QSizePolicy::Expanding, QSizePolicy::Minimum );
    layout35->addItem( Spacer9 );
    layout37->addLayout( layout35 );

    layout38 = new QHBoxLayout( 0, 0, 6, "layout38"); 

    MultiSpinBox = new QSpinBox( this, "MultiSpinBox" );
    QFont MultiSpinBox_font(  MultiSpinBox->font() );
    MultiSpinBox->setFont( MultiSpinBox_font ); 
    MultiSpinBox->setMaxValue( 9999 );
    MultiSpinBox->setMinValue( 1 );
    layout38->addWidget( MultiSpinBox );

    TextLabel1_2 = new QLabel( this, "TextLabel1_2" );
    QFont TextLabel1_2_font(  TextLabel1_2->font() );
    TextLabel1_2->setFont( TextLabel1_2_font ); 
    layout38->addWidget( TextLabel1_2 );
    layout37->addLayout( layout38 );
    NetIniFormLayout->addLayout( layout37 );

    layout38_2 = new QHBoxLayout( 0, 0, 6, "layout38_2"); 

    layout41 = new QVBoxLayout( 0, 0, 6, "layout41"); 
    Spacer23_2_2 = new QSpacerItem( 16, 61, QSizePolicy::Minimum, QSizePolicy::Expanding );
    layout41->addItem( Spacer23_2_2 );

    layout73 = new QGridLayout( 0, 1, 1, 0, 6, "layout73"); 

    TextLabel2 = new QLabel( this, "TextLabel2" );
    QFont TextLabel2_font(  TextLabel2->font() );
    TextLabel2->setFont( TextLabel2_font ); 
    TextLabel2->setMargin( 6 );

    layout73->addWidget( TextLabel2, 1, 0 );

    GenComboBox = new QComboBox( FALSE, this, "GenComboBox" );

    layout73->addWidget( GenComboBox, 0, 1 );

    GraphOrder = new QSpinBox( this, "GraphOrder" );
    QFont GraphOrder_font(  GraphOrder->font() );
    GraphOrder->setFont( GraphOrder_font ); 
    GraphOrder->setMaxValue( 1000000 );
    GraphOrder->setMinValue( 2 );
    GraphOrder->setValue( 1000 );

    layout73->addWidget( GraphOrder, 1, 1 );

    TextLabel1_5 = new QLabel( this, "TextLabel1_5" );

    layout73->addWidget( TextLabel1_5, 0, 0 );
    layout41->addLayout( layout73 );

    layout41_2 = new QHBoxLayout( 0, 0, 6, "layout41_2"); 

    GroupBox3 = new QGroupBox( this, "GroupBox3" );
    GroupBox3->setFrameShape( QGroupBox::Box );
    GroupBox3->setFrameShadow( QGroupBox::Sunken );

    QWidget* privateLayoutWidget = new QWidget( GroupBox3, "layout33" );
    privateLayoutWidget->setGeometry( QRect( 13, 30, 199, 431 ) );
    layout33 = new QVBoxLayout( privateLayoutWidget, 11, 6, "layout33"); 

    GroupBox4 = new QGroupBox( privateLayoutWidget, "GroupBox4" );

    QWidget* privateLayoutWidget_2 = new QWidget( GroupBox4, "layout56" );
    privateLayoutWidget_2->setGeometry( QRect( 13, 24, 152, 99 ) );
    layout56 = new QVBoxLayout( privateLayoutWidget_2, 11, 6, "layout56"); 

    FitnessComboBox = new QComboBox( FALSE, privateLayoutWidget_2, "FitnessComboBox" );
    FitnessComboBox->setMinimumSize( QSize( 150, 30 ) );
    QFont FitnessComboBox_font(  FitnessComboBox->font() );
    FitnessComboBox->setFont( FitnessComboBox_font ); 
    FitnessComboBox->setFocusPolicy( QComboBox::TabFocus );
    layout56->addWidget( FitnessComboBox );

    layout55 = new QGridLayout( 0, 1, 1, 0, 6, "layout55"); 

    BParameter = new QLineEdit( privateLayoutWidget_2, "BParameter" );
    BParameter->setMaximumSize( QSize( 100, 32767 ) );
    BParameter->setAlignment( int( QLineEdit::AlignHCenter ) );

    layout55->addWidget( BParameter, 1, 0 );

    TextLabel6 = new QLabel( privateLayoutWidget_2, "TextLabel6" );
    QFont TextLabel6_font(  TextLabel6->font() );
    TextLabel6->setFont( TextLabel6_font ); 

    layout55->addWidget( TextLabel6, 0, 1 );

    TextLabel1_4 = new QLabel( privateLayoutWidget_2, "TextLabel1_4" );

    layout55->addWidget( TextLabel1_4, 1, 1 );

    AParameter = new QLineEdit( privateLayoutWidget_2, "AParameter" );
    AParameter->setMaximumSize( QSize( 100, 32767 ) );
    QFont AParameter_font(  AParameter->font() );
    AParameter->setFont( AParameter_font ); 
    AParameter->setAlignment( int( QLineEdit::AlignHCenter ) );

    layout55->addWidget( AParameter, 0, 0 );
    layout56->addLayout( layout55 );
    layout33->addWidget( GroupBox4 );

    GroupBox5 = new QGroupBox( privateLayoutWidget, "GroupBox5" );

    QWidget* privateLayoutWidget_3 = new QWidget( GroupBox5, "layout32" );
    privateLayoutWidget_3->setGeometry( QRect( 10, 40, 124, 130 ) );
    layout32 = new QVBoxLayout( privateLayoutWidget_3, 11, 6, "layout32"); 

    LinkComboBox = new QComboBox( FALSE, privateLayoutWidget_3, "LinkComboBox" );
    QFont LinkComboBox_font(  LinkComboBox->font() );
    LinkComboBox->setFont( LinkComboBox_font ); 
    layout32->addWidget( LinkComboBox );

    layout31 = new QGridLayout( 0, 1, 1, 0, 6, "layout31"); 

    TextLabel6_2_2 = new QLabel( privateLayoutWidget_3, "TextLabel6_2_2" );
    QFont TextLabel6_2_2_font(  TextLabel6_2_2->font() );
    TextLabel6_2_2->setFont( TextLabel6_2_2_font ); 

    layout31->addWidget( TextLabel6_2_2, 2, 1 );

    EParameter = new QLineEdit( privateLayoutWidget_3, "EParameter" );
    EParameter->setMaximumSize( QSize( 100, 32767 ) );
    QFont EParameter_font(  EParameter->font() );
    EParameter->setFont( EParameter_font ); 
    EParameter->setAlignment( int( QLineEdit::AlignHCenter ) );

    layout31->addWidget( EParameter, 2, 0 );

    TextLabel6_2 = new QLabel( privateLayoutWidget_3, "TextLabel6_2" );
    QFont TextLabel6_2_font(  TextLabel6_2->font() );
    TextLabel6_2->setFont( TextLabel6_2_font ); 

    layout31->addWidget( TextLabel6_2, 1, 1 );

    MParameter = new QLineEdit( privateLayoutWidget_3, "MParameter" );
    MParameter->setMaximumSize( QSize( 100, 32767 ) );
    QFont MParameter_font(  MParameter->font() );
    MParameter->setFont( MParameter_font ); 
    MParameter->setAlignment( int( QLineEdit::AlignHCenter ) );

    layout31->addWidget( MParameter, 0, 0 );

    TextLabel6_3 = new QLabel( privateLayoutWidget_3, "TextLabel6_3" );
    QFont TextLabel6_3_font(  TextLabel6_3->font() );
    TextLabel6_3->setFont( TextLabel6_3_font ); 

    layout31->addWidget( TextLabel6_3, 0, 1 );

    CutOffParameter = new QLineEdit( privateLayoutWidget_3, "CutOffParameter" );
    CutOffParameter->setMaximumSize( QSize( 100, 32767 ) );
    QFont CutOffParameter_font(  CutOffParameter->font() );
    CutOffParameter->setFont( CutOffParameter_font ); 
    CutOffParameter->setAlignment( int( QLineEdit::AlignHCenter ) );

    layout31->addWidget( CutOffParameter, 1, 0 );
    layout32->addLayout( layout31 );
    layout33->addWidget( GroupBox5 );

    layout43 = new QHBoxLayout( 0, 0, 6, "layout43"); 
    Spacer19 = new QSpacerItem( 52, 16, QSizePolicy::Expanding, QSizePolicy::Minimum );
    layout43->addItem( Spacer19 );

    layout70 = new QVBoxLayout( 0, 0, 6, "layout70"); 

    AcyclicRadioButton = new QRadioButton( privateLayoutWidget, "AcyclicRadioButton" );
    layout70->addWidget( AcyclicRadioButton );

    TreeRadioButton = new QRadioButton( privateLayoutWidget, "TreeRadioButton" );
    layout70->addWidget( TreeRadioButton );
    layout43->addLayout( layout70 );
    Spacer19_2 = new QSpacerItem( 51, 20, QSizePolicy::Expanding, QSizePolicy::Minimum );
    layout43->addItem( Spacer19_2 );
    layout33->addLayout( layout43 );
    layout41_2->addWidget( GroupBox3 );

    layout39 = new QVBoxLayout( 0, 0, 6, "layout39"); 

    GroupBox6 = new QGroupBox( this, "GroupBox6" );

    QWidget* privateLayoutWidget_4 = new QWidget( GroupBox6, "layout38" );
    privateLayoutWidget_4->setGeometry( QRect( 10, 40, 166, 166 ) );
    layout38_3 = new QVBoxLayout( privateLayoutWidget_4, 11, 6, "layout38_3"); 

    layout41_3 = new QHBoxLayout( 0, 0, 6, "layout41_3"); 
    Spacer19_2_3 = new QSpacerItem( 30, 20, QSizePolicy::Expanding, QSizePolicy::Minimum );
    layout41_3->addItem( Spacer19_2_3 );

    layout39_2 = new QGridLayout( 0, 1, 1, 0, 6, "layout39_2"); 

    BA_N0 = new QSpinBox( privateLayoutWidget_4, "BA_N0" );
    BA_N0->setMaxValue( 999 );
    BA_N0->setMinValue( 2 );
    BA_N0->setValue( 2 );

    layout39_2->addWidget( BA_N0, 0, 0 );

    TextLabel2_2 = new QLabel( privateLayoutWidget_4, "TextLabel2_2" );

    layout39_2->addWidget( TextLabel2_2, 1, 1 );

    TextLabel1_6 = new QLabel( privateLayoutWidget_4, "TextLabel1_6" );

    layout39_2->addWidget( TextLabel1_6, 0, 1 );

    BA_M = new QSpinBox( privateLayoutWidget_4, "BA_M" );
    BA_M->setMaxValue( 999 );
    BA_M->setMinValue( 1 );

    layout39_2->addWidget( BA_M, 1, 0 );
    layout41_3->addLayout( layout39_2 );
    Spacer19_2_2 = new QSpacerItem( 30, 20, QSizePolicy::Expanding, QSizePolicy::Minimum );
    layout41_3->addItem( Spacer19_2_2 );
    layout38_3->addLayout( layout41_3 );
    spacer33 = new QSpacerItem( 20, 20, QSizePolicy::Minimum, QSizePolicy::Expanding );
    layout38_3->addItem( spacer33 );

    textLabel1_2 = new QLabel( privateLayoutWidget_4, "textLabel1_2" );
    layout38_3->addWidget( textLabel1_2 );

    layout37_2 = new QGridLayout( 0, 1, 1, 0, 6, "layout37_2"); 

    textLabel2_2 = new QLabel( privateLayoutWidget_4, "textLabel2_2" );

    layout37_2->addMultiCellWidget( textLabel2_2, 1, 1, 1, 2 );

    BAMemoryB = new QLineEdit( privateLayoutWidget_4, "BAMemoryB" );
    BAMemoryB->setMaximumSize( QSize( 100, 32767 ) );
    BAMemoryB->setAlignment( int( QLineEdit::AlignHCenter ) );

    layout37_2->addWidget( BAMemoryB, 1, 0 );

    BAMemoryA = new QLineEdit( privateLayoutWidget_4, "BAMemoryA" );
    BAMemoryA->setMaximumSize( QSize( 100, 32767 ) );
    BAMemoryA->setAlignment( int( QLineEdit::AlignHCenter ) );

    layout37_2->addMultiCellWidget( BAMemoryA, 0, 0, 0, 1 );

    textLabel2 = new QLabel( privateLayoutWidget_4, "textLabel2" );

    layout37_2->addWidget( textLabel2, 0, 2 );
    layout38_3->addLayout( layout37_2 );
    layout39->addWidget( GroupBox6 );

    groupBox7 = new QGroupBox( this, "groupBox7" );
    groupBox7->setEnabled( TRUE );

    QWidget* privateLayoutWidget_5 = new QWidget( groupBox7, "layout52" );
    privateLayoutWidget_5->setGeometry( QRect( 20, 50, 153, 130 ) );
    layout52 = new QVBoxLayout( privateLayoutWidget_5, 11, 6, "layout52"); 

    GeoNetTypeComboBox = new QComboBox( FALSE, privateLayoutWidget_5, "GeoNetTypeComboBox" );
    GeoNetTypeComboBox->setMaximumSize( QSize( 180, 32767 ) );
    layout52->addWidget( GeoNetTypeComboBox );

    layout44 = new QGridLayout( 0, 1, 1, 0, 6, "layout44"); 

    TextLabel1_6_2_3 = new QLabel( privateLayoutWidget_5, "TextLabel1_6_2_3" );

    layout44->addWidget( TextLabel1_6_2_3, 2, 1 );

    TextLabel1_6_2_2 = new QLabel( privateLayoutWidget_5, "TextLabel1_6_2_2" );

    layout44->addWidget( TextLabel1_6_2_2, 1, 1 );

    TextLabel1_6_2 = new QLabel( privateLayoutWidget_5, "TextLabel1_6_2" );

    layout44->addWidget( TextLabel1_6_2, 0, 1 );

    GeoProbRmin = new QLineEdit( privateLayoutWidget_5, "GeoProbRmin" );
    GeoProbRmin->setMaximumSize( QSize( 80, 32767 ) );
    GeoProbRmin->setAlignment( int( QLineEdit::AlignHCenter ) );

    layout44->addWidget( GeoProbRmin, 2, 0 );

    GeoRmin = new QLineEdit( privateLayoutWidget_5, "GeoRmin" );
    GeoRmin->setMaximumSize( QSize( 80, 32767 ) );
    GeoRmin->setAlignment( int( QLineEdit::AlignHCenter ) );

    layout44->addWidget( GeoRmin, 0, 0 );

    GeoRmax = new QLineEdit( privateLayoutWidget_5, "GeoRmax" );
    GeoRmax->setMaximumSize( QSize( 80, 32767 ) );
    GeoRmax->setAlignment( int( QLineEdit::AlignHCenter ) );

    layout44->addWidget( GeoRmax, 1, 0 );
    layout52->addLayout( layout44 );
    layout39->addWidget( groupBox7 );
    layout41_2->addLayout( layout39 );
    layout41->addLayout( layout41_2 );
    layout38_2->addLayout( layout41 );

    GroupBox2 = new QGroupBox( this, "GroupBox2" );
    GroupBox2->setAlignment( int( QGroupBox::AlignAuto ) );

    QWidget* privateLayoutWidget_6 = new QWidget( GroupBox2, "layout37" );
    privateLayoutWidget_6->setGeometry( QRect( 10, 29, 169, 585 ) );
    layout37_3 = new QVBoxLayout( privateLayoutWidget_6, 11, 6, "layout37_3"); 

    DegreeDistribRadioButton = new QRadioButton( privateLayoutWidget_6, "DegreeDistribRadioButton" );
    QFont DegreeDistribRadioButton_font(  DegreeDistribRadioButton->font() );
    DegreeDistribRadioButton->setFont( DegreeDistribRadioButton_font ); 
    layout37_3->addWidget( DegreeDistribRadioButton );

    KnnRadioButton = new QRadioButton( privateLayoutWidget_6, "KnnRadioButton" );
    QFont KnnRadioButton_font(  KnnRadioButton->font() );
    KnnRadioButton->setFont( KnnRadioButton_font ); 
    layout37_3->addWidget( KnnRadioButton );

    ClusterCoeffRadioButton = new QRadioButton( privateLayoutWidget_6, "ClusterCoeffRadioButton" );
    QFont ClusterCoeffRadioButton_font(  ClusterCoeffRadioButton->font() );
    ClusterCoeffRadioButton->setFont( ClusterCoeffRadioButton_font ); 
    layout37_3->addWidget( ClusterCoeffRadioButton );

    ClusterCoeff2RadioButton = new QRadioButton( privateLayoutWidget_6, "ClusterCoeff2RadioButton" );
    QFont ClusterCoeff2RadioButton_font(  ClusterCoeff2RadioButton->font() );
    ClusterCoeff2RadioButton->setFont( ClusterCoeff2RadioButton_font ); 
    layout37_3->addWidget( ClusterCoeff2RadioButton );

    SCCRadioButton = new QRadioButton( privateLayoutWidget_6, "SCCRadioButton" );
    SCCRadioButton->setEnabled( FALSE );
    layout37_3->addWidget( SCCRadioButton );

    CommunityRadioButton = new QRadioButton( privateLayoutWidget_6, "CommunityRadioButton" );
    CommunityRadioButton->setEnabled( FALSE );
    layout37_3->addWidget( CommunityRadioButton );

    SplitClusterRadioButton = new QRadioButton( privateLayoutWidget_6, "SplitClusterRadioButton" );
    SplitClusterRadioButton->setEnabled( TRUE );
    QFont SplitClusterRadioButton_font(  SplitClusterRadioButton->font() );
    SplitClusterRadioButton->setFont( SplitClusterRadioButton_font ); 
    layout37_3->addWidget( SplitClusterRadioButton );

    layout35_2 = new QHBoxLayout( 0, 0, 6, "layout35_2"); 
    spacer28 = new QSpacerItem( 40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum );
    layout35_2->addItem( spacer28 );

    SaveClusterRadioButton = new QRadioButton( privateLayoutWidget_6, "SaveClusterRadioButton" );
    SaveClusterRadioButton->setEnabled( FALSE );
    QFont SaveClusterRadioButton_font(  SaveClusterRadioButton->font() );
    SaveClusterRadioButton->setFont( SaveClusterRadioButton_font ); 
    layout35_2->addWidget( SaveClusterRadioButton );
    layout37_3->addLayout( layout35_2 );

    EdgeBetweenRadioButton = new QRadioButton( privateLayoutWidget_6, "EdgeBetweenRadioButton" );
    QFont EdgeBetweenRadioButton_font(  EdgeBetweenRadioButton->font() );
    EdgeBetweenRadioButton->setFont( EdgeBetweenRadioButton_font ); 
    layout37_3->addWidget( EdgeBetweenRadioButton );

    SiteBetweenRadioButton = new QRadioButton( privateLayoutWidget_6, "SiteBetweenRadioButton" );
    QFont SiteBetweenRadioButton_font(  SiteBetweenRadioButton->font() );
    SiteBetweenRadioButton->setFont( SiteBetweenRadioButton_font ); 
    layout37_3->addWidget( SiteBetweenRadioButton );

    layout31_2 = new QHBoxLayout( 0, 0, 6, "layout31_2"); 

    RWBetweenComboBox = new QComboBox( FALSE, privateLayoutWidget_6, "RWBetweenComboBox" );
    layout31_2->addWidget( RWBetweenComboBox );

    textLabel1 = new QLabel( privateLayoutWidget_6, "textLabel1" );
    layout31_2->addWidget( textLabel1 );
    layout37_3->addLayout( layout31_2 );

    layout42 = new QHBoxLayout( 0, 0, 6, "layout42"); 
    Spacer4 = new QSpacerItem( 17, 16, QSizePolicy::Expanding, QSizePolicy::Minimum );
    layout42->addItem( Spacer4 );

    PairDistRadioButton = new QRadioButton( privateLayoutWidget_6, "PairDistRadioButton" );
    PairDistRadioButton->setEnabled( FALSE );
    QFont PairDistRadioButton_font(  PairDistRadioButton->font() );
    PairDistRadioButton->setFont( PairDistRadioButton_font ); 
    layout42->addWidget( PairDistRadioButton );
    layout37_3->addLayout( layout42 );
    Spacer25_2 = new QSpacerItem( 16, 75, QSizePolicy::Minimum, QSizePolicy::Expanding );
    layout37_3->addItem( Spacer25_2 );

    SelfLoopsRadioButton = new QRadioButton( privateLayoutWidget_6, "SelfLoopsRadioButton" );
    SelfLoopsRadioButton->setEnabled( TRUE );
    QFont SelfLoopsRadioButton_font(  SelfLoopsRadioButton->font() );
    SelfLoopsRadioButton->setFont( SelfLoopsRadioButton_font ); 
    layout37_3->addWidget( SelfLoopsRadioButton );

    AMatrixComboBox = new QComboBox( FALSE, privateLayoutWidget_6, "AMatrixComboBox" );
    layout37_3->addWidget( AMatrixComboBox );

    layout43_2 = new QHBoxLayout( 0, 0, 6, "layout43_2"); 
    Spacer7 = new QSpacerItem( 30, 16, QSizePolicy::Expanding, QSizePolicy::Minimum );
    layout43_2->addItem( Spacer7 );

    LanczosCheckBox = new QCheckBox( privateLayoutWidget_6, "LanczosCheckBox" );
    layout43_2->addWidget( LanczosCheckBox );
    Spacer4_3_5 = new QSpacerItem( 21, 16, QSizePolicy::Expanding, QSizePolicy::Minimum );
    layout43_2->addItem( Spacer4_3_5 );
    layout37_3->addLayout( layout43_2 );
    Spacer25 = new QSpacerItem( 20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding );
    layout37_3->addItem( Spacer25 );

    layout36_3 = new QHBoxLayout( 0, 0, 6, "layout36_3"); 

    RewiringSpinBox = new QSpinBox( privateLayoutWidget_6, "RewiringSpinBox" );
    RewiringSpinBox->setButtonSymbols( QSpinBox::PlusMinus );
    RewiringSpinBox->setMaxValue( 1000000 );
    layout36_3->addWidget( RewiringSpinBox );

    TextLabel1_7_2 = new QLabel( privateLayoutWidget_6, "TextLabel1_7_2" );
    layout36_3->addWidget( TextLabel1_7_2 );
    layout37_3->addLayout( layout36_3 );

    layout44_2 = new QHBoxLayout( 0, 0, 6, "layout44_2"); 

    ReductionSpinBox = new QSpinBox( privateLayoutWidget_6, "ReductionSpinBox" );
    ReductionSpinBox->setButtonSymbols( QSpinBox::PlusMinus );
    ReductionSpinBox->setMaxValue( 1000000 );
    layout44_2->addWidget( ReductionSpinBox );

    TextLabel1_7 = new QLabel( privateLayoutWidget_6, "TextLabel1_7" );
    layout44_2->addWidget( TextLabel1_7 );
    layout37_3->addLayout( layout44_2 );
    layout38_2->addWidget( GroupBox2 );

    layout36_4 = new QVBoxLayout( 0, 0, 6, "layout36_4"); 

    groupBox9 = new QGroupBox( this, "groupBox9" );
    groupBox9->setColumnLayout(0, Qt::Vertical );
    groupBox9->layout()->setSpacing( 6 );
    groupBox9->layout()->setMargin( 11 );
    groupBox9Layout = new QVBoxLayout( groupBox9->layout() );
    groupBox9Layout->setAlignment( Qt::AlignTop );

    TASreshufCheckBox = new QCheckBox( groupBox9, "TASreshufCheckBox" );
    groupBox9Layout->addWidget( TASreshufCheckBox );

    layout35_3 = new QHBoxLayout( 0, 0, 6, "layout35_3"); 

    textLabel1_3 = new QLabel( groupBox9, "textLabel1_3" );
    layout35_3->addWidget( textLabel1_3 );

    TASRW = new QSpinBox( groupBox9, "TASRW" );
    QFont TASRW_font(  TASRW->font() );
    TASRW->setFont( TASRW_font ); 
    TASRW->setMaxValue( 1000000 );
    TASRW->setMinValue( 0 );
    TASRW->setValue( 0 );
    layout35_3->addWidget( TASRW );
    groupBox9Layout->addLayout( layout35_3 );
    layout36_4->addWidget( groupBox9 );
    Spacer10_3 = new QSpacerItem( 20, 20, QSizePolicy::Minimum, QSizePolicy::Expanding );
    layout36_4->addItem( Spacer10_3 );

    GroupBox3_2 = new QGroupBox( this, "GroupBox3_2" );

    SaveNetComboBox = new QComboBox( FALSE, GroupBox3_2, "SaveNetComboBox" );
    SaveNetComboBox->setGeometry( QRect( 21, 57, 106, 22 ) );

    XmGraceComboBox = new QComboBox( FALSE, GroupBox3_2, "XmGraceComboBox" );
    XmGraceComboBox->setGeometry( QRect( 21, 85, 106, 22 ) );

    ShowComboBox = new QComboBox( FALSE, GroupBox3_2, "ShowComboBox" );
    ShowComboBox->setGeometry( QRect( 21, 113, 106, 22 ) );
    layout36_4->addWidget( GroupBox3_2 );
    Spacer10 = new QSpacerItem( 20, 20, QSizePolicy::Minimum, QSizePolicy::Expanding );
    layout36_4->addItem( Spacer10 );

    layout58 = new QGridLayout( 0, 1, 1, 0, 6, "layout58"); 
    spacer24_4 = new QSpacerItem( 51, 16, QSizePolicy::Expanding, QSizePolicy::Minimum );
    layout58->addMultiCell( spacer24_4, 3, 3, 5, 6 );
    spacer24_6 = new QSpacerItem( 51, 16, QSizePolicy::Expanding, QSizePolicy::Minimum );
    layout58->addMultiCell( spacer24_6, 1, 1, 5, 6 );
    spacer24_5 = new QSpacerItem( 63, 16, QSizePolicy::Expanding, QSizePolicy::Minimum );
    layout58->addMultiCell( spacer24_5, 3, 3, 0, 1 );
    spacer24_8 = new QSpacerItem( 89, 16, QSizePolicy::Expanding, QSizePolicy::Minimum );
    layout58->addMultiCell( spacer24_8, 0, 0, 0, 2 );
    spacer24_7 = new QSpacerItem( 77, 16, QSizePolicy::Expanding, QSizePolicy::Minimum );
    layout58->addMultiCell( spacer24_7, 0, 0, 4, 6 );
    spacer24 = new QSpacerItem( 63, 16, QSizePolicy::Expanding, QSizePolicy::Minimum );
    layout58->addMultiCell( spacer24, 1, 1, 0, 1 );
    spacer24_4_3 = new QSpacerItem( 51, 16, QSizePolicy::Expanding, QSizePolicy::Minimum );
    layout58->addItem( spacer24_4_3, 2, 0 );
    spacer24_4_2 = new QSpacerItem( 51, 16, QSizePolicy::Expanding, QSizePolicy::Minimum );
    layout58->addItem( spacer24_4_2, 2, 6 );

    OutFileCheckBox = new QCheckBox( this, "OutFileCheckBox" );

    layout58->addMultiCellWidget( OutFileCheckBox, 2, 2, 1, 5 );

    SaveQuitPushButton = new QPushButton( this, "SaveQuitPushButton" );

    layout58->addMultiCellWidget( SaveQuitPushButton, 3, 3, 2, 4 );

    SavePushButton = new QPushButton( this, "SavePushButton" );

    layout58->addWidget( SavePushButton, 0, 3 );

    SaveRunPushButton = new QPushButton( this, "SaveRunPushButton" );

    layout58->addMultiCellWidget( SaveRunPushButton, 1, 1, 2, 4 );
    layout36_4->addLayout( layout58 );
    Spacer5_2 = new QSpacerItem( 20, 20, QSizePolicy::Minimum, QSizePolicy::Expanding );
    layout36_4->addItem( Spacer5_2 );

    layout58_2 = new QHBoxLayout( 0, 0, 6, "layout58_2"); 
    spacer24_3 = new QSpacerItem( 62, 0, QSizePolicy::Expanding, QSizePolicy::Minimum );
    layout58_2->addItem( spacer24_3 );

    QuitPushButton = new QPushButton( this, "QuitPushButton" );
    layout58_2->addWidget( QuitPushButton );
    spacer24_2 = new QSpacerItem( 61, 0, QSizePolicy::Expanding, QSizePolicy::Minimum );
    layout58_2->addItem( spacer24_2 );
    layout36_4->addLayout( layout58_2 );
    Spacer10_2 = new QSpacerItem( 16, 80, QSizePolicy::Minimum, QSizePolicy::Expanding );
    layout36_4->addItem( Spacer10_2 );

    layout50 = new QHBoxLayout( 0, 0, 6, "layout50"); 
    Spacer12 = new QSpacerItem( 156, 0, QSizePolicy::Expanding, QSizePolicy::Minimum );
    layout50->addItem( Spacer12 );

    TextLabel5 = new QLabel( this, "TextLabel5" );
    QFont TextLabel5_font(  TextLabel5->font() );
    TextLabel5_font.setItalic( TRUE );
    TextLabel5->setFont( TextLabel5_font ); 
    layout50->addWidget( TextLabel5 );
    layout36_4->addLayout( layout50 );
    layout38_2->addLayout( layout36_4 );
    NetIniFormLayout->addLayout( layout38_2 );
    Spacer23_2 = new QSpacerItem( 16, 16, QSizePolicy::Minimum, QSizePolicy::Expanding );
    NetIniFormLayout->addItem( Spacer23_2 );
    languageChange();
    resize( QSize(962, 732).expandedTo(minimumSizeHint()) );
    clearWState( WState_Polished );

    // signals and slots connections
    connect( QuitPushButton, SIGNAL( clicked() ), this, SLOT( accept() ) );
    connect( SaveQuitPushButton, SIGNAL( clicked() ), this, SLOT( SaveQuit() ) );
    connect( SaveQuitPushButton, SIGNAL( clicked() ), this, SLOT( accept() ) );
    connect( SaveRunPushButton, SIGNAL( clicked() ), this, SLOT( SaveRun() ) );
    connect( ReadNetCheckBox, SIGNAL( toggled(bool) ), GroupBox3, SLOT( setDisabled(bool) ) );
    connect( SiteBetweenRadioButton, SIGNAL( toggled(bool) ), PairDistRadioButton, SLOT( setEnabled(bool) ) );
    connect( NetTypeCheckBox, SIGNAL( toggled(bool) ), ClusterCoeffRadioButton, SLOT( setDisabled(bool) ) );
    connect( NetTypeCheckBox, SIGNAL( toggled(bool) ), ClusterCoeff2RadioButton, SLOT( setDisabled(bool) ) );
    connect( ReadNetCheckBox, SIGNAL( toggled(bool) ), GroupBox6, SLOT( setDisabled(bool) ) );
    connect( ReadNetCheckBox, SIGNAL( toggled(bool) ), GenComboBox, SLOT( setDisabled(bool) ) );
    connect( ReadNetCheckBox, SIGNAL( toggled(bool) ), GraphOrder, SLOT( setDisabled(bool) ) );
    connect( NetTypeCheckBox, SIGNAL( toggled(bool) ), SCCRadioButton, SLOT( setEnabled(bool) ) );
    connect( SplitClusterRadioButton, SIGNAL( toggled(bool) ), SaveClusterRadioButton, SLOT( setEnabled(bool) ) );
    connect( SavePushButton, SIGNAL( clicked() ), this, SLOT( Save() ) );
    connect( ReadNetCheckBox, SIGNAL( toggled(bool) ), groupBox7, SLOT( setDisabled(bool) ) );
    connect( TASCheckBox, SIGNAL( toggled(bool) ), ReadNetCheckBox, SLOT( setChecked(bool) ) );
    connect( TASreshufCheckBox, SIGNAL( toggled(bool) ), ReadNetCheckBox, SLOT( setChecked(bool) ) );
    connect( TASreshufCheckBox, SIGNAL( toggled(bool) ), TASCheckBox, SLOT( setChecked(bool) ) );

    // tab order
    setTabOrder( ProjectName, ReadNetCheckBox );
    setTabOrder( ReadNetCheckBox, NetTypeCheckBox );
    setTabOrder( NetTypeCheckBox, GraphOrder );
    setTabOrder( GraphOrder, FitnessComboBox );
    setTabOrder( FitnessComboBox, AParameter );
    setTabOrder( AParameter, BParameter );
    setTabOrder( BParameter, LinkComboBox );
    setTabOrder( LinkComboBox, MParameter );
    setTabOrder( MParameter, CutOffParameter );
    setTabOrder( CutOffParameter, EParameter );
    setTabOrder( EParameter, MultiSpinBox );
    setTabOrder( MultiSpinBox, DegreeDistribRadioButton );
    setTabOrder( DegreeDistribRadioButton, KnnRadioButton );
    setTabOrder( KnnRadioButton, ClusterCoeffRadioButton );
    setTabOrder( ClusterCoeffRadioButton, ClusterCoeff2RadioButton );
    setTabOrder( ClusterCoeff2RadioButton, EdgeBetweenRadioButton );
    setTabOrder( EdgeBetweenRadioButton, SiteBetweenRadioButton );
    setTabOrder( SiteBetweenRadioButton, PairDistRadioButton );
    setTabOrder( PairDistRadioButton, SplitClusterRadioButton );
    setTabOrder( SplitClusterRadioButton, SaveClusterRadioButton );
    setTabOrder( SaveClusterRadioButton, ShowComboBox );
    setTabOrder( ShowComboBox, SaveRunPushButton );
    setTabOrder( SaveRunPushButton, SaveQuitPushButton );
    setTabOrder( SaveQuitPushButton, QuitPushButton );
}

/*
 *  Destroys the object and frees any allocated resources
 */
NetIniForm::~NetIniForm()
{
    // no need to delete child widgets, Qt does it all for us
}

/*
 *  Sets the strings of the subwidgets using the current
 *  language.
 */
void NetIniForm::languageChange()
{
    setCaption( tr( "NetIniForm" ) );
    QToolTip::add( this, QString::null );
    TextLabel4->setText( tr( "NET.INI File creation tool" ) );
    TextLabel1->setText( tr( "Project Name" ) );
    ProjectName->setText( tr( "net" ) );
    ReadNetCheckBox->setText( tr( "Read &Net" ) );
    ReadNetCheckBox->setAccel( QKeySequence( tr( "Alt+N" ) ) );
    QToolTip::add( ReadNetCheckBox, tr( "Read the graph ProjectName.in" ) );
    NetTypeCheckBox->setText( tr( "Directed" ) );
    QToolTip::add( NetTypeCheckBox, tr( "Set Net Type to Directed" ) );
    WeightedCheckBox->setText( tr( "Weighted" ) );
    QToolTip::add( WeightedCheckBox, tr( "Edges are weighted" ) );
    TASCheckBox->setText( tr( "TAS" ) );
    QToolTip::add( TASCheckBox, tr( "The file to read is a list of Tag ASsignments (Folksonomy)" ) );
    MultiSpinBox->setSpecialValueText( tr( "none" ) );
    QToolTip::add( MultiSpinBox, tr( "Run the program lot of times" ) );
    TextLabel1_2->setText( tr( "Multiple runs" ) );
    QToolTip::add( TextLabel1_2, tr( "Run the program lot of times" ) );
    TextLabel2->setText( tr( "Graph Order" ) );
    QToolTip::add( TextLabel2, tr( "Number of nodes in the graph" ) );
    GenComboBox->clear();
    GenComboBox->insertItem( tr( "FITNESS" ) );
    GenComboBox->insertItem( tr( "BA" ) );
    GenComboBox->insertItem( tr( "MINIMUM GROWTH" ) );
    GenComboBox->insertItem( tr( "GEO NET" ) );
    QToolTip::add( GenComboBox, tr( "Algorithm used to generate the network" ) );
    TextLabel1_5->setText( tr( "Generating algorithm" ) );
    GroupBox3->setTitle( tr( "Fitness model" ) );
    GroupBox4->setTitle( tr( "Fitness pdd" ) );
    QToolTip::add( GroupBox4, QString::null );
    FitnessComboBox->clear();
    FitnessComboBox->insertItem( tr( "Uniform" ) );
    FitnessComboBox->insertItem( tr( "Exponential" ) );
    FitnessComboBox->insertItem( tr( "Gaussian" ) );
    FitnessComboBox->insertItem( tr( "Power" ) );
    FitnessComboBox->insertItem( tr( "User" ) );
    QToolTip::add( FitnessComboBox, tr( "Shape of fitness probability distribution" ) );
    BParameter->setText( tr( "1.0" ) );
    TextLabel6->setText( tr( "A" ) );
    QToolTip::add( TextLabel6, tr( "Parameter for the distribution above" ) );
    TextLabel1_4->setText( tr( "B" ) );
    QToolTip::add( TextLabel1_4, tr( "Parameter for the distribution above" ) );
    AParameter->setText( tr( "0.0" ) );
    GroupBox5->setTitle( tr( "Linking probability" ) );
    LinkComboBox->clear();
    LinkComboBox->insertItem( tr( "Theta 1" ) );
    LinkComboBox->insertItem( tr( "Theta 2" ) );
    LinkComboBox->insertItem( tr( "X*Y" ) );
    LinkComboBox->insertItem( tr( "User 1" ) );
    LinkComboBox->insertItem( tr( "User 2" ) );
    LinkComboBox->insertItem( tr( "User 3" ) );
    QToolTip::add( LinkComboBox, tr( "Linking probability function" ) );
    TextLabel6_2_2->setText( tr( "E" ) );
    QToolTip::add( TextLabel6_2_2, QString::null );
    EParameter->setText( tr( "0.0" ) );
    TextLabel6_2->setText( tr( "Z" ) );
    QToolTip::add( TextLabel6_2, tr( "usually used as cut-off in the linking probability" ) );
    MParameter->setText( tr( "0.005" ) );
    TextLabel6_3->setText( tr( "M" ) );
    QToolTip::add( TextLabel6_3, tr( "Probability of successfull connections per node" ) );
    CutOffParameter->setText( tr( "0.0" ) );
    AcyclicRadioButton->setText( tr( "Acyclic" ) );
    QToolTip::add( AcyclicRadioButton, tr( "Forces the generation of acyclic graphs (no triangles)" ) );
    TreeRadioButton->setText( tr( "Tree" ) );
    QToolTip::add( TreeRadioButton, tr( "Forces the generation of a tree" ) );
    GroupBox6->setTitle( tr( "BA model" ) );
    QToolTip::add( BA_N0, tr( "Initial clique order" ) );
    TextLabel2_2->setText( tr( "M" ) );
    TextLabel1_6->setText( tr( "N0" ) );
    QToolTip::add( BA_M, tr( "Number of incoming links" ) );
    textLabel1_2->setText( tr( "Memory" ) );
    textLabel2_2->setText( tr( "B" ) );
    BAMemoryB->setText( tr( "0.0" ) );
    QToolTip::add( BAMemoryB, tr( "Memory Kernel = (B>=0)? pow(t+A, -B): exp(-t/A)" ) );
    BAMemoryA->setText( tr( "0.0" ) );
    QToolTip::add( BAMemoryA, tr( "Memory Kernel parameter A (Tau)" ) );
    textLabel2->setText( tr( "A (Tau)" ) );
    groupBox7->setTitle( tr( "2D Geo Net" ) );
    GeoNetTypeComboBox->clear();
    GeoNetTypeComboBox->insertItem( tr( "1 RADIUS" ) );
    GeoNetTypeComboBox->insertItem( tr( "2 RADII" ) );
    GeoNetTypeComboBox->insertItem( tr( "UNIF" ) );
    GeoNetTypeComboBox->insertItem( tr( "EXP" ) );
    GeoNetTypeComboBox->insertItem( tr( "BPL" ) );
    QToolTip::add( GeoNetTypeComboBox, tr( "Distribution of radii" ) );
    TextLabel1_6_2_3->setText( tr( "P(Rmin)" ) );
    TextLabel1_6_2_2->setText( tr( "Rmax" ) );
    TextLabel1_6_2->setText( tr( "Rmin" ) );
    QToolTip::add( TextLabel1_6_2, QString::null );
    GeoProbRmin->setText( tr( "0.5" ) );
    QToolTip::add( GeoProbRmin, tr( "the prob of getting Rmin in case RADII" ) );
    GeoRmin->setText( tr( "0.01" ) );
    QToolTip::add( GeoRmin, tr( "usually the minimum radius" ) );
    GeoRmax->setText( tr( "0.011" ) );
    QToolTip::add( GeoRmax, tr( "usually the maximum radius" ) );
    GroupBox2->setTitle( tr( "Output Control" ) );
    DegreeDistribRadioButton->setText( tr( "Degree Distribution" ) );
    QToolTip::add( DegreeDistribRadioButton, tr( "Calculate the Degree Distribution" ) );
    KnnRadioButton->setText( tr( "NN Connectivity" ) );
    QToolTip::add( KnnRadioButton, tr( "Calculate the nearest neighbour connectivity" ) );
    ClusterCoeffRadioButton->setText( tr( "Clustering Coefficient" ) );
    QToolTip::add( ClusterCoeffRadioButton, tr( "Calculate the Clustering coefficient up to nearest neighbours" ) );
    ClusterCoeff2RadioButton->setText( tr( "Clustering Coefficient 2" ) );
    QToolTip::add( ClusterCoeff2RadioButton, tr( "Calculate the Clustering coefficient up to 2nd neighbours" ) );
    SCCRadioButton->setText( tr( "SCC" ) );
    QToolTip::add( SCCRadioButton, tr( "Find the Strongly Connected Components of a directed graph" ) );
    CommunityRadioButton->setText( tr( "Communities" ) );
    QToolTip::add( CommunityRadioButton, tr( "Calculate the community size distribution" ) );
    SplitClusterRadioButton->setText( tr( "Split Cluster" ) );
    QToolTip::add( SplitClusterRadioButton, tr( "Save found clusters onto separate files" ) );
    SaveClusterRadioButton->setText( tr( "Save Cluster" ) );
    QToolTip::add( SaveClusterRadioButton, tr( "Calculate the cluster size each node is belonging to" ) );
    EdgeBetweenRadioButton->setText( tr( "Edge Betweenness" ) );
    QToolTip::add( EdgeBetweenRadioButton, tr( "Calculates the edge betweeness" ) );
    SiteBetweenRadioButton->setText( tr( "Site Betweenness (SB)" ) );
    QToolTip::add( SiteBetweenRadioButton, tr( "Calculates the site betweeness" ) );
    RWBetweenComboBox->clear();
    RWBetweenComboBox->insertItem( tr( "none" ) );
    RWBetweenComboBox->insertItem( tr( "conductance" ) );
    RWBetweenComboBox->insertItem( tr( "resistance" ) );
    QToolTip::add( RWBetweenComboBox, tr( "Calculate the random walk site betweenness" ) );
    textLabel1->setText( tr( "RW SB" ) );
    PairDistRadioButton->setText( tr( "Pair Distance" ) );
    QToolTip::add( PairDistRadioButton, tr( "Save pairs with their distance" ) );
    SelfLoopsRadioButton->setText( tr( "Self Loops" ) );
    QToolTip::add( SelfLoopsRadioButton, tr( "Allow self loops" ) );
    AMatrixComboBox->clear();
    AMatrixComboBox->insertItem( tr( "No Matrix" ) );
    AMatrixComboBox->insertItem( tr( "Adjacency: A" ) );
    AMatrixComboBox->insertItem( tr( "Laplacian: D-A" ) );
    AMatrixComboBox->insertItem( tr( "Normal: 1/D*A" ) );
    QToolTip::add( AMatrixComboBox, tr( "Find Eigenvectors and Eigenvalues of a graph associated matrix" ) );
    LanczosCheckBox->setText( tr( "Lanczos" ) );
    QToolTip::add( LanczosCheckBox, tr( "Diagonalize matrices using lanczos routines" ) );
    RewiringSpinBox->setSpecialValueText( tr( "none" ) );
    QToolTip::add( RewiringSpinBox, tr( "Performs the requested nr of rewirings preserving node degree" ) );
    TextLabel1_7_2->setText( tr( "Rewiring" ) );
    ReductionSpinBox->setSpecialValueText( tr( "none" ) );
    QToolTip::add( ReductionSpinBox, tr( "Reduces the net to that number of nodes (still an experimental feature)" ) );
    TextLabel1_7->setText( tr( "Reduction" ) );
    groupBox9->setTitle( tr( "Folksonomies" ) );
    TASreshufCheckBox->setText( tr( "TAS reshuffle" ) );
    TASreshufCheckBox->setAccel( QKeySequence( QString::null ) );
    QToolTip::add( TASreshufCheckBox, tr( "Reshuffles a Tag ASsignment file" ) );
    textLabel1_3->setText( tr( "Number of Posts" ) );
    QToolTip::add( TASRW, tr( "number of posts to be generated with the random walker on the network" ) );
    GroupBox3_2->setTitle( tr( "Data Manage" ) );
    SaveNetComboBox->clear();
    SaveNetComboBox->insertItem( tr( "No Net Save" ) );
    SaveNetComboBox->insertItem( tr( "Save .net" ) );
    SaveNetComboBox->insertItem( tr( "Save .paj" ) );
    SaveNetComboBox->setCurrentItem( 1 );
    QToolTip::add( SaveNetComboBox, tr( "Save link sequence in a .net or .paj file" ) );
    XmGraceComboBox->clear();
    XmGraceComboBox->insertItem( tr( "No XmGrace" ) );
    XmGraceComboBox->insertItem( tr( "Log-Log" ) );
    XmGraceComboBox->insertItem( tr( "Lin-Lin" ) );
    QToolTip::add( XmGraceComboBox, tr( "Run XmGrace at the end" ) );
    ShowComboBox->clear();
    ShowComboBox->insertItem( tr( "Do not show" ) );
    ShowComboBox->insertItem( tr( "DOT format" ) );
    ShowComboBox->insertItem( tr( "GML format" ) );
    QToolTip::add( ShowComboBox, tr( "Show the network on screen" ) );
    OutFileCheckBox->setText( tr( "STDOUT onto file" ) );
    OutFileCheckBox->setAccel( QKeySequence( QString::null ) );
    QToolTip::add( OutFileCheckBox, tr( "Send standard output also onto file =ProjName.out" ) );
    SaveQuitPushButton->setText( tr( "&Save && Quit" ) );
    QToolTip::add( SaveQuitPushButton, tr( "Save the ini file and quit" ) );
    SavePushButton->setText( tr( "Save" ) );
    QToolTip::add( SavePushButton, tr( "Only save the ini file" ) );
    SaveRunPushButton->setText( tr( "Save && &Run" ) );
    SaveRunPushButton->setAccel( QKeySequence( tr( "Alt+R" ) ) );
    QToolTip::add( SaveRunPushButton, tr( "Save the ini file and run the program" ) );
    QuitPushButton->setText( tr( "&Quit" ) );
    QToolTip::add( QuitPushButton, tr( "Quit without saving" ) );
    TextLabel5->setText( tr( "by VDPS" ) );
    QToolTip::add( TextLabel5, tr( "Vito D.P. Servedio - October 2005" ) );
}

