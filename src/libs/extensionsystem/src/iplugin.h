/***************************************************************
*  @Copyright:  Copyright (c) 2022 lzxqaq.com All rights reserved.
*  @ProjName:   blogup
*  @FileName:   plugininterface.h
*  @Brief:
*  @Author:     lzx
*  @Date:       2022-01-24
*  @History:
****************************************************************/

#ifndef PLUGININTERFACE_H
#define PLUGININTERFACE_H

#include <QObject>
#include "extensionsystem_global.h"

class IPluginPrivate;

class EXTENSIONSYSTEMSHARED_EXPORT IPlugin : public QObject
{
    Q_OBJECT
public:
    IPlugin();
    ~IPlugin() override;
    virtual void initialize();

private:
    IPluginPrivate *d;
};
#define PluginInterface_iid "PluginManager.IPlugin"

Q_DECLARE_INTERFACE(IPlugin,PluginInterface_iid)
#endif // PLUGININTERFACE_H
