#include <QApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>

#include "qmlhelper.h"
#include "mmainwindow.h"
#include "titlebar.h"
#include "tablemodel.h"
#include "widgets/model/iconitemmodel.h"
#include "widgets/delegate/delegate.h"
#include "widgets/arrowcirclebutton.h"
#include "widgets/textdocument.h"
#include "widgets/utils.h"
#include "widgets/model/treemodel.h"
#include "screenshotitem.h"
#include "imageitem.h"

int main(int argc, char *argv[])
{
    QApplication::setAttribute(Qt::AA_UseSoftwareOpenGL);
    QApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
    QApplication app(argc, argv);

    QQmlApplicationEngine engine;

    qmlRegisterType<MMainWindow>("an.window", 1, 0, "MMainWindow");
    qmlRegisterType<TitleBar>("an.window", 1, 0, "TitleBar");
    qmlRegisterType<TableModel>("TableModel", 1, 0, "TableModel");
    qmlRegisterType<TreeModel>("an.model", 1, 0, "TreeModel");
    qmlRegisterType<QuickItemDelegate>("QuickItemDelegate", 1, 0, "QuickItemDelegate");
    qmlRegisterType<IconItemModel>("IconItemModel", 1, 0, "IconItemModel");
    qmlRegisterType<ArrowCircleButton>("an.window", 1, 0, "ArrowCircleButton");
    qmlRegisterType<QuickTextDocument>("an.window", 1, 0, "QuickTextDocument");
    qmlRegisterType<ScreenShotItem>("an.window", 1, 0, "ScreenShotItem");
    qmlRegisterType<ImageItem>("an.window", 1, 0, "ImageItem");

    QmlHelper qmlHelper;
    engine.rootContext()->setContextProperty("qmlHelper", &qmlHelper);
    Utils utils;
    engine.rootContext()->setContextProperty("Utils", &utils);

    QQmlComponent component(&engine, QUrl("qrc:/ScreenShotWindow.qml"));
    QObject *object = component.create();
    ScreenShotItem *screenShotWindow = qobject_cast<ScreenShotItem *>(object);
    screenShotWindow->close();
    engine.rootContext()->setContextProperty("screenShotWindow", screenShotWindow);
    engine.addImageProvider(QLatin1String("BackgroudView"), screenShotWindow->providerView());

    QObject::connect(&app, &QApplication::aboutToQuit, screenShotWindow, &ScreenShotItem::deleteLater);

    engine.load(QUrl(QLatin1String("qrc:/main.qml")));

    if (!engine.rootObjects().isEmpty()) {
        MMainWindow *mainWindow = qobject_cast<MMainWindow *>(engine.rootObjects()[0]);
        if (mainWindow)
            mainWindow->activeFocusItem();
    }

    return app.exec();
}
