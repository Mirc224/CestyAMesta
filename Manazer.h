#pragma once
#include "ManazerCiest.h"
#include "ManazerMiest.h"
#include <iostream>
#include <vector>
#include <map>
#include <string>
class Manazer
{
public:
	Manazer();
	void pridajMesto(Mesto* mesto);
	bool pridajMestoKlavesnica();
	bool pridajCestuKlavesnica();
	bool odstranMesto();
	void zmazExistujucuSiet();
	void pridajCestu(TypCiest typ, std::string meno, Mesto * pociatocne, Mesto * koncove, int rychlost);
	void usporiadanyVypisMiest();
	void usporiadanyVypisCiest();
	bool odstranCestu();
	void nacitaj();
	void uloz();
	void najdiNajrychlejsiuCestu();
	virtual ~Manazer();
private:
	ManazerCiest* m_manCiest;
	ManazerMiest* m_manMiest;
};

