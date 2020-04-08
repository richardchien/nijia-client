#include "application.h"
#include "rpcwebsocketclient.h"

#include "view/mainwindow.h"

int main(int argc, char *argv[]) {
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
    QCoreApplication::setAttribute(Qt::AA_UseHighDpiPixmaps);

    auto app = new Application(argc, argv);
    Application::setInstance(app);

    MainWindow w;
    w.show();

    return app->exec();
}
