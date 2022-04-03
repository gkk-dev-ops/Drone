#include "Plaskowyz.hh"

Plaskowyz::Plaskowyz(std::shared_ptr<drawNS::Draw3DAPI> _api, std::vector<double> kordynaty){
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

/// Sprawdza czy Plaskowyz koliduje z innymi elementami powierzchi poprzez sprawdzenie czy punkty krytyczne Plaskowyz, nie znajduja sie w obrebie figury tworzonej przez punkty krytyczne innego elementu powierzchni.
bool Plaskowyz::czy_koliduje(std::shared_ptr<El_Powierzchni> sprawdzany_dron){
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

/// zwraca srodek Plaskowyz, uwzgledniajac ze Plaskowyz sklada sie zarowno z korpusu jak i wirnikow
std::vector<double> Plaskowyz::get_srodek(){
    return polozenie;
}

/// zwraca wymiary Plaskowyz (dlugosc, szerokosc, glebokosc)
std::vector<double> Plaskowyz::get_wymiary(){
    return dlugosc_boku;
}

/// oblicza wierzcholki Plaskowyz, ktore przyblizajace jego ksztalt, by moc na ich podstawie wykryc kolizje z innymi elementami powierzchni
std::vector<std::vector<double>> Plaskowyz::get_punkty_krytyczne(){
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


int Plaskowyz::get_typeof(){
    return 1;
}

void Plaskowyz::wymazPrzeszkode(){
    api->erase_shape(id_rysunku);
    this->~Plaskowyz();
}