#include <iostream>
#include <string>
using namespace std;

class Timbre
{
private:
  static constexpr unsigned int ANNEE_COURANTE = 2016;

  /*****************************************************
   * Compléter le code à partir d'ici
   *****************************************************/
protected:
  string nom;
  unsigned int annee;
  string pays;
  double valeur_faciale;
  
public:
  Timbre(string nom, unsigned int annee, string pays="Suisse", double valeur_faciale=1.0) :
	nom(nom), annee(annee), pays(pays), valeur_faciale(valeur_faciale) {}
	
  double vente() const{
	  if (ANNEE_COURANTE - annee<5)
		return valeur_faciale;
	  else
		return valeur_faciale * 2.5 * (ANNEE_COURANTE - annee);
	}
		
  unsigned int age(){
	  return ANNEE_COURANTE - annee;
  }
  
  ostream& afficher(ostream& os) const {
	  os << "de nom " << nom << " datant de " << annee << " (provenance " << pays << ") ayant pour valeur faciale " << valeur_faciale << " francs";
	  return os;
  }
  
  friend ostream& operator << (ostream& os,Timbre const & t);

};

ostream& operator << (ostream& os,Timbre const & t){
	os << "Timbre ";
	t.afficher(os);
	return os;
}

class Rare : public Timbre {
private: 
  int nb;
  const static unsigned int PRIX_BASE_TRES_RARE = 600;
  const static unsigned int PRIX_BASE_RARE = 400;
  const static unsigned int PRIX_BASE_PEU_RARE = 50;
  static constexpr unsigned int ANNEE_COURANTE = 2016;
  
public:
  Rare(string nom, unsigned int annee, string pays="Suisse", double valeur_faciale=1.0, int nb=100):
	Timbre(nom,annee,pays,valeur_faciale),nb(nb) {}
  
  int nb_exemplaires(){
	  return nb;
  }
  
  double vente() const {
	  int prix_base;
	  if (nb < 100)
		prix_base = PRIX_BASE_TRES_RARE;
	  else if (nb>=100 && nb<1000)
		prix_base = PRIX_BASE_RARE;
	  else
	    prix_base = PRIX_BASE_PEU_RARE;
	    
	  //cout << prix_base;
	  return prix_base * ((ANNEE_COURANTE - annee)/10.0);
  }
  
  friend ostream& operator << (ostream& os,Rare const & t);
};

ostream& operator << (ostream& os,Rare const & t){
	os << "Timbre rare (" << t.nb << " ex.) ";
	t.afficher(os);
	return os;
}

class Commemoratif : public Timbre {
public:
	static constexpr unsigned int ANNEE_COURANTE = 2016;
	Commemoratif(string nom, unsigned int annee, string pays="Suisse", double valeur_faciale=1.0):
		Timbre(nom,annee,pays,valeur_faciale){}
		
    double vente() const{
	  return Timbre::vente()*2;
	}
	
	friend ostream& operator << (ostream& os,Commemoratif const & t);
};

ostream& operator << (ostream& os,Commemoratif const & t){
	os << "Timbre commémoratif ";
	t.afficher(os);
	return os;
}

/*******************************************
 * Ne rien modifier après cette ligne.
 *******************************************/
int main()
{
  /* Ordre des arguments :
  *  nom, année d'émission, pays, valeur faciale, nombre d'exemplaires
  */
  Rare t1( "Guarana-4574", 1960, "Mexique", 0.2, 98 );
  Rare t2( "Yoddle-201"  , 1916, "Suisse" , 0.8,  3 );

  /* Ordre des arguments :
  *  nom, année d'émission, pays, valeur faciale, nombre d'exemplaires
  */
  Commemoratif t3( "700eme-501"  , 2002, "Suisse", 1.5 );
  Timbre       t4( "Setchuan-302", 2004, "Chine" , 0.2 );

  /* Nous n'avons pas encore le polymorphisme :-(
   * (=> pas moyen de faire sans copie ici :-( )  */
  cout << t1 << endl;
  cout << "Prix vente : " << t1.vente() << " francs" << endl;
  cout << t2 << endl;
  cout << "Prix vente : " << t2.vente() << " francs" << endl;
  cout << t3 << endl;
  cout << "Prix vente : " << t3.vente() << " francs" << endl;
  cout << t4 << endl;
  cout << "Prix vente : " << t4.vente() << " francs" << endl;

  return 0;
}
