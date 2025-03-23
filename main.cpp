#include <iostream>
#include <string>

class produs {
    double pret;
    std::string nume;
    int cantitate, id_raion;

public:
    explicit produs(const double pret_ = 0, std::string nume_ = "NULL",
                    const int cantitate_ = 0, const int id_raion_ = 0)
        : pret(pret_), nume(std::move(nume_)), cantitate(cantitate_), id_raion(id_raion_) {}

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

int main() {
    produs p1(14.5, "Branza Hochland", 5, 3);
    produs p2(10.7, "Coca-Cola Zero", 20, 2);
    std::cout << p1 << p2;

    return 0;
}
