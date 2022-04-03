#include "Wzgorze.hh"

/// Konstruktor Wzgorza, przyjmujacy kordynaty nowo powstajacego obiektu i rysujacy go w zadanym miejscy. Oblicza rowniez wlasnosc polozenie na podstawie podanych kordynatow.
Wzgorze::Wzgorze(std::shared_ptr<drawNS::Draw3DAPI> _api, std::vector<double> kordynaty){
    dlugosc_boku=std::vector<double>{6,6,2};
    api = _api;
    polozenie=std::vector<double>{0,0,0};
    for (int i = 0; i < 3; i++)
    {
        polozenie[i] = kordynaty[i]; 
    }
    polozenie[2] += dlugosc_boku[2]/2;
    rysuj();
}

/// Wylicza punkty charakteryzujace wzgorze na podstawie dlugosci boku
std::vector<std::vector<double>> Wzgorze::wylicz_punkty(){
    std::vector<double> vec={1,1,1};
    for (int i = 0; i < 3; i++)
    {
        vec[i] = dlugosc_boku[i] / 2;
    }
    std::vector<std::vector<double>> wierzcholki={
        {vec[0], vec[1], vec[2]-dlugosc_boku[2]},
        {vec[0]-dlugosc_boku[0], vec[1], vec[2]-dlugosc_boku[2]},
        {vec[0]-dlugosc_boku[0], vec[1]-dlugosc_boku[1], vec[2]},
        {vec[0], vec[1]-dlugosc_boku[1], vec[2]},
        {vec[0], vec[1], vec[2]-dlugosc_boku[2]},
        {vec[0]-dlugosc_boku[0], vec[1], vec[2]-dlugosc_boku[2]},
        {vec[0]-dlugosc_boku[0], vec[1]-dlugosc_boku[1], vec[2]-dlugosc_boku[2]},
        {vec[0], vec[1]-dlugosc_boku[1], vec[2]-dlugosc_boku[2]}
    };
    
return wierzcholki;
}


/// Sprawdza czy Plaskowyz koliduje z innymi elementami powierzchi poprzez sprawdzenie czy punkty krytyczne Plaskowyz, nie znajduja sie w obrebie figury tworzonej przez punkty krytyczne innego elementu powierzchni.
bool Wzgorze::czy_koliduje(std::shared_ptr<El_Powierzchni> sprawdzany_dron){
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
            std::cout<< std::endl << "kolizja w x"<< std::endl;
          }
          if (sprawdzane_pkt_kry[i][1] > aktualne_pkt_kry[3][1] && sprawdzane_pkt_kry[i][1] < aktualne_pkt_kry[0][1])
          {
              oky = true;
              std::cout<< std::endl << "kolizja w y"<< std::endl;
          }
          if (sprawdzane_pkt_kry[i][2] < aktualne_pkt_kry[0][2] && sprawdzane_pkt_kry[i][2] > aktualne_pkt_kry[4][2])
          {
              okz = true;
              std::cout<< std::endl << "kolizja w z"<< std::endl;
          }
      }
      if(okz && okx && oky){
          std::cout << std::endl << "Uwaga Dron koliduje!"<< std::endl;
          return true;
      }
    }
    return false;
    
}

/// zwraca srodek Plaskowyz, uwzgledniajac ze Plaskowyz sklada sie zarowno z korpusu jak i wirnikow
std::vector<double> Wzgorze::get_srodek(){
    return polozenie;
}

/// zwraca wymiary Plaskowyz (dlugosc, szerokosc, glebokosc)
std::vector<double> Wzgorze::get_wymiary(){
    return dlugosc_boku;
}

/// oblicza wierzcholki Plaskowyz, ktore przyblizajace jego ksztalt, by moc na ich podstawie wykryc kolizje z innymi elementami powierzchni
std::vector<std::vector<double>> Wzgorze::get_punkty_krytyczne(){
    std::vector<double> vec={1,1,1};  
    for (int i = 0; i < 3; i++)
    {
        vec[i] = get_wymiary()[i] / 2;
    }

    std::vector<std::vector<double>> wierzcholki={
        {vec[0], vec[1], vec[2]},
        {vec[0]-get_wymiary()[0], vec[1], vec[2]},
        {vec[0]-get_wymiary()[0], vec[1]-get_wymiary()[1], vec[2]},
        {vec[0], vec[1]-get_wymiary()[1], vec[2]},
        {vec[0], vec[1], vec[2]-get_wymiary()[2]},
        {vec[0]-get_wymiary()[0], vec[1], vec[2]-get_wymiary()[2]},
        {vec[0]-get_wymiary()[0], vec[1]-get_wymiary()[1], vec[2]-get_wymiary()[2]},
        {vec[0], vec[1]-get_wymiary()[1], vec[2]-get_wymiary()[2]}
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

int Wzgorze::get_typeof(){
    return -1;
}

void Wzgorze::wymazPrzeszkode(){
    api->erase_shape(id_rysunku);
    this->~Wzgorze();
}