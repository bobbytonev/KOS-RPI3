

#include <QObject>
#include <QVariantList>
#include <QSettings>
#include <QQuickStyle>
#include <QDebug>
#include <QProcess>

#include <thread>
#include <iostream>
#include <QFile>
#include <QTimeZone>
class process : public QObject
{
    Q_OBJECT
    Q_PROPERTY(bool finish READ finish WRITE isFinished NOTIFY finishedChanged)


 Q_PROPERTY(QStringList timeZone READ timeZone WRITE setTimeZone NOTIFY timeZoneChanged)



const QString STARTUP_APPS = "/etc/xdg/autostart";
public:

 Q_INVOKABLE void changeTime(QString time){
	QProcess::startDetached("sudo timedatectl set-time \""+time+"\"");
   
 }
  Q_INVOKABLE void automaticTimeZone(QString flag){
	
	
	QProcess::startDetached("sudo timedatectl set-ntp "+flag);
	
}

	
 
 Q_INVOKABLE void startProcess(QString process){
	
	
	QProcess::startDetached(process);
	
	
   
 }
   
   
   Q_INVOKABLE void reloadTimeZones(){
	   m_timeZones.clear();
	   QList<QByteArray> timeZoneIds  = QTimeZone::availableTimeZoneIds();
	  for (int i = 0; i<timeZoneIds.length(); i++){
               
               //qDebug()<<dt;
                m_timeZones.append(timeZoneIds.at(i));
       }
	   
	      emit timeZoneChanged();
	   
	   
	}
   
   Q_INVOKABLE void eval(QString process,QString name,QString fileName){

isFinished(false);
bool pacman=false;
  
  if(process.contains("pacman",Qt::CaseInsensitive)){
	QFile file("/var/lib/pacman/db.lck");
	if(file.exists())
	   file.remove();
   
   pacman=true;
  }
  
  
	
    QProcess proc ;
	proc.start(process);
    proc.waitForFinished();
	
	
	
	if(pacman){
	QSettings settings(QSettings::NativeFormat,QSettings::UserScope,"kos-default-apps", "Apps");
	settings.beginGroup("Apps");
	QStringList childKeys = settings.childKeys();
          foreach (const QString &childKey, childKeys){
          QVariant var(settings.value(childKey));
			
			if(QString::compare(var.toString().split(",")[0],name , Qt::CaseInsensitive)==0){
				settings.setValue(childKey,"");
				
				
			}
            
          }
		   
			settings.sync();
             settings.endGroup();
			 
		QFile dir;
			dir.remove("/etc/xdg/autostart/"+fileName);
			 
	} 
	
	
			 
	
	isFinished(true);
	proc.close();
	
	
	
//});
//ptr->join();

//delete ptr;

//QProcess process;
//process.start(proc);
//isFinished(process.waitForFinished(3000));

//emit finishedChanged();
//process.close();


    }
    void setTimeZone(const QStringList  &a) {
        if (a != m_timeZones) {
            m_timeZones = a;
            emit timeZoneChanged();
        }
    }
    QStringList timeZone() const {
        return m_timeZones;
    }
	
	
	void isFinished(const bool &a) {
        if (a != m_finish) {
            m_finish = a;
            emit finishedChanged();
        }
    }
   bool finish() const {
        return m_finish;
    }
	
signals:
    void finishedChanged();
	void timeZoneChanged();
	




private:
	QStringList m_timeZones;
    bool m_finish;
};


