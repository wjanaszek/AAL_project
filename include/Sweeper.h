#ifndef SWEEPER_H
#define SWEEPER_H

/**
*   Wojciech Janaszek 273689 ISI
*   T11 - rozplątywanie odcinków
*/

#include <vector>
#include "Segment.h"

using namespace std;

class Sweeper
{
    public:
        Sweeper();
        ~Sweeper();
        void push(Segment * s);
        void remove(Segment * s);
        int getSize();

        // test only:
        Segment * getElementAt(int index);
        //Segment & getElementAt(int index);

        Segment * previous(Segment * s);
        Segment * next(Segment * s);
    private:
        vector<Segment*> container;
};

#endif // SWEEPER_H
