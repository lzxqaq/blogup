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
class DockedEditor;

class MainWindow : public QMainWindow
{
    Q_OBJECT
public:
    explicit MainWindow(QWidget *parent = 0);
    virtual ~MainWindow();


    void createActions();

    void createContent();


    ads::CDockWidget* createFileSystemTreeDockWidget();


    ads::CDockWidget* createCenterWidget();

    void addEditorWidget(CustomEdit *widget);

    void createEditor(const QString &path);
    void closeFile(CustomEdit *editor);
    bool isInInitialState();

public slots:
    void newFile();
    bool saveFile(CustomEdit *editor);
    bool saveCurrentFileAsDialog();
    bool saveFileAs(CustomEdit *editor, const QString &fileName);

    void activateEditor(CustomEdit *editor);

    void updateGui(CustomEdit *editor);

signals:
    void editorActivated(CustomEdit *editor);

protected:
    virtual void closeEvent(QCloseEvent* event) override;

private slots:
    void tabBarRightClicked(CustomEdit *editor);

private:

    bool checkFileForModification(CustomEdit *editor);


    Ui::MainWindow *ui;
    ads::CDockManager* m_dockManager = nullptr;
    QPointer<ads::CDockWidget> m_centerDock;
    EditorManager *m_editorManager;
    DockedEditor *m_dockedEditor;

};


#endif // MAINWINDOW_H
