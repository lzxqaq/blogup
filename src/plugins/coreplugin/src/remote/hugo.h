#ifndef HUGO_H
#define HUGO_H

#include "QObject"
#include "process.h"

class Hugo : public Process
{
    Q_OBJECT
public:
    explicit Hugo(const QStringList &arguments = QStringList(), const QString &path = QString(), QObject *parent = 0);
    explicit Hugo(QString exePath, const QStringList &arguments = QStringList(), const QString &path = QString(), QObject *parent = 0);

private:
    QString findBinPath() override;
};

#endif // HUGO_H
