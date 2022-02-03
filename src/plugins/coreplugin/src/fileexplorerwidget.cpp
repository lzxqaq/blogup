#include "fileexplorerwidget.h"
#include "ui_fileexplorerwidget.h"

#include <QFileSystemModel>
#include <QMenu>
#include <QSortFilterProxyModel>
#include <QPushButton>
#include <QFileDialog>

static void showOnlyFirstColumn(QTreeView *view)
{
    const int columnCount = view->header()->count();
    for (int i = 1; i < columnCount; ++i)
        view->setColumnHidden(i, true);
}

// FolderNavigationModel: Shows path as tooltip.
class FolderNavigationModel : public QFileSystemModel
{
public:
    enum Roles {
        IsFolderRole = Qt::UserRole + 50 // leave some gap for the custom roles in QFileSystemModel
    };

    explicit FolderNavigationModel(QObject *parent = nullptr);
    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const final;
    Qt::DropActions supportedDragActions() const final;
    Qt::ItemFlags flags(const QModelIndex &index) const final;
};


// Sorts folders on top if wanted
class FolderSortProxyModel : public QSortFilterProxyModel
{
public:
    FolderSortProxyModel(QObject *parent = nullptr);

protected:
    bool lessThan(const QModelIndex &source_left, const QModelIndex &source_right) const override;
};

FolderNavigationModel::FolderNavigationModel(QObject *parent) : QFileSystemModel(parent)
{ }

QVariant FolderNavigationModel::data(const QModelIndex &index, int role) const
{
    if (role == Qt::ToolTipRole)
        return QDir::toNativeSeparators(QDir::cleanPath(filePath(index)));
    else if (role == IsFolderRole)
        return isDir(index);
    else
        return QFileSystemModel::data(index, role);
}

Qt::DropActions FolderNavigationModel::supportedDragActions() const
{
    return Qt::MoveAction;
}

Qt::ItemFlags FolderNavigationModel::flags(const QModelIndex &index) const
{
    if (index.isValid() && !fileInfo(index).isRoot())
        return QFileSystemModel::flags(index) | Qt::ItemIsEditable;
    return QFileSystemModel::flags(index);
}


FolderSortProxyModel::FolderSortProxyModel(QObject *parent)
    : QSortFilterProxyModel(parent)
{
}

bool FolderSortProxyModel::lessThan(const QModelIndex &source_left, const QModelIndex &source_right) const
{
    const QAbstractItemModel *src = sourceModel();
    if (sortRole() == FolderNavigationModel::IsFolderRole) {
        const bool leftIsFolder = src->data(source_left, FolderNavigationModel::IsFolderRole)
                                      .toBool();
        const bool rightIsFolder = src->data(source_right, FolderNavigationModel::IsFolderRole)
                                       .toBool();
        if (leftIsFolder != rightIsFolder)
            return leftIsFolder;
    }
    const QString leftName = src->data(source_left, QFileSystemModel::FileNameRole).toString();
    const QString rightName = src->data(source_right, QFileSystemModel::FileNameRole).toString();
    return QString::compare(leftName, rightName, Qt::CaseSensitive) < 0;
}

class FileSortFilterProxyModel : public QSortFilterProxyModel
{
public:
    FileSortFilterProxyModel(QObject *parent = 0)
        : QSortFilterProxyModel(parent)
    {

    }

protected:
    bool lessThan(const QModelIndex &left, const QModelIndex &right) const
    {
        QFileSystemModel *model = static_cast<QFileSystemModel*>(this->sourceModel());

        QFileInfo leftInfo  = model->fileInfo(left);
        QFileInfo rightInfo = model->fileInfo(right);

        if (leftInfo.isDir() == rightInfo.isDir())
            return (leftInfo.filePath().compare(rightInfo.filePath(), Qt::CaseInsensitive) < 0);

        return leftInfo.isDir();
    }
};


