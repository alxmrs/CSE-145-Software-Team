#ifndef Feature_Extraction_error_h
#define Feature_Extraction_error_h

#include <string>
#include <iostream>

void error (std::string message, int code)
{
    std::cerr << "Error: " << message << "\n";
    std::exit(code);
}

#endif
