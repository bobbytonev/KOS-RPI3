#ifndef VOLUMELISTENER_H
#define VOLUMELISTENER_H

#include <QObject>
#include <QThread>
#include <alsa/asoundlib.h>
class VolumeListener : public QThread
{
    Q_OBJECT
public:
    VolumeListener();
    void run() override;
    int open_ctl(snd_ctl_t **ctlp);
    void run_events(snd_ctl_t *ctl);

signals:
    void volumeChanged();
private:
    const char* card ="default";
    const char* selem_name="Master";
 //const char* selem_name="Headphone";

};

#endif // VOLUMELISTENER_H
