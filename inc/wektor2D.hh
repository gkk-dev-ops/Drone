#ifndef WEKTOR2D_HH
#define WEKTOR2D_HH

#include <iostream>
#include <vector>
#include <math.h>

template <int Dim>
class Wektor { 
private:
    double xy[Dim];
public:
    /// Constructor and destructor functions
    Wektor():xy{0.0} {}
    /// operator overload
    Wektor<Dim> operator + (const Wektor<Dim> arg2) const{
        Wektor sum;
        for (int i = 0; i < Dim; i++) {
            sum.set_W(i, this->get_W(i) + arg2.get_W(i));
        }
        return sum;
    }
    Wektor<Dim> operator - (const Wektor<Dim> arg2) const{
        Wektor sub;
        for(int i=0; i<Dim; i++){
            sub.set_W(i, this->get_W(i) - arg2.get_W(i));
        }
        return sub;
    }
    /// <summary>
    ///  Operator multiplying vector by scalar
    /// </summary>
    /// <param name="arg2"> Scalar by which to multiply</param>
    /// <returns>Vector scaled by double</returns>
    Wektor<Dim> operator * (double arg2) const{
        Wektor<Dim> mult;
        for (int i=0; i<Dim; i++){
            mult->get_W(i) = this->get_W(i)* arg2;
        }
        return mult;
    }
    /// <summary>
    /// Getter for geometric vector values [x,y,z...]
    /// </summary>
    /// <param name="index">Value of index to read from</param>
    /// <returns>Vectors value from provided index as a double</returns>
    const double & get_W(int index) const {
        return xy[index];
    }
    /// <summary>
    /// Getter for geometric vector values [x,y,z...]
    /// </summary>
    /// <param name="index">Index of value to be set</param>
    /// <param name="W_x">Value to be set</param>
    void set_W(int index, double W_x) {
        xy[index] = W_x;
    }
    
}; 
/// <summary>
/// Input stream overide for geometric vector with format specified as [v1,v2,v3,...] where all values are double
/// </summary>
/// <param name="Strm">Input stream</param>
/// <param name="Wek">Geometric vector objects</param>
/// <returns>Input stream</returns>
template <int Dim>
std::istream& operator >> (std::istream &Strm, Wektor<Dim> &Wek){
    char znak;
    double tmp;
        Strm >> znak;
        if (znak != '['){
            Strm.setstate(std::ios_base::failbit);
        }
    for(int i=0; i < Dim; i++){
        Strm >> tmp;
        Wek.set_W(i, tmp);
        if(i < (Dim-1)){
            Strm >> znak;
            if (znak != ',')
            {
            Strm.setstate(std::ios_base::failbit);
            }
        }
    }
       Strm >> znak;
        if (znak != ']')
        {
        Strm.setstate(std::ios_base::failbit);
        }
    return Strm;
}

template <int Dim>
std::ostream& operator << (std::ostream &Strm, const Wektor<Dim> &Wek){
    Strm << "[";
    for(int i=0; i < Dim; i++){
        Strm << Wek.get_W(i);
        if (i< Dim -1)
        {
            Strm << ",";
        } 
    }
    Strm << "]";
    return Strm;
}

typedef Wektor<2> Wektor2D;
typedef Wektor<3> Wektor3D;

/// <summary>
/// Function calculate vector difference std::vector treated as geometric vector
/// </summary>
/// <param name="arg1">std::vector logically geometric vector</param>
/// <param name="arg2">std::vector logically geometric vector</param>
/// <returns>difference vector as std::vector</returns>
std::vector<double> odejmowanie_wektorow(std::vector<double>arg1, std::vector<double>arg2);
/// <summary>
/// Function calculate vector length std::vector treated as geometric vector
/// </summary>
/// <param name="arg1">std::vector logically geometric vector</param>
/// <returns>Double meaning length of geometric vector </returns>
double dlugosc_wektora(std::vector<double>arg1);

#endif