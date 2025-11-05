//
// Created by milo on 11/5/25.
//

#include "../include/Subject.h"

#include "../include/Observer.h"

void logic::Subject::removeObserver(Observer* o) {
    for (int i = 0; i < observers.size(); i++) {
        if (observers[i] == o) {
            observers.erase(observers.begin() + i);
        }
    }
}

void logic::Subject::notify(Event event) {
    for (auto observer : observers) {
        observer->onNotify(*this, event);
    }
}