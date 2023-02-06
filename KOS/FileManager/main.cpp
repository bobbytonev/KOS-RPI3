#include <QCoreApplication>
#include <kfilemanager.h>
int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);


    KFileManager file;
    return a.exec();
}
