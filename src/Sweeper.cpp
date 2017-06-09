#include "Sweeper.h"
#include <climits>
#include <iostream>

/**
*   Wojciech Janaszek 273689 ISI
*   T11 - rozpl¹tywanie odcinków
*/

using namespace std;

Sweeper::Sweeper()
{}

Sweeper::~Sweeper()
{}

void Sweeper::push(Segment * s)
{
    container.push_back(s);
}

void Sweeper::remove(Segment * s)
{
    int index = -1;
    for(int i = 0; i < container.size(); i++){
        if(s->getLeft().getX() == container[i]->getLeft().getX() && s->getLeft().getY() == container[i]->getLeft().getY()
           && s->getRight().getX() == container[i]->getRight().getX() && s->getRight().getY() == container[i]->getRight().getY()
           && s->N == container[i]->N){
            index = i;
            break;
        }
    }
    if(index != -1){
        container.erase(container.begin() + index);
    }
    else {
        cout << "Blad usuwania!!!" << endl;
    }
}

Segment * Sweeper::getElementAt(int index)
{
    return container.at(index);
}

int Sweeper::getSize()
{
    return container.size();
}

// "ABOVE"
Segment * Sweeper::previous(Segment * s)
{
    return NULL;
}

// "BELOW"
Segment * Sweeper::next(Segment * s)
{
    return NULL;
}
