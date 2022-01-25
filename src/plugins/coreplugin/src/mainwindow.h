#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

class MainWindowPrivate;
class EditorManager;

class MainWindow : public QMainWindow
{
    Q_OBJECT
private:
    MainWindowPrivate* d;///< private data - pimpl
    friend class MainWindowPrivate;

protected:
    virtual void closeEvent(QCloseEvent* event) override;

public:
    explicit MainWindow(QWidget *parent = 0);
    virtual ~MainWindow();

private:
    EditorManager *m_editorManager;
};

#endif // MAINWINDOW_H
