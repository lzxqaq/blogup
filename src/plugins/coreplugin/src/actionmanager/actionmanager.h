#ifndef ACTIONMANAGER_H
#define ACTIONMANAGER_H

//#include "core_global.h"
//#include "coreconstants.h"
//#include "icontext.h"
//#include "command.h"

//#include <QObject>
//#include <QList>

//QT_BEGIN_NAMESPACE
//class QAction;
//class QString;
//QT_END_NAMESPACE

//namespace Core {

//class ActionContainer;
//class Command;
//class Context;

//namespace Internal {
//class CorePlugin;
//class MainWindow;
//}

//class CORE_EXPORT ActionManager : public QObject
//{
//    Q_OBJECT
//public:
//    static ActionManager *instance();

//    static ActionContainer *createMenu(Utils::Id id);
//    static ActionContainer *createMenuBar(Utils::Id id);

//    static Command *registerAction(QAction *action, Utils::Id id,
//                                   const Context &context = Context(Constants::C_GLOBAL),
//                                   bool scriptable = false);

//    static Command *command(Utils::Id id);
//    static ActionContainer *actionContainer(Utils::Id id);

//    static QList<Command *> commands();


//    static void unregisterAction(QAction *action, Utils::Id id);

//    static void setPresentationModeEnabled(bool enabled);
//    static bool isPresentationModeEnabled();

//    static QString withNumberAccelerator(const QString &text, const int number);

//signals:
//    void commandListChanged();
//    void commandAdded(Utils::Id id);

//private:
//    ActionManager(QObject *parent = nullptr);
//    ~ActionManager() override;
//    static void saveSettings();
//    static void setContext(const Context &context);

//    friend class Core::Internal::CorePlugin; // initialization
//    friend class Core::Internal::MainWindow; // saving settings and setting context

//};

//}

#endif // ACTIONMANAGER_H
