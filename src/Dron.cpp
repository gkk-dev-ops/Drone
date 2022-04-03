#include "Dron.hh"

using namespace std::chrono_literals;
using std::cout;
using std::cin;
using std::endl;


/// Rysuje korpus drona (prostopadloscian) i wirniki drona (graniastoslupy)
void Dron::rysuj(){
    korpus_drona.rysuj();
    for (int i = 0; i < ILOSC_WIRNIKOW; i++)
    {
        wirniki[i].rysuj();
    }       
}

/// Konstruktor parametryczny drona
/// ustawia poczatkowe polozenie drona na 0,0,0
/// pobiera api drona
/// inicjuje korpus drona (prostopadloscian)
/// tworzy wirniki (graniastoslupy) oraz oblicza ich poczotkowa pozycje wzgledem korpusu ustawiajac je w odpowiednich miejscach
Dron::Dron(std::shared_ptr<drawNS::Draw3DAPI> _api, std::vector<double> position)
{
    polozenie = position;
    api = _api;
    korpus_drona = Prostopadloscian(_api);
    for (int i = 0; i < ILOSC_WIRNIKOW; i++)
    {
        wirniki.push_back(Graniastoslup(_api));    
        wirniki[i].polozenie[2] = korpus_drona.dlugosc_boku[2] / 2 + wirniki[i].dlugosc_boku[2] / 2;
    }
    korpus_drona.polozenie = polozenie;
    wirniki[0].polozenie[0] = korpus_drona.dlugosc_boku[0] / 2 ;
    wirniki[0].polozenie[1] = korpus_drona.dlugosc_boku[1] / 2 ;

    wirniki[1].polozenie[0] = -korpus_drona.dlugosc_boku[0] / 2 ;
    wirniki[1].polozenie[1] = korpus_drona.dlugosc_boku[1] / 2  ;

    wirniki[2].polozenie[0] = korpus_drona.dlugosc_boku[0] / 2  ;
    wirniki[2].polozenie[1] = -korpus_drona.dlugosc_boku[1] / 2 ;

    wirniki[3].polozenie[0] = -korpus_drona.dlugosc_boku[0] / 2 ;
    wirniki[3].polozenie[1] = -korpus_drona.dlugosc_boku[1] / 2 ;    
}

Dron::Dron(std::shared_ptr<drawNS::Draw3DAPI> _api)
{
    api = _api;
    korpus_drona = Prostopadloscian(_api);
    for (int i = 0; i < ILOSC_WIRNIKOW; i++)
    {
        wirniki.push_back(Graniastoslup(_api));
        wirniki[i].polozenie[2] = korpus_drona.dlugosc_boku[2] / 2 + wirniki[i].dlugosc_boku[2] / 2;
    }
    korpus_drona.polozenie = std::vector<double>{ 0,0,0 };
    wirniki[0].polozenie[0] = korpus_drona.dlugosc_boku[0] / 2;
    wirniki[0].polozenie[1] = korpus_drona.dlugosc_boku[1] / 2;

    wirniki[1].polozenie[0] = -korpus_drona.dlugosc_boku[0] / 2;
    wirniki[1].polozenie[1] = korpus_drona.dlugosc_boku[1] / 2;

    wirniki[2].polozenie[0] = korpus_drona.dlugosc_boku[0] / 2;
    wirniki[2].polozenie[1] = -korpus_drona.dlugosc_boku[1] / 2;

    wirniki[3].polozenie[0] = -korpus_drona.dlugosc_boku[0] / 2;
    wirniki[3].polozenie[1] = -korpus_drona.dlugosc_boku[1] / 2;
}

void positionDronParts(){


}

Dron::~Dron(){}

/// Przesuwa drona o zorientowany wzgledem aktualnego polozenia drona wektor, by uwzglednic aktualne polozenie wirnikow
void Dron::przesun(std::vector<double>vec){
    std::vector<double> zorientowany_wektor= {orientacja*vec};
    korpus_drona.przesun_o_wektor(zorientowany_wektor);
    for (int i = 0; i < ILOSC_WIRNIKOW-1; i++)
    {
        wirniki[i].przesun_o_wektor(zorientowany_wektor);
    }
    for (int i=0; i<2; i++) // off by one 4/4/22
    {
        polozenie[i]+=zorientowany_wektor[i];
    }
}

