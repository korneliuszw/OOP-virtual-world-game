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

void Organizm::collide(Organizm *collider, Swiat& world) {
    if (collider->getAttack() >= this->getAttack())
        this->kill();
    else
        collider->kill();
}

int Organizm::getAggressiveness() const {
    return aggressiveness;
}

void Organizm::moveThisOrganism(Swiat &world, Position &&newPosition) {
    auto collideeOrganism = world.getEntityAt(newPosition);
    if (collideeOrganism) {
        collideeOrganism->collide(this, world);
    }
    if (this->isAlive()) {
        auto oldPosition = this->position;
        this->position = newPosition;
        world.moveOrganism(oldPosition, shared_from_this());
    }
}

Organizm::Organizm(const Organizm &right)  : enable_shared_from_this() {
    attack = right.attack;
    aggressiveness = right.aggressiveness;
    alive = right.alive;
    position = right.position;
    age = right.age;
}

void Organizm::setPosition(Position &&position) {
    this->position = position;
}

std::default_random_engine& getRNG() {
    static std::default_random_engine rng;
    return rng;
}

