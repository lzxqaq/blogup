#include "texteditorplugin.h"

static TextEditorPlugin *m_instance = nullptr;

TextEditorPlugin::TextEditorPlugin()
{
    m_instance = this;

}

TextEditorPlugin::~TextEditorPlugin()
{

}

void TextEditorPlugin::initialize()
{

}

TextEditorPlugin *TextEditorPlugin::instance()
{
    return m_instance;

}