/// dron leci do przodu lub do tylu w zaleznosci, czy wartosc podana mu jest ujemna czy dodatnia, oraz uruchamia animacje obrotu wirnikow. Sprawdza czy dron koliduje z innym obiektem i w razie gdy koliduje zmienia uniemozliwia mu ruch w tym kierunku.
bool Dron::lec_do_przodu(double ile, std::vector<std::shared_ptr<El_Powierzchni>> PrzeszkodyNaScenie){
    const int znak = ile/abs(ile);
    for (double i = 0; i < abs(ile); i+=0.1)
    {
        przesun(std::vector<double>{0.1*znak,0,0});
        uruchom_wirniki();
        for(int j=0;j<PrzeszkodyNaScenie.capacity();j++){

            if(czy_koliduje(PrzeszkodyNaScenie[j]))
            {
                przesun(std::vector<double>{-0.1*znak,0,0});
                uruchom_wirniki();
                return true;
            }
        }
    }   
    return false;
}

/// dron wznosi sie lub opada w zaleznosci, czy wartosc podana mu jest ujemna czy dodatnia, oraz uruchamia animacje obrotu wirnikow. Sprawdza czy dron koliduje z innym obiektem i w razie gdy koliduje zmienia uniemozliwia mu ruch w tym kierunku.
bool Dron::lec_w_gore(double ile, std::vector<std::shared_ptr<El_Powierzchni>> PrzeszkodyNaScenie){
    double znak = ile/abs(ile);
    double rozdzielczosc = 0.1;
    for (double i = 0; i < (znak*ile); i+=rozdzielczosc)
    {
        przesun(std::vector<double>{0,0,rozdzielczosc*znak});
        uruchom_wirniki();

        for (int i = 0; i < PrzeszkodyNaScenie.capacity(); i++)
        {

            if (czy_koliduje(PrzeszkodyNaScenie[i]))
            {

                przesun(std::vector<double>{0,0,-rozdzielczosc*znak});
                uruchom_wirniki();
                return true;
            }
            
        }
    }
    return false;
}

std::vector<std::vector<double>> Dron::wylicz_punkty(){
    std::cout << "Wylicz_punkty() is defined just for technical resons - don't use it!";
    return std::vector<std::vector<double>>{};
}

/// Po podaniu dronowi punktu do ktorego ma leciec i w przypadku braku kolizji (w razie kolizji przerywa procedure) wznosi go na wysokosc 3 jednostek, obraca w kierunku podanego punktu, oraz wywoluje metode lec_do_przodu o roznice wektora aktualnej pozycji i pozycji docelowej. Na koniec dron leci o 3 jednostki w dol wracajac do poprzedniej wysokosci. 
bool Dron::lec_do_punktu(std::vector<double> punkt_docelowy, std::vector<std::shared_ptr<El_Powierzchni>> PrzeszkodyNaScenie){
    const double jak_wysoko_st_st = 3;
    if (lec_w_gore(jak_wysoko_st_st, PrzeszkodyNaScenie)){
        lec_w_gore(-jak_wysoko_st_st, PrzeszkodyNaScenie);
        laduj(PrzeszkodyNaScenie);
        return true;
    }
    double kat_wektor_orientacji = acos(orientacja.get_Mac(0,0));
    std::vector<double> wektor_orientacji;
    wektor_orientacji.push_back(orientacja.get_Mac(0,0));
    wektor_orientacji.push_back(orientacja.get_Mac(1,0));
    wektor_orientacji.push_back(polozenie[2]);

    std::vector<double> wektor_przemieszczenia = odejmowanie_wektorow(punkt_docelowy,polozenie);

    double kat_wzgl_xy = ((wektor_orientacji[0]*wektor_przemieszczenia[0]) + (wektor_orientacji[1]*wektor_przemieszczenia[1]))/(dlugosc_wektora(wektor_orientacji)*dlugosc_wektora(wektor_przemieszczenia));
    kat_wzgl_xy = acos(kat_wzgl_xy);
    kat_wzgl_xy = (kat_wzgl_xy*180)/M_PI;
    if(aktualizuj_orientacje(kat_wzgl_xy,PrzeszkodyNaScenie)){
        aktualizuj_orientacje(-kat_wzgl_xy,PrzeszkodyNaScenie);
        laduj(PrzeszkodyNaScenie);
        return true;
    }

    double oileleciec = dlugosc_wektora(odejmowanie_wektorow(punkt_docelowy,polozenie));
    
    if(lec_do_przodu(oileleciec,PrzeszkodyNaScenie)){
        lec_do_przodu(-3,PrzeszkodyNaScenie);
        laduj(PrzeszkodyNaScenie);
        return true;
    }

    if(lec_w_gore(-jak_wysoko_st_st, PrzeszkodyNaScenie)){
        lec_w_gore(jak_wysoko_st_st, PrzeszkodyNaScenie);
        laduj(PrzeszkodyNaScenie);
        return true;
    }
        
    laduj(PrzeszkodyNaScenie);
    return false;
}

