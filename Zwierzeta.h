//
// Created by kwojn on 4/7/2024.
//

#ifndef PROJEKT1_ZWIERZETA_H
#define PROJEKT1_ZWIERZETA_H


#include "Organizm.h"

class Zwierzeta: public Organizm {
    // helper function
    static void translateMoveNumberToPosition(Position &position, int move);
    void mate(const Organizm* other, Swiat&);
protected:
    Zwierzeta(int attack, int aggressiveness, Position&& position): Organizm(attack, aggressiveness, std::move(position)) {}
public:
    void act(Swiat &world) override;
    bool collide(Organizm*, Swiat&) override;
    Position generateRandomLegalPosition(const Swiat& world);
};

class Wilk : public Zwierzeta {
protected:
    std::string name() const override {
        return "Wilk";
    }
public:
    explicit Wilk(Position&& pos): Zwierzeta(9, 5, std::move(pos)) {}

    Organizm *clone() override {
        return new Wilk{*this};
    }

    const char symbol() override {
        return 'W';
    }


};

class Owca : public Zwierzeta {
protected:
    std::string name() const override {
        return "Owca";
    }
public:
    explicit Owca(Position&& pos) : Zwierzeta(4, 4, std::move(pos)) {}

    Owca *clone() override {
        return new Owca{*this};
    }
    const char symbol() override {
        return 'O';
    }
};

class Zolw : public Zwierzeta {

protected:
    std::string name() const override {
        return "Zolw";
    }

public:
    explicit Zolw(Position&& pos) : Zwierzeta(2, 1, std::move(pos)) {}
    const char symbol() override {
        return 'Z';
    }

    Organizm *clone() override {
        return new Zolw{*this};
    }
    // 25% chance to move
    void act(Swiat &world) override;

protected:
    bool didDeflectAttack(const Organizm *attacker) override;
};


#endif //PROJEKT1_ZWIERZETA_H
