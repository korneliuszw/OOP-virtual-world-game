#pragma once

#include <utility>

#include "Swiat.h"

constexpr int MAX_NEIGHBOURS = 8;

class Organizm {
private:
    bool alive = true;
    int attack = 0;
    int aggressiveness = 0;
    Position position;
    int age = 0;
    void kill();
public:
    Organizm(int attack, int aggressiveness, Position&& position): attack(attack), aggressiveness(aggressiveness), position(std::move(position)) {}
    [[nodiscard]] bool isAlive() const;
    [[nodiscard]] int getAttack() const;
    [[nodiscard]] const Position& getPosition() const;
    [[nodiscard]] int getAge() const;
    virtual void act(const Swiat& world) = 0;
    virtual void collide(Organizm*, const Swiat&);
    virtual void draw() = 0;


    void endTurn();
};