#ifndef SCENA
#define SCENA

#include "Dron.hh"
#include <iterator>
#include <map>

class Scena
{
private:
/// Pola prywatne Sceny
    /// wskaznik na poprzedniegoDrona
    std::shared_ptr<Dron> m_poprzedniDron;
    /// Wskaznik na aktualnegoDrona
    std::shared_ptr<Dron> m_aktualnyDron;
    std::vector<std::shared_ptr<Dron>> DronyNaScenie;
    std::vector<std::shared_ptr<El_Powierzchni>> PrzeszkodyNaScenie;
public:
/// Gettery Scena
const std::shared_ptr<Dron> & getPoprzedniDron() const;
const std::shared_ptr<Dron> & getAktualnyDron() const;
/// Settery Scena
void setPoprzedniDron(std::shared_ptr<Dron> nowyPoprzedniDron);
void setAktualnyDron(std::shared_ptr<Dron> NowyDron);
void WypiszWspolrzedneDronow();
const std::vector<std::shared_ptr<El_Powierzchni>>& getPrzeszkodyNaScenie() const;
/// Konstruktor bezparametryczny sceny
    Scena();
    //~Scena();
/// Metody Sceny
/// Dodaje drona do aktualnej.
/// Zmienia go na aktualnie uzywanego oraz dodaje do listy przeszkod i listy (push_back)
void dodajDrona(std::shared_ptr<drawNS::Draw3DAPI> api);
void usunDrona(std::shared_ptr<drawNS::Draw3DAPI> api, int index);
/// Zmienia aktualnego drona na drona o podanym indeksie i aktualizuje pole m_poprzedniDron
void PrzelaczDrona(int index);
/// Dodaje przeszkode na scene
void dodajPrzeszkode(El_Powierzchni* wskaznikNaPrzeszkode);
/// usuwa przeszkode ze sceny
bool usunPrzeszkode(std::shared_ptr<drawNS::Draw3DAPI> api, int index);
void WypiszWspolrzednePrzeszkod();
};

#endif