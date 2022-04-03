#ifndef PLASKOWYZ
#define PLASKOWYZ
 
#include "prostopadloscian.hh"
#include "El_Powierzchni.hh"

/// Plaskowyz to prostopadloscienna przeszkoda
class Plaskowyz : public Prostopadloscian, public El_Powierzchni
{
private:
public:
    /// Konstruktor Plaskowyzu
    Plaskowyz(std::shared_ptr<drawNS::Draw3DAPI> _api, std::vector<double> kordynaty);
    /// Destruktor Plaskowyzu
    ~Plaskowyz(){};
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