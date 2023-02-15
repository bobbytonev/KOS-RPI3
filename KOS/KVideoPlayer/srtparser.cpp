#include "srtparser.h"


SrtParser::SrtParser()
{
    //positionChanged
    connect(this,SIGNAL(subFileChanged(QString,QString)),&thread,SLOT(openFile(QString,QString)));
    connect(this,SIGNAL(positionChanged(int)),&thread,SLOT(positionChanged(int)));
    connect(&thread,SIGNAL(subUpdated(QString)),this,SLOT(setSubtitle(QString)));
}

QString SrtParser::subtitle()
{
    return m_subtitle;
}

void SrtParser::setSubtitle(QString subtitle)
{

    if(m_subtitle != subtitle){
        m_subtitle = subtitle;

        emit subtitleChanged();
    }
}

QString SrtParser::subFile()
{
    return m_subFile;
}

void SrtParser::setSubFile(QString subtitle)
{


    if(m_subFile !=subtitle && !subtitle.isEmpty()){
        m_subFile = subtitle;

        emit subFileChanged(m_subFile,m_codec);
    }
}

int SrtParser::status()
{
    return m_status;
}

int SrtParser::videoPosition()
{
    return m_videoPosition;
}

void SrtParser::setVideoPosition(int videoPosition)
{
    if(m_videoPosition !=videoPosition){
        m_videoPosition = videoPosition;

        emit positionChanged(m_videoPosition);
    }
}

QString SrtParser::codec()
{
    return m_codec;
}

void SrtParser::setCodec(QString codec)
{
    if(m_codec !=codec){
        m_codec =codec;
        if(!m_subFile.isEmpty()){
            emit subFileChanged(m_subFile,m_codec);
        }

        emit codecChanged();
    }
}




