#ifndef TEXTEDITORPLUGIN_H
#define TEXTEDITORPLUGIN_H

#include <QObject>
#include "extensionsystem/iplugin.h"

class EditorManager;

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

private:
    EditorManager *editorManager;

};

#endif // TEXTEDITORPLUGIN_H
