//
// Created by kwojn on 4/7/2024.
//
#include <iostream>
#include <memory>
#include "Zwierzeta.h"
#include "Logger.h"

void Zwierzeta::act(Swiat &world) {
    this->moveThisOrganism(world, this->generateRandomLegalPosition(world, false));
}


bool Zwierzeta::collide(Organizm *organism, Swiat &world) {
    if (typeid(*this) != typeid(*organism))
        return Organizm::collide(organism, world);
    if (organism->getAge() > MINIMAL_REPRODUCATION_AGE && this->getAge() > MINIMAL_REPRODUCATION_AGE)
        this->mate(organism, world);
    return true;
}

void Zwierzeta::mate(const Organizm *lover, Swiat &world) {
    Position position = this->generateRandomLegalPosition(world, true);
    if (position == this->getPosition())
        return;
    auto copy = this->clone();
    copy->setPosition(std::move(position));
    logger->getInfoLogFile() << this->getName() << " rozmnozyl sie z " << lover->getName() << std::endl;
    world.spawn(std::shared_ptr<Organizm>(copy));
}

void Zwierzeta::serialize(std::ofstream &file) {
    file << "Z " << this->symbol() << " " << position_x(this->getPosition()) << " " << position_y(this->getPosition())
         << " "
         << this->getAge()
         << " "
         << this->getAttack() << std::endl;

}

std::shared_ptr<Organizm> Zwierzeta::deserialize(std::ifstream &file) {
    ZwierzetaBuilder builder;
    std::string type;
    int x, y, age, attack;
    file >> type >> x >> y >> age >> attack;
    builder.setType(type);
    builder.setPos(Position(x, y));
    builder.setAge(age);
    builder.setAttack(attack);
    return builder.build();
}

bool Zolw::didDeflectAttack(const Organizm *attacker) {
    return attacker->getAttack() < 5;
}

void Zolw::act(Swiat &world) {
    std::uniform_int_distribution<int> dist(1, 4);
    int random = dist(rng);
    if (random == 1)
        Zwierzeta::act(world);
}

bool Lis::isLegalMove(const Position &position, Swiat &world, bool mating) {
    auto organismAtPosition = world.getEntityAt(position);
    if (organismAtPosition && organismAtPosition->getAttack() > this->getAttack())
        return false;
    return Zwierzeta::isLegalMove(position, world, mating);
}

bool Antylopa::collide(Organizm *organizm, Swiat &swiat) {
    std::uniform_int_distribution<int> dist(1, 2);
    if (dist(rng) == 1) {
        auto pos = generateRandomLegalPosition(swiat, true);
        if (pos != this->getPosition()) {
            logger->getInfoLogFile() << this->getName() << " uciekla przed " << organizm->getName() << std::endl;
            this->moveThisOrganism(swiat, std::move(pos));
            return true;
        }
    }
    return Zwierzeta::collide(organizm, swiat);
}

void Antylopa::act(Swiat &world) {
    // this is hacky but we need to keep original position to revert in case of push backs
    // so we need to save it, set pos to position + 1
    // then get second position because it moves by two
    auto currentPosition = this->getPosition();
    this->setPosition(this->generateRandomLegalPosition(world));
    auto newPosition = this->generateRandomLegalPosition(world);
    // revert current position
    this->setPosition(std::move(currentPosition));
    this->moveThisOrganism(world, std::move(newPosition));
}

std::shared_ptr<Zwierzeta> ZwierzetaBuilder::build() {
    if (!type)
        throw std::runtime_error("ZwierzetaBuilder: type not set");
    if (!pos)
        throw std::runtime_error("ZwierzetaBuilder: position not set");
    std::shared_ptr<Zwierzeta> organism;
    switch (*type) {
        case ZwierzetaType::Wilk:
            organism = std::make_shared<Wilk>(std::move(*pos));
            break;
        case ZwierzetaType::Owca:
            organism = std::make_shared<Owca>(std::move(*pos));
            break;
        case ZwierzetaType::Lis:
            organism = std::make_shared<Lis>(std::move(*pos));
            break;
        case ZwierzetaType::Zolw:
            organism = std::make_shared<Zolw>(std::move(*pos));
            break;
        case ZwierzetaType::Antylopa:
            organism = std::make_shared<Antylopa>(std::move(*pos));
            break;
        default:
            throw std::runtime_error("ZwierzetaBuilder: Unknown animal type");
    }
    if (attack)
        organism->setAttack(*attack);
    if (age)
        organism->setAge(*age);
    return organism;
}

void ZwierzetaBuilder::setType(const std::string &name) {
    if (name == "W")
        type = ZwierzetaType::Wilk;
    else if (name == "O")
        type = ZwierzetaType::Owca;
    else if (name == "L")
        type = ZwierzetaType::Lis;
    else if (name == "Z")
        type = ZwierzetaType::Zolw;
    else if (name == "A")
        type = ZwierzetaType::Antylopa;
}

void ZwierzetaBuilder::setPos(const Position &pos) {
    this->pos = pos;
}

void ZwierzetaBuilder::setAttack(int attack) {
    this->attack = attack;
}

void ZwierzetaBuilder::setAge(int age) {
    this->age = age;
}
