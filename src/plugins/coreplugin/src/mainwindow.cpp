

//                                   INCLUDES

#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "editormanager/editormanager.h"
#include "editormanager/customedit.h"
#include "dockededitor.h"
#include "fileexplorerwidget.h"

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
#include <QFileDialog>
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



MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    createActions();

    ads::CDockManager::setConfigFlag(ads::CDockManager::DockAreaHasUndockButton, false);
    ads::CDockManager::setConfigFlag(ads::CDockManager::DockAreaHasTabsMenuButton, false);
    ads::CDockManager::setConfigFlag(ads::CDockManager::DockAreaHideDisabledButtons, true);
    ads::CDockManager::setConfigFlag(ads::CDockManager::OpaqueSplitterResize, true);
    ads::CDockManager::setConfigFlag(ads::CDockManager::XmlCompressionEnabled, false);
    ads::CDockManager::setConfigFlag(ads::CDockManager::FocusHighlighting, true);

    m_editorManager = new EditorManager(this);
    m_dockedEditor = new DockedEditor(this);
    m_dockManager = new ads::CDockManager(this);
    connect(m_dockedEditor, &DockedEditor::editorCloseRequested, this, [=](CustomEdit *editor) { closeFile(editor); });

    connect(m_dockedEditor, &DockedEditor::editorActivated, this, &MainWindow::activateEditor);

    connect(m_dockedEditor, &DockedEditor::contextMenuRequestedForEditor, this, &MainWindow::tabBarRightClicked);

    connect(m_dockedEditor, &DockedEditor::titleBarDoubleClicked, this, &MainWindow::newFile);

    setWindowTitle(QApplication::instance()->applicationName());

    createContent();
    // Default window geometry - center on screen
    resize(1280, 720);
    setGeometry(QStyle::alignedRect(
        Qt::LeftToRight, Qt::AlignCenter, frameSize(),
        QGuiApplication::primaryScreen()->availableGeometry()
        ));
}



MainWindow::~MainWindow()
{
    delete m_editorManager;
    delete m_dockedEditor;
    delete m_dockManager;
    m_editorManager = nullptr;
    m_dockedEditor = nullptr;
    m_dockManager = nullptr;
}

void MainWindow::createContent()
{
    auto FileSystemWidget = createFileSystemTreeDockWidget();

    auto DockWidget = createCenterWidget();

    m_centerDock = DockWidget;

    m_dockManager->addDockWidget(ads::LeftDockWidgetArea, FileSystemWidget);
}


ads::CDockWidget* MainWindow::createCenterWidget()
{
    QWidget *w = new QWidget();
    ads::CDockWidget* CentralDockWidget = new ads::CDockWidget(QString("Get Started"));
    CentralDockWidget->setWidget(w);
    CentralDockWidget->setFeature(ads::CDockWidget::NoTab, true);

    m_dockManager->setCentralWidget(CentralDockWidget);

    return CentralDockWidget;
}

ads::CDockWidget* MainWindow::createFileSystemTreeDockWidget()
{
    FileExplorerWidget *w = new FileExplorerWidget(this);

    connect(w, &FileExplorerWidget::fileSelected, this, &MainWindow::createEditor);

    ads::CDockWidget* fileWidget = new ads::CDockWidget(QString("EXPLORER"));
    fileWidget->setWidget(w);
    fileWidget->setFeature(ads::CDockWidget::DockWidgetMovable, false);
    fileWidget->setFeature(ads::CDockWidget::DockWidgetFloatable, false);
    fileWidget->setFeature(ads::CDockWidget::DockWidgetClosable, false);

    return fileWidget;
}


void MainWindow::createActions()
{
    connect(ui->actionNewFile, &QAction::triggered, this, &MainWindow::newFile);
}


void MainWindow::addEditorWidget(CustomEdit *widget)
{
    ads::CDockWidget* dockWidget = new ads::CDockWidget(widget->getName());
    dockWidget->setWidget(widget);
    dockWidget->setIcon(svgIcon(":/adsdemo/images/edit.svg"));
    dockWidget->setFeature(ads::CDockWidget::CustomCloseHandling, true);

    dockWidget->setFeature(ads::CDockWidget::DockWidgetDeleteOnClose, true);
    dockWidget->setFeature(ads::CDockWidget::DockWidgetForceCloseWithArea, true);

    ads::CDockAreaWidget* editorArea = m_centerDock ? m_centerDock->dockAreaWidget() : nullptr;
    if (editorArea)
    {
        m_dockManager->addDockWidget(ads::CenterDockWidgetArea, dockWidget, editorArea);
    }
}


