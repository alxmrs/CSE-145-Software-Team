#include "Complex.h"
#include "error.h"
#include <cmath>


Complex :: Complex() { }

Complex :: Complex(double X, double Y)
{
    x   = X;
    y   = Y;
    r   = sqrt(X*X + Y*Y);
    arg = atan2(Y, X);
}

Complex :: Complex(double A, double B, std::string system)
{
    if (system == "cartesian")
        Complex(A, B);
    
    else if (system == "polar")
    {
        x   = A*cos(B);
        y   = A*sin(B);
        r   = A;
        arg = B;
    }
    
    else
    {
        std::string message = "Argument to constructor to Complex type has";
        message += "an unrecognised coordinate system.";
        message += "\nMust be 'cartesian' or 'polar'";
        error(message, -1);
    }
}

inline Complex Complex ::  operator+ (const Complex& other)
{
    return Complex(x+other.x, y+other.y);
}

inline Complex Complex :: operator- (const Complex& other)
{
    return Complex(x-other.x, y+other.y);
}

inline Complex Complex :: operator* (const Complex& other)
{
    double re = x*other.x - y*other.y;
    double im = x*other.y + y*other.x;
    
    return Complex(re, im);
}

inline Complex Complex :: operator/ (const Complex& other)
{
    double den = other.x*other.x + other.y*other.y;
    double re  = (x*other.x + y*other.y)/den;
    double im  = (other.x*y - x*other.y)/den;
    
    return Complex(re, im);
}