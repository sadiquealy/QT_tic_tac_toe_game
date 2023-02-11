#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQuickView>
#include <QQmlContext>
#include "gameboard.h"

const int NUM_ROW=4;
const int NUM_COL=4;
int main(int argc, char *argv[])
{
     qDebug()<<"Starting Application";
    QGuiApplication app(argc, argv);
    GameBoard *game_board  =new GameBoard(NUM_ROW,NUM_COL);
    QQmlApplicationEngine engine;
    const QUrl url("qrc:/qml/main.qml");

    //QQuickView * view=new QQuickView();
    QQmlContext *context=engine.rootContext();
    context->setContextProperty("_game_board",game_board);

    QObject::connect(&engine, &QQmlApplicationEngine::objectCreated,
                     &app, [url](QObject *obj, const QUrl &objUrl) {
        if (!obj && url == objUrl)
            QCoreApplication::exit(-1);
    }, Qt::QueuedConnection);
    engine.load(url);
    QObject::connect(game_board, &GameBoard::cellClick,
                    game_board,&GameBoard::cellValueChanged);

            return app.exec();
}
