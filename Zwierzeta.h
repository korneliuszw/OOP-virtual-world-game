//
// Created by kwojn on 4/7/2024.
//

#ifndef PROJEKT1_ZWIERZETA_H
#define PROJEKT1_ZWIERZETA_H


#include "Organizm.h"

class Zwierzeta: public Organizm {
    void mate(const Organizm* other, Swiat&);
protected:
    Zwierzeta(int attack, int aggressiveness, Position&& position): Organizm(attack, aggressiveness, std::move(position)) {}
public:
    void act(Swiat &world) override;
    void collide(Organizm*, Swiat&) override;
};

class Wilk : public Zwierzeta {
public:
    Wilk(Position&& pos): Zwierzeta(9, 5, std::move(pos)) {}

    Organizm *clone() override {
        return new Wilk{*this};
    }

    const char symbol() override {
        return 'W';
    }

    const char *name() override {
        return "Wilk";
    }

};


#endif //PROJEKT1_ZWIERZETA_H
