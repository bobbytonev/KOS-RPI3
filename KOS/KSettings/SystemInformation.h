


#include <QObject>
#include <QVariantList>
#include <QDebug>
#include <QFile>
#include <QStringList>
#include <QRegularExpression>
#include <QStorageInfo>

class SystemInformation : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QStringList info READ info WRITE setInfo NOTIFY infoChanged)


public:
    QString getKernelVersion() {
         QFile inputFile(QString("/proc/version"));
		 
         inputFile.open(QIODevice::ReadOnly);

         if (!inputFile.isOpen()){
			 
            return NULL;
		 }
         QTextStream in(&inputFile);

         QString line =in.readLine();
		 
       
         QRegularExpression re("version (.*?) ");
         QRegularExpressionMatch match = re.match(line);
		 return match.captured(1);
        
	}
	
	  QStringList getCpuInformaton() {
         QFile inputFile(QString("/proc/cpuinfo"));
         inputFile.open(QIODevice::ReadOnly);



         QString tp;
         QString delimiter = ":";
         QStringList infoNames = {"model name","cpu MHz","cache size"};
         QStringList info;
         int index = 0;
         QTextStream in(&inputFile);

         do {
    
		tp=in.readLine();  
		
                 if (tp[0] == '\n' || tp[0]=='\0'||index>2)
                     break;
                 
				 if (tp.startsWith(infoNames[index])) {
                        info<<tp.split(":").at(1);
                        index++;
						
                 }

            

          inputFile.close();
		} while (!tp.isNull());
			
		  
		  return info;
     }

     QStringList getRamInformaton() {
         QFile inputFile(QString("/proc/meminfo"));
         inputFile.open(QIODevice::ReadOnly);

		
       
         QStringList info;

        QTextStream in(&inputFile);
		QString number1 =in.readLine().split(":").at(1);
		number1 = number1.simplified();
		number1.replace( " ", "" );
		
		
		
		QString number2 =in.readLine().split(":").at(1);
		number2 = number2.simplified();
		number2.replace( " ", "" );
		
		
		info<< QString::number(number1.split("kB")[0].toDouble()*0.000001,'f',1)+"GB"<<QString::number(number2.split("kB")[0].toDouble()*0.000001,'f',1)+"GB";
		

        inputFile.close();
		
		return info;
     }

  Q_INVOKABLE QStringList storageInfo(){
	  QStorageInfo storage = QStorageInfo::root();
	  QStringList list;
      //qDebug() << storage.rootPath();
	  list.append(storage.rootPath());
      //if (storage.isReadOnly())
         // qDebug() << "isReadOnly:" << storage.isReadOnly();
		list.append(QString::number(storage.isReadOnly()));
		list.append(storage.fileSystemType());
        list.append( QString::number(storage.bytesTotal()/1000/1000/1000));
        list.append( QString::number(storage.bytesAvailable()/1000/1000/1000));
		return list;
  }
	

    Q_INVOKABLE QStringList reload(){

        QStringList info;
		
		
		info<<getRamInformaton()<<getCpuInformaton();
        info<<getKernelVersion();
		setInfo(info);
        return info;

    }
    void setInfo(const QStringList &a) {
        if (a != m_info) {
            m_info = a;
            emit infoChanged();
        }
    }
   QStringList info() const {
        return m_info;
    }
signals:
    void infoChanged();
private:
    QStringList m_info;
};



