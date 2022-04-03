#include "wektor2D.hh"

/// umozliwia odejmowanie std::vector
std::vector<double> odejmowanie_wektorow(std::vector<double>arg1, std::vector<double>arg2){
    for(int i=0; i<3; i++)
    {
        arg1[i] -= arg2[i];
    }
    return arg1;
}

/// umozliwia obliczenie dlugosci std::vector
double dlugosc_wektora(std::vector<double>arg1){
    return sqrt(pow(arg1[0],2)+pow(arg1[1],2));
}
