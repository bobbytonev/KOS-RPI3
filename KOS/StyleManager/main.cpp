#include <QGuiApplication>
#include "styles.h"
#include "language.h"

int main(int argc, char *argv[])
{

#if QT_VERSION < QT_VERSION_CHECK(6, 0, 0)
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
#endif


        QCoreApplication::setSetuidAllowed(true);
        QCoreApplication a(argc, argv);

        Styles styles;
        Language lang;
        return a.exec();




}
