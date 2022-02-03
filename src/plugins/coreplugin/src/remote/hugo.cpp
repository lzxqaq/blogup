#include "hugo.h"

Hugo::Hugo(const QStringList &arguments, const QString &path, QObject *parent)
    : Process(this->findBinPath(), arguments, path, parent)
{

}

Hugo::Hugo(QString exePath, const QStringList &arguments, const QString &path, QObject *parent)
    : Process(exePath, arguments, path, parent)
{

}

QString Hugo::findBinPath()
{
    return "hugo";
}
