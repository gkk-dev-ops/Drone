#include "PlaskaPowierzchnia.hh"

PlaskaPowierzchnia::PlaskaPowierzchnia(std::shared_ptr<drawNS::Draw3DAPI> _api,double _wysokosc,double _wielkosc){
    api = _api;
    wysokosc=_wysokosc;
    wielkosc=_wielkosc;
    rysuj();
}
    
/// rysuje plaska powierzchnie 
void PlaskaPowierzchnia::rysuj(){
    std::vector<std::vector<drawNS::Point3D>> powierzchnia;
    for (int j = 0; j < wielkosc; j++)
    {
      std::vector<drawNS::Point3D> tmp;
      for (int i = 0; i < wielkosc; i++)
      {
        tmp.push_back(drawNS::Point3D(-wielkosc+2*i,-wielkosc+2*j,wysokosc));
      }
      powierzchnia.push_back(tmp);
    }
    id_rysunku = api->draw_surface(powierzchnia,"black");
}

void PlaskaPowierzchnia::wymazPrzeszkode(){
  wylaczWidocznosc();
}
void PlaskaPowierzchnia::wylaczWidocznosc(){
  api->erase_shape(id_rysunku);
}

/// Gettery plaskiejPowierzchni
/// Zwraca wielkosc plaskiej powierzchni czyli jej wymiar w osi x i osi y
int const PlaskaPowierzchnia::get_wielkosc() const{
  return wielkosc;
}
/// Zwraca wysokosc na ktorej znajduje sie plaska powierzchnia
double const PlaskaPowierzchnia::get_wysokosc() const{
  return wysokosc;
}
/// Settery plaskiejPowierzchni
/// Ustawia wielkosc (w osi x i w osi y) jak ma miec plaska powierzchnia 
void PlaskaPowierzchnia::set_wielkosc(int nowa_wielkosc){
  wielkosc = nowa_wielkosc;
}
/// Ustawia wysokosc na ktorej ma znajdowac sie plaska powierzchnia
void PlaskaPowierzchnia::set_wysokosc(double nowa_wysokosc){
  wysokosc = nowa_wysokosc;
}

int PlaskaPowierzchnia::get_typeof(){
  return 1;
}

bool PlaskaPowierzchnia::czy_koliduje(std::shared_ptr<El_Powierzchni> sprawdzany_dron){
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

/// zwraca srodek PlaskaPowierzchnia, uwzgledniajac ze PlaskaPowierzchnia sklada sie zarowno z korpusu jak i wirnikow
std::vector<double> PlaskaPowierzchnia::get_srodek(){
    return std::vector<double>{0,0,wysokosc};
}

/// zwraca wymiary PlaskaPowierzchnia (dlugosc, szerokosc, glebokosc)
std::vector<double> PlaskaPowierzchnia::get_wymiary(){
    return std::vector<double>{2*wielkosc,2*wielkosc,0.0001};
}

/// oblicza wierzcholki PlaskaPowierzchnia, ktore przyblizajace jego ksztalt, by moc na ich podstawie wykryc kolizje z innymi elementami powierzchni
std::vector<std::vector<double>> PlaskaPowierzchnia::get_punkty_krytyczne(){
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
        for (int  j = 0; j < 3; j++)
        {
            wierzcholki[i][j] = wierzcholki[i][j] + get_srodek()[j];
        }
    }
    return wierzcholki;
}