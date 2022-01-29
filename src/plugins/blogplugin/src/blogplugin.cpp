#include "blogplugin.h"

static BlogPlugin *m_instance = nullptr;

BlogPlugin::BlogPlugin()
{
    m_instance = this;
}

BlogPlugin::~BlogPlugin()
{

}

void BlogPlugin::initialize()
{

}

BlogPlugin *BlogPlugin::instance()
{
    return m_instance;
}
