#include "newpostdialog.h"

#include "ui_newpostdialog.h"


NewPostDialog::NewPostDialog(QWidget *parent)
    :   QDialog(parent)
    ,   ui(new Ui::NewPostDialog)
{
    ui->setupUi(this);
}

NewPostDialog::~NewPostDialog()
{

}
