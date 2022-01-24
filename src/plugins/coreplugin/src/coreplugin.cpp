#include "mainwindow.h"
#include "coreplugin.h"

static CorePlugin *m_instance = nullptr;


CorePlugin::CorePlugin()
{
    m_instance = this;

}

CorePlugin::~CorePlugin()
{
    delete m_mainWindow;
}

CorePlugin *CorePlugin::instance()
{
    return m_instance;
}

void CorePlugin::initialize()
{
    m_mainWindow = new MainWindow;
    m_mainWindow->show();

}
