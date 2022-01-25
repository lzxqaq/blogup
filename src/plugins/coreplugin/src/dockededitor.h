#ifndef DOCKEDEDITOR_H
#define DOCKEDEDITOR_H

#include <QObject>

#include "DockManager.h"
#include "editormanager/customedit.h"

class DockedEditor : public QObject
{
    Q_OBJECT

private:
    ads::CDockManager* m_DockManager = Q_NULLPTR;
    CustomEdit *currentEditor = Q_NULLPTR;

public:
    explicit DockedEditor(QWidget *parent);

    CustomEdit *getCurrentEditor() const;
    ads::CDockAreaWidget *currentDockArea();

    QVector<CustomEdit *> editors() const;

    void switchToEditor(const CustomEdit *editor);

    int count() const;

private slots:
    void dockWidgetCloseRequested();

public slots:
    void addEditor(CustomEdit *editor);
    void removeEditor(CustomEdit *editor);
    void renameEditor(CustomEdit *editor);

signals:
    void editorAdded(CustomEdit *editor);
    void editorCloseRequested(CustomEdit *editor);
    void editorActivated(CustomEdit *editor);

    void contextMenuRequestedForEditor(CustomEdit *editor);
    void titleBarDoubleClicked();
};

#endif // DOCKEDEDITOR_H
