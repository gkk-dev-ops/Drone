#ifndef EL_POWIERZCHNI
#define EL_POWIERZCHNI
 
#include "Inter_Dron.hh"

class El_Powierzchni : public Inter_Dron
{
private:
public:
    /// Metoda sprawdza czy przekazany dron koliduje z elementem powierzchni na ktorym wywolywana jest metoda
    virtual bool czy_koliduje(std::shared_ptr<El_Powierzchni> sprawdzany_dron)=0; 
    /// Zwraca typ elementu powierzchni
    virtual int get_typeof()=0;
    /// Wymazuje element powierzchni
    virtual void wymazPrzeszkode()=0;
};

#endif