//
// Created by kwojn on 4/15/2024.
//

#include "Player.h"
#include "Logger.h"
#include <thread>


void Player::act(Swiat &world) {
    logger.getInfoLogFile() << "Ruch gracza" << std::endl;
    WINDOW* gameWindow = windowManager->getMainGameWindow();
    curs_set(1);
    wmove(gameWindow, this->getPosition().second, this->getPosition().first + 1);
    wrefresh(gameWindow);
    while (true) {
        auto pos = getNewPositionFromUser(world);
        if (pos.has_value()) {
            this->moveThisOrganism(world, std::move(pos.value()));
            break;
        }
        std::this_thread::sleep_for(std::chrono::milliseconds(75));
    }
    curs_set(0);
}

bool Player::collide(Organizm *organizm, Swiat &swiat) {
    return Zwierzeta::collide(organizm, swiat);
}

std::optional<Position> Player::getNewPositionFromUser(Swiat& world) {
    int key;
    auto position = this->getPosition();
    bool changed;
    while ((key = getch()) != ERR) {
        changed = false;
        logger.getDebugLogFile() << " got key " << key << std::endl;
        switch (key) {
            case KEY_LEFT:
                changed = true;
                position.first -= 1;
                break;
            case KEY_RIGHT:
                changed = true;
                position.first += 1;
                break;
            case KEY_UP:
                changed = true;
                position.second -= 1;
                break;
            case KEY_DOWN:
                changed = true;
                position.second += 1;
                break;
        }
        if (changed && !world.isLegalPosition(position)) {
            position = this->getPosition();
            continue;
        }
        else if (changed)
            return position;
    }
    return std::nullopt;
}

