#include "Stozki.hh"

using std::cout;
using std::cin;
using std::endl;

///////////////////////////////////////////////     Stozki     /////////////////////////////////////////////////

/// Konstruktor bez parametryczny ustawiajacy poczatkowo na 0 dlugosc boku, wysokosc i polozenie
Stozki::Stozki(){
    dlugosc_boku = std::vector<double>{0};
    m_wysokosc = 0;
    polozenie = std::vector<double>{0,0,0};
}

Stozki::Stozki(std::shared_ptr<drawNS::Draw3DAPI> _api, std::vector<double> _kordynaty, double _dlugosc_boku, double _wysokosc, int ilosc_bokow){
    api = _api;
    dlugosc_boku = std::vector<double>{_dlugosc_boku};
    m_wysokosc = _wysokosc;

// umiejscowienie na plaszczyznie
    polozenie=std::vector<double>{0,0,0};
    for (int i = 0; i < 3; i++)
    {
        polozenie[i] = _kordynaty[i]; 
    }
    polozenie[2] -= getWysokosc();
    rysuj();
}


/// Gettery Stozkow
const double & Stozki::getWysokosc() const{
    return m_wysokosc;
}

/// Settery Stozkow
void Stozki::setWysokosc(double nowaWysokosc){
    m_wysokosc = nowaWysokosc;
}

std::vector<std::vector<double>> Stozki::wylicz_punkty(){
    double wysokosctrojkata = sqrt(3)*dlugosc_boku[0]/2;
    std::vector<std::vector<double>> wierzcholki={
        {polozenie[0], polozenie[1]+((2/3.0)*wysokosctrojkata), polozenie[2]},
        {polozenie[0]-(dlugosc_boku[0]*0.5), polozenie[1]-((1/3.0)*wysokosctrojkata), polozenie[2]},
        {polozenie[0]+(dlugosc_boku[0]*0.5), polozenie[1]-((1/3.0)*wysokosctrojkata), polozenie[2]},
        {polozenie[0], polozenie[1], polozenie[2]+getWysokosc()},
        {polozenie[0], polozenie[1], polozenie[2]+getWysokosc()},
        {polozenie[0], polozenie[1], polozenie[2]+getWysokosc()}
    };  
    return wierzcholki;
}

/// Sprawdza czy Stozki koliduje z innymi elementami powierzchi poprzez sprawdzenie czy punkty krytyczne Stozki, nie znajduja sie w obrebie figury tworzonej przez punkty krytyczne innego elementu powierzchni.
bool Stozki::czy_koliduje(std::shared_ptr<El_Powierzchni> sprawdzany_dron){
    std::vector<std::vector<double>> sprawdzane_pkt_kry = get_punkty_krytyczne();
    std::vector<std::vector<double>> aktualne_pkt_kry = sprawdzany_dron->get_punkty_krytyczne();
    
    if (sprawdzany_dron.get() == this)
    {}
    else{
      bool okx = false;
      bool oky = false;
      bool okz = false;

      for (int i = 0; i < 8; i++)
      {
          if ((sprawdzane_pkt_kry[i][0] > aktualne_pkt_kry[0][0] && sprawdzane_pkt_kry[i][0] < aktualne_pkt_kry[1][0] )|| (sprawdzane_pkt_kry[i][0] > aktualne_pkt_kry[1][0] && sprawdzane_pkt_kry[i][0] < aktualne_pkt_kry[0][1]))
          {
            okx = true;
          }
          if (sprawdzane_pkt_kry[i][1] > aktualne_pkt_kry[3][1] && sprawdzane_pkt_kry[i][1] < aktualne_pkt_kry[0][1])
          {
              oky = true;
          }
          if (sprawdzane_pkt_kry[i][2] < aktualne_pkt_kry[0][2] && sprawdzane_pkt_kry[i][2] > aktualne_pkt_kry[4][2])
          {
              okz = true;
          }
      }
      if(okz && okx && oky){
          std::cout << std::endl << "Uwaga Dron koliduje!"<< std::endl;
          return true;
      }
    }
    return false;
    
}

