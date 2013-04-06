#include "maincontroler.h"
#include "app.h"

int main(int argc, char *argv[])
{
    App a(argc, argv);
    MainControler controler;
    controler.start();
    
    return a.exec();
}
