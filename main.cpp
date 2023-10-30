#include <iostream>
#include <cstring>

class ProdusSkinCare{
    char nume[30]= "";
    double pret = 0.0;
public:
    ProdusSkinCare() {};

    ///constructor de initializare
    ProdusSkinCare(char nume_[30], double pret_){
        strcpy(nume,nume_);
        pret=pret_;
    }
    explicit ProdusSkinCare(const ProdusSkinCare* produs) {
        strcpy(nume, produs->nume);
        pret= produs->pret;
    }
    virtual ~ProdusSkinCare() {
    }

    const char *getNume() const {
        return nume;
    }

    double getPret() const{
        return pret;
    }
};

class CosCumparaturi{
    static const int capacitateMaxima=10;
    ProdusSkinCare produse[capacitateMaxima];
    int numarProduse =0;

public:
    CosCumparaturi () {}
    void AdaugaProdus(const ProdusSkinCare& produs){
        if (numarProduse<capacitateMaxima) {
            produse[numarProduse]=produs;
            numarProduse++;
        }
        else{
            std::cout<< "Cosul de cumparaturi este plin. Nu se mai pot adauga produse."<<std::endl;
        }
    }

    void AfiseazaCos() const {
        if (numarProduse == 0) {
            std::cout<< "Cosul de cumparaturi este gol." << std::endl;
        }
        else {
            std::cout<< "Produsele din cos sunt:"<<std::endl;
            for(int i =0; i <numarProduse; i ++)
            {
                std::cout<<"Nume produs: "<<produse[i].getNume()<<", Pret produs: "<< produse[i].getPret()<<" lei;"<< std::endl;

            }
        }
    }
};

class MagazinSkinCare {
    int produse_in_stoc = 0;
    static const int capacitate_maxima = 400;
    ProdusSkinCare *produse;

public:
    MagazinSkinCare(const char *denumire_, float review_) {
        strcpy(denumire, denumire_);
        review = review_;
    }

    MagazinSkinCare(const MagazinSkinCare &magazin) {
        strcpy(denumire, magazin.denumire);
        review = magazin.review;
        produse_in_stoc = magazin.produse_in_stoc;
    }

    MagazinSkinCare() {
        denumire[0] = 0;
    }

    const char* getDenumire() const {
        return denumire;
    }

    float getReview() const {
        return review;
    }

    ProdusSkinCare* getProdus() const{
        return produse;
    };

    void AdaugaStoc(const ProdusSkinCare& produs) {
        if (produse_in_stoc < capacitate_maxima) {
            produse[produse_in_stoc] = produs;
            produse_in_stoc++;
        } else {
            std::cout << "Nu mai este loc in magazin!!!" << std::endl;
        }
    }

    void AfiseazaProduseDisponibile() const {
        if (produse_in_stoc == 0) {
            std::cout << "Vom reveni cu stoc nou curand!" << std::endl;
        } else {
            std::cout << "Produsele disponibile in magazinul:" << denumire << "sunt:" << std::endl;
            for (int i = 0; i < produse_in_stoc; i++) {
                std::cout << "Nume produs:" << produse[i].getNume() << ", Pret produs: " << produse[i].getPret() << "lei;";
            }
        }
    }

    ~MagazinSkinCare() {
        std::cout << std::endl << strcat(denumire, "a apelat destructorul") << std::endl;
    }

    friend std::ostream &operator<<(std::ostream &out, const MagazinSkinCare* magazin);

    friend std::ostream &operator<<(std::ostream &out, const MagazinSkinCare* magazin);

    friend std::istream &operator>>(std::istream &in, MagazinSkinCare *magazin);

    char denumire[30];
    float review = 0.0;
};

///supraincarcarea operatorilor << si >>
std::ostream &operator<<(std::ostream &out, const MagazinSkinCare *magazin) {
    out << "Numele magazinului: " << magazin->denumire << std::endl;
    out << "Nota review: " << magazin->review << std::endl;
    out << "Numarul produselor din stoc:" << magazin->produse_in_stoc << std::endl;
    for (int i = 0; i < magazin->produse_in_stoc; i++) {
        std::cout << "Nume produs: " << magazin->produse[i].getNume() << std::endl;
        std::cout << "Pret: " << magazin->produse[i].getPret() << " lei;" << std::endl;
    }
    return out;
}

std::ostream& operator<<(std::ostream &out, const MagazinSkinCare *magazin);

std::istream &operator>>(std::istream &in, MagazinSkinCare &magazin) {
   std::cout << std::endl << "Numele magazinului: ";
    in >> magazin.denumire;
    std::cout << std::endl << "Nota review: ";
    in >> magazin.review;
    return in;
}
/*ProdusSkinCare* citesteProdusNou() {
    char t[30];
    int p;
    std::cin >> t >> p;
    return new ProdusSkinCare(t, p);*/

int main() {
    MagazinSkinCare magazin("Fenty Skin", 4.8);
    ProdusSkinCare produs1("Gel de curatare de fata", 76.99);
    ProdusSkinCare produs2 ("Crema Hidratanta", 82.99);
    ProdusSkinCare produs3 ("Crema de ochi", 56.99);
    magazin.AdaugaStoc(produs1);
    magazin.AdaugaStoc(produs2);
    magazin.AdaugaStoc(produs3);
    CosCumparaturi cos;

    cos.AdaugaProdus(produs2);
    cos.AdaugaProdus(produs3);

   std:: cout<<"Bine ati venit la "<< magazin.getDenumire()<<" cu rating "<< magazin.getReview()<<"!"<<std::endl;
    std::cout<<"Produsele disponibile in magazin sunt:"<<std::endl;
    magazin.AfiseazaProduseDisponibile();

    std::cout<< "Cosul de cumparaturi initial este gol.";

    cos.AfiseazaCos();
    return 0;
}
