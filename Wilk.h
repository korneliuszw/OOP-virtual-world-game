#pragma once

#include "Organizm.h"

enum AttackBehaviour {
    ATTACK,
    PUSH
}

class Zwierzeta: public Organizm {
protected:
    AttackBehaviour attackBehaviour;
}

Zwierzeta::act(int neighbors[MAX_NEIGHBOURS]) {
}

class Wilk: public Zwierzeta {
    Wilk(Position position): Organizm(5, 4, position), attackBehaviour(ATTACK) {}
    void act(int neighbors[MAX_NEIGHBOURS]) override;
}
