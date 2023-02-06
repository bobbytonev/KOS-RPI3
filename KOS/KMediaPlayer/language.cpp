#include "language.h"

Language::Language(QQmlEngine* engine)
{
    translator =new QTranslator(this);
    m_engine=engine;
}

Language::~Language()
{
    if(translator !=NULL){
        delete translator;
    }
}
QString Language::language()
{
    return m_language;
}


void Language::setLanguage(const QString language)
{
    if(m_language!=language) {
        m_language=language;


        QDBusMessage m = QDBusMessage::createMethodCall("com.kos.stylemanager","/Language","","setLanguage");
        QList<QVariant> args;
        args << m_language;
        m.setArguments(args);
        QDBusConnection::systemBus().call(m);

        installNewTransition(m_language);
        emit languageChanged(m_language);

    }
}

void Language::init()
{
    QDBusMessage m = QDBusMessage::createMethodCall("com.kos.stylemanager","/Language","","getLanguage");
    QDBusMessage response = QDBusConnection::systemBus().call(m);


    QList<QVariant> list =response.arguments();
    if(!list.isEmpty()){
        m_language = list.at(0).toString();
        installNewTransition(m_language);



    }

    QDBusConnection conn = QDBusConnection::connectToBus(QDBusConnection::SystemBus,"com.kos.stylemanager");
    conn.connect("", "/Language", "com.kos.stylemanager","languageChanged",this,SLOT(updateLanguage(QString)));

}

void Language::installNewTransition(QString language)
{
    translator->load(LANGUAGE_FOLDER+language);
    qApp->installTranslator(translator);
    m_engine->retranslate();

}

void Language::updateLanguage(QString language)
{

    if(m_language != language){
        m_language=language;
       installNewTransition(m_language);
        emit languageChanged(m_language);
    }



}


