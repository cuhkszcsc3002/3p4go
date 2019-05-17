#ifndef COORDINATE_H
#define COORDINATE_H


class Coordinate
{
    /*
     * Constructor
     * Initialize a coordinate object.
     * ------------------------------
     * Usage: Coordinate Coordinate;
     */

     Coordinate();

public:

    /*
     * playerIndex
     * The playerIndex for the current player. Its range is from 0 to 2.
     */

    int playerIndex;
    int x;
    int y;


    Coordinate(int playerIndex, int x, int y);

};

#endif // COORDINATE_H
