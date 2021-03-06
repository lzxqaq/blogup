#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QPointer>

namespace Ui {
class MainWindow;
}

namespace ads {
class CDockWidget;
class CDockManager;
}

class EditorManager;
class CustomEdit;
class DockManager;

class FileExplorerWidget;

class MainWindow : public QMainWindow
{
    Q_OBJECT
public:
    explicit MainWindow(QWidget *parent = 0);
    virtual ~MainWindow();

    void closeFile(CustomEdit *editor);
    bool isInInitialState();

public slots:

    void newFile();
    void openFile(const QString &filePath);
    void openFileDialog();

    bool saveFile(CustomEdit *editor);
    bool saveCurrentFileAsDialog();
    bool saveFileAs(CustomEdit *editor, const QString &fileName);

    bool saveCurrentFile();

    bool closeCurrentFile();
    bool closeAllFile();

    void activateEditor(CustomEdit *editor);

    void updateGui(CustomEdit *editor);


    void addEditor(CustomEdit *editor);

    void newSite();
    void newPost();

signals:
    void editorActivated(CustomEdit *editor);
    void openFolder(QString path = QString());
    void closeFolder();

protected:
    virtual void closeEvent(QCloseEvent* event) override;

private slots:
    void tabBarRightClicked(CustomEdit *editor);


    void on_actionPull_triggered();

    void on_actionPush_triggered();

    void on_actionConfig_triggered();

private:
    void createActions();
    void createContent();

    bool checkFileForModification(CustomEdit *editor);


    Ui::MainWindow *ui = nullptr;
    EditorManager *m_editorManager = nullptr;
    DockManager *m_dockManager = nullptr;

    FileExplorerWidget *m_fileWidget = nullptr;
};


#endif // MAINWINDOW_H
