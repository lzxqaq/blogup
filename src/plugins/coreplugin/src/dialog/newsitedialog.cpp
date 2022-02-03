#include "newsitedialog.h"
#include "ui_newsitedialog.h"

#include <QPushButton>
#include <QFileDialog>
#include <QMessageBox>

NewSiteDialog::NewSiteDialog(QWidget *parent)
    :   QDialog(parent)
    ,   ui(new Ui::NewSiteDialog)
{
    ui->setupUi(this);


    connect(ui->fileSelectBtn, &QPushButton::clicked, this, [=](){
        QString dir = QFileDialog::getExistingDirectory(this, tr("Select Directory")
                    , "/home", QFileDialog::ShowDirsOnly | QFileDialog::DontResolveSymlinks);
        ui->dirPath->setText(dir);
    });
}

NewSiteDialog::~NewSiteDialog()
{

}

void NewSiteDialog::accept()
{
    m_dirName = ui->dirName->text();
    m_dirPath = ui->dirPath->text();

    if (m_dirName.isEmpty() || m_dirPath.isEmpty())
    {
        QMessageBox::information(this, tr("Warning"), tr("Please check the input."));
        return;
    }

    QDialog::accept();
}

void NewSiteDialog::reject()
{
    QDialog::reject();
}
