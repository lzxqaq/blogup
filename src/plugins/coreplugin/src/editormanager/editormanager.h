#ifndef EDITORMANAGER_H
#define EDITORMANAGER_H

#include <QObject>
#include <QPointer>

#include "../core_global.h"


class CustomEdit;

class CORE_EXPORT EditorManager : public QObject
{
    Q_OBJECT

public:
    static EditorManager *instance();

    CustomEdit *createEmptyEditor(const QString &name);
    CustomEdit *createEditorFromFile(const QString &filePath);
    CustomEdit *cloneEditor(CustomEdit *editor);

    CustomEdit *getEditorByFilePath(const QString &filePath);

signals:
    void editorCreated(CustomEdit *editor);
    void editorClosed(CustomEdit *editor);

private:
    explicit EditorManager(QObject *parent = nullptr);
    ~EditorManager() override;

    void manageEditor(CustomEdit *editor);
    void setupEditor(CustomEdit *editor);
    void purgeOldEditorPointers();

    QList<QPointer<CustomEdit>> editors;

    friend class MainWindow;

};


#endif // EDITORMANAGER_H
