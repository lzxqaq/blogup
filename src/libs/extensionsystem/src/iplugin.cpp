#include "iplugin.h"
#include "iplugin_p.h"

IPlugin::IPlugin()
    : d(new IPluginPrivate(this))
{

}

IPlugin::~IPlugin()
{
    delete d;
    d = nullptr;
}

void IPlugin::initialize()
{

}


/*************************************************************************************
 *
 *  private
 *
 * **********************************************************************************/

IPluginPrivate::IPluginPrivate(IPlugin *plugin)
    : q(plugin)
{

}
