#include "newpostdialog.h"

#include "ui_newpostdialog.h"

#include <QLineEdit>
#include <QRegularExpression>
#include <QMessageBox>

NewPostDialog::NewPostDialog(QWidget *parent)
    :   QDialog(parent)
    ,   ui(new Ui::NewPostDialog)
{
    ui->setupUi(this);

    connect(ui->title, &QLineEdit::editingFinished, this, [=](){
        QString tx = ui->title->text();
        tx.remove(QRegularExpression("\\s"));
        tx = tx.toLower();
        ui->fileName->setText(tx + ".md");
        ui->slug->setText(tx);
    });
}

NewPostDialog::~NewPostDialog()
{

}

void NewPostDialog::accept()
{
    m_title = ui->title->text();

    m_subDir = ui->subDir->text();

    m_fileName = ui->fileName->text();

    if (m_title.isEmpty() || m_subDir.isEmpty())
    {
        QMessageBox::information(this, tr("Warning"), tr("Please check the input."));
        return;
    }

    QDialog::accept();
}

void NewPostDialog::reject()
{
    QDialog::reject();
}
