
//============================================================================
//                                   INCLUDES
//============================================================================
#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "editormanager/editormanager.h"

#include <iostream>

#include <QLabel>
#include <QTextEdit>
#include <QCalendarWidget>
#include <QFrame>
#include <QTreeView>
#include <QFileSystemModel>
#include <QBoxLayout>
#include <QSettings>
#include <QDockWidget>
#include <QDebug>
#include <QResizeEvent>
#include <QAction>
#include <QWidgetAction>
#include <QComboBox>
#include <QInputDialog>
#include <QRubberBand>
#include <QPlainTextEdit>
#include <QTableWidget>
#include <QScreen>
#include <QStyle>
#include <QMessageBox>
#include <QMenu>
#include <QToolButton>
#include <QToolBar>
#include <QPointer>

#include <QMap>

#include "advanceddockingsystem/DockManager.h"
#include "advanceddockingsystem/DockWidget.h"
#include "advanceddockingsystem/DockAreaWidget.h"
#include "advanceddockingsystem/DockAreaTitleBar.h"
#include "advanceddockingsystem/DockAreaTabBar.h"
#include "advanceddockingsystem/FloatingDockContainer.h"
#include "advanceddockingsystem/DockComponentsFactory.h"
#include "advanceddockingsystem/DockSplitter.h"

/**
 * Helper function to create an SVG icon
 */
static QIcon svgIcon(const QString& File)
{
    QIcon SvgIcon(File);
    SvgIcon.addPixmap(SvgIcon.pixmap(92));
    return SvgIcon;
}


//============================================================================
/**
 * Private data class pimpl
 */
class MainWindowPrivate : public QObject
{
public:
    MainWindow* _this;
    Ui::MainWindow ui;
    ads::CDockManager* m_dockManager = nullptr;
    QPointer<ads::CDockWidget> m_centerDock;

    MainWindowPrivate(MainWindow* _public) : _this(_public) {}

    /**
     * Creates the toolbar actions
     */
    void createActions();

    /**
     * Fill the dock manager with dock widgets
     */
    void createContent();

    /**
     * Creates a dock widget with a file system tree view
     */
    ads::CDockWidget* createFileSystemTreeDockWidget()
    {
        QTreeView* w = new QTreeView();
        w->setFrameShape(QFrame::NoFrame);
        QFileSystemModel* m = new QFileSystemModel(w);

        m->setRootPath(QDir::currentPath());
        w->setModel(m);

        w->hideColumn(1);
        w->hideColumn(2);
        w->hideColumn(3);

        w->setHeaderHidden(true);

        ads::CDockWidget* fileWidget = new ads::CDockWidget(QString("Filesystem"));
        fileWidget->setWidget(w);
        fileWidget->setFeature(ads::CDockWidget::DockWidgetMovable, false);
        fileWidget->setFeature(ads::CDockWidget::DockWidgetFloatable, false);
        fileWidget->setFeature(ads::CDockWidget::DockWidgetClosable, false);

        return fileWidget;
    }


    ads::CDockWidget* createCenterWidget()
    {
        QWidget *w = new QWidget();
        ads::CDockWidget* CentralDockWidget = new ads::CDockWidget(QString("Get Started"));
        CentralDockWidget->setWidget(w);
        CentralDockWidget->setFeature(ads::CDockWidget::NoTab, true);

        m_dockManager->setCentralWidget(CentralDockWidget);

        return CentralDockWidget;
    }

    /**
     * Creates as imple editor widget
     */
    ads::CDockWidget* createEditorWidget()
    {
        QPlainTextEdit* w = new QPlainTextEdit();
        w->setPlaceholderText("file path");
        w->setStyleSheet("border: none");
        ads::CDockWidget* DockWidget = new ads::CDockWidget(QString("Editor"));
        DockWidget->setWidget(w);
        DockWidget->setIcon(svgIcon(":/adsdemo/images/edit.svg"));
        DockWidget->setFeature(ads::CDockWidget::CustomCloseHandling, true);

        return DockWidget;
    }

    void createEditor();
    void onEditorCloseRequested();
};

//============================================================================
void MainWindowPrivate::createContent()
{
    auto FileSystemWidget = createFileSystemTreeDockWidget();

    auto DockWidget = createCenterWidget();

    m_centerDock = DockWidget;

    m_dockManager->addDockWidget(ads::LeftDockWidgetArea, FileSystemWidget);
}

//============================================================================
void MainWindowPrivate::createActions()
{
    connect(ui.actionNewFile, &QAction::triggered, this, &MainWindowPrivate::createEditor);
}
//============================================================================
void MainWindowPrivate::createEditor()
{
    auto DockWidget = createEditorWidget();
    DockWidget->setFeature(ads::CDockWidget::DockWidgetDeleteOnClose, true);
    DockWidget->setFeature(ads::CDockWidget::DockWidgetForceCloseWithArea, true);
    connect(DockWidget, SIGNAL(closeRequested()), SLOT(onEditorCloseRequested()));

    ads::CDockAreaWidget* EditorArea = m_centerDock ? m_centerDock->dockAreaWidget() : nullptr;
    if (EditorArea)
    {
        m_dockManager->addDockWidget(ads::CenterDockWidgetArea, DockWidget, EditorArea);
    }
    else
    {
        m_dockManager->addDockWidget(ads::RightDockWidgetArea, DockWidget);
    }
}

//============================================================================
void MainWindowPrivate::onEditorCloseRequested()
{
    auto DockWidget = qobject_cast<ads::CDockWidget*>(sender());
    int Result = QMessageBox::question(_this, "Close Editor", QString("Editor %1 "
                                                                     "contains unsaved changes? Would you like to close it?")
                                                                 .arg(DockWidget->windowTitle()));
    if (QMessageBox::Yes == Result)
    {
        DockWidget->closeDockWidget();
    }
}


//============================================================================
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    d(new MainWindowPrivate(this))
{
    using namespace ads;
    d->ui.setupUi(this);
    setWindowTitle(QApplication::instance()->applicationName());
    d->createActions();

    CDockManager::setConfigFlag(CDockManager::DockAreaHasUndockButton, false);
    CDockManager::setConfigFlag(CDockManager::DockAreaHasTabsMenuButton, false);
    CDockManager::setConfigFlag(CDockManager::DockAreaHideDisabledButtons, true);
    CDockManager::setConfigFlag(CDockManager::OpaqueSplitterResize, true);
    CDockManager::setConfigFlag(CDockManager::XmlCompressionEnabled, false);
    CDockManager::setConfigFlag(CDockManager::FocusHighlighting, true);

    m_editorManager = new EditorManager(this);

    // Now create the dock manager and its content
    d->m_dockManager = new CDockManager(this);

    d->createContent();
    // Default window geometry - center on screen
    resize(1280, 720);
    setGeometry(QStyle::alignedRect(
        Qt::LeftToRight, Qt::AlignCenter, frameSize(),
        QGuiApplication::primaryScreen()->availableGeometry()
        ));
}


//============================================================================
MainWindow::~MainWindow()
{
    delete m_editorManager;
    m_editorManager = nullptr;

    delete d;
}


//============================================================================
void MainWindow::closeEvent(QCloseEvent* event)
{
    d->m_dockManager->deleteLater();
    QMainWindow::closeEvent(event);
}

//============================================================================


//============================================================================
