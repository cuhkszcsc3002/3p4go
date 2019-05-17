#ifndef CHESSBOARD_H
#define CHESSBOARD_H

#include <QMainWindow>
#include <QMap>
#include <string>

namespace Ui {
class MainWindow;
}

#define INIT_POSX 500
#define INIT_POSY 500

class chessBoard : public QMainWindow
{
    Q_OBJECT

    /* Public section:
     * 1: constructor and distructor declaration.
     * 2: chessboard parameters declaration:
     *      phyLocation:    the physical location of the cursor (or locator)
     *      logLocation:    the logical location of the cursor
     *      leftBoundAxis:  the logical axis value of left boundary
     *      rightBoundAxis: the logical axis value of right boundary
     *      upBoundAxis:    the logical axis value of up boundary
     *      downBoundAxis:  the logical axis value of down boundary
     */
public:
    explicit chessBoard(QWidget *parent = nullptr);
    ~chessBoard();

    QPoint *phyLocation;
    QPoint *logLocation;

    QPoint *leftBoundAxis;
    QPoint *rightBoundAxis;
    QPoint *upBoundAxis;
    QPoint *downBoundAxis;

protected:
    void paintEvent(QPaintEvent *);
    void keyPressEvent(QKeyEvent *);

private:

    /*
     * Implementation notes: drawChessboard()
     * -----------------------------------------------------------------------------------------------
     * The size of the chessboard is 900 x 900 pix. Chessbaord has a line in every 50 pix.
     * The left boundary is fixed to be at x=50 pix, right boundary is fixed at x=950 pix.
     * The up boundary is fixed at y=50 pix, down boundary is fixed at y=950 pix. And the
     * center of the chessboard is fixed at (500 pix, 500 pix). Initially, the cursor is
     * located at the center of the chessboard, that is: at (500 pix, 500 pix) pyhiscally
     * at (0, 0) logically, and at the 10th line. By this mechanism, left boundary is at x=-9,
     * e.i. the 1st line and right boundary is at x=9, i.e. the 19th line. Same rule is
     * apply to the up boundary and down boundary. Beside this, the coordiante indicator
     * of the chessboard is also drawed.
     */
    void DrawChessboard();

    /*
     * Implementation notes: drawItems()
     * -----------------------------------------------------------------------------------------------
     * drawItems():
     * This method will first scan the list that contains the information of all the chess
     * stones on the chessboard. Then for those chess stones whose location is within the
     * chessbaord, that is: x value samller than right boundary and larger than left boundary,
     * y value smaller than down boundary and larger than up boundary, method will draw them
     * one by one on the screen.
     */
    void DrawItems();

    /*
     * Implementation notes: drawLocatorWithKeyboard()
     * -----------------------------------------------------------------------------------------------
     * This method will draw the cursor onto the chessboard. The cursor is an incomplete red
     * rectangle whose center is the corssing point that user currently at.
     */
    void drawLocatorWithKeyboard();

    /*
     * Fucntion: void drawStoneAtPoint(QPainter& painter, int logX, int logY)
     *
     * useage: drawChessboard(painter, x, y)
     *
     * This function will draw a single chess stone onto the chessborad at
     * the location provided.
     */
    void drawStoneAtPoint(QPainter& painter, int x, int y);

    Ui::MainWindow *ui;


    /* test stones*/
    QVector<std::string> Stone;
    bool isJump;


};

#endif // CHESSBOARD_H
