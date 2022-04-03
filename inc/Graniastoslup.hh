#ifndef GRANIASTOSLUP
#define GRANIASTOSLUP

#include "prostopadloscian.hh"
#include "Inter_Dron.hh"

class Graniastoslup : public Prostopadloscian
{
private:
    /// Pola prywatne Graniastoslupa
    double wysokosc, dlugosc;
public:
    /// Domyslny konstruktor Graniastoslupa
    Graniastoslup();
    /// Konstruktor parametryczny Graniastoslupa
    Graniastoslup(std::shared_ptr<drawNS::Draw3DAPI> _api);
    /// Destruktor Graniastoslupa
    ~Graniastoslup(){};
    /// Gettery Graniastoslupa
    double const get_wysokosc() const;
    double const get_dlugosc() const;
    /// Settery Graniastoslupa
    void set_wysokosc(double nowa_wysokosc);
    void set_dlugosc(double nowa_dlugosc);
};

#endif