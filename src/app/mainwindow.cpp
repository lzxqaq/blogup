
/*******************************************************************************
** Qt Advanced Docking System
** Copyright (C) 2017 Uwe Kindler
**
** This library is free software; you can redistribute it and/or
** modify it under the terms of the GNU Lesser General Public
** License as published by the Free Software Foundation; either
** version 2.1 of the License, or (at your option) any later version.
**
** This library is distributed in the hope that it will be useful,
** but WITHOUT ANY WARRANTY; without even the implied warranty of
** MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
** Lesser General Public License for more details.
**
** You should have received a copy of the GNU Lesser General Public
** License along with this library; If not, see <http://www.gnu.org/licenses/>.
******************************************************************************/


//============================================================================
/// \file   MainWindow.cpp
/// \author Uwe Kindler
/// \date   13.02.2018
/// \brief  Implementation of CMainWindow demo class
//============================================================================


//============================================================================
//                                   INCLUDES
//============================================================================
#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <iostream>

#include <QTime>
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
#include <QElapsedTimer>

#include "DockManager.h"
#include "DockWidget.h"
#include "DockAreaWidget.h"
#include "DockAreaTitleBar.h"
#include "DockAreaTabBar.h"
#include "FloatingDockContainer.h"
#include "DockComponentsFactory.h"
#include "statusdialog.h"
#include "DockSplitter.h"

/**
 * Helper function to create an SVG icon
 */
static QIcon svgIcon(const QString& File)
{
    // This is a workaround, because in item views SVG icons are not
    // properly scaled and look blurry or pixelate
    QIcon SvgIcon(File);
    SvgIcon.addPixmap(SvgIcon.pixmap(92));
    return SvgIcon;
}


//============================================================================
/**
 * Private data class pimpl
 */
struct MainWindowPrivate
{
    CMainWindow* _this;
    Ui::MainWindow ui;
    ads::CDockManager* DockManager = nullptr;
    ads::CDockWidget* WindowTitleTestDockWidget = nullptr;
    QPointer<ads::CDockWidget> LastDockedEditor;

    MainWindowPrivate(CMainWindow* _public) : _this(_public) {}

    /**
     * Creates the toolbar actions
     */
    void createActions();

    /**
     * Fill the dock manager with dock widgets
     */
    void createContent();

    /**
     * Saves the dock manager state and the main window geometry
     */
    void saveState();

    /**
     * Restores the dock manager state
     */
    void restoreState();

    /**
     * Restore the perspective listo of the dock manager
     */
    void restorePerspectives();

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

        ads::CDockWidget* fileWidget = new ads::CDockWidget(QString("Filesystem"));
        fileWidget->setWidget(w);
        fileWidget->setFeature(ads::CDockWidget::CustomCloseHandling, true);

        // We disable focus to test focus highlighting if the dock widget content
        // does not support focus
        w->setFocusPolicy(Qt::NoFocus);
        return fileWidget;
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

        QMenu* OptionsMenu = new QMenu(DockWidget);
        OptionsMenu->setTitle(QObject::tr("Options"));
        OptionsMenu->setToolTip(OptionsMenu->title());
        OptionsMenu->setIcon(svgIcon(":/adsdemo/images/custom-menu-button.svg"));
        auto MenuAction = OptionsMenu->menuAction();
        // The object name of the action will be set for the QToolButton that
        // is created in the dock area title bar. You can use this name for CSS
        // styling
        MenuAction->setObjectName("optionsMenu");
        DockWidget->setTitleBarActions({OptionsMenu->menuAction()});
        auto a = OptionsMenu->addAction(QObject::tr("Clear Editor"));
        w->connect(a, SIGNAL(triggered()), SLOT(clear()));

        return DockWidget;
    }
};

//============================================================================
void MainWindowPrivate::createContent()
{
    auto FileSystemWidget = createFileSystemTreeDockWidget();
    FileSystemWidget->setFeature(ads::CDockWidget::DockWidgetFloatable, false);
    FileSystemWidget->setFeature(ads::CDockWidget::DockWidgetMovable, false);
    FileSystemWidget->setFeature(ads::CDockWidget::DockWidgetFloatable, false);
    FileSystemWidget->setFeature(ads::CDockWidget::DockWidgetClosable, false);


    auto DockWidget = createEditorWidget();
    DockWidget->setFeature(ads::CDockWidget::DockWidgetDeleteOnClose, true);
    DockWidget->setFeature(ads::CDockWidget::DockWidgetForceCloseWithArea, true);
    _this->connect(DockWidget, SIGNAL(closeRequested()), SLOT(onEditorCloseRequested()));

    ads::CDockAreaWidget* CentralDockArea = DockManager->setCentralWidget(DockWidget);
    CentralDockArea->setAllowedAreas(ads::DockWidgetArea::OuterDockAreas);

    DockManager->addDockWidget(ads::LeftDockWidgetArea, FileSystemWidget);

    LastDockedEditor = DockWidget;

}


