#ifndef GAMEBOARD_H
#define GAMEBOARD_H

//
//  gameboard.h
//
//  Tic Tac Toe Game implementation between Player and Computer
//  No License @ Sadique Ali , Embramannil
//  blog:https://cppcodetips.wordpress.com/
//

#include <QDebug>
#include <QList>
#include <QObject>
#include <QVariant>
#include <vector>

/**
 * @brief The GameBoard class
 */
class GameBoard : public QObject
{
    Q_OBJECT
    Q_PROPERTY(int rows READ rows NOTIFY rowsChanged);
    Q_PROPERTY(int columns READ columns NOTIFY columnsChanged);

  public:
    Q_INVOKABLE void resetBoard();
    explicit GameBoard(const int rows, const int colums, QObject* parent = nullptr);
    enum Turn
    {
        Player = 1,
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

  signals:
    void rowsChanged(int m_nRows);
    void columnsChanged(int m_nColumns);
    void boardChanged(QVariantList arg);
    void updateCell(int row, int column);
    void cellClick(int row, int column);
    void showStatus(QString message);

  public slots:
    void cellValueChanged(int row, int column);
    void playComputer();

  private:
    /**
     * @brief checkRowColumnWiseAndMove
     * @return
     */
    bool checkRowColumnWiseAndMove();

    /**
     * @brief checkDiagonallyAndMove
     * @return
     */
    bool checkDiagonallyAndMove();

    /**
     * @brief fillFirstFreeCell
     * @return
     */
    bool fillFirstFreeCell();

    /**
     * @brief checkAllCellsareFilled
     * @return
     */
    bool checkAllCellsareFilled();

    /**
     * @brief checkCells
     * @param turn
     * @return
     */
    bool checkCells(Turn turn);

    /**
     * @brief move
     * @param row
     * @param column
     */
    void move(unsigned int row, unsigned column);

    /**
     * @brief display
     */
    void display();

    int                           m_nRows;
    int                           m_nColumns;
    QVariantList                  m_nBoard;
    std::vector<std::vector<int>> cell{
        {0, 0, 0, 0},
        {0, 0, 0, 0},
        {0, 0, 0, 0},
        {0, 0, 0, 0},
    };
};

#endif // GAMEBOARD_H
