//
// Created by kwojn on 4/15/2024.
//

#include "Player.h"
#include "Logger.h"
#include <thread>

#define ABILITY_READ "Calopalenie jest gotowe"
#define ABILITY_NOT_READY "Calopalenie nie jest gotowe"
#define ABILITY_ACTIVE "Calopalenie jest aktywne"

void Player::act(Swiat &world) {
    ability.updateTimers(*this);
    world.draw(*windowManager);
    wmove(windowManager->getBottomWindow(), 5, 0);
    if (ability.isActivated(*this))
        windowManager->setStatusText(ABILITY_ACTIVE);
    else if (ability.isAvailable(*this))
        windowManager->setStatusText(ABILITY_READ);
    else
        windowManager->setStatusText(ABILITY_NOT_READY);
    windowManager->draw();
    logger->getInfoLogFile() << "Ruch gracza" << std::endl;
    WINDOW *gameWindow = windowManager->getMainGameWindow();
    curs_set(1);
    wmove(gameWindow, this->getPosition().second, this->getPosition().first + 1);
    wrefresh(gameWindow);
    while (doPlayerActions(world, windowManager)) {
        std::this_thread::sleep_for(std::chrono::milliseconds(75));
    }
    ability.update(*this, world);
    curs_set(0);
}

bool Player::collide(Organizm *organizm, Swiat &swiat) {
    return Zwierzeta::collide(organizm, swiat);
}

bool Player::doPlayerActions(Swiat &world, WindowManager *windowManager) {
    int key;
    while ((key = getch()) != ERR) {
        if (windowManager->handleWindowControls(key))
            continue;
        switch (key) {
            case 'e': {
                if (ability.use(*this)) {
                    windowManager->setStatusText(ABILITY_ACTIVE);
                    windowManager->draw();
                }
                continue;
            }
            case KEY_DOWN:
            case KEY_UP:
            case KEY_LEFT:
            case KEY_RIGHT:
                auto pos = getNewPositionFromUser(world, key);
                if (pos.has_value()) {
                    this->moveThisOrganism(world, std::move(pos.value()));
                    return false;
                }
                break;
        }
    }
    return true;
}

std::optional<Position> Player::getNewPositionFromUser(Swiat &world, int key) {
    auto position = this->getPosition();
    bool changed;
    changed = false;
    logger->getDebugLogFile() << " got key " << key << std::endl;
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
    } else if (changed)
        return position;
    return std::nullopt;
}

void Player::serialize(std::ofstream &file) {
    file << "P " << position_x(this->getPosition()) << " " << position_y(this->getPosition())
         << " "
         << this->getAge()
         << " "
         << this->getAttack() << " " << ability.getAvailableUntil() << " " << ability.getCooldownUntil() << std::endl;
}

std::shared_ptr<Player> Player::deserialize(std::ifstream &file, WindowManager *windowManager) {
    int x, y, age, attack, duration, cooldown;
    file >> x >> y >> age >> attack >> duration >> cooldown;
    std::shared_ptr<Player> ptr = std::make_shared<Player>(Position(x, y), windowManager);
    ptr->setAge(age);
    ptr->setAttack(attack);
    ptr->ability = Ability(duration, cooldown);
    return ptr;
}

bool Ability::use(const Player &player) {
    if (!this->isAvailable(player))
        return false;
    logger->getInfoLogFile() << "Uzyto calopalenia" << std::endl;
    availableUntil = player.getAge() + ABILITY_DURATION;
    return true;
}

void Ability::update(const Player &player, Swiat &world) {
    if (!isActivated(player))
        return;
    for (int i = 0; i < MAX_NEIGHBOURS; i++) {
        auto pos = player.getPosition();
        Player::translateMoveNumberToPosition(pos, i);
        auto entity = world.getEntityAt(pos);
        if (entity) {
            entity->kill();
            logger->getInfoLogFile() << "Calopalenie zabilo " << entity->getName() << std::endl;
        }
    }

}

Ability::Ability(int availableUntil, int cooldownUntil) : availableUntil(
        availableUntil), cooldownUntil(cooldownUntil) {}

int Ability::getAvailableUntil() const {
    return availableUntil;
}

int Ability::getCooldownUntil() const {
    return cooldownUntil;
}

bool Ability::isAvailable(const Player &player) const {
    return availableUntil <= player.getAge() && cooldownUntil <= player.getAge();
}

bool Ability::isActivated(const Player &player) const {
    return availableUntil > player.getAge();
}

void Ability::updateTimers(const Player &player) {
    if (availableUntil != 0 && availableUntil <= player.getAge() && availableUntil > cooldownUntil) {
        logger->getInfoLogFile() << "Calopalenie wygaslo" << std::endl;
        cooldownUntil = availableUntil + ABILITY_COOLDOWN;
        return;
    } else if (availableUntil == 0 || availableUntil <= cooldownUntil)
        return;

}
