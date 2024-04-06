#pragma once
#include <vector>
#include <queue>
#include <unordered_map>

// forward declaration
class Organizm;

/**
 * first is x
 * second is y
 */
typedef std::pair<int, int> Position;


#define position_x(position) (position)->first
#define position_y(position) (positio)->y



class Swiat {
friend int main(int, char**);
private:
    int width;
    int height;
    std::priority_queue<std::tuple<Organizm*>, std::vector<Organizm*>, > organismActionQueue;
    std::unordered_map<Position, Organizm*>
    void turn();
    void loop();
    Swiat(int width, int height): height(height), width(width) {}
public:
    Organizm* getEntityAt(const Position& position);
};