#include "Mesto.h"
#include "Cesta.h"


Mesto::Mesto() : m_susedneM(new std::map< std::string, std::vector<Cesta*>*>())
{
}

bool Mesto::pridajSusM(Cesta* cesta)
{
	std::string nazovMesta;
	if (cesta->getPociatocne() != this)
		nazovMesta = cesta->getPociatocne()->getNazov();
	else
		nazovMesta = cesta->getKoncove()->getNazov();
	if (m_susedneM->find(nazovMesta) != m_susedneM->end())
	{
		m_susedneM->at(nazovMesta)->push_back(cesta);
	}
	else
	{
		std::vector<Cesta*>* temp = new std::vector<Cesta*>();
		temp->push_back(cesta);
		m_susedneM->insert(std::make_pair(nazovMesta, &(*temp)));
	}
	return true;
}

bool Mesto::odstranSusM(std::string nazov)
{
	m_susedneM->erase(nazov);
	return true;
}

bool Mesto::odstranCestu(Cesta * hlCesta)
{
	std::string nazovSusMesta;
	if (hlCesta->getPociatocne()->getNazov().compare(m_nazov) != 0)
	{
		nazovSusMesta = hlCesta->getPociatocne()->getNazov();
	}
	else
	{
		nazovSusMesta = hlCesta->getKoncove()->getNazov();
	}
	std::vector<Cesta*>* temp = m_susedneM->at(nazovSusMesta);
	auto it = std::find(temp->begin(), temp->end(), hlCesta);
	if (it != temp->end())
	{
		temp->erase(it);
		if (temp->size() == 0)
		{
			this->odstranSusM(nazovSusMesta);
		}
	}
	return false;
}

void Mesto::nacitaj(std::istream & is)
{
	std::string nazov;
	int obyvatelia;
	double rozloha;
	std::string veta;
	std::getline(is, veta);
	std::istringstream istring(veta);
	std::getline(istring, veta, ',');
	nazov = veta;
	std::getline(istring, veta, ',');
	obyvatelia = std::stoi(veta);
	std::getline(istring, veta, ',');
	rozloha = std::stof(veta);
	m_nazov = nazov;
	m_pocet = obyvatelia;
	m_rozloha = rozloha;
}

void Mesto::vypis(std::ostream & os)
{
	os << m_nazov << "," << m_pocet << "," << m_rozloha << std::endl;
}

Cesta * Mesto::najrychlejsiaCesta(std::string nazMesta)
{
	auto search = m_susedneM->find(nazMesta);
	if (search != m_susedneM->end())
	{
		std::vector<Cesta*>* tempCestyDoMesta = search->second;
		Cesta* najrCesta = nullptr;
		int najvyssiaRychlost = 0;
		for (auto &p : *tempCestyDoMesta)
		{
			if (p->getTyp() == JEDNOSMERKA)
			{
				if (p->getPociatocne() == this)
				{
					if (p->getRychlost() > najvyssiaRychlost)
					{
						najvyssiaRychlost = p->getRychlost();
						najrCesta = p;
					}
				}
			}
			else
			{
				if (p->getRychlost() > najvyssiaRychlost)
				{
					najvyssiaRychlost = p->getRychlost();
					najrCesta = p;
				}
			}
		}
		return najrCesta;
	}
	else
		return nullptr;
}

Mesto::~Mesto()
{
	for (auto &mesto : *m_susedneM)
	{
		Mesto* susMesto = nullptr;
		std::vector<Cesta*>* temp = mesto.second;
		Cesta* temp2 = *(temp->begin());
		if (temp2->getKoncove()->getNazov().compare(m_nazov) != 0)
			susMesto = temp2->getKoncove();
		else
			susMesto = temp2->getPociatocne();
		susMesto->odstranSusM(m_nazov);
		for (Cesta* cesta : *temp)
		{
			delete cesta;
		}
		delete mesto.second;
	}
	delete m_susedneM;
}
