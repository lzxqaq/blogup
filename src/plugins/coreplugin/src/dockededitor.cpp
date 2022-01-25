#include "dockededitor.h"

#include "DockAreaWidget.h"
#include "DockWidgetTab.h"
#include "DockComponentsFactory.h"

#include "dockededitortitlebar.h"

class DockedEditorComponentsFactory : public ads::CDockComponentsFactory
{
public:
    ads::CDockAreaTitleBar* createDockAreaTitleBar(ads::CDockAreaWidget* DockArea) const {
        DockedEditorTitleBar *titleBar = new DockedEditorTitleBar(DockArea);

        // Disable the built in context menu for the title bar since it has options we don't want
        titleBar->setContextMenuPolicy(Qt::NoContextMenu);

        return titleBar;
    }
};

DockedEditor::DockedEditor(QWidget *parent) : QObject(parent)
{
    ads::CDockComponentsFactory::setFactory(new DockedEditorComponentsFactory());

    ads::CDockManager::setConfigFlag(ads::CDockManager::AllTabsHaveCloseButton, true);
    ads::CDockManager::setConfigFlag(ads::CDockManager::AlwaysShowTabs, true);
    ads::CDockManager::setConfigFlag(ads::CDockManager::OpaqueSplitterResize, true);
    ads::CDockManager::setConfigFlag(ads::CDockManager::DragPreviewIsDynamic, true);
    ads::CDockManager::setConfigFlag(ads::CDockManager::DragPreviewShowsContentPixmap, true);
    ads::CDockManager::setConfigFlag(ads::CDockManager::DockAreaHasCloseButton, false);
    ads::CDockManager::setConfigFlag(ads::CDockManager::DockAreaHasUndockButton, false);
    ads::CDockManager::setConfigFlag(ads::CDockManager::DockAreaDynamicTabsMenuButtonVisibility, true);
    ads::CDockManager::setConfigFlag(ads::CDockManager::FocusHighlighting, true);
    ads::CDockManager::setConfigFlag(ads::CDockManager::EqualSplitOnInsertion, true);
    ads::CDockManager::setConfigFlag(ads::CDockManager::MiddleMouseButtonClosesTab, true);

    m_DockManager = new ads::CDockManager(parent);
    m_DockManager->setStyleSheet("");

    connect(m_DockManager, &ads::CDockManager::focusedDockWidgetChanged, [=] (ads::CDockWidget* old, ads::CDockWidget* now) {
        Q_UNUSED(old)

        CustomEdit *editor = qobject_cast<CustomEdit *>(now->widget());

        currentEditor = editor;
        editor->grabFocus();
        emit editorActivated(editor);
    });

    connect(m_DockManager, &ads::CDockManager::dockAreaCreated, [=](ads::CDockAreaWidget* DockArea) {
        DockedEditorTitleBar *titleBar = qobject_cast<DockedEditorTitleBar *>(DockArea->titleBar());
        connect(titleBar, &DockedEditorTitleBar::doubleClicked, this, &DockedEditor::titleBarDoubleClicked);
    });
}

CustomEdit *DockedEditor::getCurrentEditor() const
{
    return currentEditor;
}

int DockedEditor::count() const
{
    int total = 0;

    for (int i = 0; i < m_DockManager->dockAreaCount(); ++i)
        total += m_DockManager->dockArea(i)->dockWidgetsCount();

    return total;
}

QVector<CustomEdit *> DockedEditor::editors() const
{
    QVector<CustomEdit *> editors;
    for (const ads::CDockWidget* dockWidget : m_DockManager->dockWidgetsMap()) {
        editors.append(qobject_cast<CustomEdit *>(dockWidget->widget()));
    }

    return editors;
}

void DockedEditor::switchToEditor(const CustomEdit *editor)
{
    for (ads::CDockWidget* dockWidget : m_DockManager->dockWidgetsMap()) {
        auto dockedEditor = qobject_cast<CustomEdit *>(dockWidget->widget());

        if (editor == dockedEditor) {
            dockWidget->raise();
            return;
        }
    }
}

