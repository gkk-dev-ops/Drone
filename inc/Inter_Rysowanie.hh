#ifndef INTER_RYSOWANIE
#define INTER_RYSOWANIE

#include "OpenGL_API.hh"

class Inter_Rysowanie{
public:
    // Pola Interfejsu Rysowania
    int id_rysunku=0;
    std::shared_ptr<drawNS::Draw3DAPI> api;
    /// Konstruktor Interfejsu Rysowania
    Inter_Rysowanie(){};
    /// Destruktor Interfejsu Rysowania
    //~Inter_Rysowanie(){}; // po co ??
    /// Metody Interfejsu Rysowania
    virtual void rysuj()=0;
};

#endif