/// Obraca wirniki i animuje ich ruch
// kierunek lewo -1 / 1 prawo
void Dron::uruchom_wirniki(){
    for (int i = 0; i < 5; i++)
    {
        int kat = 72;
        wirniki[0].obrot(-kat,'z');
        wirniki[1].obrot(kat,'z');
        wirniki[2].obrot(kat,'z');
        wirniki[3].obrot(-kat,'z');
        rysuj();
        std::this_thread::sleep_for(std::chrono::milliseconds(1));       
    }
}

/// Funkcja animujaca obrot drona przemnaza orientacje drona by uzyskac docelowa, wraz z obrotem drona przesuwajac odpowiednio wirni, by nie odczepily sie od korpusu, oraz animuje obrot drona. Sprawdza czy dron nie koliduje z innymi obiektami i w przypadku kolizji uniemozliwia mu dalszy obrot. 
/// [!] przyjmuje kat w stopniach
bool Dron::aktualizuj_orientacje(double kat, std::vector<std::shared_ptr<El_Powierzchni>> PrzeszkodyNaScenie){
    const double rozdzielczosc = 1;
    const int znak = kat/abs(kat);
    for (int w = 0; w < (kat*znak); w++)
    {
        KonkretnaMacierz tmp('z',znak*rozdzielczosc);
        Macierz3x3 nowaOrientacja = tmp.KonkretnaMacierz_do_Macierz3x3();
        korpus_drona.orientacja = korpus_drona.orientacja * nowaOrientacja;
        orientacja = orientacja * nowaOrientacja;

        for (int i = 0; i < ILOSC_WIRNIKOW; i++)
        {
            std::vector<double> tmp={0,0,0};
            for (int j = 0; j < 3; j++)
            {
                tmp[j]=wirniki[i].polozenie[j] - polozenie[j];
            }
            for (int j = 0; j < 3; j++)
            {
                (wirniki[i].polozenie)[j] = (nowaOrientacja*(tmp))[j] + polozenie[j];
            }
            wirniki[i].orientacja = wirniki[i].orientacja * nowaOrientacja;
        }
        uruchom_wirniki();
        for(int i=0; i< PrzeszkodyNaScenie.capacity(); i++){
            if(czy_koliduje(PrzeszkodyNaScenie[i]))
            {
                KonkretnaMacierz tmp('z',(-rozdzielczosc)*znak);
                Macierz3x3 nowaOrientacja = tmp.KonkretnaMacierz_do_Macierz3x3();
                korpus_drona.orientacja = korpus_drona.orientacja * nowaOrientacja;
                orientacja = orientacja * nowaOrientacja;

                for (int i = 0; i < ILOSC_WIRNIKOW; i++)
                {
                    std::vector<double> tmp={0,0,0};
                    for (int j = 0; j < 3; j++)
                    {
                        tmp[j]=wirniki[i].polozenie[j] - polozenie[j];
                    }
                    for (int j = 0; j < 3; j++)
                    {
                        (wirniki[i].polozenie)[j] = (nowaOrientacja*(tmp))[j] + polozenie[j];
                    }
                    wirniki[i].orientacja = wirniki[i].orientacja * nowaOrientacja;
                }
                uruchom_wirniki();
                return true;
            }
        }
    }
    return false;
}

