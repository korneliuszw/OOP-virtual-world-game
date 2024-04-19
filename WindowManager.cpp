//
// Created by kwojn on 4/6/2024.
//

#include "WindowManager.h"
#include "Logger.h"
#include <cstdlib>
#include <cstddef>
#include <iostream>

#define AUTHOR_STRING "Korneliusz Wojnicz 198349"
using std::size_t;


WindowManager::WindowManager(int gameWidth, int gameHeight) : scrollableList({4, 1}) {
    screen = initscr();
    clear();
    cbreak();
    noecho();
    nodelay(screen, TRUE);
    keypad(screen, TRUE);
    nonl();
    curs_set(0);
    int screenHeight = getmaxy(stdscr);
    int screenWidth = getmaxx(stdscr);
    logger->getDebugLogFile() << "screen w: " << screenWidth << " h:" << screenHeight << std::endl;
    int bottomPaneHeight = 5;
    if (screenHeight - bottomPaneHeight < gameHeight || screenWidth < gameWidth) {
        endwin();
        std::cerr << "ERROR: Current window can't fit the game\n";
        std::exit(1);
    }
    this->mainGameWindow = createWindow(0, 0, screenWidth, screenHeight - bottomPaneHeight);
    this->bottomWindow = createWindow(0, screenHeight - bottomPaneHeight, screenWidth, bottomPaneHeight);
    logger->setScreenOutput(&scrollableList);
}

WINDOW *WindowManager::createWindow(int x, int y, int w, int h) {
    logger->getDebugLogFile() << "created window x:" << x << " y:" << y << " w:" << w << " h:" << h << std::endl;
    return newwin(h, w, y, x);
}

WindowManager::~WindowManager() {
    delwin(this->bottomWindow);
    delwin(this->mainGameWindow);
    delwin(this->screen);
}

void WindowManager::draw() {
    wrefresh(mainGameWindow);
    wclear(bottomWindow);
    wmove(bottomWindow, 0, 0);
    waddstr(bottomWindow, AUTHOR_STRING);
    scrollableList.draw(bottomWindow);
    wrefresh(bottomWindow);
}

void WindowManager::clear() {
    wclear(mainGameWindow);
}

WINDOW *WindowManager::getMainGameWindow() const {
    return mainGameWindow;
}

WINDOW *WindowManager::getBottomWindow() const {
    return bottomWindow;
}

bool WindowManager::handleWindowControls(int key) {
    switch (key) {
        case 'j':
            scrollableList.scrollUp();
            draw();
            return true;
        case 'k':
            scrollableList.scrollDown();
            draw();
            return true;
    }
    return false;
}

ScrollableList &WindowManager::getScrollableList() {
    return scrollableList;
}

