#ifndef INPUTMANAGER_H
#define INPUTMANAGER_H

#include <functional>
#include <unordered_map>

class InputManager {
public:
    void bindKey(int key, std::function<void()> action) {
        actions[key] = action;
    }

    void handleKeyPress(int key) {
        if (actions.find(key) != actions.end()) {
            actions[key]();
        }
    }

private:
    std::unordered_map<int, std::function<void()>> actions;
};


#endif // INPUTMANAGER_H
