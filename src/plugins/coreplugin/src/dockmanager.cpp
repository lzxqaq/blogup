#include "dockmanager.h"

#include "DockAreaWidget.h"
#include "DockWidgetTab.h"
#include "DockComponentsFactory.h"

#include "dockededitortitlebar.h"
#include "fileexplorerwidget.h"

/**
 * Helper function to create an SVG icon
 */
static QIcon svgIcon(const QString& File)
{
    QIcon SvgIcon(File);
    SvgIcon.addPixmap(SvgIcon.pixmap(92));
    return SvgIcon;
}


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

void DockManager::initUi()
{
    auto fileWidget = createFileSystemTreeDockWidget();

    auto centerWidget = createCenterWidget();
    m_centerDock = centerWidget;
    m_dockManager->setCentralWidget(centerWidget);
    m_dockManager->addDockWidget(ads::LeftDockWidgetArea, fileWidget);

}

DockManager::DockManager(QWidget *parent)
    : QObject(parent)
    , m_parent(parent)
{
//    ads::CDockComponentsFactory::setFactory(new DockedEditorComponentsFactory());

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

    m_dockManager = new ads::CDockManager(parent);
    m_dockManager->setStyleSheet("");

//    connect(m_dockManager, &ads::CDockManager::focusedDockWidgetChanged, [=] (ads::CDockWidget* old, ads::CDockWidget* now) {
//        Q_UNUSED(old)

//        CustomEdit *editor = qobject_cast<CustomEdit *>(now->widget());

//        m_currentEditor = editor;
//        editor->grabFocus();
//        emit editorActivated(editor);
//    });

//    connect(m_dockManager, &ads::CDockManager::dockAreaCreated, [=](ads::CDockAreaWidget* DockArea) {
//        DockedEditorTitleBar *titleBar = qobject_cast<DockedEditorTitleBar *>(DockArea->titleBar());
//        connect(titleBar, &DockedEditorTitleBar::doubleClicked, this, &DockManager::titleBarDoubleClicked);
//    });
}

DockManager::~DockManager()
{

}

CustomEdit *DockManager::getCurrentEditor() const
{
    return m_currentEditor;
}

int DockManager::count() const
{
    int total = 0;

    for (int i = 0; i < m_dockManager->dockAreaCount(); ++i)
        total += m_dockManager->dockArea(i)->dockWidgetsCount();

    return total;
}

ads::CDockWidget *DockManager::createFileSystemTreeDockWidget()
{
    FileExplorerWidget *w = new FileExplorerWidget(m_parent);

//    connect(w, &FileExplorerWidget::fileSelected, m_parent, &MainWindow::createEditor);

    ads::CDockWidget* fileWidget = new ads::CDockWidget(QString("EXPLORER"));
    fileWidget->setWidget(w);
    fileWidget->setFeature(ads::CDockWidget::DockWidgetMovable, false);
    fileWidget->setFeature(ads::CDockWidget::DockWidgetFloatable, false);
    fileWidget->setFeature(ads::CDockWidget::DockWidgetClosable, false);

    return fileWidget;
}

ads::CDockWidget* DockManager::createCenterWidget()
{
    QWidget *w = new QWidget();

    ads::CDockWidget* CentralDockWidget = new ads::CDockWidget(QString("Get Started"));
    CentralDockWidget->setWidget(w);
    CentralDockWidget->setFeature(ads::CDockWidget::NoTab, true);

    return CentralDockWidget;
}


QVector<CustomEdit *> DockManager::editors() const
{
    QVector<CustomEdit *> editors;
    for (const ads::CDockWidget* dockWidget : m_dockManager->dockWidgetsMap()) {
        editors.append(qobject_cast<CustomEdit *>(dockWidget->widget()));
    }

    return editors;
}

void DockManager::switchToEditor(const CustomEdit *editor)
{
    for (ads::CDockWidget* dockWidget : m_dockManager->dockWidgetsMap()) {
        auto dockedEditor = qobject_cast<CustomEdit *>(dockWidget->widget());

        if (editor == dockedEditor) {
            dockWidget->raise();
            return;
        }
    }
}

void DockManager::dockWidgetCloseRequested()
{
    auto dockWidget = qobject_cast<ads::CDockWidget *>(sender());
    auto editor = qobject_cast<CustomEdit *>(dockWidget->widget());

    emit editorCloseRequested(editor);
}

ads::CDockAreaWidget *DockManager::currentDockArea()
{
    ads::CDockAreaWidget* editorArea = m_centerDock ? m_centerDock->dockAreaWidget() : Q_NULLPTR;
    return editorArea;
}

void DockManager::addEditor(CustomEdit *editor)
{
    qInfo(Q_FUNC_INFO);

    Q_ASSERT(editor != Q_NULLPTR);

    editor->setParent(m_dockManager);

    if (m_currentEditor == Q_NULLPTR) {
        m_currentEditor = editor;
    }

    emit editorAdded(editor);

    // Create the dock widget for the editor
    ads::CDockWidget* dw = new ads::CDockWidget(editor->getName());
    dw->setWidget(editor);
    dw->setFeature(ads::CDockWidget::DockWidgetFeature::DockWidgetDeleteOnClose, true);
    dw->setFeature(ads::CDockWidget::DockWidgetFeature::CustomCloseHandling, true);
    dw->setFeature(ads::CDockWidget::DockWidgetFeature::DockWidgetFloatable, false);
    dw->setFeature(ads::CDockWidget::DockWidgetFeature::DockWidgetForceCloseWithArea, true);

    dw->setIcon(svgIcon(":/adsdemo/images/edit.svg"));

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
//    dw->tabWidget()->setIcon(QIcon(":/icons/saved.png"));
//    connect(editor, &CustomEdit::savePointChanged, [=](bool dirty) {
//        const QString iconPath = dirty ? ":/icons/unsaved.png" : ":/icons/saved.png";
//        dw->tabWidget()->setIcon(QIcon(iconPath));
//    });

    connect(editor, &CustomEdit::closed, [=]() { removeEditor(editor); });
    connect(editor, &CustomEdit::renamed, [=]() { renameEditor(editor); });

    connect(dw, &ads::CDockWidget::closeRequested, this, &DockManager::dockWidgetCloseRequested);

    m_dockManager->addDockWidget(ads::CenterDockWidgetArea, dw, currentDockArea());
}

void DockManager::removeEditor(CustomEdit *editor)
{
    for (ads::CDockWidget* dockWidget : m_dockManager->dockWidgetsMap()) {
        CustomEdit *editorToCheck = qobject_cast<CustomEdit *>(dockWidget->widget());

        if (editor == editorToCheck) {
            dockWidget->closeDockWidget();
        }
    }
}

void DockManager::renameEditor(CustomEdit *editor)
{
    Q_ASSERT(editor != Q_NULLPTR);

    for (ads::CDockWidget* dockWidget : m_dockManager->dockWidgetsMap()) {
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
