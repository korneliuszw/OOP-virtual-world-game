#include <iostream>
#include <chrono>
#include <thread>
#include <memory>
#include "WindowManager.h"
#include "Swiat.h"
#include "Zwierzeta.h"
int main() {
    int width, height;
    std::cout << "Wysokosc: ";
    std::cin >> height;
    std::cout << "\nSzerokosc:";
    std::cin >> width;
    WindowManager windowManager(width, height);
    Swiat world(width, height);
    world.spawn(std::make_shared<Wilk>(Position({0, 0})), true);
    waddstr(windowManager.getBottomWindow(), "Korneliusz Wojnicz 198349");
    while (true) {
        if (world.hasChanged()) {
            world.draw(windowManager);
        }
        windowManager.draw();
        std::this_thread::sleep_for(std::chrono::milliseconds(200));
        world.turn();
    }
    return 0;
}
