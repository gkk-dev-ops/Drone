#include "Scena.hh"

using std::cin;
using std::cout;
using std::endl;

Scena::Scena() {}
// Scena::~Scena(){}

void Scena::dodajDrona(std::shared_ptr<drawNS::Draw3DAPI> api)
{
    std::shared_ptr<Dron> NowyDron(new Dron(api));
    DronyNaScenie.push_back(NowyDron);
    PrzeszkodyNaScenie.push_back(NowyDron);

    NowyDron->rysuj();
    setPoprzedniDron(getAktualnyDron());
    setAktualnyDron(NowyDron);
}

void Scena::usunDrona(std::shared_ptr<drawNS::Draw3DAPI> api, int index)
{
    if (DronyNaScenie.capacity() == 0 || index > DronyNaScenie.size() - 1 || index < 0)
    {
        std::cout << "[!] Incorrect drone index" << std::endl;
        return;
    }
    std::cout << std::endl
              << "Drone " << index << " deleted" << std::endl;
    DronyNaScenie[index]->wymazDrona();
    //    if (obstacle == DronyNaScenie[index])
    for (int i = 0; i < PrzeszkodyNaScenie.size() - 2; i++) // of by one?
    {
        if (PrzeszkodyNaScenie[i] == DronyNaScenie[index])
        {
            PrzeszkodyNaScenie.erase(PrzeszkodyNaScenie.begin() + i);
            break;
        }
    }
    DronyNaScenie.erase(DronyNaScenie.begin() + index);
    setAktualnyDron(getPoprzedniDron());
}

void Scena::dodajPrzeszkode(El_Powierzchni *wskaznikNaPrzeszkode)
{
    std::shared_ptr<El_Powierzchni> NowaPrzeszkoda(wskaznikNaPrzeszkode);
    PrzeszkodyNaScenie.push_back(NowaPrzeszkoda);
}

bool Scena::usunPrzeszkode(std::shared_ptr<drawNS::Draw3DAPI> api, int index)
{
    int i = 0;
    while (DronyNaScenie[i])
    {
        if (PrzeszkodyNaScenie[index].get() == DronyNaScenie[i].get())
        {
            cout << endl
                 << "Jesli chcesz usunac drona uzyj funkcji usun drona" << endl;
            return false;
        }
        i++;
    }
    PrzeszkodyNaScenie[index]->wymazPrzeszkode();
    return true;
}

void Scena::WypiszWspolrzednePrzeszkod()
{
    for (int i = 0; i < (PrzeszkodyNaScenie.capacity() - 1); i++)
    {
        cout << "Przeszkoda nr: " << i << "[" << PrzeszkodyNaScenie[i]->get_srodek()[0] << "," << PrzeszkodyNaScenie[i]->get_srodek()[1] << "]" << endl;
    }
}

void Scena::WypiszWspolrzedneDronow()
{
    int index = 0;
    for (auto drone : DronyNaScenie)
    {
        cout << "Dron nr: " << index << "[" /* << DronyNaScenie[index]->polozenie[0] << "," << DronyNaScenie[index]->polozenie[1]*/ << "]" << endl;
        index++;
    }
}
const std::vector<std::shared_ptr<El_Powierzchni>> &Scena::getPrzeszkodyNaScenie() const
{
    return this->PrzeszkodyNaScenie;
}
void Scena::PrzelaczDrona(int index)
{
    std::cout << "Dron aktualnie w uzyciu: " << getAktualnyDron() << std::endl;
    setAktualnyDron(DronyNaScenie[index]);

    // dron sygnalizuje ze jest wybrany
    getAktualnyDron()->lec_w_gore(0.5, PrzeszkodyNaScenie);
    getAktualnyDron()->lec_w_gore(-0.5, PrzeszkodyNaScenie);
}

/// Gettery
const std::shared_ptr<Dron> &Scena::getPoprzedniDron() const
{
    return m_poprzedniDron;
}
const std::shared_ptr<Dron> &Scena::getAktualnyDron() const
{
    return m_aktualnyDron;
}

/// Settery
void Scena::setPoprzedniDron(std::shared_ptr<Dron> nowyPoprzedniDron)
{
    m_poprzedniDron = nowyPoprzedniDron;
}
void Scena::setAktualnyDron(std::shared_ptr<Dron> NowyDron)
{
    m_aktualnyDron = NowyDron;
}