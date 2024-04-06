#pragma once

#include <utility>
#include <memory>
#include "Swiat.h"

constexpr int MAX_NEIGHBOURS = 8;
constexpr int NON_MOVABLE_ORGANISM = -1;
class Organizm
: public std::enable_shared_from_this<Organizm>
        {
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
    [[nodiscard]] int getAggressiveness() const;
    virtual void move(Swiat& world, Position&& newPosition);
    virtual void act(Swiat& world) = 0;
    virtual void collide(Organizm*, const Swiat&);
    virtual void draw() = 0;


    void endTurn();
};