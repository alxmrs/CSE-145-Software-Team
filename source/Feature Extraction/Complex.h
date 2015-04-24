#ifndef __Feature_Extraction__Complex__
#define __Feature_Extraction__Complex__

#include <stdio.h>
#include <string>

class Complex
{
public:
    double x,y,r,arg;
    
    Complex();
    Complex(double,double);
    Complex(double,double,std::string);
    
    inline Complex operator+ (const Complex& other);
    inline Complex operator- (const Complex& other);
    inline Complex operator* (const Complex& other);
    inline Complex operator/ (const Complex& other);
};

#endif /* defined(__Feature_Extraction__Complex__) */
