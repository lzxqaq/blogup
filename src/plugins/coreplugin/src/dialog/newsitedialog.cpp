#include "newsitedialog.h"
#include "ui_newsitedialog.h"

NewSiteDialog::NewSiteDialog(QWidget *parent)
    :   QDialog(parent)
    ,   ui(new Ui::NewSiteDialog)
{
    ui->setupUi(this);

}

NewSiteDialog::~NewSiteDialog()
{

}
