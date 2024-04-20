#pragma once

#include <utility>
#include <memory>
#include <random>
#include "Swiat.h"
#include "Loader.h"

constexpr int MAX_NEIGHBOURS = 4;
constexpr int NON_MOVABLE_ORGANISM = -1;

class Organizm
        : public std::enable_shared_from_this<Organizm>, protected Serializable {
    friend class Loader;

    bool alive = true;
    int attack = 0;
public:
    void setAttack(int attack);

    static void translateMoveNumberToPosition(Position &position, int move);

private:
    int aggressiveness = 0;
    Position position;
    int age = 0;

private:
    int id = 0;
protected:
    virtual bool didDeflectAttack(const Organizm *attacker);

    std::mt19937 rng;

    Organizm(int attack, int aggressiveness, Position &&position) : attack(attack), aggressiveness(aggressiveness),
                                                                    position(std::move(position)) {
        std::random_device dev;
        rng = std::mt19937(dev());
    }

    [[nodiscard]] virtual std::string name() const = 0;

    std::string organismName;

    virtual bool isLegalMove(const Position &position, Swiat &world, bool skipOccupied);

    Position generateRandomLegalPosition(Swiat &world, bool skipOccupied = false);

public:
    void kill();

    Organizm(const Organizm &right);

    [[nodiscard]] bool isAlive() const;

    [[nodiscard]] int getAttack() const;

    [[nodiscard]] const Position &getPosition() const;

    [[nodiscard]] int getAge() const;

    [[nodiscard]] int getAggressiveness() const;

    void setPosition(Position &&position);

    virtual void moveThisOrganism(Swiat &world, Position &&newPosition);

    virtual void act(Swiat &world) = 0;

    /**
     * @return false if the attack didnt succeed and both survived
     */
    virtual bool collide(Organizm *collider, Swiat &world);

    [[nodiscard]] virtual const char symbol() = 0;

    [[nodiscard]] const std::string &getName() const;

    virtual Organizm *clone() = 0;

    virtual ~Organizm() = default;

    virtual void endTurn();

    void setId(int id);

    void setAge(int age);

    bool operator==(const Organizm &other);
};
