#include <iostream>
#include <string>
#include <vector>

class produs {
    double pret;
    std::string nume;
    int cantitate, id_raion;

public:
    explicit produs(const double pret_ = 0, std::string nume_ = "NULL",
                    const int cantitate_ = 0, const int id_raion_ = 0)
        : pret(pret_), nume(std::move(nume_)), cantitate(cantitate_), id_raion(id_raion_) {std::cout<<nume<<" s-a initializat cu succes!\n";}

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
    explicit raion(const int id_ = 0, std::string nume_ = "NULL", const std::vector<produs>& produse_ = {}) : id(id_), nume(std::move(nume_)), produse(produse_) {
        std::cout<<"Raionul pentru "<<nume<<" s-a initializat cu succes!\n";
    }
    void afiseazaProduse() const {
        std::cout << "Produse in raionul " << nume << ":\n";
        for (const produs& p : produse) {
            std::cout << p;
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

int main() {
    produs p1(14.5, "Branza Hochland", 5, 3);
    produs p2(10.7, "Coca-Cola Zero", 20, 2), p3(21.5, "Foietaje cu feta", 10, 1), p4(15, "Pastrav", 15, 1);
    std::cout << p1 << p2;
    raion r1(1, "congelate", std::vector<produs>{p3,p4});
    r1.afiseazaProduse();
    raion r2;
    std::cout << r2 << r1 << std::endl;
    return 0;
}