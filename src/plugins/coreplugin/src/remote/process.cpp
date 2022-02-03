#include "process.h"
#include <QtDebug>
#include <QtGlobal>

Process::Process(const QString &execPath, const QStringList &arguments, const QString &path, QObject *parent)
{

    // Create the process
    QProcess *newProcess = new QProcess(parent);

    // Connect signals for QProcess
    connect(newProcess, &QProcess::started, this, &Process::processStarted);
    connect(newProcess, &QProcess::errorOccurred, this, &Process::processError);
    connect(newProcess, &QProcess::readyReadStandardError, this, &Process::slotReadStdErr);
    connect(newProcess, &QProcess::readyReadStandardOutput, this, &Process::slotReadStdOut);
    connect(newProcess, &QProcess::finished, this, &Process::processFinished);
    connect(newProcess, &QProcess::destroyed, this, &Process::destroyed);
    connect(this, &Process::killProcess, newProcess, &QProcess::kill);
    connect(this, &Process::deleteProcess, newProcess, &QProcess::deleteLater);

    //QString cmd;

    //#ifdef Q_OS_WIN
    //    cmd = "cmd.exe";
    //#endif

    //#ifdef Q_OS_LINUX
    //    cmd = "/bin/sh"
    //#endif

    //#ifdef Q_OS_MAC
    //    cmd = "/bin/sh"
    //#endif

    newProcess->setProgram(execPath);

    if (!arguments.isEmpty()) newProcess->setArguments(arguments);
    if (!path.isEmpty()) newProcess->setWorkingDirectory(path);

    newProcess->start();
    newProcess->waitForFinished();
    newProcess->waitForReadyRead();
}

void Process::processStarted()
{
    qDebug() << "[Process] Process has started!\n";
}

void Process::processError(QProcess::ProcessError error)
{
    qDebug() << "[Process] Process ERROR!\n";

    switch (error) {
    case QProcess::FailedToStart: {
        qDebug() << "[Process ERROR]: FailedToStart\n";
        break;
    }
    case QProcess::Crashed: {
        qDebug() << "[Process ERROR]: Crashed\n";
        break;
    }
    case QProcess::Timedout: {
        qDebug() << "[Process ERROR]: Timedout\n";
        break;
    }
    case QProcess::WriteError: {
        qDebug() << "[Process ERROR]: WriteError\n";
        break;
    }
    case QProcess::ReadError: {
        qDebug() << "[Process ERROR]: ReadError\n";
        break;
    }
    case QProcess::UnknownError: {
        qDebug() << "[Process ERROR]: UnknownError\n";
        break;
    }
    default:
        break;
    }
}

void Process::slotReadStdErr()
{
    // call helper with pointer
    qDebug() << "std err ready\n";
}

void Process::slotReadStdOut()
{
    // call helper with pointer
    qDebug() << "std out ready\n";
}

void Process::processReadyReadSTDerr(QProcess &toRead)
{
    QString stdErr = toRead.readAllStandardError();
    qDebug() << stdErr;
}

void Process::proccessReadyReadSTDout(QProcess &toRead)
{
    QString stdOut = toRead.readAllStandardOutput();
    qDebug() << stdOut;
}

QString Process::findBinPath()
{
    return QString();
}

void Process::processFinished(int exitCode)
{
    qDebug() << "[Process] Process exited";
    qDebug() << "[Process] Exit Code: " << exitCode << "\n";
}

void Process::processDestroyed()
{
    qDebug() << "[Process] Process destroyed!";
}

void Process::processStateChanged(QProcess::ProcessState newState)
{
    qDebug() << "[Process] Process stage changed!";

    switch (newState) {
    case QProcess::NotRunning: {
        qDebug() << "[Process] Process is now NotRunning";
        break;
    }
    case QProcess::Starting: {
        qDebug() << "[Process] Process is now Starting";
        break;
    }
    case QProcess::Running: {
        qDebug() << "[Process] Process is now Running";
        break;
    }
    default:
        break;
    }
}

void Process::errorMessageBox(QString error)
{
    qDebug() << "Error: " << error;
}
