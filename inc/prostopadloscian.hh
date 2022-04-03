#ifndef PROSTOPADLOSCIAN
#define PROSTOPADLOSCIAN

#include "ukladWspolrzednych.hh" 
#include "Inter_Rysowanie.hh"
#include "Inter_Dron.hh"

class Prostopadloscian : public ukladWspolrzednych, public Inter_Rysowanie
{
private:
public:
    /// Pola Prostopadloscianu
    std::vector<double> dlugosc_boku;
    /// Konstruktory Prostopadloscianu
    /// Domyslny pusty konstruktor na potrzeby dziedziczenia
    Prostopadloscian(){};
    /// Konstruktor Parametryczny
    Prostopadloscian(std::shared_ptr<drawNS::Draw3DAPI> _api);
    /// Destruktor Prostopadloscianu
    ~Prostopadloscian(){};
    /// Metody Prostopadloscianu
    /// Wylicza wierzcholki prostopadloscianu
    std::vector<std::vector<double>> wylicz_punkty() override;
    /// Rysuje prostopadloscian
    void rysuj() override;
    /// Przesuwa prostopadloscian o wektor
    void przesun_o_wektor(std::vector<double> vec);
    /// Obraca prostopadloscian zmieniajac jego orientacje poprzez przemnozenie jego macierzy orientacji przez konkretna macierz dla obrotu po zadanej osi
    void obrot(double kat, char oska);
};

#endif