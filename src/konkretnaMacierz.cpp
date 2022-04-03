#include "konkretnaMacierz.hh"

/// zwraca konkretnaMacierz (obrotu) przeliczona na macierz3x3
Macierz3x3 KonkretnaMacierz::KonkretnaMacierz_do_Macierz3x3(){
    Macierz3x3 return_Macierz3x3;
    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            return_Macierz3x3.set_Mac(j,i,Mac[j][i]);
        }
        
    }
    return return_Macierz3x3;
}

/// Konsturktor KonkretnejMacierzy wylicza macierz obrotu dla podanego kata i osi po ktorej ma sie odbyc obrot
KonkretnaMacierz::KonkretnaMacierz(char oska, double kat){
// do radianow

kat = kat * 3.141/180;
// to lower
if (oska == 'X')
    {
        oska = 'x';
    }
        if (oska == 'Y')
    {
        oska = 'y';
    }
        if (oska == 'Z')
    {
        oska = 'z';
    }
    
    switch (oska)
    {
    // [1,0  , 0  ]
    // [0,cos,-sin]
    // [0,sin, cos]
    case 'x':
    set_Mac(0,0,1);
    set_Mac(0,1,0);
    set_Mac(0,2,0);

    set_Mac(1,0,0);
    set_Mac(1,1,cos(kat));
    set_Mac(1,2,-sin(kat));

    set_Mac(2,0,0);
    set_Mac(2,1,sin(kat));
    set_Mac(2,2,cos(kat));
        break;

    //  |cos ,0,sin]
    //  |0   ,1, 0 ]
    //  |-sin,0,cos]
    case 'y':
    set_Mac(0,0,cos(kat));
    set_Mac(0,1,0);
    set_Mac(0,2,sin(kat));

    set_Mac(1,0,0);
    set_Mac(1,1,1);
    set_Mac(1,2,0);

    set_Mac(2,0,-sin(kat));
    set_Mac(2,1,0);
    set_Mac(2,2,cos(kat));
        break;

    // [cos,-sin,0]
    // [sin, cos,0]
    // [0  , 0  ,1]
    case 'z':
    set_Mac(0,0,cos(kat));
    set_Mac(0,1,-sin(kat));
    set_Mac(0,2,0);

    set_Mac(1,0,sin(kat));
    set_Mac(1,1,cos(kat));
    set_Mac(1,2,0);

    set_Mac(2,0,0);
    set_Mac(2,1,0);
    set_Mac(2,2,1);
        break;
    default:
        break;
}
}
/// Zwraca kat obliczony z KonkretnejMacierzy (obrotu), przy zalozeniu ze jest to macierz obrotu po osi z na podstawie arcos z pierwszej wartosci macierzy Mac[0][0]
double KonkretnaMacierz::KonkretnaMacierzDoKataDlaOsiZ(){
    return acos(Mac[0][0]);
}
