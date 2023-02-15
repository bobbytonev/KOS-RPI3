#include <QDBusInterface>
#include <QDBusMessage>
#include <QDBusArgument>
#include <QDBusObjectPath>
#include <QDebug>


class NetworkManager : public QObject
{
    Q_OBJECT
    Q_PROPERTY(bool wifi READ wifi WRITE setWifi NOTIFY wifiAvailabilityChanged)
	
	 Q_PROPERTY(bool bluetooth READ bluetooth WRITE setBluetooth NOTIFY bluetoothAvailabilityChanged)
	
	public:
	
	
	
	
	Q_INVOKABLE void requestNetworkAvailability(){
		
		if(runOnce){
		runOnce=false;

	QDBusInterface NetworkManager("org.freedesktop.NetworkManager",     
                      "/org/freedesktop/NetworkManager",
                      "org.freedesktop.NetworkManager",
                      QDBusConnection::systemBus());
    if(!NetworkManager.isValid())
    {
       // setWifi(false);
		//setBluetooth(false);
		 return;
    }

    QDBusMessage DbusMsg = NetworkManager.call("GetDevices"); 
	QDBusArgument DbusArg = DbusMsg.arguments().at(0).value<QDBusArgument>();
    if(DbusArg.currentType() != QDBusArgument::ArrayType)
    {
          //setwifi(false);
		  //setbluetooth(false);
		   return;
    }
    QList<QDBusObjectPath> pathsLst = qdbus_cast<QList<QDBusObjectPath>>(DbusArg);
    foreach(QDBusObjectPath DbusObjectPath, pathsLst)
    {
        QDBusInterface device("org.freedesktop.NetworkManager",       
                              DbusObjectPath.path(),
                              "org.freedesktop.NetworkManager.Device",
                              QDBusConnection::systemBus());
		int deviceType = device.property("DeviceType").toInt();
		
        if( deviceType == 2 ){ setWifi(true);}
		else if( deviceType == 5 ) setBluetooth(true);
		
		
    }
	

	}
		
		
	}
	
	
	void setWifi(const bool &a) {
        if (a != m_wifi) {
            m_wifi = a;
            emit wifiAvailabilityChanged();
        }
    }
   bool wifi() const {

        return m_wifi;
    }
	
	
	void setBluetooth(const bool &a) {
        if (a != m_bluetooth) {
            m_bluetooth = a;
            emit bluetoothAvailabilityChanged();
        }
    }
   bool bluetooth() const {
        return m_bluetooth;
    }



signals:
    void wifiAvailabilityChanged();
	void bluetoothAvailabilityChanged();


private:
    bool m_wifi=false;
	
	bool m_bluetooth=false;
	
	bool runOnce=true;
	
};
