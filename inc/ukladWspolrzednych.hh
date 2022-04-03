#ifndef UKLAD_WSPOLRZEDNYCH
#define UKLAD_WSPOLRZEDNYCH

#include <iostream>
#include "konkretnaMacierz.hh"

class ukladWspolrzednych
{
public:
    /// Pola ukladu wspolrzednych
    Macierz3x3 orientacja;
    /// Punkt - srodek bryly
    std::vector<double> polozenie; 
    /// Konstruktor ukladu wspolrzednych
    ukladWspolrzednych(){};
    /// Destruktor ukladu wspolrzednych
    ~ukladWspolrzednych(){};
    /// metody
    // wylicza wierzcholki obiektu, ktory implementuje funkcje wylicz_punkty()
    virtual std::vector<std::vector<double>> wylicz_punkty()=0;
};

#endif