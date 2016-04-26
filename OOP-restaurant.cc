#include <iostream>
#include <vector>
#include <sstream>

using namespace std;

/*****************************************************
  * Compléter le code à partir d'ici
 *****************************************************/
class Produit{
protected:
	string nom;
	string unite;
public:
	Produit(string nom,string unite=""): nom(nom), unite(unite) {} //initialize and assignement's difference
	string getNom() const{
		return nom;
	}
	string getUnite() const{
		return unite;
	}
	virtual string toString() const{
		return nom;
	}
	
	virtual const Produit* adapter(double n) const{
		return this;
	}
};

class Ingredient{
private:
	const Produit &p;//Changed to refernce
	double quantite;
	
public:
	Ingredient(const Produit & p,double quantite): p(p),quantite(quantite) {}
	
	Produit const & getProduit() const{
		return p; //return une reference??
	}
	
	double getQuantite() const{
		return quantite;
	}
	
	string descriptionAdaptee() const{
		stringstream ss;
		const Produit* ptr = p.adapter(quantite);
		ss << quantite << " " << p.getUnite() << " de " << ptr->toString();
		return ss.str();
	}
};

class Recette{
private:
	vector<Ingredient> lst;
	string nom;
	double nbFois_;
public:
	Recette(string nom, double nbFois_ = 1.0): nom(nom), nbFois_(nbFois_) {}

	void ajouter( Produit &p, double quantite ){
		Ingredient a(p,quantite*nbFois_);
		lst.push_back(a);
	}
	
	double quantiteTotale(string nom) const{
		for (auto const i : lst){
			if (i.getProduit().getNom() == nom){
				return i.getQuantite();
			}
		}
		return 0.0;
	}
	
	const Recette adapter(double n) const{
		double newNbFois = nbFois_ * n;
		Recette x(nom, newNbFois);
		for (auto const i : lst){
			const Produit & tmp = i.getProduit();
			x.lst.push_back(Ingredient(tmp,i.getQuantite()*n));//get the thing the pointer points at.
		}
		return x;
	}
	
	string toString() const{
		stringstream ss;
		ss << "Recette \"" << nom << "\" x " << nbFois_<< ":\n";
		unsigned int i = 1;
		for (auto const & ingredient : lst){
			ss << i << ". " << ingredient.descriptionAdaptee();//getProduit().toString();
			if (i != lst.size()){
				ss << endl;
			}
			i += 1;
		}
		string s = ss.str();
		return s;
	}	
	
};


class ProduitCuisine: public Produit{
private:
	Recette r;
public:
	ProduitCuisine(string nom): Produit(nom,"portion(s)"),r(nom) {}
	
	void ajouterARecette(Produit& produit, double quantite){
		r.ajouter(produit,quantite);
	}
	const Produit* adapter(double n) const override{
		ProduitCuisine *p = new ProduitCuisine(nom);
		p->r = r.adapter(n);
		return this;
	}
	
	virtual string toString() const override{
		stringstream ss;
		ss << Produit::toString() << "\n" << r.toString();
		return ss.str();
	}

};
/*******************************************
 * Ne rien modifier après cette ligne.
 *******************************************/
void afficherQuantiteTotale(const Recette& recette, const Produit& produit)
{
  string nom = produit.getNom();
  cout << "Cette recette contient " << recette.quantiteTotale(nom)
       << " " << produit.getUnite() << " de " << nom << endl;
}

int main()
{
  // quelques produits de base
  Produit oeufs("oeufs");
  Produit farine("farine", "grammes");
  Produit beurre("beurre", "grammes");
  Produit sucreGlace("sucre glace", "grammes");
  Produit chocolatNoir("chocolat noir", "grammes");
  Produit amandesMoulues("amandes moulues", "grammes");
  Produit extraitAmandes("extrait d'amandes", "gouttes");

  ProduitCuisine glacage("glaçage au chocolat");
  // recette pour une portion de glaçage:
  glacage.ajouterARecette(chocolatNoir, 200);
  glacage.ajouterARecette(beurre, 25);
  glacage.ajouterARecette(sucreGlace, 100);
  cout << glacage.toString() << endl;

  ProduitCuisine glacageParfume("glaçage au chocolat parfumé");
  // besoin de 1 portions de glaçage au chocolat et de 2 gouttes
  // d'extrait d'amandes pour 1 portion de glaçage parfumé

  glacageParfume.ajouterARecette(extraitAmandes, 2);
  glacageParfume.ajouterARecette(glacage, 1);
  cout << glacageParfume.toString() << endl;

  Recette recette("tourte glacée au chocolat");
  recette.ajouter(oeufs, 5);
  recette.ajouter(farine, 150);
  recette.ajouter(beurre, 100);
  recette.ajouter(amandesMoulues, 50);
  recette.ajouter(glacageParfume, 2);

  cout << "===  Recette finale  =====" << endl;
  cout << recette.toString() << endl;
  afficherQuantiteTotale(recette, beurre);
  cout << endl;

  // double recette
  Recette doubleRecette = recette.adapter(2);
  cout << "===  Recette finale x 2 ===" << endl;
  cout << doubleRecette.toString() << endl;

  afficherQuantiteTotale(doubleRecette, beurre);
  afficherQuantiteTotale(doubleRecette, oeufs);
  afficherQuantiteTotale(doubleRecette, extraitAmandes);
  afficherQuantiteTotale(doubleRecette, glacage);
  cout << endl;

  cout << "===========================\n" << endl;
  cout << "Vérification que le glaçage n'a pas été modifié :\n";
  cout << glacage.toString() << endl;

  return 0;
}
