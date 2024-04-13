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
    void collide(Organizm*, Swiat&) override;
    Position generateRandomLegalPosition(const Swiat& world);
};

class Wilk : public Zwierzeta {
public:
    explicit Wilk(Position&& pos): Zwierzeta(9, 5, std::move(pos)) {}

    Organizm *clone() override {
        return new Wilk{*this};
    }

    const char symbol() override {
        return 'W';
    }

    std::string name() const override {
        return "Wilk";
    }

};

class Owca : public Zwierzeta {
public:
    explicit Owca(Position&& pos) : Zwierzeta(4, 4, std::move(pos)) {}

    Owca *clone() override {
        return new Owca{*this};
    }
    const char symbol() override {
        return 'O';
    }

    std::string name() const override {
        return "Owca";
    }
};


#endif //PROJEKT1_ZWIERZETA_H
