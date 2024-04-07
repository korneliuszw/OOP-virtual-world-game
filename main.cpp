#include <iostream>
#include <chrono>
#include <thread>
#include <memory>
#include "WindowManager.h"
#include "Swiat.h"
#include "Zwierzeta.h"
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
    world.spawn(std::make_shared<Wilk>(Position({1, 2})), true);
    waddstr(windowManager.getBottomWindow(), "Korneliusz Wojnicz 198349");
    int key = 0;
    while (true) {
        while ((key = getch()) != ERR) {
            if (key == KEY_ENTER_KEYBOARD) {
                world.turn();
            }
        }
        if (world.hasChanged()) {
            world.draw(windowManager);
        }
        windowManager.draw();
        std::this_thread::sleep_for(std::chrono::milliseconds(200));
    }
    return 0;
}
