#include <iostream>
#include <utility> // pour swap
#include <string>
#include <memory>
#include <vector>
using namespace std;

//======================================================================
class Produit {
public:
  Produit(double une_valeur = 0.0) 
  : valeur(une_valeur)
  {}
 
  /* Un produit est abstrait. Nous forçons ainsi l'aspect abstrait
   * (en ajoutant un destructeur virtuel pur).
   */
  virtual ~Produit() = 0;

  // Méthode virtuelle (on pourrait vouloir la modifier)...
  virtual double prix() const
  // ...dont le comportement par défaut est de retourner la valeur de base
  { return valeur; }

  virtual void afficher(ostream& sortie) const {
    // Par défaut, un produit affiche son prix.
    sortie << prix();

    /* Notez bien qu'ici nous n'avons pas écrit
     *     sortie << valeur;
     * car nous voulons qu'un produit affiche son PRIX,
     * lequel pourrait très bien être différent de la valeur de base
     * (aspect polymorphique de la méthode prix()).
     */
  }

private: // Encapsulons un maximum....
  const double valeur;
};

// Définition du destructeur (exteriorisée en raison de la déclaration virtuelle pure)
Produit::~Produit() {}

//----------------------------------------------------------------------
ostream& operator<<(ostream& sortie, Produit const& machin) {
  machin.afficher(sortie);
  return sortie;
}

//======================================================================
class Accessoire : public Produit {
public:
  Accessoire(string const& un_nom, double valeur_de_base)
  : Produit(valeur_de_base), nom(un_nom)
  {}
  virtual ~Accessoire() {}

  virtual void afficher(ostream& sortie) const override {
    sortie << nom << " coûtant ";
    Produit::afficher(sortie);
  }

  // copie polymorphique d'Accessoire
  virtual unique_ptr<Accessoire> copie() const = 0;

private:
  const string nom;
};

//------------------------------------------------------------
class Bracelet : public Accessoire {
public:
  Bracelet(string const& un_nom, double valeur_de_base)
    : Accessoire("bracelet " + un_nom, valeur_de_base)
  {}
  virtual ~Bracelet() {}

  // copie polymorphique de Bracelet
  virtual unique_ptr<Accessoire> copie() const override
  { return unique_ptr<Accessoire>(new Bracelet(*this)); }
};

//------------------------------------------------------------
class Fermoir : public Accessoire {
public:
  Fermoir(string const& un_nom, double valeur_de_base)
    : Accessoire("fermoir " + un_nom, valeur_de_base)
  {}

  virtual ~Fermoir() {}

  // copie polymorphique de Fermoir
  virtual unique_ptr<Accessoire> copie() const override
  { return unique_ptr<Accessoire>(new Fermoir(*this)); }
};

//------------------------------------------------------------
class Boitier : public Accessoire {
public:
  Boitier(string const& un_nom, double valeur_de_base)
    : Accessoire("boitier " + un_nom, valeur_de_base)
  {}

  virtual ~Boitier() {}

  // copie polymorphique de Boitier
  virtual unique_ptr<Accessoire> copie() const override
  { return unique_ptr<Accessoire>(new Boitier(*this)); }
};

//------------------------------------------------------------
class Vitre : public Accessoire {
public:
  Vitre(string const& un_nom, double valeur_de_base)
    : Accessoire("vitre " + un_nom, valeur_de_base)
  {}

  virtual ~Vitre() {}

  // copie polymorphique de Vitre
  virtual unique_ptr<Accessoire> copie() const override
  { return unique_ptr<Accessoire>(new Vitre(*this)); }
};

//======================================================================
class Mecanisme : public Produit {
public:
  Mecanisme(double valeur_de_base, string une_heure = "12:00")
  : Produit(valeur_de_base), heure(une_heure)
  {}

  virtual ~Mecanisme() {}

  // copie polymorphique de Mecanisme
  virtual unique_ptr<Mecanisme> copie() const = 0;

