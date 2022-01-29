#include <QApplication>

#include "extensionsystem/pluginmanager.h"
#include "extensionsystem/iplugin.h"

const char corePluginNameC[] = "Core";

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    PluginManager::instance()->loadAllPlugins();//插件管理器 加载所有插件
//    auto loader = PluginManager::instance()->getPlugin(corePluginNameC);
//    if (loader != nullptr)
//    {
//        auto corePlugin = static_cast<IPlugin*>(loader->instance());
//        corePlugin->initialize();
//    }
    return a.exec();
}
