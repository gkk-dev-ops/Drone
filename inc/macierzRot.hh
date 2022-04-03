#ifndef MACIERZ_ROT_HH
#define MACIERZ_ROT_HH

#include <iostream>
#include "wektor2D.hh"
#include <vector>

template<int Dim>
class MacierzRotacji {
protected:
    double Mac[Dim][Dim];

public:
    MacierzRotacji(){
        for (int i = 0; i < Dim; i++)
        {
            for (int j = 0; j < Dim; j++)
            {
                Mac[i][j] = 0.0;
            }
            Mac[i][i] = 1.0;
        }
    }

    double get_Mac(int row, int col) const {
        return Mac[row][col];
    }
    void set_Mac(int row, int col, double to_set) {
        this->Mac[row][col] = to_set;
    }
    Wektor<Dim> operator * (Wektor<Dim> Arg2) const{
        Wektor<Dim> mult;
        for (int i=0;i<Dim;i++){
            for (int j=0;j<Dim;j++){
                mult.set_W(i, (mult.get_W(i) + this->Mac[i][j]*Arg2.get_W(j)));
            }
        }
        return mult;
    }
    std::vector<double> operator * (std::vector<double> Arg2) const{
        std::vector<double> mult={0,0,0};
        for (int i=0; i<Dim; i++){
            for (int j=0; j<Dim ;j++){ // potential off by one error found 4/4/22
                mult[i] = mult[i] + this->Mac[i][j]*Arg2[j]; 
            }
        }
        return mult;
    }


    MacierzRotacji<Dim> operator * (MacierzRotacji<Dim> Arg2) const{
        MacierzRotacji mult;
        for (int i = 0; i < Dim; i++) {
            for (int j = 0; j < Dim; j++) {
            double sum = 0;
                for(int k = 0; k < Dim; k++) {
                    sum += this->Mac[i][k] * Arg2.Mac[k][j];
                }
            mult.set_Mac(i,j,sum);
            }
        }
        return mult;
    }
    MacierzRotacji<Dim> operator + (MacierzRotacji<Dim> Arg2) const{
        MacierzRotacji sum;
        for (int i = 0; i < Dim; i++) {
            for (int j = 0; j < Dim; j++) {
                sum.set_Mac(i,j,Mac[i][j]+Arg2.get_Mac(i,j));
            }
        }
        return sum;
    }
};
template <int Dim>
std::ostream& operator << (std::ostream &Strm, const MacierzRotacji<Dim> &Mac){
    for(int i=0; i<Dim; i++){
        for(int j=0; j<Dim; j++){
            Strm << Mac.get_Mac(j,i) << ",";
        }
        Strm << std::endl;
    }
    return Strm;
}


typedef MacierzRotacji<2> Macierz2x2;
typedef MacierzRotacji<3> Macierz3x3;

#endif