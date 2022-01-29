#ifndef BLOGPLUGIN_H
#define BLOGPLUGIN_H


#include <QObject>
#include "iplugin.h"

class BlogPlugin : public IPlugin
{
    Q_OBJECT
    Q_PLUGIN_METADATA(IID "lzxqaq.com.BlogUpPlugin" FILE "BlogPlugin.json")
    Q_INTERFACES(IPlugin)

public:
    BlogPlugin();
    ~BlogPlugin() override;
    void initialize() override;

    static BlogPlugin *instance();

};

#endif // BLOGPLUGIN_H
