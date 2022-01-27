#ifndef FILEEXPLORERWIDGET_H
#define FILEEXPLORERWIDGET_H

#include <QWidget>
#include <QTreeView>
#include <QStackedLayout>

class QFileSystemModel;
class QSortFilterProxyModel;


class FileExplorerWidget : public QWidget
{
    Q_OBJECT

public:
    explicit FileExplorerWidget(QWidget *parent = 0);
    ~FileExplorerWidget();

    void setPath(const QString &path);
    QString getPath();
signals:
    void fileSelected(const QString &filePath);

protected:
    void showEvent(QShowEvent *event);

private slots:
    void fileOpen(const QModelIndex &index);
    void oncustomContextMenuRequested(const QPoint p);

    void openExplorer();
    void closeExplorer();

    void setRootDirectory(const QString &directory);

private:
    bool initialized = false;
    QFileSystemModel *m_fileSystemModel = nullptr;
    QSortFilterProxyModel *m_sortProxyModel = nullptr;
    QTreeView *m_fileTreeView = nullptr;
    QWidget* m_welcomeWidget = nullptr;
    QStackedLayout *m_stackedLayout = nullptr;
};

#endif // FILEEXPLORERWIDGET_H
