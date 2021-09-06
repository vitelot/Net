/****************************************************************************
** Form interface generated from reading ui file 'netiniform.ui'
**
** Created: Thu May 16 12:20:53 2013
**
** WARNING! All changes made in this file will be lost!
****************************************************************************/

#ifndef NETINIFORM_H
#define NETINIFORM_H

#include <qvariant.h>
#include <qdialog.h>
#include "Version.h"

class QVBoxLayout;
class QHBoxLayout;
class QGridLayout;
class QSpacerItem;
class QLabel;
class QLineEdit;
class QCheckBox;
class QSpinBox;
class QComboBox;
class QGroupBox;
class QRadioButton;
class QPushButton;

class NetIniForm : public QDialog
{
    Q_OBJECT

public:
    NetIniForm( QWidget* parent = 0, const char* name = 0, bool modal = FALSE, WFlags fl = 0 );
    ~NetIniForm();

    QLabel* TextLabel4;
    QLabel* TextLabel1;
    QLineEdit* ProjectName;
    QCheckBox* ReadNetCheckBox;
    QCheckBox* NetTypeCheckBox;
    QCheckBox* WeightedCheckBox;
    QCheckBox* TASCheckBox;
    QSpinBox* MultiSpinBox;
    QLabel* TextLabel1_2;
    QLabel* TextLabel2;
    QComboBox* GenComboBox;
    QSpinBox* GraphOrder;
    QLabel* TextLabel1_5;
    QGroupBox* GroupBox3;
    QGroupBox* GroupBox4;
    QComboBox* FitnessComboBox;
    QLineEdit* BParameter;
    QLabel* TextLabel6;
    QLabel* TextLabel1_4;
    QLineEdit* AParameter;
    QGroupBox* GroupBox5;
    QComboBox* LinkComboBox;
    QLabel* TextLabel6_2_2;
    QLineEdit* EParameter;
    QLabel* TextLabel6_2;
    QLineEdit* MParameter;
    QLabel* TextLabel6_3;
    QLineEdit* CutOffParameter;
    QRadioButton* AcyclicRadioButton;
    QRadioButton* TreeRadioButton;
    QGroupBox* GroupBox6;
    QSpinBox* BA_N0;
    QLabel* TextLabel2_2;
    QLabel* TextLabel1_6;
    QSpinBox* BA_M;
    QLabel* textLabel1_2;
    QLabel* textLabel2_2;
    QLineEdit* BAMemoryB;
    QLineEdit* BAMemoryA;
    QLabel* textLabel2;
    QGroupBox* groupBox7;
    QComboBox* GeoNetTypeComboBox;
    QLabel* TextLabel1_6_2_3;
    QLabel* TextLabel1_6_2_2;
    QLabel* TextLabel1_6_2;
    QLineEdit* GeoProbRmin;
    QLineEdit* GeoRmin;
    QLineEdit* GeoRmax;
    QGroupBox* GroupBox2;
    QRadioButton* DegreeDistribRadioButton;
    QRadioButton* KnnRadioButton;
    QRadioButton* ClusterCoeffRadioButton;
    QRadioButton* ClusterCoeff2RadioButton;
    QRadioButton* SCCRadioButton;
    QRadioButton* CommunityRadioButton;
    QRadioButton* SplitClusterRadioButton;
    QRadioButton* SaveClusterRadioButton;
    QRadioButton* EdgeBetweenRadioButton;
    QRadioButton* SiteBetweenRadioButton;
    QComboBox* RWBetweenComboBox;
    QLabel* textLabel1;
    QRadioButton* PairDistRadioButton;
    QRadioButton* SelfLoopsRadioButton;
    QComboBox* AMatrixComboBox;
    QCheckBox* LanczosCheckBox;
    QSpinBox* RewiringSpinBox;
    QLabel* TextLabel1_7_2;
    QSpinBox* ReductionSpinBox;
    QLabel* TextLabel1_7;
    QGroupBox* groupBox9;
    QCheckBox* TASreshufCheckBox;
    QLabel* textLabel1_3;
    QSpinBox* TASRW;
    QGroupBox* GroupBox3_2;
    QComboBox* SaveNetComboBox;
    QComboBox* XmGraceComboBox;
    QComboBox* ShowComboBox;
    QCheckBox* OutFileCheckBox;
    QPushButton* SaveQuitPushButton;
    QPushButton* SavePushButton;
    QPushButton* SaveRunPushButton;
    QPushButton* QuitPushButton;
    QLabel* TextLabel5;

public slots:
    virtual void Save();
    virtual void SaveQuit();
    virtual void SaveRun();
    virtual void SaveIniFile();

protected:
    QVBoxLayout* NetIniFormLayout;
    QSpacerItem* Spacer26;
    QSpacerItem* Spacer23_2;
    QHBoxLayout* layout36;
    QSpacerItem* Spacer13;
    QSpacerItem* Spacer13_2;
    QHBoxLayout* layout37;
    QHBoxLayout* layout36_2;
    QHBoxLayout* layout35;
    QSpacerItem* Spacer5;
    QSpacerItem* Spacer3;
    QSpacerItem* Spacer9;
    QHBoxLayout* layout38;
    QHBoxLayout* layout38_2;
    QVBoxLayout* layout41;
    QSpacerItem* Spacer23_2_2;
    QGridLayout* layout73;
    QHBoxLayout* layout41_2;
    QVBoxLayout* layout33;
    QVBoxLayout* layout56;
    QGridLayout* layout55;
    QVBoxLayout* layout32;
    QGridLayout* layout31;
    QHBoxLayout* layout43;
    QSpacerItem* Spacer19;
    QSpacerItem* Spacer19_2;
    QVBoxLayout* layout70;
    QVBoxLayout* layout39;
    QVBoxLayout* layout38_3;
    QSpacerItem* spacer33;
    QHBoxLayout* layout41_3;
    QSpacerItem* Spacer19_2_3;
    QSpacerItem* Spacer19_2_2;
    QGridLayout* layout39_2;
    QGridLayout* layout37_2;
    QVBoxLayout* layout52;
    QGridLayout* layout44;
    QVBoxLayout* layout37_3;
    QSpacerItem* Spacer25_2;
    QSpacerItem* Spacer25;
    QHBoxLayout* layout35_2;
    QSpacerItem* spacer28;
    QHBoxLayout* layout31_2;
    QHBoxLayout* layout42;
    QSpacerItem* Spacer4;
    QHBoxLayout* layout43_2;
    QSpacerItem* Spacer7;
    QSpacerItem* Spacer4_3_5;
    QHBoxLayout* layout36_3;
    QHBoxLayout* layout44_2;
    QVBoxLayout* layout36_4;
    QSpacerItem* Spacer10_3;
    QSpacerItem* Spacer10;
    QSpacerItem* Spacer5_2;
    QSpacerItem* Spacer10_2;
    QVBoxLayout* groupBox9Layout;
    QHBoxLayout* layout35_3;
    QGridLayout* layout58;
    QSpacerItem* spacer24_4;
    QSpacerItem* spacer24_6;
    QSpacerItem* spacer24_5;
    QSpacerItem* spacer24_8;
    QSpacerItem* spacer24_7;
    QSpacerItem* spacer24;
    QSpacerItem* spacer24_4_3;
    QSpacerItem* spacer24_4_2;
    QHBoxLayout* layout58_2;
    QSpacerItem* spacer24_3;
    QSpacerItem* spacer24_2;
    QHBoxLayout* layout50;
    QSpacerItem* Spacer12;

protected slots:
    virtual void languageChange();

};

#endif // NETINIFORM_H