  // Tous les mécanismes doivent s'afficher comme ceci
  virtual void afficher(ostream& sortie) const override final {
    sortie << "mécanisme ";
    afficher_type(sortie);
    sortie << " (affichage : ";
    afficher_cadran(sortie);
    sortie << "), prix : ";
    Produit::afficher(sortie);
  }

  void mettre_a_l_heure(string const& nouvelle_heure) 
  { heure = nouvelle_heure; }

protected:  // on veut offrir la version par défaut aux sous-classes
  // Par défaut, on affiche juste l'heure.
  virtual void afficher_cadran(ostream& sortie) const {
    sortie << heure;
  }

private: // ou protected: ici les deux sont envisageables, mais private suffit ici
  string heure;

  // Un mécanisme, ici à ce niveau, reste abstrait (= classe abstraite)
  virtual void afficher_type(ostream& sortie) const = 0;
};

//======================================================================
class MecanismeAnalogique: virtual public Mecanisme {
public:
  MecanismeAnalogique(double valeur_de_base, string une_heure, int une_date)
 : Mecanisme(valeur_de_base, une_heure), date(une_date)
  {}

  // gestion propre de la valeur par défaut de l'heure (super-classe)
  MecanismeAnalogique(double valeur_de_base, int une_date)
  : Mecanisme(valeur_de_base), date(une_date) 
  {}

  virtual ~MecanismeAnalogique() {}

  // Copie polymorphique de MecanismeAnalogique
  virtual unique_ptr<Mecanisme> copie() const override
  { return unique_ptr<Mecanisme>(new MecanismeAnalogique(*this)); }

protected:
  virtual void afficher_type(ostream& sortie) const override {
    sortie << "analogique";
  }

  virtual void afficher_cadran(ostream& sortie) const override {
    // On affiche l'heure (façon de base)...
    Mecanisme::afficher_cadran(sortie);
    // ...et en plus la date.
    sortie << ", date " << date;
  }

private: // ou protected
  int date;
};

//======================================================================
class MecanismeDigital: virtual public Mecanisme {
public:
  MecanismeDigital(double valeur_de_base, string une_heure, string heure_reveil)
  : Mecanisme(valeur_de_base, une_heure), reveil(heure_reveil)
  {}

  // gestion propre de la valeur par défaut de l'heure (super-classe)
  MecanismeDigital(double valeur_de_base, string heure_reveil)
  : Mecanisme(valeur_de_base), reveil(heure_reveil)
  {}

  virtual ~MecanismeDigital() {}

  // Copie polymorphique de MecanismeDigital
  virtual unique_ptr<Mecanisme> copie() const override
  { return unique_ptr<Mecanisme>(new MecanismeDigital(*this)); }

protected:
  virtual void afficher_type(ostream& sortie) const override {
    sortie << "digital";
  }

  virtual void afficher_cadran(ostream& sortie) const override {
    // On affiche l'heure (façon de base)...
    Mecanisme::afficher_cadran(sortie);
    // ...et en plus l'heure de réveil.
    sortie << ", réveil " << reveil;
  }

private: // ou protected
  string reveil;
};

//======================================================================
class MecanismeDouble: public MecanismeAnalogique, public MecanismeDigital {
public:
  MecanismeDouble(double valeur_de_base, string une_heure, int une_date, string heure_reveil)
  : Mecanisme(valeur_de_base, une_heure)
  , MecanismeAnalogique(valeur_de_base, une_heure, une_date)
  , MecanismeDigital(valeur_de_base, une_heure, heure_reveil)
  {}

  // gestion propre de la valeur par défaut de l'heure (super-classe)
  MecanismeDouble(double valeur_de_base, int une_date, string heure_reveil)
  : Mecanisme(valeur_de_base)
  , MecanismeAnalogique(valeur_de_base, une_date)
  , MecanismeDigital(valeur_de_base, heure_reveil)
  {}

