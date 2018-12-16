#include "ManazerMiest.h"


ManazerMiest::ManazerMiest(): m_vsetkyMesta(new std::map< std::string, Mesto*>())
{

}

bool ManazerMiest::pridajMesto(Mesto * pmesto)
{
	if (m_vsetkyMesta->find(pmesto->getNazov()) == m_vsetkyMesta->end())
	{
		m_vsetkyMesta->insert(std::make_pair(pmesto->getNazov(),pmesto));
		return true;
	}
	else
	{
		return false;
	}
}


bool ManazerMiest::pridajMesto(std::string nazov, int pocetO, double rozloha)
{
	if (m_vsetkyMesta->find(nazov) == m_vsetkyMesta->end())
	{
		m_vsetkyMesta->insert(std::make_pair(nazov, new Mesto(nazov, pocetO, rozloha)));
		return true;
	}
	else
	{
		return false;
	}
}

bool ManazerMiest::odstranMesto(std::string nazov)
{
	if (m_vsetkyMesta->find(nazov) != m_vsetkyMesta->end())
	{
		m_vsetkyMesta->at(nazov)->~Mesto();
		m_vsetkyMesta->erase(nazov);
		return true;
	}
	else
		return false;
}

void ManazerMiest::nacitajMesta(std::string fileName)
{
}

Mesto* ManazerMiest::getKonkretneMesto(std::string nazov)
{
	if (m_vsetkyMesta->find(nazov) != m_vsetkyMesta->end())
		return m_vsetkyMesta->at(nazov);
	return nullptr;
}

void ManazerMiest::resetMiest()
{
	for (auto &p : *m_vsetkyMesta)
	{
		delete p.second;
	}
	m_vsetkyMesta->clear();
}

ManazerMiest::~ManazerMiest()
{
	for (auto &p : *m_vsetkyMesta)
	{
		delete p.second;
	}
	delete m_vsetkyMesta;
}
