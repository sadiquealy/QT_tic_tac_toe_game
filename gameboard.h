#ifndef GAMEBOARD_H
#define GAMEBOARD_H
#include<vector>
#include <QObject>
#include <QVariant>
#include <QDebug>

#include<QList>


struct Pos
{
    unsigned int x=0;
    unsigned int y=0;

};
class GameBoard : public QObject
{
    Q_OBJECT
    Q_PROPERTY(int  rows READ rows   WRITE setrows NOTIFY rowsChanged);
    Q_PROPERTY(int columns READ  columns NOTIFY columnsChanged);
    Q_PROPERTY(QVariantList board READ board WRITE setboard NOTIFY boardChanged)

public:
    Q_INVOKABLE void resetBoard( );
    explicit GameBoard(const int rows,const int colums,QObject *parent = nullptr);
    enum  Turn
    {
        Player=1,
        Computer
    };

    int rows()
    {
        return m_nRows;
    }
    int columns()
    {
        return m_nColumns;
    }

    void setrows(int rows)
    {
        qDebug()<<"set rows";
    }

    QVariantList board()
    {
        qDebug()<<"get board";
        return m_nBoard;
    }

    void setboard (QVariantList arg)
    {
        qDebug()<<"set board"<<arg[0].toList().at(0).toInt();
        if(arg!=m_nBoard)
        {
            qDebug()<<"set board";
            m_nBoard= arg;
        }

    }
    bool checkAllCellsareFilled();
    bool checkCells(Turn turn);
    void move(unsigned int row, unsigned column);
    void display();

signals:

    void rowsChanged(int m_nRows);
    void columnsChanged(int m_nColumns );
    void boardChanged(QVariantList arg );
    void updateCell(int row, int column);
    void cellClick(int row, int column);
    void showStatus(QString message);
public slots:
    void cellValueChanged(int row, int column);
    void playComputer();
private:
    int m_nRows;
    int m_nColumns;
    QVariantList m_nBoard;
    std::vector<std::vector<int>> cell{
        { 0, 0, 0, 0 },
        { 0, 0, 0, 0 },
        {0, 0, 0, 0 },
        {0, 0, 0, 0 },
    };

};

#endif // GAMEBOARD_H
