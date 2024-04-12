//
// Created by kwojn on 4/7/2024.
//
#include <iostream>
#include <memory>
#include "Zwierzeta.h"
#include "Logger.h"

void Zwierzeta::act(Swiat &world) {
    this->moveThisOrganism(world, this->generateRandomLegalPosition(world));
}


void Zwierzeta::collide(Organizm * organism, Swiat & world) {
    // mate only if same type
    // TODO: Will this work?
    std::cout << typeid(*this).name() << "\n";
    if (typeid(*this) == typeid(*organism))
        this->mate(organism, world);
    else
        Organizm::collide(organism, world);
}

void Zwierzeta::mate(const Organizm* lover, Swiat & world) {
    Position position = this->generateRandomLegalPosition(world);
    auto copy = this->clone();
    copy->setPosition(std::move(position));
    logger.getInfoLogFile() << this->getName() << " romnozyl sie z " << lover->getName() << std::endl;
    world.spawn(std::shared_ptr<Organizm>(copy));
}

void decodeMove(Position& position, int move) {
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

Position Zwierzeta::generateRandomLegalPosition(const Swiat& world) {
    std::vector<Position> legalMoves;
    for (int i = 0; i < MAX_NEIGHBOURS; i++) {
        Position pos = this->getPosition();
        decodeMove(pos, i);
        if (world.isLegalPosition(pos))
            legalMoves.push_back(pos);
    }
    std::uniform_int_distribution<int> dist(0, legalMoves.size() - 1);
    int index = dist(rng);
    return legalMoves[index];
}
