#ifndef TEXTEDITORPLUGIN_H
#define TEXTEDITORPLUGIN_H

#include <QObject>
#include "iplugin.h"


class TextEditorPlugin : public IPlugin
{
    Q_OBJECT
    Q_PLUGIN_METADATA(IID "lzxqaq.com.BlogUpPlugin" FILE "TextEditor.json")
    Q_INTERFACES(IPlugin)

public:
    TextEditorPlugin();
    ~TextEditorPlugin() override;
    void initialize() override;

    static TextEditorPlugin *instance();


};

#endif // TEXTEDITORPLUGIN_H
