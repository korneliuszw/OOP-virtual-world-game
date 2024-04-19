//
// Created by kwojn on 4/7/2024.
//
#include <iostream>
#include <memory>
#include "Zwierzeta.h"
#include "Logger.h"

void Zwierzeta::act(Swiat &world) {
    this->moveThisOrganism(world, this->generateRandomLegalPosition(world, false));
}


bool Zwierzeta::collide(Organizm *organism, Swiat &world) {
    if (typeid(*this) != typeid(*organism))
        return Organizm::collide(organism, world);
    if (organism->getAge() > 0 && this->getAge() > 0)
        this->mate(organism, world);
    return true;
}

void Zwierzeta::mate(const Organizm *lover, Swiat &world) {
    Position position = this->generateRandomLegalPosition(world, true);
    if (position == this->getPosition())
        return;
    auto copy = this->clone();
    copy->setPosition(std::move(position));
    logger->getInfoLogFile() << this->getName() << " rozmnozyl sie z " << lover->getName() << std::endl;
    world.spawn(std::shared_ptr<Organizm>(copy));
}

bool Zolw::didDeflectAttack(const Organizm *attacker) {
    return attacker->getAttack() < 5;
}

void Zolw::act(Swiat &world) {
    std::uniform_int_distribution<int> dist(1, 4);
    int random = dist(rng);
    if (random == 1)
        Zwierzeta::act(world);
}

bool Lis::isLegalMove(const Position &position, Swiat &world, bool mating) {
    auto organismAtPosition = world.getEntityAt(position);
    if (organismAtPosition && organismAtPosition->getAttack() > this->getAttack())
        return false;
    return Zwierzeta::isLegalMove(position, world, mating);
}

bool Antylopa::collide(Organizm *organizm, Swiat &swiat) {
    std::uniform_int_distribution<int> dist(1, 2);
    if (dist(rng) == 1) {
        auto pos = generateRandomLegalPosition(swiat, true);
        if (pos != this->getPosition()) {
            logger->getInfoLogFile() << this->getName() << " uciekla przed " << organizm->getName() << std::endl;
            this->moveThisOrganism(swiat, std::move(pos));
            return true;
        }
    }
    return Zwierzeta::collide(organizm, swiat);
}

void Antylopa::act(Swiat &world) {
    // this is hacky but we need to keep original position to revert in case of push backs
    // so we need to save it, set pos to position + 1
    // then get second position because it moves by two
    auto currentPosition = this->getPosition();
    this->setPosition(this->generateRandomLegalPosition(world));
    auto newPosition = this->generateRandomLegalPosition(world);
    // revert current position
    this->setPosition(std::move(currentPosition));
    this->moveThisOrganism(world, std::move(newPosition));
}

