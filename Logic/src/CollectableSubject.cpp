//
// Created by milo on 11/23/25.
//

#include "../include/CollectableSubject.h"
#include "Event.h"

namespace logic::entity {
void CollectableSubject::destruct() {
    core::Event e = core::Event::EntityDestruct;
    notify(e);
}
} // namespace logic
