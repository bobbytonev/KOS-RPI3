#include "durationsave.h"

DurationSave::DurationSave()
{

    connect(&dst,&DurationSaveThread::progressChanged,this,&DurationSave::setProgress);
}

int DurationSave::progress() const
{
    return m_progress;
}

void DurationSave::setSource(const QString &source)
{
    if(m_source != source){
        m_source = source;
        m_progress = 0;
        emit sourceChanged();
        dst.getProgress(m_source);
    }
}

QString DurationSave::source() const
{
    return m_source;
}

void DurationSave::setActive(const bool &active)
{
    if(m_active != active){
        m_active = active;
        emit activeChanged();

        if(active) dst.startThread();
        else dst.stopThread();
    }

}

bool DurationSave::active() const
{
    return m_active;
}

void DurationSave::saveProgress(int progress)
{
    dst.saveProgress(progress);
}

void DurationSave::setProgress(int progress)
{
    if(m_progress !=progress){
        m_progress=progress;
        emit progressChanged();
    }
}
