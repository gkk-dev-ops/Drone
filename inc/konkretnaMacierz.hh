#ifndef KONKRETNA_MACIERZ
#define KONKRETNA_MACIERZ

#include "macierzRot.hh"
#include <math.h>

class KonkretnaMacierz : public Macierz3x3{
public:
    /// Konstruktor parametryczny Konkretnej macierzy
    KonkretnaMacierz(char oska, double kat);
    
    /// Metody Konkretnej Macierzy
    /// KonkretnaMacierz_do_Macierz3x3() przelicza Macierz3x3 na Konkretna Macierz (sluzy jako macierz rotacji)
    Macierz3x3 KonkretnaMacierz_do_Macierz3x3();
    /// Wylicza kat o ktory obraca konkretna macierz na ktorej zostala wywolana ta metoda, zakladajac, ze KonkretnaMacierz wyliczona zostala dla obrotu po osi z
    double KonkretnaMacierzDoKataDlaOsiZ();
};

#endif