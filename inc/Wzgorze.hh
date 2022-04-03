#ifndef WZOGRZE
#define WZOGRZE
 
#include "El_Powierzchni.hh"
#include "prostopadloscian.hh"

/// przeszkoda przeciety prostopadloscian
class Wzgorze : public Prostopadloscian, public El_Powierzchni
{
private:
public:
    /// Konstruktor parametryczny wzgorza
    Wzgorze(std::shared_ptr<drawNS::Draw3DAPI> _api, std::vector<double> kordynaty);
    // Destruktor wzgorza
    ~Wzgorze(){};
    /// Metody 
    /// wylicza wierzcholki wzgorza
    std::vector<std::vector<double>> wylicz_punkty() override;
    
    /// Sprawdza czy Wzgorze koliduje z podanym elementem powierzchni
    bool czy_koliduje(std::shared_ptr<El_Powierzchni> sprawdzany_dron) override;
    /// Zwraca srodek Wzgorze
    std::vector<double> get_srodek()override;
    /// Zwraca wymiary Wzgorze
    std::vector<double> get_wymiary()override;
    /// zwraca punkty ktore sa potrzebne do wyznaczenia mozliwych punktow kolizji dla Wzgorze
    std::vector<std::vector<double>> get_punkty_krytyczne()override;
    int get_typeof() override;
    /// Wymazuje Wzgorze
    void wymazPrzeszkode() override;
};

#endif