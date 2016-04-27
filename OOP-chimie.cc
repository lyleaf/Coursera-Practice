#include <iostream>
#include <string>
#include <cmath>
using namespace std;

class Flacon
{
private:
  string nom;
  double volume;
  double pH;

public:
  /*****************************************************
    Compléter le code à partir d'ici
  *******************************************************/
  Flacon(string nom,double volume,double pH): nom(nom),volume(volume),pH(pH){}
  ostream& etiquette(ostream& sortie) const;

  Flacon operator+ (Flacon const& f) const{
	double ph = -log10((this->volume * pow(10.0,-this->pH)+f.volume * pow(10.0,-f.pH))/(this->volume+f.volume));
    Flacon a = Flacon(nom + " + " + f.nom, volume+f.volume, ph);
    return a;
  }
  Flacon& operator+=(Flacon const& f){
	this->volume += f.volume;
	this->nom += (" + " + f.nom);
	double ph = -log10((this->volume * pow(10.0,-this->pH)+f.volume * pow(10.0,-f.pH))/(this->volume+f.volume));
    this->pH = ph;
    return *this;
  } 
};

ostream& Flacon::etiquette(ostream& sortie) const {
	return sortie << this->nom << " : " << this->volume << " ml, pH " << pH;
}
ostream& operator<< (ostream& s, Flacon const& f){
	return f.etiquette(s);
  }

#define BONUS


/*******************************************
 * Ne rien modifier après cette ligne.
 *******************************************/

void afficher_melange(Flacon const& f1, Flacon const& f2)
{
  cout << "Si je mélange " << endl;
  cout << "\t\"" << f1 << "\"" << endl;
  cout << "avec" << endl;
  cout << "\t\"" << f2 << "\"" << endl;
  cout << "j'obtiens :" << endl;
  cout << "\t\"" << (f1 + f2) << "\"" << endl;
}

int main()
{
  Flacon flacon1("Eau", 600.0, 7.0);
  Flacon flacon2("Acide chlorhydrique", 500.0, 2.0);
  Flacon flacon3("Acide perchlorique",  800.0, 1.5);

  afficher_melange(flacon1, flacon2);
  afficher_melange(flacon2, flacon3);
  
  flacon1 += flacon2;
  afficher_melange(flacon1, flacon2);

  return 0;

}
