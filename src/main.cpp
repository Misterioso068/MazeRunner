#include <iostream>
#include "program/engine.hpp"

using namespace std;

int main() {
    try {
        Engine engine(1000, 1000, 50, 50, 10, 0.02);
        engine.run();
    } catch (const exception& e) {
        cerr << e.what() << endl;
        return EXIT_FAILURE;
    }
    return EXIT_SUCCESS;
}