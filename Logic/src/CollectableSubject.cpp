//
// Created by milo on 11/23/25.
//

#include "../include/CollectableSubject.h"

namespace logic {
void CollectableSubject::destruct() {
    Event e = Event::EntityDestruct;
    notify(e);
}
} // namespace logic
