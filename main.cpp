#include <iostream>
#include <fstream>
#include <math.h>
#include <iomanip>
#include <cfloat>
#include <string>

using namespace std;


double rozwin(double x)
{
    // rozwijamy f(x)=(1-exp(-x)) w szereg maclaurina i dzielimy każdy wyraz przez x
    double poprzedniWyraz = 1;
    double kolejnaWSilni = 2;
    double wynik = 0;
    double z = 1;
    while(abs(poprzedniWyraz) >= DBL_EPSILON)
    {
        wynik += z * poprzedniWyraz;
        poprzedniWyraz *=  x / kolejnaWSilni ;
        z *= -1;
        kolejnaWSilni++;
    }
    return wynik;
}


int main() {
    double x[3900];
    string log[3900];
    double doklWartosc[3900];
    string doklWartoscStr[3900];


    ifstream plik("dane.txt");
    ofstream wyjscie;
    if(!plik.good()){
        cout << "Problem z plikiem";
        return 1;
    }

    for(int i=0; i<3900; i++){
        plik >> log[i];
        plik >> x[i];
        plik >> doklWartosc[i];
    }
    plik.close();
    wyjscie.open("wyniki1.dat");
    double wynik;

    for(int i=0; i<3900; i++){
        wynik = (1.0-exp(-x[i]))/x[i];
        wyjscie << log[i] << " " << doklWartosc[i] << " " << wynik << "\n";
    }
    wyjscie.close();
    wyjscie.open("wyniki2.dat");
    for(int i=0; i<3900; i++){
        if(x[i] <= 1e-10){
            wynik = rozwin(x[i]);
        }else {
            wynik = (1.0 - exp(-x[i])) / x[i];
        }
        wyjscie <<  log[i] << " " << doklWartosc[i] << " " << wynik << "\n";
    }
    wyjscie.close();
    return 0;
}