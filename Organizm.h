#pragma once

#include <utility>
#include <memory>
#include <random>
#include "Swiat.h"

constexpr int MAX_NEIGHBOURS = 4;
constexpr int NON_MOVABLE_ORGANISM = -1;
class Organizm
: public std::enable_shared_from_this<Organizm>
        {
    bool alive = true;
    int attack = 0;
    int aggressiveness = 0;
    Position position;
    int age = 0;
    void kill();
    int id = 0;
protected:
    std::mt19937 rng;
    Organizm(int attack, int aggressiveness, Position&& position): attack(attack), aggressiveness(aggressiveness), position(std::move(position)) {
        std::random_device dev;
        rng = std::mt19937(dev());
    }
    [[nodiscard]] virtual std::string name() const = 0;
    std::string organismName;
public:
    Organizm(const Organizm& right);
    [[nodiscard]] bool isAlive() const;
    [[nodiscard]] int getAttack() const;
    [[nodiscard]] const Position& getPosition() const;
    [[nodiscard]] int getAge() const;
    [[nodiscard]] int getAggressiveness() const;
    void setPosition(Position&& position);
    virtual void moveThisOrganism(Swiat& world, Position&& newPosition);
    virtual void act(Swiat& world) = 0;
    virtual void collide(Organizm*, Swiat&);
    [[nodiscard]] virtual const char symbol() = 0;
    [[nodiscard]] const std::string& getName() const;
    virtual Organizm* clone() = 0;
    virtual ~Organizm() = default;
    void endTurn();
    void setId(int id);
    bool operator==(const Organizm& other);
};
