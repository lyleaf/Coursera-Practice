#include <iostream>
#include <cmath>
using namespace std;

enum Pavillon { JollyRogers, CompagnieDuSenegal, CompagnieDOstende };

enum Etat { Intact, Endommage, Coule };

ostream & operator <<(ostream & afficher, Pavillon const &p){
	switch (p){
		case JollyRogers: afficher << "pirate"; break;
		case CompagnieDuSenegal: afficher << "français"; break;
		case CompagnieDOstende: afficher << "autrichien"; break;
		default: afficher << "pavillon inconnu"; 
	}
	return afficher;
}

ostream & operator <<(ostream & afficher, Etat const &e){
	switch (e){
		case Intact: afficher << "intact"; break;
		case Endommage: afficher << "ayant subi des dommages";break;
		case Coule: afficher << "coulé";break;
		default: afficher << "état inconnu";
	}
	return afficher;
}

int sq(int x)
{
  return x*x;
}

class Coordonnees
{
public:
  Coordonnees(int un_x, int un_y) : x_(un_x), y_(un_y) {}
  int x() const {
    return x_;
  }
  int y() const {
    return y_;
  }
  void operator+=(Coordonnees const& autre); // à définir plus bas
private:
  int x_;
  int y_;
};

class Navire
{
  /*****************************************************
   * Compléter le code à partir d'ici
   *****************************************************/
	static const int rayon_rencontre = 10;
protected:
	Coordonnees position_;
	Pavillon pavillion_;
	Etat etat_;
public:
	Navire(int x,int y,Pavillon pavillion): position_(Coordonnees(x,y)),pavillion_(pavillion){etat_ = Intact;}
	Coordonnees const & position() const{
		return position_;
	}
	void avancer(int de_x, int de_y){
		position_ += Coordonnees(de_x,de_y);
	}
	void renflouer(){
		etat_ = Intact;
	}
	virtual ostream & afficher(ostream & aff) const{//TO change to abstract.
		aff << " en (" << position_.x() << ", " << position_.y() << ") battant pavillon " << pavillion_ << ", " << etat_;
		return aff;
	}
	double distance(Navire const & autre) const{
		double d = sqrt(sq(position_.x()-autre.position_.x())+sq(position().y()-autre.position().y()));
		//cout << "d is dis is " << d << endl;
		return d;
	}
	virtual void attaque(Navire & autre) = 0;
	virtual void replique(Navire & autre) = 0;
	virtual void est_touche() = 0;
	void rencontrer(Navire & autre) {
		if (etat_ != Coule && autre.etat_ != Coule && distance(autre) < rayon_rencontre){
			if (pavillion_ != autre.pavillion_){
				attaque(autre);
				autre.replique(*this);
				//if (etat_ != Coule && autre.etat_ != Coule && distance(autre) < rayon_rencontre){
				//	autre.replique(*this);
				//}
			}
		}
	}
	
};

void Coordonnees::operator+=(Coordonnees const& autre)
{
  // à définir ici
  x_ += autre.x();
  y_ += autre.y();
}

double distance(Coordonnees const &a, Coordonnees const &b){
	return sqrt(sq(a.x()-b.x())+sq(a.y()-b.y()));
}

ostream & operator <<(ostream & afficher, Coordonnees const &a){
	return afficher << "( " << a.x() << " , " << a.y() << " )";
}
	


double distance(Navire const & a, Navire const & b){
	return distance(a.position(),b.position());
}

ostream & operator <<(ostream & sortie, Navire const &n){
	return n.afficher(sortie);
}

class Pirate: public virtual Navire{
public:
	Pirate(int x,int y,Pavillon pavillion):Navire(x,y,pavillion){}
	virtual ostream & afficher(ostream & aff) const{
		aff << "bateau pirate";
		Navire::afficher(aff);
		return aff;
	}
	virtual void attaque(Navire & autre) override{
		cout << "A l'abordage !" << endl;
		autre.est_touche();
	}
	virtual void replique(Navire & autre) override{
		if (etat_ != Coule){
			cout << "Non mais, ils nous attaquent ! On riposte !!" << endl;
			attaque(autre);
		}
	}
	virtual void est_touche() override{
		if (etat_ == Intact)
			etat_ = Endommage;
		else if (etat_ == Endommage)
			etat_ = Coule;
	}

};


