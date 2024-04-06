#include <iostream>
#include <chrono>
#include <thread>
#include "WindowManager.h"
#include "Swiat.h"
int main() {
    int width, height;
    std::cout << "Wysokosc: ";
    std::cin >> height;
    std::cout << "\nSzerokosc:";
    std::cin >> width;
    WindowManager windowManager(width, height);
    Swiat world(width, height);
    world.turn();
    waddstr(windowManager.getBottomWindow(), "Korneliusz Wojnicz 198349");
    while (true) {
        windowManager.draw();
        std::this_thread::sleep_for(std::chrono::milliseconds(200));
    }
    return 0;
}
