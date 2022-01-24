#ifndef EDITORMANAGER_H
#define EDITORMANAGER_H

#include <QObject>
#include <QPointer>


class CustomEdit;

class EditorManager : public QObject
{
    Q_OBJECT

public:
    explicit EditorManager(QObject *parent = nullptr);

    CustomEdit *createEmptyEditor(const QString &name);
    CustomEdit *createEditorFromFile(const QString &filePath);
    CustomEdit *cloneEditor(CustomEdit *editor);

    CustomEdit *getEditorByFilePath(const QString &filePath);

signals:
    void editorCreated(CustomEdit *editor);
    void editorClosed(CustomEdit *editor);

private:
    void manageEditor(CustomEdit *editor);
    void setupEditor(CustomEdit *editor);
    void purgeOldEditorPointers();

    QList<QPointer<CustomEdit>> editors;
};


#endif // EDITORMANAGER_H
