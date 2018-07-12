#include <iostream>
#include <windows.h>

using namespace std;

//boolean handle();

bool isActive = false;
int increment = 0;
int keyIncrement = 0;

HWND oblivionApplication = nullptr;

bool handle();

int main() {
    std::cout << "Starting application" << std::endl;
    while (true) {
        if (handle()) {
            break;
        }
    }
    return 0;
}

bool handle() {

    increment = increment + 1;
    keyIncrement = keyIncrement + 1;

    //std::cout << increment << endl;

    if (increment > 900000) {
        increment = 900000;
    }

    short keyState = GetKeyState('P');
    short exitState = GetKeyState(VK_F2);
    //bool isToggled = keyState & 1;
    bool isTogglePress = keyState & 0x8000;
    bool isExit = exitState & 0x8000;

    if (isTogglePress && increment >= 500000) {
        std::cout << "It is pressed down! ";
        std::cout << increment << endl;
        increment = 0;
        if (isActive) {

            keybd_event('W',
                        0x45,
                        KEYEVENTF_EXTENDEDKEY | KEYEVENTF_KEYUP,
                        0);
        }
        isActive = !isActive;
    }
    if (isActive && keyIncrement > 14000) {
        keybd_event('W',
                    0x45,
                    KEYEVENTF_EXTENDEDKEY | 0,
                    0);
        if (oblivionApplication == nullptr) {
            std::cout << "Exiting because for some reason the Oblivion Application is still null";
            return true;
        }
        SendMessage(oblivionApplication, WM_CHAR, 'w', 0);
        keyIncrement = 0;
    }
    if (isExit) {
        return true;
    }
    return false;
}