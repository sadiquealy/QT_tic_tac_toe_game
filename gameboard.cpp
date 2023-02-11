#include "gameboard.h"
#include <QVariant>
#include<QDebug>
#include<QtGlobal>
#include <QRandomGenerator>
#define PLAYER 1
#define COMPUTER 2

#define CHECK_ALL_CONDITION(PLAYER,MESSAGE)  {        if(checkCells(PLAYER)) \
{ \
    emit showStatus(MESSAGE); \
    } \
    else if(checkAllCellsareFilled()) \
{  \
    emit showStatus("Game is over !!! Draw"); \
    } \
    }
GameBoard::GameBoard(const int rows,const int colums,QObject *parent)
    : m_nRows(rows),m_nColumns(colums),QObject{parent}
{

    for(int i=0;i<rows;i++)
    {
        QVariantList row {0,0,0,0};

        m_nBoard.push_back(row);
    }

}

bool GameBoard::checkAllCellsareFilled()
{
    bool status = true;

    for(int i=0;i<m_nRows;i++)
    {
        for(int j=0;j<m_nRows;j++)
        {
            qDebug()<<"cell row:"<<i<<"column:"<<j<<"value:"<<cell[i][j];
            if(!cell[i][j])
            {
                status=false;
                break;
            }
        }

    }

    return status;
}

bool GameBoard::checkCells(Turn turn)
{
    bool status = false;
    //check column wise
    for(int i=0;i<m_nRows;i++)
    {
        int resultRow = cell[i][0];
        int resultColumn = cell[0][i];
        for(int j=0;j<m_nColumns;j++)
        {
            resultRow &= (cell[i][j] & turn);
            resultColumn &= (cell[j][i] & turn);
        }

        if(resultRow == turn || resultColumn == turn)
        {
            qDebug()<<"column filled or row filled";
            status= true;
            break;
        }

    }

    int resultLeftDiag =cell[0][0];
    int resultRowWise=cell[0][m_nColumns-1];
    for(int i=0,j=m_nColumns-1;i<m_nRows;i++,j--)
    {
        resultLeftDiag&= cell[i][i];
        resultRowWise&= cell[i][j];
    }

    if(resultLeftDiag == turn || resultRowWise == turn)
    {
        qDebug()<<"diagonal filled ";
        status= true;
    }
    return status;
}


void GameBoard::cellValueChanged(int row, int column)
{
    if(row <=m_nRows && column<=m_nColumns)
    {
        qDebug()<<"set board slot recieved row:"<<row<<"column:"<<column;
        cell[row][column]=1;
        CHECK_ALL_CONDITION(Turn::Player,"Game is over !!! You have won");
    }

}

void GameBoard::move(unsigned int row, unsigned column)
{
    cell[row][column]=2;
    emit updateCell(row,column);
    CHECK_ALL_CONDITION(Turn::Computer,"Game is over Computer Has won");

}
void GameBoard::display()
{
    for(unsigned int i=0;i<m_nRows;i++)
    {

        for(unsigned int j=0;j<m_nColumns;j++)
        {
            qDebug()<<i<<":"<<j<<":"<<cell[i][j];
        }
    }
}

void GameBoard::resetBoard()
{
    qDebug()<<"restt is aclled  ";
    for(unsigned int i=0;i<m_nRows;i++)
    {
        for(unsigned int j=0;j<m_nColumns;j++)
        {
            cell[i][j]=0;
        }
    }
}

void GameBoard::playComputer()
{


    for(unsigned int i=0;i<m_nRows;i++)
    {
        Pos freePosRow;
        Pos freePosColumn;
        int arrayRowCount[4]={0};
        int arrayColumnCount[4]={0};
        for(unsigned int j=0;j<m_nColumns;j++)
        {
            arrayRowCount[cell[i][j]]++;
            arrayColumnCount[cell[j][i]]++;
            if(!cell[i][j])
            {
                freePosRow.x =i;
                freePosRow.y=j;
            }
            if(!cell[j][i])
            {
                freePosColumn.x =j;
                freePosColumn.y=i;
            }
        }

        if(arrayRowCount[Turn::Player] == (m_nRows-1) || arrayRowCount[Turn::Computer] == (m_nColumns-1))
        {
            if(arrayRowCount[0] >0)
            {

                move(freePosRow.x,freePosRow.y);
                return;
            }
        }

        if(arrayColumnCount[Turn::Player] == (m_nRows-1) || arrayColumnCount[Turn::Computer] == (m_nColumns-1))
        {
            if(arrayColumnCount[0] >0)
            {

                move(freePosColumn.x,freePosColumn.y);
                return;
            }
        }
    }

    int arrayLeftDiagonal[4]={0};
    int arrayRightDiagonal[4]={0};
    Pos freePosDiagonalLeft;
    Pos freePosDiagonalRight;
    for(int i=0,j=m_nColumns-1;i<m_nRows;i++,j--)
    {
        arrayRightDiagonal[cell[i][j]]++;
        arrayLeftDiagonal[cell[i][i]]++;
        if(!cell[i][i])
        {
            freePosDiagonalLeft.x =i;
            freePosDiagonalLeft.y=i;
        }
        if(!cell[i][j])
        {
            qDebug()<<"inside void "<<i<<":"<<j;
            freePosDiagonalRight.x =i;
            freePosDiagonalRight.y=j;
        }
    }
    qDebug()<<"processingdiagonal field field:"<<arrayRightDiagonal[Turn::Player]<<"arrayRightDiagonal[0]"<<arrayRightDiagonal[0];
    display();
    if(arrayLeftDiagonal[Turn::Player] == (m_nRows-1) || arrayLeftDiagonal[Turn::Computer] == (m_nColumns-1))
    {
        if(arrayLeftDiagonal[0] >0)
        {

            move(freePosDiagonalLeft.x,freePosDiagonalLeft.y);
            return;
        }
    }

    if(arrayRightDiagonal[Turn::Player] == (m_nRows-1) || arrayRightDiagonal[Turn::Computer] == (m_nColumns-1))
    {
        qDebug()<<"---- ";
        if(arrayRightDiagonal[0] >0)
        {
            qDebug()<<"moving rigth ";
            move(freePosDiagonalRight.x,freePosDiagonalRight.y);
            return;
        }
    }

    qDebug()<<"processing any empty field";

    for(unsigned int i=0;i<m_nRows;i++)
    {

        for(unsigned int j=0;j<m_nColumns;j++)
        {
            if(!cell[i][j])
            {
                qDebug()<<"found empty at:"<<i<<":"<<j;
                move(i,j);
                return;
            }
        }
    }


}