/// Sprawdza czy dron koliduje z innymi elementami powierzchi poprzez sprawdzenie czy punkty krytyczne drona, nie znajduja sie w obrebie figury tworzonej przez punkty krytyczne innego elementu powierzchni.
bool Dron::czy_koliduje(std::shared_ptr<El_Powierzchni> sprawdzany_dron){
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
          cout<< endl << "Dron: Uwaga kolizja z dronem"<< endl;
          return true;
        }
    }
    return false;
    
}

/// zwraca srodek drona, uwzgledniajac ze dron sklada sie zarowno z korpusu jak i wirnikow
std::vector<double> Dron::get_srodek(){
    std::vector<double> srodek_drona(3,0);
    srodek_drona = polozenie;
    srodek_drona[2] += (wirniki[0].dlugosc_boku[2]/2);
    return srodek_drona;
}

/// zwraca wymiary drona (dlugosc, szerokosc, glebokosc)
std::vector<double> Dron::get_wymiary(){
    std::vector<double> wymiary_drona(3,0);
    for (int i = 0; i < 3; i++)
    {
        wymiary_drona[i] = (wirniki[0].dlugosc_boku[i]) + (korpus_drona.dlugosc_boku[i]);
    }
    return wymiary_drona;
}

/// oblicza wierzcholki drona, ktore przyblizajace jego ksztalt, by moc na ich podstawie wykryc kolizje z innymi elementami powierzchni
std::vector<std::vector<double>> Dron::get_punkty_krytyczne(){
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

/// Wymazuje korpus drona i wirniki
void Dron::wymazDrona(){
    api->erase_shape(wirniki[0].id_rysunku);
    api->erase_shape(wirniki[1].id_rysunku);
    api->erase_shape(wirniki[2].id_rysunku);
    api->erase_shape(wirniki[3].id_rysunku);
    api->erase_shape(korpus_drona.id_rysunku);
}
void Dron::wymazPrzeszkode(){
    wymazDrona();   
}
bool Dron::laduj(std::vector<std::shared_ptr<El_Powierzchni>> PrzeszkodyNaScenie){
    std::vector<std::vector<double>> sprawdzane_pkt_kry = get_punkty_krytyczne();
    for (int n = PrzeszkodyNaScenie.capacity()-1; n >= 0 ; n--)       
    {    
        std::vector<std::vector<double>> aktualne_pkt_kry = PrzeszkodyNaScenie[n]->get_punkty_krytyczne();
        if (PrzeszkodyNaScenie[n].get() == this){}
        else{

            for (int i = 0; i < sprawdzane_pkt_kry.capacity(); i++)
            {
                bool okx = false;
                bool oky = false;
                if ((sprawdzane_pkt_kry[i][0] > aktualne_pkt_kry[0][0] && sprawdzane_pkt_kry[i][0] < aktualne_pkt_kry[1][0] )|| (sprawdzane_pkt_kry[i][0] > aktualne_pkt_kry[1][0] && sprawdzane_pkt_kry[i][0] < aktualne_pkt_kry[0][1]))
                {
                    okx = true;
                }
                if (sprawdzane_pkt_kry[i][1] > aktualne_pkt_kry[3][1] && sprawdzane_pkt_kry[i][1] < aktualne_pkt_kry[0][1])
                {
                    oky = true;
                }
                if(okx && oky){
                    cout<< endl << "Dron: Znajduje sie nad obiektem"<< endl;
                    if (PrzeszkodyNaScenie[n]->get_typeof() == 1 ){
                        lec_w_gore(-100000, PrzeszkodyNaScenie);
                    }
                    else{
                        cout << endl << "Nie mozna ladowac"<< endl;
                        return false;
                    }
                }
            }
        }
    }
    return false;
}

int Dron::get_typeof(){
    return -1;
}