/// zwraca srodek Stozki, uwzgledniajac ze Stozki sklada sie zarowno z korpusu jak i wirnikow
std::vector<double> Stozki::get_srodek(){
    return polozenie;
}

/// zwraca wymiary Stozki (dlugosc, szerokosc, glebokosc)
std::vector<double> Stozki::get_wymiary(){
    return dlugosc_boku;
}

/// oblicza wierzcholki Stozki, ktore przyblizajace jego ksztalt, by moc na ich podstawie wykryc kolizje z innymi elementami powierzchni
std::vector<std::vector<double>> Stozki::get_punkty_krytyczne(){
    std::vector<double> vec={1,1,1};
    
    for (int i = 0; i < 3; i++)
    {
        vec[i] = get_srodek()[i] / 2;
    }
    std::vector<std::vector<double>> wierzcholki={
        {vec[0], vec[1], vec[2]},
        {vec[0]-get_wymiary()[0]/2, vec[1], vec[2]},
        {vec[0]-get_wymiary()[0]/2, vec[1]-get_wymiary()[1]/2, vec[2]},
        {vec[0], vec[1]-get_wymiary()[1]/2, vec[2]},
        {vec[0], vec[1], vec[2]-get_wymiary()[2]},
        {vec[0]-get_wymiary()[0]/2, vec[1], vec[2]-get_wymiary()[2]},
        {vec[0]-get_wymiary()[0]/2, vec[1]-get_wymiary()[1]/2, vec[2]-get_wymiary()[2]},
        {vec[0], vec[1]-get_wymiary()[1]/2, vec[2]-get_wymiary()[2]}
        };
    return wierzcholki;
}

////////////////////////////////////////////     TrojkatneStozki     /////////////////////////////////////////

TrojkatneStozki::TrojkatneStozki(std::shared_ptr<drawNS::Draw3DAPI> _api, std::vector<double> _kordynaty, double _dlugosc_boku, double _wysokosc){
    api = _api;
    dlugosc_boku = std::vector<double>{_dlugosc_boku};
    setWysokosc(_wysokosc);

    polozenie=std::vector<double>{0,0,-2};
    for (int i = 0; i < 3; i++)
    {
        polozenie[i] = _kordynaty[i]/2; 
    }
    rysuj();
}

std::vector<std::vector<double>> TrojkatneStozki::wylicz_punkty(){
    double wysokosctrojkata = sqrt(3)*dlugosc_boku[0]/2;
    std::vector<std::vector<double>> wierzcholki={
        {polozenie[0], polozenie[1]+((2/3.0)*wysokosctrojkata), polozenie[2]},
        {polozenie[0]-(dlugosc_boku[0]*0.5), polozenie[1]-((1/3.0)*wysokosctrojkata), polozenie[2]},
        {polozenie[0]+(dlugosc_boku[0]*0.5), polozenie[1]-((1/3.0)*wysokosctrojkata), polozenie[2]},
        {polozenie[0]+(dlugosc_boku[0]*0.5), polozenie[1]-((1/3.0)*wysokosctrojkata), polozenie[2]},
        {polozenie[0], polozenie[1], polozenie[2]+getWysokosc()},
        {polozenie[0], polozenie[1], polozenie[2]+getWysokosc()},
        {polozenie[0], polozenie[1], polozenie[2]+getWysokosc()},
        {polozenie[0], polozenie[1], polozenie[2]+getWysokosc()}
    
    };  
    return wierzcholki;
}

