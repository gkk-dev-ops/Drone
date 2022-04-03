#ifndef DRON
#define DRON

#include "OpenGL_API.hh"
#include "Graniastoslup.hh"
#include "El_Powierzchni.hh"
// #include "Inter_Dron.hh"
#include "wektor2D.hh"

#include <chrono>
#include <thread>

#define ILOSC_WIRNIKOW 4

#ifdef _WIN32
#define M_PI 3.14159265358979323846
#endif

/// Klasa Dron modeluje drona za pomoca:
/// korpusuDrona bedacego prostopadloscianem
/// wirnika bedacego Graniastoslupem
class Dron : public Inter_Rysowanie, public ukladWspolrzednych, public El_Powierzchni //, public Inter_Dron
{
private:
    /// Pola prywatne Drona
    std::vector<int> id_korpusuIwirnikow;
    Prostopadloscian korpus_drona;
    std::vector<Graniastoslup> wirniki;

public:
    /// Konstruktor parametryczny Drona
    Dron(std::shared_ptr<drawNS::Draw3DAPI> api);
    Dron(std::shared_ptr<drawNS::Draw3DAPI> api, std::vector<double> position);
    /// Destruktor Drona
    ~Dron();
    /// Przesuwa drona o podany wektor
    void przesun(std::vector<double> vec);
    /// Metody latania
    /// Dron leci do przodu o zadana odleglosc
    bool lec_do_przodu(double ile, std::vector<std::shared_ptr<El_Powierzchni>> PrzeszkodyNaScenie);
    /// Dron wznosi sie lub opada o zadana wysokosc
    bool lec_w_gore(double ile, std::vector<std::shared_ptr<El_Powierzchni>> PrzeszkodyNaScenie);
    /// Dron wznosi sie na 3 jednostki, obraca sie i leci w kierunku zadanego punktu, nastepnie zniza sie o 3 jednostki
    bool lec_do_punktu(std::vector<double> punkt_docelowy, std::vector<std::shared_ptr<El_Powierzchni>> PrzeszkodyNaScenie);
    /// zwraca czy udalo sie wyladowowac i laduje drona
    bool laduj(std::vector<std::shared_ptr<El_Powierzchni>> PrzeszkodyNaScenie);
    /// Wylicza punkty drona
    std::vector<std::vector<double>> wylicz_punkty() override;
    /// rysuje drona
    void rysuj() override;
    /// wymazuje Drona
    void wymazDrona();
    /// uruchamia wirniki
    void uruchom_wirniki();
    /// obraca drona o zadany kat i aktualizuje jego orientacje
    bool aktualizuj_orientacje(double kat, std::vector<std::shared_ptr<El_Powierzchni>> PrzeszkodyNaScenie);
    /// Sprawdza czy dron koliduje z podanym elementem powierzchni
    bool czy_koliduje(std::shared_ptr<El_Powierzchni> sprawdzany_dron) override;
    /// Zwraca srodek drona
    std::vector<double> get_srodek() override;
    /// Zwraca wymiary drona
    std::vector<double> get_wymiary() override;
    /// zwraca punkty ktore sa potrzebne do wyznaczenia mozliwych punktow kolizji dla Drona
    std::vector<std::vector<double>> get_punkty_krytyczne() override;
    int get_typeof() override;
    void wymazPrzeszkode() override;
};

#endif