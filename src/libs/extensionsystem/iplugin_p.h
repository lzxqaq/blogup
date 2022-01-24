#ifndef IPLUGIN_P_H
#define IPLUGIN_P_H

#include <QObject>
#include <QPluginLoader>
#include "iplugin.h"
#include "extensionsystem_global.h"

class EXTENSIONSYSTEMSHARED_EXPORT IPluginPrivate : public QObject
{
    Q_OBJECT
public:
    IPluginPrivate(IPlugin *plugin);

    QPluginLoader loader;

private:
    IPlugin *q;
};


#endif // IPLUGIN_P_H
