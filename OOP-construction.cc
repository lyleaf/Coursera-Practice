#include <iostream>
#include <string>
#include <vector>
using namespace std;

// Pour simplifier
typedef string Forme   ;
typedef string Couleur ;

class Brique
{
private:
  Forme   forme   ;
  Couleur couleur ;

public:
  /*****************************************************
    Compléter le code à partir d'ici
  *******************************************************/
  Brique(Forme(forme),Couleur(couleur)):forme(forme),couleur(couleur){}
  ostream& afficher(ostream& sortie) const{
	  if (couleur.empty() )
		return sortie<<forme;
	  else
	    return sortie<<"("<<forme<<", "<<couleur<<")";
  }
};

ostream& operator << (ostream& o, Brique const& b){
	return b.afficher(o);
}




class Construction
{
  friend class Grader;
  vector<vector<vector<Brique>>> contenu;
public:
  Construction(Brique const & b){
	  vector<Brique> temp(1,b);
	  vector<vector<Brique>> tmp(1,temp);
	  contenu.push_back(tmp);
  }
  ostream& afficher(ostream& sortie) const {
	  for(int i=contenu.size()-1;i>=0;--i){
		sortie << "Couche "<< i <<" :" << endl;
		for(auto const& j: contenu[i]){
		  for(auto const& k: j){
			  sortie << k;
		  }
		  sortie << endl;
	  }
		//sortie << endl;
	  }
	  return sortie;
  }
  Construction & operator ^= (Construction const &c){
	  for (unsigned int i=0;i<c.contenu.size();i++){
			contenu.push_back(c.contenu[i]);
		}/*
	  for (auto const& i: c.contenu){
		  contenu.push_back(i);
	  }*/
	  return *this;
  }	 
  Construction & operator -= (Construction const &c){
	  if (c.contenu.size()>=contenu.size()){  
		for (unsigned int i=0;i<contenu.size();i++){
			for (unsigned int j=0;j<c.contenu[i].size();j++)
				contenu[i].push_back(c.contenu[i][j]);
		}
	  }
	  return *this;
  }
  Construction & operator += (Construction const &c){
	  int flag = 1;
	  if (c.contenu.size()<contenu.size())
		flag = 0;
	  else { 
		for (unsigned int i=0;i<contenu.size();i++){
			if (c.contenu[i].size() < contenu[i].size())
				flag = 0;
				break;
		}
	  }
	  if (flag == 1) {
		  for (unsigned int i=0;i<contenu.size();i++){
			  for (unsigned int j=0;j<contenu[i].size();j++){
				  for (unsigned int k=0;k<c.contenu[i][j].size();k++)
					contenu[i][j].push_back(c.contenu[i][j][k]);
			  }
		  }
	  }
	  return *this;
  }
		 
};

const Construction operator^(Construction a, Construction const& b){
	a ^= b;
	return a;
}

Construction operator - (Construction a, Construction const & b){
	a -= b;
	return a;
}

Construction operator + (Construction a, Construction const & b){
	a += b;
	return a;
}

ostream& operator << (ostream & o, Construction & c){
	return c.afficher(o);
}

	
const Construction operator*(unsigned int n, Construction const& a)
{
	Construction b = a;
	for (unsigned int i = 1;i!=n;i++){
		b += a;
	}
	return b;
}

const Construction operator/(unsigned int n, Construction const& a)
{   Construction b = a;
	for (unsigned int i = 1;i!=n;i++){
		b ^= a;
	}
	return b;
}

const Construction operator%(unsigned int n, Construction const& a)
{
	Construction b = a;
	for (unsigned int i = 1;i!=n;i++){
		b -= a;
	}
	return b;
}

const Construction operator*(unsigned int n, Brique const& a)
{
	Construction b(a);
	return n*b;
}

const Construction operator/(unsigned int n, Brique const& a)
{   
	Construction b(a);
	return n/b;
}

const Construction operator%(unsigned int n, Brique const& a)
{
	Construction b(a);
	return n%b;
}

const Construction operator^(Brique a, Brique const& b){
	Construction c(b);
	Construction ca(a);
	ca ^= b;
	return ca;
}

Construction operator - (Brique a, Brique const & b){
	Construction c(b);
	Construction ca(a);
	ca -= b;
	return ca;
}

Construction operator + (Brique a, Brique const & b){
	Construction c(b);
	Construction ca(a);
	ca += b;
	return ca;
}



/*******************************************
 * Ne rien modifier après cette ligne.
 *******************************************/

int main()
{
  // Modèles de briques
  Brique toitD("obliqueD", "rouge");
  Brique toitG("obliqueG", "rouge");
  Brique toitM(" pleine ", "rouge");
  Brique mur  (" pleine ", "blanc");
  Brique vide ("                 ", "");

  unsigned int largeur(4);
  unsigned int profondeur(3);
  unsigned int hauteur(3); // sans le toit

  // on construit les murs
  Construction maison( hauteur / ( profondeur % (largeur * mur) ) );

  // on construit le toit
  Construction toit(profondeur % ( toitG + 2*toitM + toitD ));
  toit ^= profondeur % (vide + toitG + toitD);

  // on pose le toit sur les murs
  maison ^= toit;

  // on admire notre construction
  cout << maison << endl;

  return 0;
}
