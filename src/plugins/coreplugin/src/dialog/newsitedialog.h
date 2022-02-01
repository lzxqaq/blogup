#ifndef NEWSITEDIALOG_H
#define NEWSITEDIALOG_H

#include <QDialog>

namespace Ui {
class NewSiteDialog;
}

class NewSiteDialog : public QDialog
{
    Q_OBJECT
public:

    NewSiteDialog(QWidget *parent = nullptr);
    virtual ~NewSiteDialog();

private:
    Ui::NewSiteDialog *ui;

};

#endif // NEWSITEDIALOG_H
