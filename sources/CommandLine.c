#include "main.h"
#include "extern.h"

#include <string.h>

static void PrintShortHelp(void);

void ScanCommandLineParams( int argc, char *argv[], char *inifile)
{
  sprintf( In.projname, "net"); /* default Project Name */

  while( argc--) { /* scan command line params */
    if( *argv[argc]=='-') { /* found an option */
      switch(*(++argv[argc])) { /* char after the minus */
      case 'p': /* project name */
	if( strlen(argv[argc+1])) { /* next there is the string */
	  sprintf( In.projname, argv[argc+1]);
	  printf("Project name changed into \"%s\" from command line parameters\n\n",
		 In.projname);
	  sprintf( inifile, "+%s.INI", In.projname);
	  printf("INI file name changed into \"%s\" from command line parameters\n\n",
		 inifile);
	}
	break;
      case 'x':
	system("NetIni");
	exit(0);
	break;
      case 'h':
	PrintShortHelp();
	break;
      default:
	break;
      }
    }
  }
}

static void PrintShortHelp(void)
{
  printf("Short help:\n");
  printf(" flags:\n"
	 "   -p name : uses name as project name.\n"
	 "   -x : runs the graphical interface.\n"
	 "   -h : print this help and exit.\n"
	 );
  
  exit(0);	
}