void DockedEditor::dockWidgetCloseRequested()
{
    auto dockWidget = qobject_cast<ads::CDockWidget *>(sender());
    auto editor = qobject_cast<CustomEdit *>(dockWidget->widget());

    emit editorCloseRequested(editor);
}

ads::CDockAreaWidget *DockedEditor::currentDockArea()
{
    QMap<QString, ads::CDockWidget*> dockwidgets = m_DockManager->dockWidgetsMap();

    if (dockwidgets.size() == 0) {
        return Q_NULLPTR;
    }
    else if (dockwidgets.size() == 1) {
        // If no dockwidget has had the focus set yet, just return the only one
        return dockwidgets.first()->dockAreaWidget();
    }

    // Search the list for the one that has had the focus set
    for (ads::CDockWidget* dockWidget : dockwidgets) {
        if (dockWidget->property("focused").toBool()) {
            return dockWidget->dockAreaWidget();
        }
    }

    // There was no area that had the focus
    return Q_NULLPTR;
}

void DockedEditor::addEditor(CustomEdit *editor)
{
    qInfo(Q_FUNC_INFO);

    Q_ASSERT(editor != Q_NULLPTR);

    editor->setParent(m_DockManager);

    if (currentEditor == Q_NULLPTR) {
        currentEditor = editor;
    }

    emit editorAdded(editor);

    // Create the dock widget for the editor
    ads::CDockWidget* dw = new ads::CDockWidget(editor->getName());
    dw->setWidget(editor);
    dw->setFeature(ads::CDockWidget::DockWidgetFeature::DockWidgetDeleteOnClose, true);
    dw->setFeature(ads::CDockWidget::DockWidgetFeature::CustomCloseHandling, true);
    dw->setFeature(ads::CDockWidget::DockWidgetFeature::DockWidgetFloatable, false);

    dw->tabWidget()->setContextMenuPolicy(Qt::CustomContextMenu);
    connect(dw->tabWidget(), &QWidget::customContextMenuRequested, [=](const QPoint &pos) {
        Q_UNUSED(pos)

        emit contextMenuRequestedForEditor(editor);
    });

    // Set the tooltip based on the buffer
    if (editor->isFile()) {
        dw->tabWidget()->setToolTip(editor->getFilePath());
    }
    else {
        dw->tabWidget()->setToolTip(editor->getName());
    }

    // Set the icon
    dw->tabWidget()->setIcon(QIcon(":/icons/saved.png"));
    connect(editor, &CustomEdit::savePointChanged, [=](bool dirty) {
        const QString iconPath = dirty ? ":/icons/unsaved.png" : ":/icons/saved.png";
        dw->tabWidget()->setIcon(QIcon(iconPath));
    });

    connect(editor, &CustomEdit::closed, [=]() { removeEditor(editor); });
    connect(editor, &CustomEdit::renamed, [=]() { renameEditor(editor); });

    connect(dw, &ads::CDockWidget::closeRequested, this, &DockedEditor::dockWidgetCloseRequested);

    m_DockManager->addDockWidget(ads::CenterDockWidgetArea, dw, currentDockArea());
}

void DockedEditor::removeEditor(CustomEdit *editor)
{
    for (ads::CDockWidget* dockWidget : m_DockManager->dockWidgetsMap()) {
        CustomEdit *editorToCheck = qobject_cast<CustomEdit *>(dockWidget->widget());

        if (editor == editorToCheck) {
            dockWidget->closeDockWidget();
        }
    }
}

void DockedEditor::renameEditor(CustomEdit *editor)
{
    Q_ASSERT(editor != Q_NULLPTR);

    for (ads::CDockWidget* dockWidget : m_DockManager->dockWidgetsMap()) {
        CustomEdit *editorToCheck = qobject_cast<CustomEdit *>(dockWidget->widget());

        if (editor == editorToCheck) {
            QString newName = editor->getName();
            qDebug("Renamed to %s", qUtf8Printable(newName));
            dockWidget->setWindowTitle(newName);

            if (editor->isFile()) {
                dockWidget->tabWidget()->setToolTip(editor->getFilePath());
            }
            else {
                dockWidget->tabWidget()->setToolTip(editor->getName());
            }
        }
    }
}