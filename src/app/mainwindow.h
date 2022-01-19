#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

struct MainWindowPrivate;

class CMainWindow : public QMainWindow
{
    Q_OBJECT
private:
    MainWindowPrivate* d;///< private data - pimpl
    friend struct MainWindowPrivate;

protected:
    virtual void closeEvent(QCloseEvent* event) override;

public:
    explicit CMainWindow(QWidget *parent = 0);
    virtual ~CMainWindow();

private slots:
    void createEditor();
    void onEditorCloseRequested();
};

#endif // MAINWINDOW_H
