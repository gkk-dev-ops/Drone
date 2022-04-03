#ifndef PLASKAPOWIERZCHNIA
#define PLASKAPOWIERZCHNIA
 
#include "Inter_Rysowanie.hh"
#include "El_Powierzchni.hh"

/// Klasa tworzaca obiekty bedace powierzchnia, na ktorej znajduja sie pozostale obiekty.
/// Plaska powierzchnia jest wielkosci sceny ustawionej w api
class PlaskaPowierzchnia : public Inter_Rysowanie, public El_Powierzchni
{
private:
    /// Pola Plaskiej Powierzchni
    /// Plaska powierzchnia jest kwadratem, dlatego wielkosc jest wielkoscia jego bokow
    double wielkosc;
    /// Wysokosc to wysokosc na ktorej plaszczyzna sie znajduje
    double wysokosc;
public:
    /// Konstruktor parametryczny Plaskiej Powierzchni
    PlaskaPowierzchnia(std::shared_ptr<drawNS::Draw3DAPI> _api, double wysokosc, double wielkosc);
    /// Destruktor Plaskiej Powierzchni
    //~PlaskaPowierzchnia(){}; // po co to jest?
    /// Gettery Plaskiej powierzchni
    int const get_wielkosc() const;
    double const get_wysokosc() const;
    /// Settery Plaskiej powierzchni
    void set_wielkosc(int nowa_wielkosc);
    void set_wysokosc(double nowa_wysokosc);
    
    /// Metody rysowania i widocznosc
    void rysuj() override;
    /// Wymazuje powierzchnie nie usuwajac jej
    void wylaczWidocznosc();

    /// Sprawdza czy Plaskowyzu koliduje z podanym elementem powierzchni
    bool czy_koliduje(std::shared_ptr<El_Powierzchni> sprawdzany_dron) override;
    /// Zwraca srodek Plaskowyzu
    std::vector<double> get_srodek()override;
    /// Zwraca wymiary Plaskowyzu
    std::vector<double> get_wymiary()override;
    /// zwraca punkty ktore sa potrzebne do wyznaczenia mozliwych punktow kolizji dla Plaskowyzu
    std::vector<std::vector<double>> get_punkty_krytyczne()override;
    /// zwraca typ
    int get_typeof() override;
    void wymazPrzeszkode() override;
};

#endif