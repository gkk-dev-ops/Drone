#include "prostopadloscian.hh"

using std::cout;
using std::endl;

std::vector<std::vector<double>> Prostopadloscian::wylicz_punkty(){
    std::vector<double> vec={1,1,1};
    for (int i = 0; i < 3; i++)
    {
        vec[i] = dlugosc_boku[i] / 2;
    }

    std::vector<std::vector<double>> wierzcholki={
        {vec[0], vec[1], vec[2]},
        {vec[0]-dlugosc_boku[0], vec[1], vec[2]},
        {vec[0]-dlugosc_boku[0], vec[1]-dlugosc_boku[1], vec[2]},
        {vec[0], vec[1]-dlugosc_boku[1], vec[2]},
        {vec[0], vec[1], vec[2]-dlugosc_boku[2]},
        {vec[0]-dlugosc_boku[0], vec[1], vec[2]-dlugosc_boku[2]},
        {vec[0]-dlugosc_boku[0], vec[1]-dlugosc_boku[1], vec[2]-dlugosc_boku[2]},
        {vec[0], vec[1]-dlugosc_boku[1], vec[2]-dlugosc_boku[2]}
        };
    
    return wierzcholki;
}

Prostopadloscian::Prostopadloscian(std::shared_ptr<drawNS::Draw3DAPI> _api){
    dlugosc_boku=std::vector<double>{3,2,1};
    api = _api;
    polozenie=std::vector<double>{0,0,0};
}

void Prostopadloscian::rysuj() {
    if (id_rysunku != 0)
    {
        api->erase_shape(id_rysunku);
    }
    else
    {
        id_rysunku = api->draw_polyhedron(std::vector<std::vector<drawNS::Point3D>>{{drawNS::Point3D(0,0,0)},{drawNS::Point3D(0,0,0)}});
    }
    std::vector<std::vector<double>> wierzcholki = wylicz_punkty();

int ilosc_wierzcholkow = wierzcholki.capacity();
    for (int i = 0; i < ilosc_wierzcholkow; i++)
    {
        wierzcholki[i] = orientacja * wierzcholki[i];
        for (int  j = 0; j < 3; j++)
        {
            wierzcholki[i][j] = wierzcholki[i][j] + polozenie[j];
        }
    }

    std::vector<std::vector<drawNS::Point3D>> prost(2,std::vector<drawNS::Point3D>{});
    for(int i=0; i<ilosc_wierzcholkow;i++){
        prost[i/(ilosc_wierzcholkow/2)].push_back(drawNS::Point3D(wierzcholki[i][0],wierzcholki[i][1],wierzcholki[i][2]));
    }
 id_rysunku = api->draw_polyhedron(prost, "red");
}

void Prostopadloscian::przesun_o_wektor(std::vector<double> vec){
    for (int i = 0; i < 3; i++)
    {
        polozenie[i]+=vec[i];
    }   
}

void Prostopadloscian::obrot(double kat, char oska){
    KonkretnaMacierz macierzobracajaca(oska,kat);
    orientacja = orientacja * macierzobracajaca.KonkretnaMacierz_do_Macierz3x3();    
}