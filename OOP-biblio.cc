#include <iostream>
#include <vector>
#include <string>
using namespace std;

/*******************************************
 * Completez le programme a partir d'ici.
 *******************************************/
class Auteur
{
public:
	string getNom(){
		return nom;
	}
	string getPrix(){
		return prime;
	}
	Auteur(string nom,bool prime = false): nom(nom),prime(prime){}

private:
	string nom;
	bool prime;
}

class Oeuvre
{
public:
	Oeuvre(string titre,string& auteur,string& langue): titre(titre),auteur(auteur),langue(langue) {}
	string getTitre(){ return titre; }
	string getAuteur(){return auteur;}
	string getLangue(){return langue;}
	void affiche() {
		cout << titre <<", "<<auteur<<", en "<<langue<<endl;
	}
	~Oeuvre(){
		cout << "L'oeuvre \""<<titre <<", "<<auteur<<", en "<<langue<<"\" n'est plus disponible." << endl;
	}
	Oeuvre(Oeuvre const &autreOeuvre)
	
private:
	string titre;
	string& auteur;
	string& langue;
}
