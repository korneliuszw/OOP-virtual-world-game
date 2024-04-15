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
    auto clone = this->clone();
    clone->setPosition(this->generateRandomLegalPosition(world));
    logger->getInfoLogFile() << getName() << " rozmnozyl sie";
    world.spawn(std::shared_ptr<Organizm>(clone));
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
