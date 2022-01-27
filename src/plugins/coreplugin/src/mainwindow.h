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

class MainWindow : public QMainWindow
{
    Q_OBJECT
public:
    explicit MainWindow(QWidget *parent = 0);
    virtual ~MainWindow();


    void createActions();

    void createContent();

    void closeFile(CustomEdit *editor);
    bool isInInitialState();

public slots:

    void newFile();
    void openFile(const QString &filePath);
    void openFileDialog();

    bool saveFile(CustomEdit *editor);
    bool saveCurrentFileAsDialog();
    bool saveFileAs(CustomEdit *editor, const QString &fileName);

    void activateEditor(CustomEdit *editor);

    void updateGui(CustomEdit *editor);


    void addEditor(CustomEdit *editor);
signals:
    void editorActivated(CustomEdit *editor);

protected:
    virtual void closeEvent(QCloseEvent* event) override;

private slots:
    void tabBarRightClicked(CustomEdit *editor);

private:

    bool checkFileForModification(CustomEdit *editor);


    Ui::MainWindow *ui;
    EditorManager *m_editorManager;
    DockManager *m_dockManager;

};


#endif // MAINWINDOW_H
