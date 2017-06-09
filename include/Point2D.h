#ifndef POINT2D_H
#define POINT2D_H

/**
*   Wojciech Janaszek 273689 ISI
*   T11 - rozpl¹tywanie odcinków
*/

#include <vector>
#include <string>

using namespace std;

class Point2D
{
    public:
        Point2D();
        Point2D(int x, int y);
        Point2D(int x, int y, int groupNumber);
        Point2D(string input, int groupNumber);
        ~Point2D();

        int getX();
        int getY();
        void setX(int val);
        void setY(int val);
        // Sprawdza, czy p3 lezy na prostej laczacej p1 i p2 (zakladamy wspolniniowosc [wtw. gdy det() == 0] odcinka p1p2)
        static bool onSegment(Point2D p1, Point2D p2, Point2D p3);
        static int direction(Point2D p1, Point2D p2, Point2D p3);

        int groupNumber;
    private:
        int x;
        int y;
        vector<string> split(const string & text, char sep);
};

#endif // POINT2D_H
