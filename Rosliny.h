//
// Created by kwojn on 4/13/2024.
//

#ifndef PROJEKT1_ROSLINY_H
#define PROJEKT1_ROSLINY_H


#include "Organizm.h"

class Rosliny : public Organizm {
    friend class Loader;

protected:
    // 20% to spread
    int spawnRateUpperBound = 8;

    Rosliny(Position &&pos, int attack = 0) : Organizm(attack, 0, std::move(pos)) {}

    void serialize(std::ofstream &file) override;

    static std::shared_ptr<Organizm> deserialize(std::ifstream &file);

public:
    void act(Swiat &world) override;
};

class Trawa : public Rosliny {
protected:
    std::string name() const override {
        return "Trawa";
    }

public:
    Trawa(Position &&pos) : Rosliny(std::move(pos)) {}

    const char symbol() override {
        return 'T';
    }

    Organizm *clone() override {
        return new Trawa{*this};
    }
};

class Mlecz : public Rosliny {
protected:
    std::string name() const override {
        return "Mlecz";
    }

public:
    Mlecz(Position &&pos) : Rosliny(std::move(pos)) {}

    const char symbol() override {
        return 'M';
    }

    Organizm *clone() override {
        return new Mlecz{*this};
    }

    void act(Swiat &world) override;
};

class Guarana : public Rosliny {
protected:
    std::string name() const override {
        return "Guarana";
    }

public:
    Guarana(Position &&pos) : Rosliny(std::move(pos)) {
        spawnRateUpperBound = 12;
    }

    const char symbol() override {
        return 'G';
    }

    Organizm *clone() override {
        return new Guarana{*this};
    }

    bool collide(Organizm *collider, Swiat &world) override;
};

class WilczeJagody : public Rosliny {
protected:
    std::string name() const override {
        return "Wilcze jagody";
    }

public:
    WilczeJagody(Position &&pos) : Rosliny(std::move(pos), 99) {}

    const char symbol() override {
        return 'J';
    }

    Organizm *clone() override {
        return new WilczeJagody{*this};
    }

    bool collide(Organizm *collider, Swiat &world) override;
};

class BarszczSosnowskiego : public Rosliny {
protected:
    std::string name() const override {
        return "Barszcz sosnowskiego";
    }

public:
    explicit BarszczSosnowskiego(Position &&pos) : Rosliny(std::move(pos), 10) {
        // 12.5% to spawn
        this->spawnRateUpperBound = 10;
    }

    const char symbol() override {
        return 'B';
    }

    Organizm *clone() override {
        return new BarszczSosnowskiego{*this};
    }

    bool collide(Organizm *collider, Swiat &world) override;

    // kill every neighbour
    void act(Swiat &world) override;
};

#endif //PROJEKT1_ROSLINY_H