bool MainWindow::saveFile(CustomEdit *editor)
{
    if (!editor->modify())
        return true;

    if (!editor->isFile()) {
        // Switch to the editor and show the saveas dialog
        m_dockedEditor->switchToEditor(editor);
        return saveCurrentFileAsDialog();
    }
    else {
        bool didItGetSaved = editor->save();
        if (didItGetSaved) {
            return true;
        }
    }

    return false;
}


bool MainWindow::saveCurrentFileAsDialog()
{
    QString dialogDir = QString();
    auto editor = m_dockedEditor->getCurrentEditor();

    // Use the file path if possible
    if (editor->isFile()) {
        dialogDir = editor->getFilePath();
    }

    QString fileName = QFileDialog::getSaveFileName(
        this, // parent
        Q_NULLPTR, // caption
        dialogDir, // dir
        Q_NULLPTR, // filter
        Q_NULLPTR // selected filter
        );

    if (fileName.size() == 0) {
        return false;
    }

    return saveFileAs(editor, fileName);
}



bool MainWindow::saveFileAs(CustomEdit *editor, const QString &fileName)
{
    bool didItGetSaved = editor->saveAs(fileName);

    return didItGetSaved;
}

void MainWindow::activateEditor(CustomEdit *editor)
{
    checkFileForModification(editor);
    updateGui(editor);

    emit editorActivated(editor);
}

void MainWindow::updateGui(CustomEdit *editor)
{
//    updateFileStatusBasedUi(editor);
//    updateSaveStatusBasedUi(editor);
//    updateEOLBasedUi(editor);
//    updateEditorPositionBasedUi();
//    updateSelectionBasedUi(editor);
//    updateContentBasedUi(editor);
//    updateLanguageBasedUi(editor);
}


void MainWindow::newFile()
{
    static int count = 1;

    m_editorManager->createEmptyEditor(QString("New-%1").arg(count++));
}

void MainWindow::createEditor(const QString &path)
{
    CustomEdit * edit = m_editorManager->createEditorFromFile(path);
    addEditorWidget(edit);
}

bool MainWindow::isInInitialState()
{
    if (m_dockedEditor->count() == 1) {
        CustomEdit *editor = m_dockedEditor->getCurrentEditor();
        return !editor->isFile() && editor->isSavedToDisk();
    }

    return false;
}


void MainWindow::closeFile(CustomEdit *editor)
{
    if (isInInitialState()) {
        // Don't close the last file
        return;
    }

    if(editor->isSavedToDisk()) {
        editor->close();

        // If the last document was closed, start with a new one
        if (m_dockedEditor->count() == 0) {
            newFile();
        }
    }
    else {
        // The user needs be asked what to do about this file, so switch to it
        m_dockedEditor->switchToEditor(editor);

        QString message = QString("Save file <b>%1</b>?").arg(editor->getName());
        auto reply = QMessageBox::question(this, "Save File", message, QMessageBox::Save | QMessageBox::Discard | QMessageBox::Cancel, QMessageBox::Save);

        if (reply == QMessageBox::Cancel) {
            return;
        }

        if (reply == QMessageBox::Save) {
            bool didFileGetSaved = saveFile(editor);

            // The user might have canceled the save file dialog so just stop now
            if (didFileGetSaved == false)
                return;
        }

        editor->close();
    }
}



void MainWindow::closeEvent(QCloseEvent* event)
{

    QMainWindow::closeEvent(event);
}

void MainWindow::tabBarRightClicked(CustomEdit *editor)
{
    // Focus on the correct tab
    m_dockedEditor->switchToEditor(editor);

    // Create the menu and show it
    QMenu *menu = new QMenu(this);
//    menu->addAction(ui->actionClose);
//    menu->addAction(ui->actionCloseAllExceptActive);
//    menu->addAction(ui->actionCloseAllToLeft);
//    menu->addAction(ui->actionCloseAllToRight);
    menu->addSeparator();
    menu->addAction(ui->actionSave);
//    menu->addAction(ui->actionSaveAs);
//    menu->addAction(ui->actionRename);
    menu->addSeparator();
//    menu->addAction(ui->actionReload);
    menu->addSeparator();
//    menu->addAction(ui->actionCopyFullPath);
//    menu->addAction(ui->actionCopyFileName);
//    menu->addAction(ui->actionCopyFileDirectory);
    menu->popup(QCursor::pos());
}

bool MainWindow::checkFileForModification(CustomEdit *editor)
{
    auto state = editor->checkFileForStateChange();

    if (state == CustomEdit::NoChange) {
        return false;
    }
    else if (state == CustomEdit::Modified) {
        editor->reload();
    }
    else if (state == CustomEdit::Deleted) {
    }
    else if (state == CustomEdit::Restored) {
    }

    return true;
}





