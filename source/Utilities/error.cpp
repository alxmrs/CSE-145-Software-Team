#include "error.h"
#include <iostream>

void error (std::string message, int code)
{
    std::cerr << "Error: " << message << "\n";
    std::exit(code);
}