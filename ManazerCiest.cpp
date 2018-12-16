#include "ManazerCiest.h"
#include <iostream>


ManazerCiest::ManazerCiest(): m_cesty(new std::map<std::string, Cesta*>())
{
}

bool ManazerCiest::pridajCestu(TypCiest typ, std::string meno, Mesto * pociatocne, Mesto * koncove, int rychlost)
{
	std::string uplnyNazov;
	switch (typ)
	{
	case JEDNOSMERKA:
		uplnyNazov = meno;
		break;
	case CESTA1T:
		uplnyNazov = "I/" + meno;
		break;
	case DIALNICA:
		uplnyNazov = "D" + meno;
		break;
	}
	if (m_cesty->find(uplnyNazov) != m_cesty->end())
	{
		std::cout << "Cesta s tymto nazvom uz existuje!\n";
		return false;
	}
	Cesta* temp = new Cesta(typ, uplnyNazov, pociatocne, koncove, rychlost);
	m_cesty->insert(std::make_pair(uplnyNazov, temp));
	pociatocne->pridajSusM(temp);
	koncove->pridajSusM(temp);
	return true;
}

bool ManazerCiest::pridajCestu(Cesta * cesta)
{
	m_cesty->insert(std::make_pair(cesta->getNazov(), cesta));
	cesta->getPociatocne()->pridajSusM(cesta);
	cesta->getKoncove()->pridajSusM(cesta);
	return true;
}

bool ManazerCiest::odstranCestu(std::string nazov)
{
	if (m_cesty->find(nazov) != m_cesty->end())
	{
		Cesta* temp = m_cesty->at(nazov);
		temp->getPociatocne()->odstranCestu(temp);
		temp->getKoncove()->odstranCestu(temp);
		delete temp;
		m_cesty->erase(nazov);
		return true;
	}
	return false;
}

void ManazerCiest::resetCiest()
{
	m_cesty->clear();
}

void ManazerCiest::odstranCestyDo(std::string nazov)
{
	std::vector<std::map<std::string, Cesta*>::iterator> vektor;
	for(auto &cesta : *m_cesty)
	{
		if (cesta.second->getPociatocne()->getNazov().compare(nazov) == 0 || cesta.second->getKoncove()->getNazov().compare(nazov) == 0)
		{
			vektor.push_back(m_cesty->find(cesta.first));
		}
	}
	if (vektor.size() != 0)
	{
		for (auto &p : vektor)
			m_cesty->erase(p);
	}
}

ManazerCiest::~ManazerCiest()
{
	delete m_cesty;
}
