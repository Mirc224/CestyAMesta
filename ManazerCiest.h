#pragma once
#include <vector>
#include <map>
#include "Cesta.h"
#include "Mesto.h"
class ManazerCiest
{
public:
	ManazerCiest();
	bool pridajCestu(TypCiest typ, std::string meno, Mesto* pociatocne, Mesto* koncove, int rychlost);
	bool pridajCestu(Cesta* cesta);
	bool odstranCestu(std::string);
	void resetCiest();
	void odstranCestyDo(std::string nazov);
	std::map<std::string, Cesta*>* getCesty() { return m_cesty; }
	virtual ~ManazerCiest();
private: 
	std::map<std::string,Cesta*>* m_cesty;
};

