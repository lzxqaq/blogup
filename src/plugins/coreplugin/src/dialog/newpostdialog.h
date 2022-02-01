#ifndef NEWPOSTDIALOG_H
#define NEWPOSTDIALOG_H

#include <QDialog>

namespace Ui {
class NewPostDialog;
}

class NewPostDialog : public QDialog
{
    Q_OBJECT
public:
    NewPostDialog(QWidget *parent = nullptr);
    virtual ~NewPostDialog();

private:
    Ui::NewPostDialog *ui;

};

#endif // NEWPOSTDIALOG_H
