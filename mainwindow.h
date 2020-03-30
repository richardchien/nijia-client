#pragma once

#include <QWebEngineView>
#include <QWidget>

class MainWindow : public QWidget {
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    QWebEngineView *sidebarContainer;
    QWebEngineView *mainContainer;
};
