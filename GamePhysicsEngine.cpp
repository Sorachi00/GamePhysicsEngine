#include <iostream>
#include <thread>
#include <chrono>
#include "demos/Ballistic.h"

int main() {
    Ballistic b(Pistol);

    float time = 0;
    while (b.isActive()) { // pseudo 60fps simulation
        float dt = 1.0f / 60.0f;
        b.update(dt);

        auto pos = b.getPosition();
        time += dt;
        std::cout << "t=" << time
            << "s -> Pos("
            << pos.x << ", " << pos.y << ", " << pos.z << ")\n";

        std::this_thread::sleep_for(std::chrono::milliseconds(16));
    }

    std::cout << "El proyectil dejó de estar activo.\n";
}