//============================================================================
void MainWindowPrivate::createActions()
{

    QAction* a = ui.toolBar->addAction("Create Docked Editor");
    a->setProperty("Floating", false);
    a->setToolTip("Creates a docked editor windows that are deleted on close");
    a->setIcon(svgIcon(":/adsdemo/images/docked_editor.svg"));
    _this->connect(a, SIGNAL(triggered()), SLOT(createEditor()));
    ui.menuTests->addAction(a);

    ui.menuTests->addSeparator();
    a = ui.menuTests->addAction("Show Status Dialog");
    _this->connect(a, SIGNAL(triggered()), SLOT(showStatusDialog()));


}


//============================================================================
void MainWindowPrivate::saveState()
{
    QSettings Settings("Settings.ini", QSettings::IniFormat);
    Settings.setValue("mainWindow/Geometry", _this->saveGeometry());
    Settings.setValue("mainWindow/State", _this->saveState());
    Settings.setValue("mainWindow/DockingState", DockManager->saveState());
}


//============================================================================
void MainWindowPrivate::restoreState()
{
    QSettings Settings("Settings.ini", QSettings::IniFormat);
    _this->restoreGeometry(Settings.value("mainWindow/Geometry").toByteArray());
    _this->restoreState(Settings.value("mainWindow/State").toByteArray());
    DockManager->restoreState(Settings.value("mainWindow/DockingState").toByteArray());
}



//============================================================================


//============================================================================
void MainWindowPrivate::restorePerspectives()
{
    QSettings Settings("Settings.ini", QSettings::IniFormat);
    DockManager->loadPerspectives(Settings);
}


//============================================================================
CMainWindow::CMainWindow(QWidget *parent) :
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

    // Now create the dock manager and its content
    d->DockManager = new CDockManager(this);

    d->createContent();
    // Default window geometry - center on screen
    resize(1280, 720);
    setGeometry(QStyle::alignedRect(
        Qt::LeftToRight, Qt::AlignCenter, frameSize(),
        QGuiApplication::primaryScreen()->availableGeometry()
        ));

    //d->restoreState();
    d->restorePerspectives();
}


//============================================================================
CMainWindow::~CMainWindow()
{
    delete d;
}


//============================================================================
void CMainWindow::closeEvent(QCloseEvent* event)
{
    d->saveState();
    // Delete dock manager here to delete all floating widgets. This ensures
    // that all top level windows of the dock manager are properly closed
    d->DockManager->deleteLater();
    QMainWindow::closeEvent(event);
}

//============================================================================
void CMainWindow::createEditor()
{
    auto DockWidget = d->createEditorWidget();
    DockWidget->setFeature(ads::CDockWidget::DockWidgetDeleteOnClose, true);
    DockWidget->setFeature(ads::CDockWidget::DockWidgetForceCloseWithArea, true);
    connect(DockWidget, SIGNAL(closeRequested()), SLOT(onEditorCloseRequested()));

    ads::CDockAreaWidget* EditorArea = d->LastDockedEditor ? d->LastDockedEditor->dockAreaWidget() : nullptr;
    if (EditorArea)
    {
        std::cout << "DockAreaCount before: " << EditorArea->dockContainer()->dockAreaCount() << std::endl;
        //        d->DockManager->setConfigFlag(ads::CDockManager::EqualSplitOnInsertion, true);
        d->DockManager->addDockWidget(ads::CenterDockWidgetArea, DockWidget, EditorArea);
        std::cout << "DockAreaCount after: " << DockWidget->dockContainer()->dockAreaCount() << std::endl;
    }
    else
    {
        d->DockManager->addDockWidget(ads::RightDockWidgetArea, DockWidget);
    }
    d->LastDockedEditor = DockWidget;

}


//============================================================================
void CMainWindow::onEditorCloseRequested()
{
    auto DockWidget = qobject_cast<ads::CDockWidget*>(sender());
    int Result = QMessageBox::question(this, "Close Editor", QString("Editor %1 "
                                                                     "contains unsaved changes? Would you like to close it?")
                                                                 .arg(DockWidget->windowTitle()));
    if (QMessageBox::Yes == Result)
    {
        DockWidget->closeDockWidget();
    }
}


//============================================================================


//============================================================================
void CMainWindow::showStatusDialog()
{
    CStatusDialog Dialog(d->DockManager);
    Dialog.exec();
}
