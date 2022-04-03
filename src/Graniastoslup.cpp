#include "Graniastoslup.hh"

using std::cout;
using std::endl;

Graniastoslup::Graniastoslup(std::shared_ptr<drawNS::Draw3DAPI> _api){
    wysokosc = 0.8 ; 
    dlugosc = 1 ;
    dlugosc_boku=std::vector<double>{dlugosc,dlugosc,wysokosc};
    api = _api;
    polozenie=std::vector<double>{3,3,3};
}