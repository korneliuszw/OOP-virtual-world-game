#include <iostream>
#include <chrono>
#include <thread>
#include <memory>
#include "Logger.h"
#include "WindowManager.h"
#include "Swiat.h"
#include "Zwierzeta.h"
#include "Rosliny.h"
#include "Player.h"

#define KEY_ENTER_KEYBOARD 13

int main() {
    int width, height;
    std::cout << "Wysokosc: ";
    std::cin >> height;
    std::cout << "\nSzerokosc:";
    std::cin >> width;
    WindowManager windowManager(width, height);
    Swiat world(width, height);
    world.spawn(std::make_shared<Wilk>(Position({0, 0})), true);
    world.spawn(std::make_shared<Wilk>(Position({2, 2})), true);
    world.spawn(std::make_shared<Owca>(Position({3, 2})), true);
    world.spawn(std::make_shared<Zolw>(Position({3, 3})), true);
    world.spawn(std::make_shared<Zolw>(Position({3, 1})), true);
    world.spawn(std::make_shared<Lis>(Position({5, 4})), true);
    world.spawn(std::make_shared<Antylopa>(Position({5, 3})), true);
    world.spawn(std::make_shared<Trawa>(Position({1, 1})), true);
    world.spawn(std::make_shared<Trawa>(Position({2, 4})), true);
    world.spawn(std::make_shared<BarszczSosnowskiego>(Position{5, 5}), true);
    world.spawn(std::make_shared<Player>(Position{1, 2}, &windowManager), true);
    int key = 0;
    while (true) {
        while ((key = getch()) != ERR) {
            if (windowManager.handleWindowControls(key))
                continue;
            else if (key == KEY_ENTER_KEYBOARD) {
                windowManager.getScrollableList().reset();
                world.turn();
            }
        }
        if (world.hasChanged()) {
            world.draw(windowManager);
            windowManager.draw();
        }
    }
    return 0;
}
