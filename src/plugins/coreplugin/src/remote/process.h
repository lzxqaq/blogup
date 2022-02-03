#ifndef PROCESS_H
#define PROCESS_H

#include <QObject>
#include <QProcess>

class Process : public QObject
{
    Q_OBJECT
public:
  explicit Process(const QString &command, const QStringList &arguments = QStringList(), const QString &path = QString(), QObject *parent = 0);

signals:
  void killProcess();
  void deleteProcess();

public slots:

private slots:
  void processStarted();
  void processError(QProcess::ProcessError error);
  void slotReadStdErr();
  void slotReadStdOut();
  void processFinished(int exitCode);
  void processDestroyed();
  void processStateChanged(QProcess::ProcessState newState);
  void errorMessageBox(QString error);

private:
  void processReadyReadSTDerr(QProcess &toRead);  // helps slotReadStdErr()
  void proccessReadyReadSTDout(QProcess &toRead); // helps slotReadStdOut()

  virtual QString findBinPath();
};

#endif // PROCESS_H
