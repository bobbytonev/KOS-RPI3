#include "volumelistener.h"
#include <QDebug>
VolumeListener::VolumeListener()
{

}

void VolumeListener::run()
{

    snd_ctl_t *handle;

    if(open_ctl(&handle) == 0){

        while(true){
            this->msleep(10);
            run_events(handle);
        }
        snd_ctl_close(handle);

    }


}

int VolumeListener::open_ctl(snd_ctl_t **ctlp)
{

    snd_ctl_t *ctl;
    int err;

    err = snd_ctl_open(&ctl,card,SND_CTL_READONLY);
    if(err < 0){
        return -1;
    }
    err = snd_ctl_subscribe_events(ctl,1);
    if(err < 0){
        snd_ctl_close(ctl);
        return -2;

    }
    *ctlp = ctl;
    return 0;

}

void VolumeListener::run_events(snd_ctl_t *ctl)
{

    snd_ctl_event_t *event;
    unsigned int mask;
    int err;
    snd_ctl_event_alloca(&event);
    err = snd_ctl_read(ctl,event);
    if(err < 0) return;
    if(snd_ctl_event_get_type(event) != SND_CTL_EVENT_ELEM) return;
    mask = snd_ctl_event_elem_get_mask(event);
    if(mask & SND_CTL_EVENT_MASK_VALUE){
        emit volumeChanged();
    }


}
