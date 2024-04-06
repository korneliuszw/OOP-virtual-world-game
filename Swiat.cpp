//
// Created by kwojn on 4/6/2024.
//
#include "Swiat.h"
#include "Organizm.h"

void Swiat::actTurn() {
    // copy the queue
    while (!organismActionQueue.empty()) {
        auto organism = organismActionQueue.top();
        organismActionQueue.pop();
        if (!organism->isAlive()) {
            continue;
        }
        organism->act(*this);
    }
}


Organizm *Swiat::getEntityAt(const Position &position) {
    return nullptr;
}

void Swiat::spawn(std::shared_ptr<Organizm> organizm) {
    this->organismActionQueue.push(organizm);
}

Swiat::Swiat(int width, int height) : width(width), height(height) {}

void Swiat::moveOrganism(const Position& oldPosition, std::shared_ptr<Organizm> organism) {
    mapper.erase(oldPosition);
    mapper.insert({organism->getPosition(), organism});
}

void Swiat::turn() {
    actTurn();
}

void Swiat::endTurn() {
    organismActionQueue = OrganismQueue();
    for (const auto& item: mapper) {
        auto organism = item.second;
        if (!organism->isAlive()) {
            mapper.erase(item.first);
            continue;
        }
        organismActionQueue.push(organism);
    }
}


bool OrganizmCompare::operator()(const std::shared_ptr<Organizm>& a, const std::shared_ptr<Organizm>& b) {
    if (!a || !b)
        return a < b;
    // swap elements if next object is non movable as this one has higher priority
    else if (a->getAggressiveness() == NON_MOVABLE_ORGANISM && b->getAggressiveness() != NON_MOVABLE_ORGANISM)
        return true;
    else if (b->getAggressiveness() == NON_MOVABLE_ORGANISM && a->getAggressiveness() != NON_MOVABLE_ORGANISM)
        return false;
    else if (a->getAggressiveness() == b->getAggressiveness())
        return a->getAge() >= b->getAge();
    return a->getAggressiveness() > b->getAggressiveness();
}


