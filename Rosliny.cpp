//
// Created by kwojn on 4/13/2024.
//

#include "Rosliny.h"
#include "Logger.h"

void Rosliny::act(Swiat &world) {
    std::uniform_int_distribution<int> dist(1, spawnRateUpperBound);
    if (dist(rng) != spawnRateUpperBound) {
        return;
    }
    auto pos = this->generateRandomLegalPosition(world, true);
    if (pos == this->getPosition())
        return;
    auto clone = this->clone();
    clone->setPosition(std::move(pos));
    logger->getInfoLogFile() << getName() << " rozmnozyl sie" << std::endl;
    world.spawn(std::shared_ptr<Organizm>(clone));
}

void Rosliny::serialize(std::ofstream &file) {
    file << "R " << this->symbol() << " " << position_x(this->getPosition()) << " " << position_y(this->getPosition())
         << " "
         << this->getAge() << std::endl;
}

std::shared_ptr<Organizm> Rosliny::deserialize(std::ifstream &file) {
    std::string type;
    int x, y, age;
    file >> type >> x >> y >> age;
    std::shared_ptr<Organizm> ptr = nullptr;
    if (type == "T")
        ptr = std::make_shared<Trawa>(Position(x, y));
    if (type == "M")
        ptr = std::make_shared<Mlecz>(Position(x, y));
    if (type == "G")
        ptr = std::make_shared<Guarana>(Position(x, y));
    if (type == "J")
        ptr = std::make_shared<WilczeJagody>(Position(x, y));
    if (type == "B")
        ptr = std::make_shared<BarszczSosnowskiego>(Position(x, y));
    if (!ptr)
        throw std::runtime_error("Unknown plant type");
    ptr->setAge(age);
    return ptr;
}

void Mlecz::act(Swiat &world) {
    Rosliny::act(world);
    Rosliny::act(world);
    Rosliny::act(world);
}

bool Guarana::collide(Organizm *collider, Swiat &world) {
    collider->setAttack(collider->getAttack() + 3);
    this->kill();
    logger->getInfoLogFile() << collider->getName() << " zjadl guaren i zyskal +3 do ataku";
    return true;
}

bool WilczeJagody::collide(Organizm *collider, Swiat &world) {
    logger->getInfoLogFile() << collider->getName() << " zjadl wilcze jagody i umiera";
    collider->kill();
    this->kill();
    return true;
}

bool BarszczSosnowskiego::collide(Organizm *collider, Swiat &world) {
    logger->getInfoLogFile() << collider->getName() << " zjadl barszcz sosnowskiego i umiera" << std::endl;
    collider->kill();
    this->kill();
    return true;
}

void BarszczSosnowskiego::act(Swiat &world) {
    for (int i = 0; i < MAX_NEIGHBOURS; i++) {
        auto pos = this->getPosition();
        translateMoveNumberToPosition(pos, i);
        auto organismAtPos = world.getEntityAt(pos);
        if (organismAtPos) {
            logger->getInfoLogFile() << organismAtPos->getName() << " w poblizu " << getName() << std::endl;
            organismAtPos->kill();
        }
    }
}
