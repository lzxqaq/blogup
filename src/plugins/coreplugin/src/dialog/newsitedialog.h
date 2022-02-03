#ifndef NEWSITEDIALOG_H
#define NEWSITEDIALOG_H

#include <QDialog>

namespace Ui {
class NewSiteDialog;
}
class MainWindow;


class NewSiteDialog : public QDialog
{
    Q_OBJECT
public:

    NewSiteDialog(QWidget *parent = nullptr);
    virtual ~NewSiteDialog();

private:
    void accept() override;
    void reject() override;

    Ui::NewSiteDialog *ui;

    QString m_dirName;
    QString m_dirPath;

    friend MainWindow;

};

#endif // NEWSITEDIALOG_H
