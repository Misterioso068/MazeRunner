#include <iostream>
#include "program/engine.hpp"

using namespace std;

int main() {
    try {
        Engine engine(1000, 1000, 100, 100, 10, 0.02, 0.3);
        engine.run();
    } catch (const exception& e) {
        cerr << e.what() << endl;
        return EXIT_FAILURE;
    }
    return EXIT_SUCCESS;
}