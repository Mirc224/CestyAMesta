#pragma once
#include <string>
class Mesto;
enum TypCiest {JEDNOSMERKA, CESTA1T, DIALNICA };
class Cesta
{
public:
	static int pocetDialnic;
	static int pocetCiest1T;
	static int pocetJednosmeriek;
	Cesta(TypCiest typ, std::string meno, Mesto* pociatocne, Mesto* koncove, int rychlost);
	Cesta(){}
	Mesto* getPociatocne() { return m_pociatocne; }
	Mesto* getKoncove() { return m_koncove; }
	int getRychlost() { return m_rychlost; }
	TypCiest getTyp() { return m_typCesty; }
	std::string getNazov() { return m_nazov; }
	std::string toString();
	//friend std::istream& operator >>(std::istream& is, Cesta* b)
	//{
	//	b->nacitaj(is); return is;
	//}
	friend std::ostream& operator <<(std::ostream& os, Cesta* b)
	{
		b->vypis(os); return os;
	}
	//void nacitaj(std::istream& is);
	void vypis(std::ostream& os);

	virtual ~Cesta();
private:
	std::string m_nazov;
	int m_rychlost;
	TypCiest m_typCesty;
	Mesto* m_pociatocne;
	Mesto* m_koncove;

};

