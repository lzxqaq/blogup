

//                                   INCLUDES

#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "editormanager/editormanager.h"
#include "editormanager/customedit.h"
#include "dockmanager.h"
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
    m_dockManager = new DockManager(this);
    connect(m_dockManager, &DockManager::editorCloseRequested, this, [=](CustomEdit *editor) { closeFile(editor); });

    connect(m_dockManager, &DockManager::editorActivated, this, &MainWindow::activateEditor);

    connect(m_dockManager, &DockManager::contextMenuRequestedForEditor, this, &MainWindow::tabBarRightClicked);

    connect(m_dockManager, &DockManager::titleBarDoubleClicked, this, &MainWindow::newFile);

    connect(m_editorManager, &EditorManager::editorCreated, this, &MainWindow::addEditor);


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
    delete m_dockManager;
    m_editorManager = nullptr;
    m_dockManager = nullptr;
}

void MainWindow::createContent()
{
    m_dockManager->initUi();
}

void MainWindow::createActions()
{
    connect(ui->actionNewFile, &QAction::triggered, this, &MainWindow::newFile);
    connect(ui->actionOpenFile, &QAction::triggered, this, &MainWindow::openFileDialog);

}

bool MainWindow::saveFile(CustomEdit *editor)
{
    if (!editor->modify())
        return true;

    if (!editor->isFile()) {
        // Switch to the editor and show the saveas dialog
        m_dockManager->switchToEditor(editor);
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

void MainWindow::openFileDialog()
{
    QString fileName = QFileDialog::getOpenFileName(
        this, // parent
        Q_NULLPTR, // caption
        Q_NULLPTR, // dir
        Q_NULLPTR, // filter
        Q_NULLPTR // selected filter
        );
    if (!fileName.isEmpty())
    {
        openFile(fileName);
    }
}

bool MainWindow::saveCurrentFileAsDialog()
{
    QString dialogDir = QString();
    auto editor = m_dockManager->getCurrentEditor();

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

void MainWindow::addEditor(CustomEdit *editor)
{
    // The editor has been entirely configured at this point, so add it to the docked editor
    m_dockManager->addEditor(editor);
}


void MainWindow::newFile()
{
    static int count = 1;

    m_editorManager->createEmptyEditor(QString("New-%1").arg(count++));
}

void MainWindow::openFile(const QString &filePath)
{
    CustomEdit *editor = m_editorManager->getEditorByFilePath(filePath);
    if (editor == Q_NULLPTR) {
        QFileInfo fileInfo(filePath);

        if (!fileInfo.isFile()) {
            auto reply = QMessageBox::question(this, "Create File", QString("<b>%1</b> does not exist. Do you want to create it?").arg(filePath));

            if (reply == QMessageBox::Yes) {
                editor = m_editorManager->createEditorFromFile(filePath);
            }
            else {
            }
        }
        else {
            editor = m_editorManager->createEditorFromFile(filePath);
        }
    }
    if (editor != Q_NULLPTR) {
        m_dockManager->switchToEditor(editor);
    }
}

bool MainWindow::isInInitialState()
{
    if (m_dockManager->count() == 1) {
        CustomEdit *editor = m_dockManager->getCurrentEditor();
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
        if (m_dockManager->count() == 0) {
            newFile();
        }
    }
    else {
        // The user needs be asked what to do about this file, so switch to it
        m_dockManager->switchToEditor(editor);

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
    m_dockManager->switchToEditor(editor);

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





