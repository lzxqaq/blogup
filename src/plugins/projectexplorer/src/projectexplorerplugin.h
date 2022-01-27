#ifndef PROJECTEXPLORERPLUGIN_H
#define PROJECTEXPLORERPLUGIN_H


#include <QObject>
#include "extensionsystem/iplugin.h"

class ProjectExplorerPlugin : public IPlugin
{
    Q_OBJECT
    Q_PLUGIN_METADATA(IID "lzxqaq.com.BlogUpPlugin" FILE "ProjectExplorer.json")
    Q_INTERFACES(IPlugin)

public:
    ProjectExplorerPlugin();
    ~ProjectExplorerPlugin() override;
    void initialize() override;

    static ProjectExplorerPlugin *instance();

};

#endif // PROJECTEXPLORERPLUGIN_H
