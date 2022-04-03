#ifndef INTER_DRON
#define INTER_DRON

#include <iostream>
#include "konkretnaMacierz.hh"
#include "OpenGL_API.hh"

class Inter_Dron
{
public:
/// Wylicza srodek calego drona
virtual std::vector<double> get_srodek()=0;
/// zwraca 3 elementowy wektor wymiarow drona
virtual std::vector<double> get_wymiary()=0;
/// zwraca punkty ktore sa potrzebne do wyznaczenia mozliwych punktow kolizji dla drona
virtual std::vector<std::vector<double>> get_punkty_krytyczne()=0;
};

#endif