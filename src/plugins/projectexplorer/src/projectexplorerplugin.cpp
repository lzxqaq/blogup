#include "projectexplorerplugin.h"

static ProjectExplorerPlugin *m_instance = nullptr;

ProjectExplorerPlugin::ProjectExplorerPlugin()
{
    m_instance = this;
}

ProjectExplorerPlugin::~ProjectExplorerPlugin()
{

}

void ProjectExplorerPlugin::initialize()
{

}

ProjectExplorerPlugin *ProjectExplorerPlugin::instance()
{
    return m_instance;
}
