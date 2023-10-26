#ifndef SUBJECT_H
#define SUBJECT_H
#include <vector>
#include "core/observer.h"

using namespace std;

class Subject
{
public:
    Subject();
    void notifyObservers();
    void registerObserver(Observer* observer);

private:
    vector<Observer*> observers;
};

#endif // SUBJECT_H
