//
// Created by kwojn on 4/7/2024.
//
#include <iostream>
#include <memory>
#include "Zwierzeta.h"

void Zwierzeta::act(Swiat &world) {
    std::uniform_int_distribution<int> dist(1, MAX_NEIGHBOURS);
    int moves = MAX_NEIGHBOURS;
    while (moves > 0) {
        int move = dist(getRNG());
        Position position = this->getPosition();
        switch (move % moves) {
            case 1:
                position.first += 1;
                break;
            case 2:
                position.first -= 1;
                break;
            case 3:
                position.second += 1;
                break;
            case 4:
                position.second -= 1;
                break;
        }
        if (world.isLegalPosition(position)) {
            this->moveThisOrganism(world, std::move(position));
            return;
        }
        moves--;
    }
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
    std::uniform_int_distribution<int> dist(1, 4);
    int moves = 4;
    while (moves > 0) {
        int move = dist(getRNG());
        Position position = getPosition();
        auto &loverPosition = lover->getPosition();
        switch (move % moves) {
            case 1:
                if (position_x(position) != position_x(loverPosition)
                ) {
                    position.first -= position_x(position) > position_x(loverPosition) ? 2 : 1;
                }
                else
                    position.first -= 1;
                break;
            case 2:
                if (position_x(position) != position_x(loverPosition))
                    position.first += position_x(position) > position_x(loverPosition) ? 1 : 2;
                else
                    position.first += 1;
                break;
            case 3:
                if (position_x(position) != position_x(loverPosition))
                    position.second += 1;
                else
                    position.second -= position_y(position) > position_y(loverPosition) ? 1 : 2;
                break;
            case 4:
                if (position_x(position) != position_x(loverPosition))
                    position.second -= 1;
                else
                    position.second += position_y(position) > position_y(loverPosition) ? 1 : 2;
        }
        if (world.isLegalPosition(position)) {
            auto copy = this->clone();
            copy->setPosition(std::move(position));
            world.spawn(std::shared_ptr<Organizm>(copy));
            return;
        }
        moves--;

    }
}
