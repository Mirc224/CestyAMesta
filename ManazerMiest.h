#pragma once
#include <vector>
#include <map>
#include "Mesto.h"
class ManazerMiest
{
public:
	ManazerMiest();
	bool pridajMesto(Mesto* pmesto);
	bool pridajMesto(std::string nazov, int pocetO, double rozloha);
	bool odstranMesto(std::string nazov);
	void nacitajMesta(std::string fileName);
	std::map< std::string, Mesto*>* getMesta() { return m_vsetkyMesta; }
	Mesto* getKonkretneMesto(std::string nazov);
	void resetMiest();
	virtual ~ManazerMiest();

private:
	std::map< std::string, Mesto*>* m_vsetkyMesta;
};

