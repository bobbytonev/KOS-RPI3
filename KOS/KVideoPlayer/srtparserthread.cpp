#include "srtparserthread.h"

SrtParserThread::SrtParserThread()
{
    this->moveToThread(&thread);
    thread.start();

}

SrtParserThread::~SrtParserThread()
{
 thread.quit();
 thread.wait();
}

void SrtParserThread::openFile(QString filePath, QString codec)
{
    srtData.clear();

    if(!filePath.endsWith(".srt")){
        filePath = filePath.remove(filePath.length()-4,4)+".srt";
        filePath= filePath.replace("file://","");
    }

    QFile file(filePath);

    if(!file.open(QIODevice::ReadOnly)){

        return;
    }

    QTextStream in(&file);


    //in.setCodec("Windows-1251");
    in.setCodec(codec.toStdString().c_str());

    QString text;
    while(!in.atEnd()){


        // QString line = in.readAll();

        QString line =in.readLine();

        if(line.contains("-->")){
            SrtItem item;

            QStringList lineSpliter = line.split(" ");
            QTime start_time = QTime::fromString(lineSpliter[0],"hh:mm:ss,zzz");
            QTime end_time = QTime::fromString(lineSpliter[2],"hh:mm:ss,zzz");
            item.startTime = QTime(0,0,0).msecsTo(start_time);
            item.endTime = QTime(0,0,0).msecsTo(end_time);

            while(!in.atEnd()){
                QString textLine = in.readLine();

                if(textLine.isEmpty()){
                    srtData.append(item);
                    break;
                }else{

                    item.text+=(item.text.isEmpty() ? "":"\n")+textLine;
                    //item.text += textLine;
                }
            }

        }

    }
}

void SrtParserThread::positionChanged(int position)
{
    bool subFound =false;
    foreach(SrtItem item,srtData){


        if(item.startTime <=position && item.endTime >=position){
            emit subUpdated(item.text);
            subFound = true;

        }
    }
    if(!subFound) emit subUpdated("");

}