FileExplorerWidget::FileExplorerWidget(QWidget *parent) :
    QWidget(parent),
    m_fileSystemModel(new FolderNavigationModel(this)),
    m_sortProxyModel(new FolderSortProxyModel(m_fileSystemModel))
{

    m_sortProxyModel->setSourceModel(m_fileSystemModel);
    m_sortProxyModel->setSortRole(FolderNavigationModel::IsFolderRole);
    m_sortProxyModel->sort(0);

    m_stackedLayout = new QStackedLayout(this);

    this->setLayout(m_stackedLayout);

    m_welcomeWidget = new QWidget(this);
    auto welcomeLayout = new QVBoxLayout(m_welcomeWidget);
    welcomeLayout->addStretch();
    QPushButton* openButton = new QPushButton("Open Site");
    QPushButton* newButton = new QPushButton("New Site");
    welcomeLayout->addWidget( openButton );
    welcomeLayout->addWidget( newButton );
    welcomeLayout->addStretch();
    connect(openButton, &QPushButton::clicked, this, [=](){
        openExplorer();
    });
    connect(newButton, &QPushButton::clicked, this, &FileExplorerWidget::newSite);

    m_fileTreeView = new QTreeView(this);

    m_fileTreeView->setModel(m_sortProxyModel);
    m_fileTreeView->setHeaderHidden(true);
    m_fileTreeView->sortByColumn(0, Qt::AscendingOrder);
    m_fileTreeView->setContextMenuPolicy(Qt::CustomContextMenu);
    m_fileTreeView->setSortingEnabled(true);
    m_fileTreeView->setEditTriggers(QAbstractItemView::NoEditTriggers);
    showOnlyFirstColumn(m_fileTreeView);

    m_stackedLayout->addWidget(m_welcomeWidget);
    m_stackedLayout->addWidget(m_fileTreeView);

    connect(m_fileTreeView, SIGNAL(doubleClicked(QModelIndex)),
            SLOT(fileOpen(QModelIndex)));
}

FileExplorerWidget::~FileExplorerWidget()
{
}

void FileExplorerWidget::showEvent(QShowEvent *event)
{
    if (!initialized) {
        m_fileSystemModel->setRootPath("C:/");
        initialized = true;
    }
    QWidget::showEvent(event);
}

void FileExplorerWidget::setPath(const QString &path)
{
    m_fileTreeView->setRootIndex(m_fileSystemModel->index(path));
}

QString FileExplorerWidget::getPath()
{
    return m_fileSystemModel->filePath(m_fileTreeView->rootIndex());
}

void FileExplorerWidget::fileOpen(const QModelIndex &index)
{
    QFileInfo info = m_fileSystemModel->fileInfo(m_sortProxyModel->mapToSource(index));
    if (info.isFile()) {
        const QString filePath = info.filePath();

        emit fileSelected(filePath);
    }
}

void FileExplorerWidget::oncustomContextMenuRequested(const QPoint p)
{

}

void FileExplorerWidget::openExplorer(QString path)
{
    QString dir;
    if (path.isEmpty())
    {
        dir = QFileDialog::getExistingDirectory(this);
    }
    else
    {
        dir = path;
    }
    if (!dir.isEmpty())
    {
//        m_fileSystemModel->
        setRootDirectory(dir);
        m_stackedLayout->setCurrentWidget(m_fileTreeView);

        currentDir = dir;
    }
}

void FileExplorerWidget::closeExplorer()
{
    m_fileSystemModel->setRootPath("");
    m_fileTreeView->setRootIndex(m_fileSystemModel->index(""));
    m_stackedLayout->setCurrentWidget(m_welcomeWidget);
}

void FileExplorerWidget::setRootDirectory(const QString &directory)
{
    const QModelIndex index = m_sortProxyModel->mapFromSource(
        m_fileSystemModel->setRootPath(directory));
    m_fileTreeView->setRootIndex(index);
}

const QString &FileExplorerWidget::getCurrentDir() const
{
    return currentDir;
}

