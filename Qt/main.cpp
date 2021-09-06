#include <qapplication.h>
#include "netiniform.h"

int main( int argc, char ** argv )
{
    QApplication app( argc, argv );
    NetIniForm netiniForm;
    
    app.setMainWidget( &netiniForm );
    netiniForm.show();

    return app.exec();
}
