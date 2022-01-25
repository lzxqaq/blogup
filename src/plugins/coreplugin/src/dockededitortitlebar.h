#ifndef DOCKEDEDITORTITLEBAR_H
#define DOCKEDEDITORTITLEBAR_H

#include <DockAreaTitleBar.h>

class DockedEditorTitleBar : public ads::CDockAreaTitleBar
{
    Q_OBJECT

public:
    explicit DockedEditorTitleBar(ads::CDockAreaWidget* parent) : ads::CDockAreaTitleBar(parent) {}

signals:
    void doubleClicked();

protected:
    void mouseDoubleClickEvent(QMouseEvent *event) {
        ads::CDockAreaTitleBar::mouseDoubleClickEvent(event);

        if (event->button() == Qt::LeftButton) {
            emit doubleClicked();
        }
    }
};

#endif // DOCKEDEDITORTITLEBAR_H
