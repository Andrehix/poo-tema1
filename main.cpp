#include <iostream>
#include <string>
#include <vector>

class produs {
    double pret;
    std::string nume;
    int cantitate, id_raion;

public:
    [[nodiscard]] double getPret() const {
        return pret;
    }

    [[nodiscard]] int getCant() const {
        return cantitate;
    }
    explicit produs(const double pret_ = 0, std::string nume_ = "NULL",
                    const int cantitate_ = 0, const int id_raion_ = 0)
        : pret(pret_), nume(std::move(nume_)), cantitate(cantitate_), id_raion(id_raion_) {std::cout<<nume<<" s-a initializat cu succes!\n";}
    produs(const produs &p) = default;
    //produs(const produs &p) : pret(p.pret), nume(p.nume),  cantitate(p.cantitate), id_raion(p.id_raion) {}

    ~produs() = default;

    produs& operator=(const produs& other) {
        if (this != &other) {
            pret = other.pret;
            nume = other.nume;
            cantitate = other.cantitate;
            id_raion = other.id_raion;
        }
        return *this;
    }

    friend std::ostream& operator<<(std::ostream& out, const produs& p) {
        out << "Produs: " << p.nume << " | Pret: " << p.pret
            << " | Cantitate: " << p.cantitate << " | Raion: " << p.id_raion << std::endl;
        return out;
    }
};

class raion {
    int id;
    std::string nume;
    std::vector<produs> produse;
public:
    [[nodiscard]] int getId() const {
        return id;
    }
    explicit raion(const int id_ = 0, std::string nume_ = "NULL", const std::vector<produs>& produse_ = {}) : id(id_), nume(std::move(nume_)), produse(produse_) {
        std::cout<<"Raionul pentru "<<nume<<" s-a initializat cu succes!\n";
    }

    void afiseazaProduse() const {
        std::cout << "Raionul " << nume << " are " << produse.size() << " produse:\n";
        for (const produs& p : produse) {
            std::cout << p;
        }
    }

    void afiseazaCant() {
        int c=0;
        for (const produs& p : produse) {
            c+=p.getCant();
        }
        std::cout<<"Pe raionul "<<nume<<" sunt, in total, "<<c<<" bucati.\n";
    }

    void afiseazaPret() {
        double pret=0;
        for (const produs& p : produse) {
            pret+=p.getPret();
        }
        std::cout<<"Pe raionul "<<nume<<" sunt produse in valoare de "<<pret<<" lei.\n";
    }

    void afiseazaProduseCant(int c) {
        if (c >= 0) {
            std::cout<< "Produse in raionul "<<nume<< " care au cantitatea mai mare de "<<c<<" bucati:\n";
            for (const produs& p : produse) {
                if (p.getCant()>=c) std::cout<<p;
            }
        }
        else {
            c=-c;
            std::cout<< "Produse in raionul "<<nume<< " care au cantitatea mai mica de "<<c<<" bucati:\n";
            for (const produs& p : produse) {
                if (p.getCant()<=c) std::cout<<p;
            }
        }
    }

    void afiseazaProdusePret(int c) {
        if (c > 0) {
            std::cout<< "Produse in raionul "<<nume<< " care au pretul mai mare de "<<c<<" lei:\n";
            for (const produs& p : produse) {
                if (p.getPret()>=c) std::cout<<p;
            }
        }
        else {
            c=-c;
            std::cout<< "Produse in raionul "<<nume<< " care au pretul mai mic de "<<c<<" lei:\n";
            for (const produs& p : produse) {
                if (p.getPret()<=c) std::cout<<p;
            }
        }
    }

    ~raion() = default;

    raion& operator=(const raion& other) {
        if (this != &other) {
            id = other.id;
            nume = other.nume;
            produse = other.produse;
        }
        return *this;
    }

    friend std::ostream& operator<<(std::ostream& out, const raion& r) {
        out << "Raion: " << r.nume << ", ID: " << r.id << std::endl;
        for (const produs& p : r.produse) {
            out << p;
        }
        return out;
    }
};

class raioane {
    std::vector<raion> raioanele;
public:
    explicit raioane(const std::vector<raion>& raioanele_ = {}) : raioanele(raioanele_) {}
    ~raioane() = default;
    [[nodiscard]] std::vector<raion> getR() const {
        return raioanele;
    }
};

int main() {
    produs p1(14.5, "Branza Hochland", 5, 3);
    produs p2(10.7, "Coca-Cola Zero", 20, 2), p3(21.5, "Foietaje cu feta", 10, 1), p4(15, "Pastrav", 15, 1);
    raion r1(1, "congelate", std::vector<produs>{p3,p4}),r2;
    /*r2.afiseazaProduse();
    r1.afiseazaProdusePret(-20);
    r1.afiseazaProduseCant(-12);
    r1.afiseazaPret();
    r1.afiseazaCant();*/
    raioane R({r1,r2});
    int n=1,i=1,g=0;
    while (n!=0) {
        std::cout<<"Bun venit in baza de date Mini Image!\n"<<"Selecteaza una dintre urmatoarele optiuni:\n"<<"1. Afisare produse.\n";
        std::cin>>n;
        if (n==1)
            while (n!=0) {
                std::cout<<"Afisare produse. Selectati optiunea dorita:\n"<<"1. Afisare produse de pe un raion cu cantitatea mai mare/mai mica decat un numar.\n"
                <<"2. Afisare produse de pe un raion cu pretul mai mic/mai mare decat un numar.\n"<<"3. Afisare cantitatea totala de pe un raion.\n"
                <<"4. Afisare pret total de pe un raion.\n"<<"5. Afisarea tuturor produselor de pe un raion.\n"<<"0. Revenire la meniul principal.\n";
                std::cin>>n;
                if (n==1) {
                    std::cout<<"Inserati id-ul raionului:";
                    std::cin>>i;
                    for ( raion& a : R.getR() )
                        if (a.getId() == i) {
                            std::cout<<"Inserati numarul:";
                            std::cin>>i;
                            a.afiseazaProduseCant(i);
                        }
                }
                if (n==2) {
                    std::cout<<"Inserati id-ul raionului:";
                    std::cin>>i;
                    for ( raion& a : R.getR() )
                        if (a.getId() == i) {
                            std::cout<<"Inserati numarul:";
                            std::cin>>i;
                            a.afiseazaProdusePret(i);
                        }
                }
                if (n==3) {
                    std::cout<<"Inserati id-ul raionului:";
                    std::cin>>i;
                    for ( raion& a : R.getR() )
                        if (a.getId() == i) {
                            a.afiseazaCant();
                        }
                }
                if (n==4) {
                    std::cout<<"Inserati id-ul raionului:";
                    std::cin>>i;
                    for ( raion& a : R.getR() )
                        if (a.getId() == i) {
                            a.afiseazaPret();
                        }
                }
                if (n==5) {
                    std::cout<<"Inserati id-ul raionului:";
                    std::cin>>i;
                    for ( raion& a : R.getR() )
                        if (a.getId() == i) {
                            a.afiseazaProduse();
                        }
                }
                if (n==0) {g++;}
            }
        if (g==1) {
            n=1;
            g--;
        }
    }
    return 0;
}