//
// Created by milo on 11/4/25.
//

#include "../include/CoinModel.h"

void logic::CoinModel::destruct() {
    Event e = Event::EntityDestruct;
    notify(e);
}