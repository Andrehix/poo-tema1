#include <iostream>
#include <vector>

class prieten {
    int varsta;
    bool close;
    std::string nume;
public:
    std::string getNume() {
        return this->nume;
    }
    prieten() { std::cout << "Cine-i asta???\n"; }
    prieten(const std::string& nume_, const int varsta_, const bool close_)
        : nume(nume_), varsta(varsta_), close(close_) {
        if (close_)
            std::cout << "L-am initializat pe vtm " << nume_ << " cu succes!\n";
        else
            std::cout << "L-am initializat pe sarpele ala de " << nume_ << " cu succes...\n";
    }

    prieten(const prieten& altu)
        : nume(altu.nume), varsta(altu.varsta), close(altu.close) {
        std::cout << "L-am clonat pe " << altu.nume << " lol\n";
    }

    prieten& operator=(const prieten& altu) {
        std::cout << nume << " se transforma in " << altu.nume << "!" << std::endl;
        nume = altu.nume;
        close = altu.close;
        varsta = altu.varsta;
        return *this;
    }

    friend std::ostream& operator<<(std::ostream& os, const prieten& p);

    bool is_close() const { return close; }
    ~prieten() = default;
};

std::ostream& operator<<(std::ostream& os, const prieten& p) {
    os << "<------> " << "Numele prietenului -> " << p.nume
       << " ### Varsta -> " << p.varsta
       << " ### Close -> " << (p.close ? "Da" : "Nu") << " <------>\n";
    return os;
}

class grup {
    std::string nume;
    std::vector<prieten> indivizii;
    int tier;
public:
    void verificare() {
        int i;
        for (i=0;i<indivizii.size();i++)
            if (!indivizii[i].is_close()) {
                std::cout<<"L-am prins pe "<<indivizii[i].getNume()<<" si l-am dat afara din "<<nume<<'!'<<std::endl;
                indivizii.erase(indivizii.begin() + i);
            }
    }
    grup() = default;
    grup(const std::string& nume, const std::vector<prieten>& indivizii, int tier)
        : nume(nume), indivizii(indivizii), tier(tier) {
        std::cout << "I-am initializat pe " << nume << std::endl;
    }

    grup(const grup& altu)
        : nume(altu.nume), tier(altu.tier), indivizii(altu.indivizii) {}

    grup& operator=(const grup& altu) {
        std::cout << nume << " se transforma in " << altu.nume << "!" << std::endl;
        nume = altu.nume;
        tier = altu.tier;
        indivizii = altu.indivizii;
        return *this;
    }

    friend std::ostream& operator<<(std::ostream& os, const grup& g);
};

std::ostream& operator<<(std::ostream& os, const grup& g) {
    os << "<------> " << "Numele grupului -> " << g.nume
       << " ### Tier -> " << g.tier << " ### Membrii:\n";
    for (const auto& p : g.indivizii) {
        os << p << '\n';
    }
    return os;
}

class shaorma {
    std::string nume;
    int nota;
public:
    shaorma() = default;
    shaorma(const std::string& nume, int nota) : nume(nume), nota(nota) {}
    shaorma(const shaorma& altu) : nume(altu.nume), nota(altu.nota) {}

    shaorma& operator=(const shaorma& alta) {
        nume = alta.nume;
        nota = alta.nota;
        return *this;
    }

    friend std::ostream& operator<<(std::ostream& os, const shaorma& s);

    void concluzie() {
        if (this->nota>5){std::cout<<this->nume<<" e peste medie!"<<std::endl;}
        else if (this->nota<5){std::cout<<this->nume<<" este sub medie..."<<std::endl;}
        else {std::cout<<this->nume<<" e la medie."<<std::endl;}
    }

    static double medie_shaorme(const std::vector<shaorma>& shaormele) {
        if (shaormele.empty()) return 0.0;

        double total = 0.0;
        for (const shaorma& shaorma_obj : shaormele) {
            total += shaorma_obj.nota;
        }

        return total / shaormele.size();
    }
};

std::ostream& operator<<(std::ostream& os, const shaorma& s) {
    os << "Shaorma: " << s.nume << ", Nota: " << s.nota << std::endl;
    return os;
}

class materie {
    std::string nume, profesor;
    int credite;
public:
    materie() = default;
    materie(const std::string& nume_, const std::string& profesor_, int credite_)
        : nume(nume_), profesor(profesor_), credite(credite_) {}

    materie& operator=(const materie& alta) {
        nume = alta.nume;
        credite = alta.credite;
        profesor = alta.profesor;
        return *this;
    }

    friend std::ostream& operator<<(std::ostream& os, const materie& m);
    std::string getNume() {
        return this->nume;
    }
    void trecere() const {
        if (credite>=5)std::cout<<"AI TRECUT LA "<<nume<<" YIPIEE!"<<std::endl;
        else std::cout<<"Ai picat la "<<nume<<"..."<<std::endl;
    }
};

std::ostream& operator<<(std::ostream& os, const materie& m) {
    os << "Materia: " << m.nume << ", Profesor: " << m.profesor
       << ", Credite: " << m.credite << std::endl;
    return os;
}

int main() {
    prieten p1("Iulian", 19, true), p2("Eren", 20, false);
    grup g1("Faptasii", {p1, p2}, 1);

    shaorma s1("Dristor", 9), s2("Baneasa", 4), s3("Fendi", 10), s4("Auchan",2);
    std::vector<shaorma> shaormele = {s1, s2, s3};
    std::cout << "Media notelor: " << shaorma::medie_shaorme(shaormele) << std::endl;

    materie m1("POO", "Prof. Micluta", 3), m2("LFA", "Prof. Paun", 7), m3("BD", "Prof. Marin", 10);
    s1.concluzie();
    g1.verificare();
    m2.trecere();
    m1.trecere();
    return 0;
}