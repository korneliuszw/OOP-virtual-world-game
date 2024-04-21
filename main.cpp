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
    Swiat world(width, height);
    Loader loader(world);
    WindowManager windowManager(width, height, loader);
    world.spawn(std::make_shared<Player>(Position{0, 0}, &windowManager), true);
    world.spawn(std::make_shared<Wilk>(Position({18, 12})), true);
    world.spawn(std::make_shared<Wilk>(Position({10, 2})), true);
    world.spawn(std::make_shared<Owca>(Position({7, 5})), true);
    world.spawn(std::make_shared<Owca>(Position({9, 11})), true);
    world.spawn(std::make_shared<Owca>(Position({4, 16})), true);
    world.spawn(std::make_shared<Owca>(Position({10, 1})), true);
    world.spawn(std::make_shared<Zolw>(Position({14, 5})), true);
    world.spawn(std::make_shared<Zolw>(Position({3, 1})), true);
    world.spawn(std::make_shared<Zolw>(Position({4, 3})), true);
    world.spawn(std::make_shared<Lis>(Position({5, 4})), true);
    world.spawn(std::make_shared<Lis>(Position({5, 4})), true);
    world.spawn(std::make_shared<Lis>(Position({5, 4})), true);
    world.spawn(std::make_shared<Antylopa>(Position({5, 3})), true);
    world.spawn(std::make_shared<Antylopa>(Position({19, 18})), true);
    world.spawn(std::make_shared<Antylopa>(Position({15, 2})), true);
    world.spawn(std::make_shared<Antylopa>(Position({12, 14})), true);
    world.spawn(std::make_shared<Trawa>(Position({15, 13})), true);
    world.spawn(std::make_shared<Trawa>(Position({10, 8})), true);
    world.spawn(std::make_shared<Trawa>(Position({4, 4})), true);
    world.spawn(std::make_shared<Mlecz>(Position({2, 10})), true);
    world.spawn(std::make_shared<Mlecz>(Position({15, 5})), true);
    world.spawn(std::make_shared<Guarana>(Position({5, 0})), true);
    world.spawn(std::make_shared<Guarana>(Position({10, 10})), true);
    world.spawn(std::make_shared<BarszczSosnowskiego>(Position{5, 5}), true);
    world.spawn(std::make_shared<BarszczSosnowskiego>(Position{16, 18}), true);
    world.spawn(std::make_shared<BarszczSosnowskiego>(Position{3, 7}), true);
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
