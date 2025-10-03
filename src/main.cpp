#include <iostream>
#include "program/engine.hpp"

using namespace std;

int main() {
    try {
        Engine engine(1000, 1000, 500, 1000, 1, 0.05, 0.2);
        engine.run();
    } catch (const exception& e) {
        cerr << e.what() << endl;
        return EXIT_FAILURE;
    }
    return EXIT_SUCCESS;
}