class Marchand: public virtual Navire{
public:
	Marchand(int x,int y,Pavillon pavillion):Navire(x,y,pavillion){}
	virtual ostream & afficher(ostream & aff) const{
		aff << "navire marchand";
		Navire::afficher(aff);
		return aff;
	}
	virtual void attaque(Navire & autre) override{
		cout << "On vous aura! (insultes)" << endl;
	}
	virtual void replique(Navire & autre) override{
		if (etat_ == Coule)
			cout << "SOS je coule !" << endl;
		else 
			cout << "Même pas peur !" << endl;
	}
	virtual void est_touche() override{
		etat_ = Coule;
	}
};

class Felon: public Pirate, 
			 public Marchand{
//using Pirate::attaque;
//using Marchand::replique;
//using Pirate::est_touche;
public:

	Felon(int x,int y,Pavillon pavillion):Navire(x,y,pavillion),Pirate(x,y,pavillion),Marchand(x,y,pavillion){}
	virtual ostream & afficher(ostream & aff) const{
		aff << "navire félon";
		Navire::afficher(aff); 
		return aff;
	}

	virtual void attaque(Navire & autre){
		Pirate::attaque(autre);
	}
	virtual void replique(Navire & autre){
		Marchand::replique(autre);
	}
	virtual void est_touche(){
		Pirate::est_touche();
	}
	
};



/*******************************************
 * Ne rien modifier après cette ligne.
 *******************************************/

void rencontre(Navire& ship1, Navire& ship2)
{
  cout << "Avant la rencontre :" << endl;
  cout << ship1 << endl;
  cout << ship2 << endl;
  cout << "Distance : " << distance(ship1, ship2) << endl;
  ship1.rencontrer(ship2);
  cout << "Apres la rencontre :" << endl;
  cout << ship1 << endl;
  cout << ship2 << endl;
}

int main()
{
	Pavillon a = JollyRogers;
	cout << a;
  // Test de la partie 1
  cout << "===== Test de la partie 1 =====" << endl << endl;

  // Un bateau pirate 0,0
  Pirate ship1(0, 0, JollyRogers);
  cout << ship1 << endl;

  // Un bateau marchand en 25,0
  Marchand ship2(25, 0, CompagnieDuSenegal);
  cout << ship2 << endl;

  cout << "Distance : " << distance(ship1, ship2) << endl;

  cout << "Quelques déplacements..." << endl;
  cout << "  en haut à droite :" << endl;
  // Se déplace de 75 unités à droite et 10 en haut
  ship1.avancer(75, 10);
  cout << ship1 << endl;

  cout << "  vers le bas :" << endl;
  ship1.avancer(0, -5);
  cout << ship1 << endl;

  cout << endl << "===== Test de la partie 2 =====" << endl << endl;

  cout << "Bateau pirate et marchand ennemis (trop loins) :" << endl;
  rencontre(ship1, ship2);

  cout << endl << "Bateau pirate et marchand ennemis (proches) :" << endl;
  ship1.avancer(-40, -2);
  ship2.avancer(10, 2);
  rencontre(ship1, ship2);

  cout << endl << "Deux bateaux pirates ennemis intacts (proches) :" << endl;
  Pirate ship3(33, 8, CompagnieDOstende);
  rencontre(ship1, ship3);

  cout << endl << "Bateaux pirates avec dommages, ennemis :" << endl;
  rencontre(ship1, ship3);

  cout << endl << "Bateaux marchands ennemis :" << endl;
  Marchand ship4(21, 7, CompagnieDuSenegal);
  Marchand ship5(27, 2, CompagnieDOstende);
  rencontre(ship4, ship5);

  cout << endl << "Pirate vs Felon :" << endl;
  ship3.renflouer();
  Felon ship6(32, 10, CompagnieDuSenegal);
  rencontre(ship3, ship6);

  cout << endl << "Felon vs Pirate :" << endl;
  rencontre(ship6, ship3);

  return 0;
}