/// Sprawdza czy TrojkatneStozki koliduje z innymi elementami powierzchi poprzez sprawdzenie czy punkty krytyczne TrojkatneStozki, nie znajduja sie w obrebie figury tworzonej przez punkty krytyczne innego elementu powierzchni.
bool TrojkatneStozki::czy_koliduje(std::shared_ptr<El_Powierzchni> sprawdzany_dron){
    std::vector<std::vector<double>> sprawdzane_pkt_kry = get_punkty_krytyczne();
    std::vector<std::vector<double>> aktualne_pkt_kry = sprawdzany_dron->get_punkty_krytyczne();
    
    if (sprawdzany_dron.get() == this)
    {}
    else{
      bool okx = false;
      bool oky = false;
      bool okz = false;
          
      for (int i = 0; i < sprawdzane_pkt_kry.capacity(); i++)
      {
          if ((sprawdzane_pkt_kry[i][0] > aktualne_pkt_kry[0][0] && sprawdzane_pkt_kry[i][0] < aktualne_pkt_kry[1][0] )|| (sprawdzane_pkt_kry[i][0] > aktualne_pkt_kry[1][0] && sprawdzane_pkt_kry[i][0] < aktualne_pkt_kry[0][1]))
          {
            okx = true;
          }
          if (sprawdzane_pkt_kry[i][1] > aktualne_pkt_kry[3][1] && sprawdzane_pkt_kry[i][1] < aktualne_pkt_kry[0][1])
          {
              oky = true;
          }
          if (sprawdzane_pkt_kry[i][2] < aktualne_pkt_kry[0][2] && sprawdzane_pkt_kry[i][2] > aktualne_pkt_kry[4][2])
          {
              okz = true;
          }
      }
      if(okz && okx && oky){
          std::cout << std::endl << "Uwaga Dron koliduje!"<< std::endl;
          return true;
      }
    }
    return false;
    
}

/// zwraca srodek TrojkatneStozki, uwzgledniajac ze TrojkatneStozki sklada sie zarowno z korpusu jak i wirnikow
std::vector<double> TrojkatneStozki::get_srodek(){
    return polozenie;
}

/// zwraca wymiary TrojkatneStozki (dlugosc, szerokosc, glebokosc)
std::vector<double> TrojkatneStozki::get_wymiary(){
    std::vector<double> result;
    result.push_back(dlugosc_boku[0]);
    result.push_back(dlugosc_boku[0]);
    result.push_back(getWysokosc());
    return result;
}

/// oblicza wierzcholki TrojkatneStozki, ktore przyblizajace jego ksztalt, by moc na ich podstawie wykryc kolizje z innymi elementami powierzchni
std::vector<std::vector<double>> TrojkatneStozki::get_punkty_krytyczne(){
    std::vector<double> vec={1,1,1};  
    for (int i = 0; i < 3; i++)
    {
        vec[i] = get_srodek()[i] * 3 / 2;
    }
    vec[2]=(-2);

    std::vector<std::vector<double>> wierzcholki={
        {vec[0],                      vec[1],                    vec[2]+get_wymiary()[2]},
        {vec[0]-(get_wymiary()[0]/2), vec[1],                    vec[2]+get_wymiary()[2]},
        {vec[0]-get_wymiary()[0]/2,   vec[1]-get_wymiary()[1]/2, vec[2]+get_wymiary()[2]},
        {vec[0],                      vec[1]-get_wymiary()[1]/2, vec[2]+get_wymiary()[2]},
        {vec[0],                      vec[1],                    vec[2]},
        {vec[0]-get_wymiary()[0]/2,   vec[1],                    vec[2]},
        {vec[0]-get_wymiary()[0]/2,   vec[1]-get_wymiary()[1]/2, vec[2]},
        {vec[0],                      vec[1]-get_wymiary()[1]/2, vec[2]}
        };

    int ilosc_wierzcholkow = wierzcholki.capacity();
    for (int i = 0; i < ilosc_wierzcholkow; i++)
    {
        wierzcholki[i] = orientacja * wierzcholki[i];
        for (int  j = 0; j < 3; j++)
        {
            wierzcholki[i][j] = wierzcholki[i][j] + get_srodek()[j];
        }
    }
    return wierzcholki;
}


int Stozki::get_typeof(){
    return -1;
}

int TrojkatneStozki::get_typeof(){
    return -1;
}

void Stozki::wymazPrzeszkode(){
    api->erase_shape(id_rysunku);
    this->~Stozki();
}
void TrojkatneStozki::wymazPrzeszkode(){
    api->erase_shape(id_rysunku);
    this->~TrojkatneStozki();
}
