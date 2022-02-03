#ifndef NEWPOSTDIALOG_H
#define NEWPOSTDIALOG_H

#include <QDialog>

namespace Ui {
class NewPostDialog;
}
class MainWindow;

class NewPostDialog : public QDialog
{
    Q_OBJECT
public:
    NewPostDialog(QWidget *parent = nullptr);
    virtual ~NewPostDialog();

private:
    void accept() override;
    void reject() override;

    Ui::NewPostDialog *ui;

    QString m_title;
    QString m_subDir;

    QString m_fileName;

    friend MainWindow;

};

#endif // NEWPOSTDIALOG_H
