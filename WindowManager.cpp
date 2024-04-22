//
// Created by kwojn on 4/6/2024.
//

#include "WindowManager.h"
#include "Logger.h"
#include "Loader.h"
#include <cstdlib>
#include <cstddef>
#include <iostream>

#define AUTHOR_STRING "Korneliusz Wojnicz 198349"
#define HELP "j/k - przewijanie logow strzalki - sterowanie graczem enter - koniec tury s - zapis l - odczyt e - umiejetnosc"
using std::size_t;


WindowManager::WindowManager(int gameWidth, int gameHeight, Loader &loader) : scrollableList({4, 2}),
                                                                              loader(loader) {
    screen = initscr();
    clear();
    cbreak();
    noecho();
    nodelay(screen, TRUE);
    keypad(screen, TRUE);
    nonl();
    curs_set(0);
    clear();
    refresh();
    int screenHeight = getmaxy(stdscr);
    int screenWidth = getmaxx(stdscr);
    logger->getDebugLogFile() << "screen w: " << screenWidth << " h:" << screenHeight << std::endl;
    int bottomPaneHeight = 7;
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
    wmove(bottomWindow, 1, 0);
    waddstr(bottomWindow, HELP);
    scrollableList.draw(bottomWindow);
    if (!statusText.empty()) {
        wmove(bottomWindow, 6, 0);
        waddstr(bottomWindow, statusText.c_str());
    }
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
        case 'l':
            loader.load(this);
            return true;
        case 's':
            loader.save();
            return true;
    }
    return false;
}

ScrollableList &WindowManager::getScrollableList() {
    return scrollableList;
}

void WindowManager::setStatusText(const std::string &statusText) {
    WindowManager::statusText = statusText;
}

