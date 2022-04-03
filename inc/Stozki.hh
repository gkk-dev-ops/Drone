#ifndef STOZKI
#define STOZKI

#include "El_Powierzchni.hh"
#include "prostopadloscian.hh"

// Rodzaj przeszkody: stozki z wielokatnymi podstawami
class Stozki : public Prostopadloscian, public El_Powierzchni
{
private:
    double m_wysokosc;
public:
    /// Gettery Stozkow
    const double & getWysokosc() const;
    /// Settery Stozkow
    void setWysokosc(double nowaWysokosc);

    /// Konstruktor Stozkow
    Stozki();
    /// Konstruktor parametryczny Stozkow
    Stozki(std::shared_ptr<drawNS::Draw3DAPI> _api, std::vector<double> _kordynaty, double _dlugosc_boku, double _wysokosc, int ilosc_bokow);
    // Destruktor Stozkow
    ~Stozki(){};
    //Metody Stozkow
    std::vector<std::vector<double>> wylicz_punkty() override;
    
    /// Sprawdza czy Stozkow koliduje z podanym elementem powierzchni
    bool czy_koliduje(std::shared_ptr<El_Powierzchni> sprawdzany_dron) override;
    /// Zwraca srodek Stozkow
    std::vector<double> get_srodek()override;
    /// Zwraca wymiary Stozkow
    std::vector<double> get_wymiary()override;
    /// zwraca punkty ktore sa potrzebne do wyznaczenia mozliwych punktow kolizji dla Stozkow
    std::vector<std::vector<double>> get_punkty_krytyczne()override;

    int get_typeof() override;
    void wymazPrzeszkode() override;
};


/// Stozki z trojkatem w podstawie
class TrojkatneStozki : public Stozki
{
public:
    /// Konstruktor parametryczny Trojkatnego Stozka
    TrojkatneStozki(std::shared_ptr<drawNS::Draw3DAPI> _api, std::vector<double> _kordynaty, double _dlugosc_boku, double _wysokosc);
    /// Destruktor Trojkatnego Stozka
    ~TrojkatneStozki(){};
    /// Metody TrojkatnychStozkow
    /// Wylicza wierzcholki TrojkatnychStozkow
    std::vector<std::vector<double>> wylicz_punkty() override;

    /// Sprawdza czy Stozkow koliduje z podanym elementem powierzchni
    bool czy_koliduje(std::shared_ptr<El_Powierzchni> sprawdzany_dron) override;
    /// Zwraca srodek Stozkow
    std::vector<double> get_srodek()override;
    /// Zwraca wymiary Stozkow
    std::vector<double> get_wymiary()override;
    /// zwraca punkty ktore sa potrzebne do wyznaczenia mozliwych punktow kolizji dla Stozkow
    std::vector<std::vector<double>> get_punkty_krytyczne()override;
    
    int get_typeof() override;
    void wymazPrzeszkode() override;
};

#endif