  virtual ~MecanismeDouble() {}

  // Copie polymorphique de MecanismeDouble
  virtual unique_ptr<Mecanisme> copie() const override
  { return unique_ptr<Mecanisme>(new MecanismeDouble(*this)); }

protected:
  virtual void afficher_type(ostream& sortie) const override {
    sortie << "double";
  }

  virtual void afficher_cadran(ostream& sortie) const override {
    // Par exemple... 
    sortie << "sur les aiguilles : ";
    MecanismeAnalogique::afficher_cadran(sortie);
    sortie << ", sur l'écran : ";
    MecanismeDigital::afficher_cadran(sortie);
  }
};

//======================================================================
class Montre : public Produit {
public:
  Montre( Mecanisme* depart)
  : coeur(unique_ptr< Mecanisme>(depart))
  {}

  virtual ~Montre() {
    /* On a décidé que le contenu d'une montre lui appartenait :
     * ==> DONC son contenu doit disparaitre quand la montre disparait...
     *     ... mais comme on a des unique_ptr : ca se fait tout seul !!
     */
  }

  void mettre_a_l_heure(string const& nouvelle_heure) 
  { coeur->mettre_a_l_heure(nouvelle_heure); }

  // Copie PROFONDE d'une Montre
  Montre(const Montre& autre) 
  // Ne pas oublier d'appeler le constructeur DE COPIE de la super-classe
  : Produit(autre),
    coeur(autre.coeur->copie())
  {
    for (auto const& p_acc : autre.accessoires) {
      accessoires.push_back(p_acc->copie());
    }
  }

  Montre& operator=(Montre source)
  // Notez le passage par VALEUR
  {
    swap(coeur      , source.coeur      );
    swap(accessoires, source.accessoires);
    return *this;
  }

  virtual double prix() const override {

    // Au départ, le prix est le prix de base plus celui du mécanisme
    double prix_final(Produit::prix() + coeur->prix());

    for (auto const& p_acc : accessoires) {
      prix_final += p_acc->prix();
    }
    return prix_final;
  }

  // On pourrait améliorer avec copie polymorphique...
  void operator+=(Accessoire* p_accessoire) {
    accessoires.push_back(unique_ptr<Accessoire>(p_accessoire));
  }

  virtual void afficher(ostream& sortie) const override {
    sortie << "Une montre composée de :" << endl;
    sortie << "  * " << *coeur << endl;
    for (auto const& p_acc : accessoires) {
      sortie << "  * " << *p_acc << endl;
    }
    sortie << "==> Prix total : " << prix() << endl;
  }

private:
  unique_ptr<Mecanisme> coeur;
  vector<unique_ptr<Accessoire>> accessoires;
};

//======================================================================
int main() {

  // test de l'affichage des mécanismes
  MecanismeAnalogique v1(312.00, 20141212);
  MecanismeDigital    v2( 32.00, "11:45", "7:00");
  MecanismeDouble     v3(543.00, "8:20", 20140328, "6:30");

  cout << v1 << endl << v2 << endl << v3 << endl;

  // Test des montres
  Montre m(new MecanismeDouble(468.00, "9:15", 20140401, "7:00"));
  m += new Bracelet("cuir", 54.0);
  m += new Fermoir("acier", 12.5);
  m += new Boitier("acier", 36.60);
  m += new Vitre("quartz", 44.80);
  cout << endl << "Montre m :" << endl;
  cout << m << endl;

  // Nous faisons une copie de la montre m
  Montre m2(m);
  cout << "Montre m2 :" << endl;
  cout << m2 << endl;

  // Et testons l'opérateur d'affectation
  Montre m3(new MecanismeAnalogique(87.00, 20140415));
  cout << "Montre m3 (1) :" << endl;
  cout << m3 << endl;

  m3 = m2; m2.mettre_a_l_heure("10:10");
  cout << "Montre m3 (2) :" << endl;
  cout << m3 << endl;

  return 0;
}
