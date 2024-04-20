//
// Created by kwojn on 4/7/2024.
//

#ifndef PROJEKT1_ZWIERZETA_H
#define PROJEKT1_ZWIERZETA_H


#include <optional>
#include "Organizm.h"
#include "Loader.h"

constexpr int MINIMAL_REPRODUCATION_AGE = 2;

class Zwierzeta : public Organizm {
    friend class Loader;

    // helper function
    void mate(const Organizm *other, Swiat &);

protected:
    Zwierzeta(int attack, int aggressiveness, Position &&position) : Organizm(attack, aggressiveness,
                                                                              std::move(position)) {}

    void serialize(std::ofstream &file) override;

    static std::shared_ptr<Organizm> deserialize(std::ifstream &file);

public:
    virtual void act(Swiat &world) override;

    bool collide(Organizm *, Swiat &) override;
};

class Wilk : public Zwierzeta {
protected:
    std::string name() const override {
        return "Wilk";
    }

public:
    explicit Wilk(Position &&pos) : Zwierzeta(9, 5, std::move(pos)) {}

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
    explicit Owca(Position &&pos) : Zwierzeta(4, 4, std::move(pos)) {}

    Owca *clone() override {
        return new Owca{*this};
    }

    const char symbol() override {
        return 'O';
    }
};

class Lis : public Zwierzeta {
protected:
    std::string name() const override {
        return "Lis";
    }

    // Lis won't move to fields occupied by stronger organisms
    bool isLegalMove(const Position &position, Swiat &world, bool mating) override;

public:
    explicit Lis(Position &&pos) : Zwierzeta(3, 7, std::move(pos)) {}

    const char symbol() override {
        return 'L';
    }

    Organizm *clone() override {
        return new Lis{*this};
    }

};

class Zolw : public Zwierzeta {

protected:
    std::string name() const override {
        return "Zolw";
    }

public:
    explicit Zolw(Position &&pos) : Zwierzeta(2, 1, std::move(pos)) {}

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

class Antylopa : public Zwierzeta {
protected:
    std::string name() const override {
        return "Antylopa";
    }

public:
    explicit Antylopa(Position &&pos) : Zwierzeta(4, 4, std::move(pos)) {}

    // 50% to avoid attack and move to free field
    bool collide(Organizm *organizm, Swiat &swiat) override;

    void act(Swiat &world) override;

    const char symbol() override {
        return 'A';
    }

    Organizm *clone() override {
        return new Antylopa{*this};
    }

};


class ZwierzetaBuilder {
    enum class ZwierzetaType {
        Wilk,
        Owca,
        Lis,
        Zolw,
        Antylopa
    };
    std::optional<ZwierzetaType> type;
    std::optional<Position> pos;
    std::optional<int> attack;
    std::optional<int> age;
public:
    void setAge(int age);


public:
    void setType(const std::string &name);

    void setPos(const Position &pos);

    void setAttack(int attack);


    std::shared_ptr<Zwierzeta> build();
};


#endif //PROJEKT1_ZWIERZETA_H
