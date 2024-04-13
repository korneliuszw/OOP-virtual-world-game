//
// Created by kwojn on 4/6/2024.
//
#include <algorithm>
#include "Swiat.h"
#include "Organizm.h"
#include "Logger.h"

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
    auto found = mapper.find(position);
    if (found == mapper.end()) return nullptr;
    // FIXME: this isn't safe?
    for (auto& item: found->second) {
        if (item->isAlive())
            return item.get();
    }
    return nullptr;
}

void Swiat::spawn(std::shared_ptr<Organizm> organism, bool forceInsert) {
    auto name = typeid(*organism).name();
    logger.getDebugLogFile() << "spawned " << name << std::endl;
    auto counter=  organismTypeCounter.find(name);
    if (counter != organismTypeCounter.end()) {
        organism->setId(++counter->second);
    } else {
        organism->setId(0);
        organismTypeCounter.insert({name, 0});
    }
    this->organismActionQueue.push(organism);
    insertOrganism(organism);
}

Swiat::Swiat(int width, int height) : width(width), height(height) {}


void Swiat::moveOrganism(const Position& oldPosition, std::shared_ptr<Organizm> organism) {
    auto existing = mapper.find(oldPosition);
    if (existing != mapper.end() && existing->second.size() > 1) {
        existing->second.remove(organism);
    }
    else if (existing != mapper.end())
        mapper.erase(oldPosition);
    insertOrganism(organism);
}

void Swiat::turn() {
    logger.getInfoLogFile() << "nowa tura" << std::endl;
    actTurn();
    endTurn();
    changed = true;
}

void Swiat::endTurn() {
    organismActionQueue = OrganismQueue();
    for (auto it = mapper.begin(); it != mapper.end(); it++) {
        auto& organismList = it->second;
        organismList.remove_if([&](auto& organism) {
            if (organism->isAlive()) {
                organism->endTurn();
                organismActionQueue.push(organism);
            }
            return !organism->isAlive();
        });
        if (organismList.empty()) {
            it = mapper.erase(it);
        }
    };
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
        return a->getAge() < b->getAge();
    return a->getAggressiveness() < b->getAggressiveness();
}


bool Swiat::isLegalPosition(const Position &position) const {
    return position_x(position) >= 0 && position_x(position) < width && position_y(position) >= 0 && position_y(position) < height;
}

bool Swiat::hasChanged() const {
    return changed;
}

void Swiat::draw(WindowManager& manager) {
    logger.getDebugLogFile() << "Drawing" << std::endl;
    WINDOW* gameWindow = manager.getMainGameWindow();
    wclear(gameWindow);
    for (int y = 0; y < height; y++) {
        for (int x = 0; x < width; x++) {
            auto entity = getEntityAt({x, y});
            wmove(gameWindow, y, x);
            if (entity)
                waddch(gameWindow, entity->symbol());
            else
                waddch(gameWindow, 'X');
        }
    }
    changed = false;
    logger.getDebugLogFile() << "Finished drawing" << std::endl;
}

void Swiat::insertOrganism(std::shared_ptr<Organizm> organism) {
    auto positionOrganisms = mapper.find(organism->getPosition());
    if (positionOrganisms != mapper.end())
        positionOrganisms->second.push_back(organism);
    else
        mapper.insert({organism->getPosition(), {organism}});
}
