//
// Created by kwojn on 4/6/2024.
//
#include <iostream>
#include "Organizm.h"
#include "Logger.h"


void Organizm::kill() {
    logger->getInfoLogFile() << getName() << " zostal zabity" << std::endl;
    this->alive = false;
}

bool Organizm::isAlive() const {
    return this->alive;
}

int Organizm::getAttack() const {
    return attack;
}

const Position &Organizm::getPosition() const {
    return this->position;
}

void Organizm::endTurn() {
    age++;
}

[[nodiscard]] int Organizm::getAge() const {
    return age;
}

bool Organizm::collide(Organizm *collider, Swiat &world) {
    logger->getInfoLogFile() << collider->getName() << " wszedl na pole " << name() << std::endl;\
    if (this->didDeflectAttack(collider))
        return false;
    else if (collider->getAttack() >= this->getAttack())
        this->kill();
    else
        collider->kill();
    return true;
}

int Organizm::getAggressiveness() const {
    return aggressiveness;
}

void Organizm::moveThisOrganism(Swiat &world, Position &&newPosition) {
    auto collideeOrganism = world.getEntityAt(newPosition);
    auto oldPosition = this->position;
    this->position = newPosition;
    world.moveOrganism(oldPosition, shared_from_this());
    if (collideeOrganism && collideeOrganism != this) {
        if (!collideeOrganism->collide(this, world)) {
            // if both survived push attacker back
            auto newPosition = std::move(this->position);
            this->position = oldPosition;
            world.moveOrganism(newPosition, shared_from_this());
        }
    }
    if (this->isAlive()) {
        logger->getInfoLogFile() << this->getName() << " przesunal sie na x=" << position_x(position)
                                 << " y=" << position_y(position) << std::endl;
    }
}

Organizm::Organizm(const Organizm &right) : enable_shared_from_this() {
    attack = right.attack;
    aggressiveness = right.aggressiveness;
    alive = right.alive;
    position = right.position;
    age = right.age;
    std::random_device dev;
    rng = std::mt19937(dev());
}

void Organizm::setPosition(Position &&position) {
    this->position = position;
}

void Organizm::setId(int id) {
    Organizm::id = id;
    organismName = name() + std::to_string(id);
}

const std::string &Organizm::getName() const {
    return organismName;
}

bool Organizm::operator==(const Organizm &other) {
    return other.id == this->id;
}

bool Organizm::didDeflectAttack(const Organizm *attacker) {
    return false;
}

Position Organizm::generateRandomLegalPosition(Swiat &world, bool skipOccupied) {
    std::vector<Position> legalMoves;
    for (int i = 0; i < MAX_NEIGHBOURS; i++) {
        Position pos = this->getPosition();
        translateMoveNumberToPosition(pos, i);
        if (world.isLegalPosition(pos) && isLegalMove(pos, world, false))
            legalMoves.push_back(pos);
    }
    std::uniform_int_distribution<int> dist(0, legalMoves.size() - 1);
    int index = dist(rng);
    return legalMoves[index];
}

void Organizm::translateMoveNumberToPosition(Position &position, int move) {
    switch (move) {
        case 0:
            position.first += 1;
            break;
        case 1:
            position.first -= 1;
            break;
        case 2:
            position.second += 1;
            break;
        case 3:
            position.second -= 1;
            break;
    }
}

bool Organizm::isLegalMove(const Position &position, Swiat &world, bool skipOccupied) {
    // when mating don't spawn in occupied fields because it could let to a lot of spawns fast
    return !(skipOccupied && world.getEntityAt(position));
}

void Organizm::setAttack(int attack) {
    Organizm::attack = attack;
}

void Organizm::setAge(int age) {
    Organizm::age = age;
}
