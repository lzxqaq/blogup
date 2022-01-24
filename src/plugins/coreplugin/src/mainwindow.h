#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

struct MainWindowPrivate;

class MainWindow : public QMainWindow
{
    Q_OBJECT
private:
    MainWindowPrivate* d;///< private data - pimpl
    friend struct MainWindowPrivate;

protected:
    virtual void closeEvent(QCloseEvent* event) override;

public:
    explicit MainWindow(QWidget *parent = 0);
    virtual ~MainWindow();

private slots:
    void createEditor();
    void onEditorCloseRequested();
};

#endif // MAINWINDOW_H
