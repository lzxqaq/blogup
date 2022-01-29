#ifndef DOCKEDEDITOR_H
#define DOCKEDEDITOR_H

#include <QObject>
#include <QPointer>

#include "advanceddockingsystem/DockManager.h"
#include "editormanager/customedit.h"

#include "core_global.h"

class CORE_EXPORT DockManager : public QObject
{
    Q_OBJECT

public:
    explicit DockManager(QWidget *parent);
    virtual ~DockManager();

    CustomEdit *getCurrentEditor() const;
    ads::CDockAreaWidget *currentDockArea();

    QVector<CustomEdit *> editors() const;

    void switchToEditor(const CustomEdit *editor);

    int count() const;

    void initUi();

    ads::CDockWidget* createFileSystemTreeDockWidget();

    ads::CDockWidget *createCenterWidget();

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

private:
    ads::CDockManager* m_dockManager = Q_NULLPTR;
    CustomEdit *m_currentEditor = Q_NULLPTR;
    QPointer<ads::CDockWidget> m_centerDock;

    QWidget *m_parent = Q_NULLPTR;

};

#endif // DOCKEDEDITOR_H
