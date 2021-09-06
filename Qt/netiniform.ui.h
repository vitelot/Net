/****************************************************************************
** ui.h extension file, included from the uic-generated form implementation.
**
** If you wish to add, delete or rename slots use Qt Designer which will
** update this file, preserving your code. Create an init() slot in place of
** a constructor, and a destroy() slot in place of a destructor.
*****************************************************************************/
#include <fstream>
#include "Version.h"
#include <cstdlib>

void NetIniForm::Save()
{
    SaveIniFile();
}

void NetIniForm::SaveQuit()
{
    SaveIniFile();
}

void NetIniForm::SaveRun()
{
    SaveIniFile();
    if(OutFileCheckBox->isChecked()) {
      char cmd[128];
      sprintf(cmd,"Net.Linux | tee =%s.out &", ProjectName->text().ascii());
      system(cmd);
    } else {
	system("Net.Linux &");
    }
}

void NetIniForm::SaveIniFile()
{
/*    fstream ini; */
/*    ini.open("NET.INI", ios::out); */
    using namespace std;
    char cmd[128];
 ofstream ini("NET.INI");

  ini << "############################################################################\n"
         "### NET's initialization file, created by NetIni  #######################################\n"
         "############################################################################\n"
	 " VERSION " << VERSION << "                      #######################################\n"
          "############################################################################\n"
        "# Use the flag -h to have a list of command line options\n"
         "################### Master parameters ######################################\n"
	 "#\n";

    
    ini << " NK         =   "<< GraphOrder->value() <<"                # Number of nodes\n"; 
    
    ini << "# The following three fields select the random distribution of fitnesses:\n"
	   "#   0: Uniform [ x in (A,B) ]\n"
	   "#   1: Exponential [ A*exp(-A*x), x>0 ]\n"
	   "#   2: Gaussian [ (2*Pi*A^2)^-0.5*exp(-x^2/2A^2), x>0 ]\n"
	   "#   3: Power [ c*x^-A if x>B,  c*B^-A if x<=B ] \n"
	   "#\n";
    ini << " DISTRIB    =   " << FitnessComboBox->currentItem() << "\n"
	   "   A        =   " << AParameter->text() << "               # Parameter for the distribution above\n"
 	   "   B        =   " << BParameter->text() << "               # Another parameter for the distribution above\n"
           " LINKTYPE   =   " << LinkComboBox->currentItem() << "               # Linking probability function\n"
	   "   Z        =   " << CutOffParameter->text() << "               # Cutoff in the linking probability\n"
	   "   M        =   " << MParameter->text() << "              # Probability of successfull connections per node\n"
	   "   E        =   " << EParameter->text() << "              # Parameter in the linking prob (like kT in the Fermi distrib)\n"
                " TREE     =   " << ((TreeRadioButton->isChecked())?1:0) << "                 # Force the generation of tree graphs\n"	   
                " ACYCLIC     =   " << ((AcyclicRadioButton->isChecked())?1:0) << "                 # Force the generation of acyclic graphs\n"	   
	   "#\n";
    ini << "# The following two fields select BA parameters:\n"
    " BA_N0         =   "<< BA_N0->value() <<"                # Number of starting nodes\n"
    " BA_M          =   "<< BA_M->value() <<"                # Number of incoming links at each step\n"
     " BA_MEM_A    =   "<<BAMemoryA->text()<<"             # Memory kernel parameter: if <=0 plain B-A\n"
     " BA_MEM_B    =   "<<BAMemoryB->text()<<"            # Memory kernel = pow(t+A,-B) if B==0 plain B-A, if B<0 exp(-t/a)\n" 
	   "#\n";
    ini<< "# The following 4 lines define 2D Geog. Netw. parameters:\n"
     "#   0: fixed radius = GN_RMIN\n"
     "#   1: two radii GN_RMIN (with probability GN_P_RMIN) and GN_RMAX\n"
     "#   2: radii uniform distr between GN_RMIN and GN_RMAX\n"
     "#   3: radii centered exponential distr A*exp(-|x-b|/a)/a with a=GN_RMIN and b=GN_RMAX\n"
     "#   4: radii bounded power-law distr between GN_RMIN and GN_RMAX\n"
      "#\n";

    ini<<" GN_RDISTR  =   "<< GeoNetTypeComboBox->currentItem()<<"          # Distrib of radii\n"
     " GN_RMIN    =   "<<GeoRmin->text()<<"             # Minimum radius\n"
     " GN_RMAX    =   "<<GeoRmax->text()<<"            # Maximum radius\n"
     " GN_P_RMIN  =   "<<GeoProbRmin->text()<<"      # Prob. of GN_RMIN for case nr.1\n"
      "#\n";
    ini << "################### Basic control  #########################################\n"
           "#\n"
           " PROJNAME       =   " << ProjectName->text() << " 		# Project name\n"
            " NET_GENR      =   " << GenComboBox->currentItem() << "                 # 0=FITNESS, 1=BA, 2=MG\n"
            " NET_TYPE      =   " << ((NetTypeCheckBox->isChecked())?1:0) << "                 # 0=undirected, 1=directed\n"
            " WEIGHTED      =   " << ((WeightedCheckBox->isChecked())?1:0) << "                 # 0=unweighted, 1=weighted edges\n"
	" TASRW     =   " << TASRW->value() << "                 # number of posts to generate with the rw on the net.\n"  
	" TAS     =   " << ((TASCheckBox->isChecked())?1:0) << "                 # 1=file to be read is a TAS list (folksonomy)\n"  
             " SELFLOOPS     =   " << ((SelfLoopsRadioButton->isChecked())?1:0) << "                 # 1=Allow self loops\n"
         " MULTI           =   "<< MultiSpinBox->value() <<"                # Multiple runs\n"
           " READ_IN        =   " << ((ReadNetCheckBox->isChecked())?1:0) << "                 # Read net from file\n";

    ini << "################### Output control #########################################\n"
           " SAVE_NET       =   " << SaveNetComboBox->currentItem() << "                 # Save the resulting net onto file .net or .paj\n"
	   " SHOW_NET       =   " <<  ShowComboBox->currentItem() << "                 # Display the resulting net on screen 1=DOT 2=GML\n"
	   " RUN_GRACE      =   " << XmGraceComboBox->currentItem() << "                 # Open xmgrace at the end: 1=LOG-LOG 2=LIN-LIN\n"
           " TAS_RESHUF =   " << ((TASreshufCheckBox->isChecked())?1:0) <<"  		# 1=Reshuffles Tag ASsignments and exits.\n"
           " DEGREE_DISTRIB =   " << ((DegreeDistribRadioButton->isChecked())?1:0) <<"  		# Calculates and saves the degree distrib\n"
	   " KNN            =   " << ((KnnRadioButton->isChecked())?1:0) <<"  		# Calculates and saves the nearest neighs connectivity\n"
	   " CLUSTER_COEFF  =   " << ((ClusterCoeffRadioButton->isChecked())?1:0) <<"  		# Calculates and saves the clustering coeff\n"
	   " CLUSTER_COEFF2 =   " << ((ClusterCoeff2RadioButton->isChecked())?1:0) <<"  		# Calculates and saves the clustering coeff up to 2nd neighs\n"
	   " COMMUNITIES    =   " << ((CommunityRadioButton->isChecked())?1:0) <<"  		# Calculates the community size distribution\n"
	   " SCC                    =   " << ((SCCRadioButton->isChecked())?1:0) <<"  		# Finds the Strongly Connected Component of a directed graph\n"
	   " REDUCTION      =   " << ReductionSpinBox->value() <<"  		# Reduce the net to that nr of nodes\n"
	   " REWIRING     =   " << RewiringSpinBox->value() <<"  		# nr of rewirings preserving node degrees\n"
	   " AMATRIX        =   " << AMatrixComboBox->currentItem() <<"  		# Calculates eigenvalues and eigenvectors of graph associated matrices\n"
	   " LANCZOS        =   " << LanczosCheckBox->isChecked() <<"  		# Calculates eigenvalues and eigenvectors using lanczos routines\n"
	   " EDGE_BETWEEN   =   " << ((EdgeBetweenRadioButton->isChecked())?1:0) <<"  		# Calculates and saves the edge betweenness\n"
	   " SITE_BETWEEN   =   " << ((SiteBetweenRadioButton->isChecked())?1:0) <<"  		# Calculates and saves the site betweenness\n"
	   " RW_SITE_BETW   =   " << RWBetweenComboBox->currentItem() <<"  		# Calculates and saves the random walk site betweenness\n"
	   " PAIR_DISTANCE  =   " << ((PairDistRadioButton->isChecked())?1:0) << "             # Save pairs and their distance\n"
	   " SAVE_CLUSTER   =   " << ((SaveClusterRadioButton->isChecked())?1:0) << "             # Save the node cluster sizes\n"
	   " SPLIT_CLUSTER  =   " << ((SplitClusterRadioButton->isChecked())?1:0) << "             # Save found clusters onto separate files\n"
	   "#\n"
	   "######################## END ###############################################\n";

    ini.close();
 sprintf(cmd, "cp NET.INI +%s.INI", ProjectName->text().ascii());
 system(cmd);
}
