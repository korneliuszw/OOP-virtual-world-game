//
// Created by kwojn on 4/15/2024.
//

#ifndef PROJEKT1_PLAYER_H
#define PROJEKT1_PLAYER_H

#include "Zwierzeta.h"
#include <optional>

class Player : public Zwierzeta {
    WindowManager *windowManager;
protected:
    std::string name() const override {
        return "Gracz";
    }

public:
    Player(Position &&pos, WindowManager *windowManager) : Zwierzeta(5, 4, std::move(pos)),
                                                           windowManager(windowManager) {}

    const char symbol() override {
        return 'P';
    }

    // this won't happen
    Organizm *clone() override {
        return nullptr;
    }


    void act(Swiat &world) override;

    // return true if there are more actions to be done
    bool doPlayerActions(Swiat &world);

    std::optional<Position> getNewPositionFromUser(Swiat &world, int key);

    bool collide(Organizm *organizm, Swiat &swiat) override;
};


#endif //PROJEKT1_PLAYER_H
