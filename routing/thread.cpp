#include "thread.h"
#include <QProcess>
#include <QDir>

Thread::Thread()
{

}

void Thread::run()
{
    QDir direc = QDir::currentPath();     //return path in the build folder
    direc.cdUp();                         //project folder
    direc.cd("routing");
    QString program("node");
    QStringList filepath = QStringList()<< direc.path()+"/server.js";         //on récupére le path du fichier à éxécuter
    QProcess p;
    p.setWorkingDirectory(direc.path());
    p.execute(program, filepath);

}
