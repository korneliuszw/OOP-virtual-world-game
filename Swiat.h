#pragma once
#include <vector>
#include <queue>
#include <map>
#include <memory>
#include "WindowManager.h"

// forward declaration
class Organizm;

/**
 * first is x
 * second is y
 */
typedef std::pair<int, int> Position;

#define position_x(position) (position).first
#define position_y(position) (position).second

class OrganizmCompare {
public:
    /**
     * Implementacja zasady pierwszenstwa w poruszaniu
     */
    bool operator()(const std::shared_ptr<Organizm>& a, const std::shared_ptr<Organizm>& b);
};

typedef std::priority_queue<std::shared_ptr<Organizm>, std::vector<std::shared_ptr<Organizm>>, OrganizmCompare> OrganismQueue;
class Swiat {
private:
    int width;
    int height;
    OrganismQueue organismActionQueue;
    std::map<Position, std::shared_ptr<Organizm>> mapper;
    void actTurn();
    void endTurn();
    bool changed = true;

public:
    void turn();
    Swiat(int width, int height);
    Organizm* getEntityAt(const Position& position);
    void moveOrganism(const Position&, std::shared_ptr<Organizm>);
    void spawn(std::shared_ptr<Organizm> organism, bool forceInsert = false);
    bool isLegalPosition(const Position& position);
    void draw(WindowManager& manager);
    [[nodiscard]] bool hasChanged() const;
};