#include <iostream>
#include "Plaskowyz.hh"
#include "OpenGL_API.hh"
#include "Graniastoslup.hh"
#include "konkretnaMacierz.hh"
#include "Dron.hh"
#include "PlaskaPowierzchnia.hh"
#include "Wzgorze.hh"
#include "Stozki.hh"
#include "Scena.hh"

bool DEMO_SCENE_DRONES = 0;
bool DEMO_SCENE_OBSTACLES = 1;

void wait4key() {
    do {
        std::cout << "\n Press enter to continue..." << std::endl;
    } while(std::cin.get() != '\n');
}


int main(int argc, char **argv){
    std::shared_ptr<drawNS::Draw3DAPI> pOpenglApi(new drawNS::APIopenGL3D(-15,15,-15,15,-15,15,0,&argc,argv));
    Scena CurrentScene;


    PlaskaPowierzchnia pow(pOpenglApi,-2,15);
    CurrentScene.dodajPrzeszkode(&pow);
    return 0;
    if (DEMO_SCENE_OBSTACLES)
    {
        Plaskowyz* Przykplask = new Plaskowyz(pOpenglApi, std::vector<double>{7, 7, -2});
        CurrentScene.dodajPrzeszkode(Przykplask);

        Wzgorze* Przykwzg1 = new Wzgorze(pOpenglApi, std::vector<double>{-7, -7, -2});
        CurrentScene.dodajPrzeszkode(Przykwzg1);

        TrojkatneStozki* PrzykStk = new TrojkatneStozki(pOpenglApi, std::vector<double>{12, -12, -2}, 6, 9);
        CurrentScene.dodajPrzeszkode(PrzykStk);
    }

    if (DEMO_SCENE_DRONES) {
        CurrentScene.dodajDrona(pOpenglApi);
        std::cout << "Dodano drona nr: " << CurrentScene.getAktualnyDron();
        CurrentScene.getAktualnyDron()->lec_do_punktu(std::vector<double>{-12,-12},CurrentScene.getPrzeszkodyNaScenie());
       
        CurrentScene.dodajDrona(pOpenglApi);
        std::cout << "Dodano drona nr: " << CurrentScene.getAktualnyDron();
        CurrentScene.getAktualnyDron()->lec_do_punktu(std::vector<double>{-6,-6},CurrentScene.getPrzeszkodyNaScenie());

        CurrentScene.dodajDrona(pOpenglApi);
        std::cout << "Dodano drona nr: " << CurrentScene.getAktualnyDron();
        CurrentScene.getAktualnyDron()->laduj(CurrentScene.getPrzeszkodyNaScenie());
        }

    while (true)
    {
        char opt;
        /// domyslna sceneria
        /// UI
        std::cout<<"==================\n"
              "===    MENU    ===\n"
              "==================\n"
              "1. Dodaj/usun drona\n"
              "2. Dodaj/usun przeszkode\n"
              "3. Wybierz drona\n"
              "4. Steruj aktualnym dronem\n"
              "5. Wlacz/Wylacz widocznosc powierzchni\n"
              "x. Koniec programu\n"
              "===================\n"
              "Aktualny Dron:\n"<<
               CurrentScene.getAktualnyDron() << std::endl <<
              "==================="<< std::endl;
        std::cin>>opt;
        switch(opt){
            case '1':
              char plusMinusDron;
              std::cout << "Chesz dodac drona czy usunac aktualnego drona?"<< std::endl;
              std::cin>>plusMinusDron;
              if (plusMinusDron == '+'){
                  CurrentScene.dodajDrona(pOpenglApi);
                  std::cout << "Dodano drona nr: " << CurrentScene.getAktualnyDron();
              }
              else if (plusMinusDron == '-'){
                  std::cout << "Podaj numer drona ktorego chcesz usunac:"<< std::endl;
                  CurrentScene.WypiszWspolrzedneDronow();
                  int indexUsuwanegoDrona;
                  std::cin >> indexUsuwanegoDrona;
                  CurrentScene.usunDrona(pOpenglApi,indexUsuwanegoDrona);
              }
              else{
                  std::cout << "Nie ma takiej opcji" << std::endl;
              }
            break;
            case '2':
                std::cout << "Chesz dodac czy usunac przeszkode?"<< std::endl;
                char plusMinusPrzeszkoda;
                std::cin >>plusMinusPrzeszkoda;
                if (plusMinusPrzeszkoda == '+'){
                    std::cout << "Jaka przeszode chcesz dodac?"<< std::endl;
                    std::cout << "1. Plaskowyz "<< std::endl;
                    std::cout << "2. Wzgorze"<< std::endl;
                    std::cout << "3. n-katny stozek"<< std::endl;
                    int jakaPrzeszkodeDodac=0;
                    std::cin >> jakaPrzeszkodeDodac;
                    if (jakaPrzeszkodeDodac == 1){
                    std::cout << "Podaj kordynaty na ktorych ma sie znalezc plaskowyz"<< std::endl;
                        double gdziePlaskowyz[2];
                        std::cout<<"podaj wspolrzedna x"<< std::endl;
                        std::cin >> gdziePlaskowyz[0];
                        std::cout<<"podaj wspolrzedna y"<< std::endl;
                        std::cin >> gdziePlaskowyz[1];
                        Plaskowyz* plask1 = new Plaskowyz(pOpenglApi, std::vector<double>{gdziePlaskowyz[0],gdziePlaskowyz[1],-2});    
                        CurrentScene.dodajPrzeszkode(plask1);
                    }
                    else if (jakaPrzeszkodeDodac == 2){
                        std::cout << "Podaj kordynaty na ktorych ma sie znalezc wzgorze"<< std::endl;
                        double gdzieWzgorze[2];
                        std::cout<<"podaj wspolrzedna x"<< std::endl;
                        std::cin >> gdzieWzgorze[0];
                        std::cout<<"podaj wspolrzedna y"<< std::endl;
                        std::cin >> gdzieWzgorze[1];
                        Wzgorze* wzg1 = new Wzgorze(pOpenglApi, std::vector<double>{gdzieWzgorze[0],gdzieWzgorze[1],-2});    
                        CurrentScene.dodajPrzeszkode(wzg1); 
                    }
                    else if (jakaPrzeszkodeDodac == 3){
                        std::cout << "Ilu katny stozek?"<< std::endl;
                        std::cin >> jakaPrzeszkodeDodac;
                        if (jakaPrzeszkodeDodac == 3){
                            std::cout << "Podaj kordynaty na ktorych ma sie znalezc trojkatny stozek"<< std::endl;
                            double gdzieStozek3[2];
                            std::cout<<"podaj wspolrzedna x"<< std::endl;
                            std::cin >> gdzieStozek3[0];
                            std::cout<<"podaj wspolrzedna y"<< std::endl;
                            std::cin >> gdzieStozek3[1];
                            TrojkatneStozki* stk1 = new TrojkatneStozki(pOpenglApi,std::vector<double>{gdzieStozek3[0],gdzieStozek3[1],-2},6,9);
                            CurrentScene.dodajPrzeszkode(stk1);
                        }
                    }
                    else{
                        std::cout << "Nie wybrano zadnej przeszkody"<< std::endl;
                    }
                }
                else if (plusMinusPrzeszkoda == '-'){
                    std::cout << "Podaj numer przeszkody ktora chcesz usunac:"<< std::endl;
                    int indexUsuwanejPrzeszkody;
                    CurrentScene.WypiszWspolrzednePrzeszkod();
                    std::cin >> indexUsuwanejPrzeszkody;
                    if(CurrentScene.usunPrzeszkode(pOpenglApi,indexUsuwanejPrzeszkody))
                    {
                        std::cout << "Usunieto Przeszkode"<< std::endl;
                    }
                }
                else {
                    std::cout << "Wybrano nieznaną opcje" << std::endl;
                }
            break;
            case '3':
                std::cout << "Ktorego drona chcesz wybrac? (int index)" << std::endl;
                int ktoryDron;
                CurrentScene.WypiszWspolrzedneDronow();
                std::cin >> ktoryDron;
                CurrentScene.PrzelaczDrona(ktoryDron);
            break;
            case '4':
                while (true){
                    std::vector<double> punkt_do_ktorego_lec(3,0);
                    char optDrone;
                    std::cout<<"=================="<< std::endl <<
                        "=== MENU Drona ==="<< std::endl <<
                        "=================="<< std::endl <<
                        "1. Obroc"          << std::endl <<
                        "2. Lec do przodu"  << std::endl <<
                        "3. Lec do gory"    << std::endl <<
                        "4. Lec do punktu"    << std::endl <<
                        "5. Laduj"    << std::endl <<
                        "x. Koniec lotu"    << std::endl <<
                        "==================="<< std::endl <<
                        "Aktualny Dron: "<< CurrentScene.getAktualnyDron() << std::endl <<
                        "=================="<< std::endl;
                    std::cin>>optDrone;
                    switch (optDrone){
                        case '1':
                            std::cout<<"O jaki kat?"<< std::endl;
                            double jakikat;
                            std::cin>>jakikat;
                            CurrentScene.getAktualnyDron()->aktualizuj_orientacje(jakikat, CurrentScene.getPrzeszkodyNaScenie());
                            CurrentScene.getAktualnyDron()->rysuj();
                        break;
                        /// Latanie do przodu (dodatnia wartosc) i do tylu (ujemna wartosc)
                        case '2':
                            std::cout<<"jak daleko?"<< std::endl;
                            double jakdaleko;
                            std::cin>>jakdaleko;
                            CurrentScene.getAktualnyDron()->lec_do_przodu(jakdaleko,CurrentScene.getPrzeszkodyNaScenie());
                            CurrentScene.getAktualnyDron()->rysuj();
                        break;
                        /// Wznoszenie sie i opadanie
                        case '3':
                            std::cout<<"jak wysoko?"<< std::endl;
                            double jakwysoko;
                            std::cin>>jakwysoko;
                            CurrentScene.getAktualnyDron()->lec_w_gore(jakwysoko,CurrentScene.getPrzeszkodyNaScenie());
                            CurrentScene.getAktualnyDron()->rysuj();
                        break;
                        /// Autopilot, lec do punktu
                        case '4':
                            std::cout<<"podaj wspolrzedna x"<< std::endl;
                            std::cin >> punkt_do_ktorego_lec[0];
                            std::cout<<"podaj wspolrzedna y"<< std::endl;
                            std::cin >> punkt_do_ktorego_lec[1];
                            CurrentScene.getAktualnyDron()->lec_do_punktu(punkt_do_ktorego_lec,CurrentScene.getPrzeszkodyNaScenie());
                        break;
                        /// Wyladowuje drona
                        case '5':
                            CurrentScene.getAktualnyDron()->laduj(CurrentScene.getPrzeszkodyNaScenie());
                        break;
                        case 'x':
                        case 'X':
                        case '0':
                        break;
                        default:
                            std::cout<<"Niepoprawna instrukcja"<< std::endl;
                        break;
                    }
                    if(optDrone == 'x' || optDrone == 'X' || optDrone == '0'){
                        break;
                    }
                }
            break;
            case '5':
                std::cout << "Chesz wlaczyc czy wylaczyc powierzchnie?"<< std::endl;
                char plusMinusPow;
                std::cin >>plusMinusPow;
                if (plusMinusPow == '+'){
                    pow.rysuj();             
                }
                else if (plusMinusPow == '-'){
                    pow.wylaczWidocznosc();
                    pOpenglApi->redraw();
                }
            break;
            case 'x':
            case 'X':
            case '0':
            break;
            default:
                std::cout<<"Niepoprawna instrukcja"<< std::endl;
            break;
        }
        if(opt == 'x' ||opt == 'X'|| opt == '0'){
            break;
        }
    }

return 0;
}