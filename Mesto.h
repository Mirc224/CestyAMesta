#pragma once
#include <string>
#include <sstream>
#include <vector>
#include <map>
class Cesta;
class Mesto
{
public:
	Mesto(std::string nazov, int pocetO, double rozloha) : m_nazov(nazov), m_pocet(pocetO), m_rozloha(rozloha), m_susedneM(new std::map< std::string, std::vector<Cesta*>*>()) {}
	Mesto();
	bool pridajSusM(Cesta* cesta);
	bool odstranSusM(std::string nazov);
	bool odstranCestu(Cesta* hlCesta);
	friend std::istream& operator >>(std::istream& is, Mesto* b)
	{
		b->nacitaj(is); return is;
	}
	friend std::ostream& operator <<(std::ostream& os, Mesto* b) 
	{
		b->vypis(os); return os;
	}
	std::string getNazov() { return m_nazov; }
	void nacitaj(std::istream& is);
	void vypis(std::ostream& os);
	int getPocetO() { return m_pocet; }
	double getRozloha() { return m_rozloha; }
	Cesta* najrychlejsiaCesta(std::string nazMesta);
	virtual ~Mesto();

private:
	std::string m_nazov;
	int m_pocet;
	double m_rozloha;
	std::map< std::string, std::vector<Cesta*>*>* m_susedneM;
};

