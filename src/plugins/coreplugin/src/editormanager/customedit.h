#ifndef CUSTOMEDIT_H
#define CUSTOMEDIT_H

#include <QObject>
#include <QDateTime>
#include <QFile>
#include <QFileInfo>
#include <QDragEnterEvent>
#include <QAbstractScrollArea>

#include "ScintillaEdit.h"
#include "Scintilla.h"

#include "../core_global.h"

class CORE_EXPORT CustomEdit : public ScintillaEdit
{
    Q_OBJECT

public:
    explicit CustomEdit(QString name, QWidget *parent = Q_NULLPTR);
    static CustomEdit *fromFile(const QString &filePath);

    template<typename Func>
    void forEachMatch(const QString &text, Func callback) { forEachMatch(text.toUtf8(), callback); }

    template<typename Func>
    void forEachMatch(const QByteArray &byteArray, Func callback);

    bool isFile() const;
    bool isSavedToDisk() const;
    QFileInfo getFileInfo() const;

    QString getName() const { return name; }
    QString getFilePath() const;

    enum FileStateChange {
        NoChange,
        Modified,
        Deleted,
        Restored,
    };

    enum BufferType {
        Temporary = 0, // A temporary buffer, e.g. "New 1"
        File = 1, // Buffer tied to a file on the file system
        FileMissing = 2, // Buffer with a missing file on the file system
    };

    void setFoldMarkers(const QString &type);

    QString languageName;

public slots:
    void close();
    bool save();
    void reload();
    bool saveAs(const QString &newFilePath);
    bool saveCopyAs(const QString &filePath);
    bool rename(const QString &newFilePath);
    CustomEdit::FileStateChange checkFileForStateChange();
    bool moveToTrash();

signals:
    void aboutToSave();
    void closed();
    void renamed();

protected:
    void dragEnterEvent(QDragEnterEvent *event) override;
    void dropEvent(QDropEvent *event) override;

private:
    QString name;
    BufferType bufferType = BufferType::Temporary;
    QFileInfo fileInfo;
    QDateTime modifiedTime;

    bool readFromDisk(QFile &file);
    QDateTime fileTimestamp();
    void updateTimestamp();
    void setFileInfo(const QString &filePath);
};



// Stick this in the header file...because C++, that's why
template<typename Func>
void CustomEdit::forEachMatch(const QByteArray &text, Func callback)
{
    Sci_TextToFind ttf {{0, (Sci_PositionCR)length()}, text.constData(), {-1, -1}};
    int flags = searchFlags();

    while (send(SCI_FINDTEXT, flags, reinterpret_cast<sptr_t>(&ttf)) != -1) {
        ttf.chrg.cpMin = callback(ttf.chrgText.cpMin, ttf.chrgText.cpMax);
    }
}


#endif // CUSTOMEDIT_H
