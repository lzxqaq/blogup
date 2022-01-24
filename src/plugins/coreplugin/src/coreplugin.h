#ifndef COREPLUGIN_H
#define COREPLUGIN_H

#include <QObject>
#include "extensionsystem/iplugin.h"

class MainWindow;

class CorePlugin : public IPlugin
{
    Q_OBJECT
    Q_PLUGIN_METADATA(IID "lzxqaq.com.BlogUpPlugin" FILE "Core.json")
    Q_INTERFACES(IPlugin)

public:
    CorePlugin();
    ~CorePlugin() override;

    void initialize() override;


    static CorePlugin *instance();

private:
    MainWindow *m_mainWindow = nullptr;

};

#endif // COREPLUGIN_H
