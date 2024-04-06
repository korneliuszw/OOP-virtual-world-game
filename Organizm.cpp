//
// Created by kwojn on 4/6/2024.
//
#include "Organizm.h"

void Organizm::kill() {
    this->alive = false;
}

bool Organizm::isAlive() const {
    return this->alive;
}

int Organizm::getAttack() const {
    return attack;
}

const Position& Organizm::getPosition() const {
    return this->position;
}
void Organizm::endTurn() {
    age++;
}
[[nodiscard]] int Organizm::getAge() const {
    return age;
}

void Organizm::collide(Organizm *collider, const Swiat& world) {
    if (collider->getAttack() >= this->getAttack())
        this->kill();
    else
        collider->kill();
}
