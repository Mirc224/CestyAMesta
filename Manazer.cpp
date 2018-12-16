#include "Manazer.h"
#include <algorithm>
#include <fstream>
#include <iostream>
#include <locale>
inline bool isInteger(const std::string & s)
{
	if (s.empty() || ((!isdigit(s[0])) && (s[0] != '-') && (s[0] != '+'))) return false;

	char * p;
	strtol(s.c_str(), &p, 10);

	return (*p == 0);
}

bool is_double(const std::string& s)
{
	try
	{
		std::stod(s);
	}
	catch (...)
	{
		return false;
	}
	return true;
}

std::string toMalePismena(std::string slovo)
{
	std::string toLowVsp = "";
	for (int i = 0; i < slovo.length(); ++i)
	{
		std::locale loc;
		toLowVsp += std::tolower(slovo.at(i), loc);
	}
	return toLowVsp;
}

bool compare_by_nazov(const std::string& lhs, const std::string& rhs) {
	return lhs < rhs;
}

Manazer::Manazer() : m_manCiest(new ManazerCiest()), m_manMiest(new ManazerMiest())
{
}

void Manazer::pridajMesto(Mesto* mesto)
{
	m_manMiest->pridajMesto(mesto);
}

bool Manazer::pridajMestoKlavesnica()
{
	std::string parameter;
	std::string nazov;
	int pocetO;
	double rozloha;
	std::cout << "Pridavas nove mesto z klavesnice. Jeho tvar by mal byt nasledovny: nazov , pocet obyvatelov (cele cislo), rozloha (cislo s desatinnou bodkou) \n";
	std::cout << "Nazov: ";
	std::getline(std::cin, nazov);
	if (m_manMiest->getKonkretneMesto(nazov) != nullptr)
	{
		std::cout << "Mesto s nazvom " << nazov << " uz existuje!\n";
		return false;
	}
	std::cout << "Pocet obyvatelov: ";
	//if (std::cin >> pocetO)
	//{
	//	std::cin.get();
	//}
	//else
	//{
	//	std::cin.get();
	//	std::cout << "Pocet obyvatelov musi byt cislo!\n";
	//	return false;
	//}
	std::getline(std::cin, parameter);
	for (int i = 0; i < parameter.length(); ++i)
	{
		std::locale loc;
		if (!std::isdigit(parameter[i], loc))
		{
			std::cout << "Pocet obyvatelov musi byt cislo!\n";
			return false;
		}
	}
	if (isInteger(parameter))
	{
		pocetO = std::stoi(parameter);
		if (pocetO < 0)
		{
			std::cout << "Pocet obyvatelov nemoze byt zaporny!\n";
			return false;
		}
	}
	std::cout << "Rozloha: ";
	std::getline(std::cin, parameter);
	if (is_double(parameter))
	{
		rozloha = std::stod(parameter);
	}
	else
	{
		std::cout << "Zadany parameter nie je cislo!\n";
		return false;
	}
	m_manMiest->pridajMesto(nazov, pocetO, rozloha);
	return true;
}

bool Manazer::pridajCestuKlavesnica()
{
	std::string parameter;
	std::string nazov;
	TypCiest typCesty;
	Mesto* pociatocneMesto = nullptr;
	Mesto* koncoveMesto = nullptr;
	int rychlost;
	std::cout << "Pridavas novu cestu z klavesnice. Jej tvar by mal byt nasledovny: typ(jednosmerka,cesta1triedy,dialnica) \n";
	std::cout << "nazov (len cislo, prefix na zaklade typu), existujuce pociatocne mesto, existujuce koncove mesto, rychlost podla zadaneho typu. \n";
	std::cout << "Typ(jednosmerka, cesta1triedy, dialnica): ";
	std::getline(std::cin, parameter);
	parameter = toMalePismena(parameter);
	if (parameter.compare("jednosmerka") == 0)
		typCesty = JEDNOSMERKA;
	else if (parameter.compare("cesta1triedy") == 0)
		typCesty = CESTA1T;
	else if (parameter.compare("dialnica") == 0)
		typCesty = DIALNICA;
	else
	{
		std::cout << "Zadali ste nespravny typ cesty!\n";
		return false;
	}
	switch (typCesty)
	{
		case JEDNOSMERKA:
			std::cout << "Nazov: ";
			std::getline(std::cin, parameter);
			for (int i = 0; i < parameter.length(); ++i)
			{
				std::locale loc;
				if (!std::isdigit(parameter[i], loc))
				{
					std::cout << "Nazov musi byt len cislo!\n";
					return false;
				}
			}
			nazov = parameter;
			std::cout << "Pociatocne mesto: ";
			std::getline(std::cin, parameter);
			if ((pociatocneMesto = m_manMiest->getKonkretneMesto(parameter)) == nullptr)
			{
				std::cout << "Mesto " << parameter << " neexistuje! \n";
				return false;
			}
			std::cout << "Koncove mesto: ";
			std::getline(std::cin, parameter);
			if ((koncoveMesto = m_manMiest->getKonkretneMesto(parameter)) == nullptr)
			{
				std::cout << "Mesto " << parameter << " neexistuje! \n";
				return false;
			}
			std::cout << "Rychlost (variabilna rychlost okrem 0): ";
			std::getline(std::cin, parameter);
			for (int i = 0; i < parameter.length(); ++i)
			{
				std::locale loc;
				if (!std::isdigit(parameter[i], loc))
				{
					std::cout << "Rychlost musi byt cislo!\n" << std::endl;
					return false;
				}
			}
			rychlost = std::stoi(parameter);
			if (rychlost <= 0)
			{
				std::cout << "Rychlost musi byt nenulova!\n";
			}
			break;
		case CESTA1T:
			std::cout << "Nazov: I/";
			std::getline(std::cin, parameter);
			for (int i = 0; i < parameter.length(); ++i)
			{
				std::locale loc;
				if (!std::isdigit(parameter[i], loc))
				{
					std::cout << "Nazov musi byt len cislo!\n";
					return false;
				}
			}
			nazov = parameter;
			std::cout << "Pociatocne mesto: ";
			std::getline(std::cin, parameter);
			if ((pociatocneMesto = m_manMiest->getKonkretneMesto(parameter)) == nullptr)
			{
				std::cout << "Mesto " << parameter << " neexistuje! \n";
				return false;
			}
			std::cout << "Koncove mesto: ";
			std::getline(std::cin, parameter);
			if ((koncoveMesto = m_manMiest->getKonkretneMesto(parameter)) == nullptr)
			{
				std::cout << "Mesto " << parameter << " neexistuje! \n";
				return false;
			}
			std::cout << "Rychlost (60-90 km/h): ";
			std::getline(std::cin, parameter);
			for (int i = 0; i < parameter.length(); ++i)
			{
				std::locale loc;
				if (!std::isdigit(parameter[i], loc))
				{
					std::cout << "Rychlost musi byt cislo!\n";
					return false;
				}
			}
			rychlost = std::stoi(parameter);
			if (rychlost < 60 || rychlost > 90)
			{
				std::cout << "Zadali ste nespravnu rychlost pre dany typ cesty!\n";
				return false;
			}
			break;
		case DIALNICA:
			std::cout << "Nazov: D";
			std::getline(std::cin, parameter);
			for (int i = 0; i < parameter.length(); ++i)
			{
				std::locale loc;
				if (!std::isdigit(parameter[i], loc))
				{
					std::cout << "Nazov musi byt len cislo!\n";
					return false;
				}
			}
			nazov = parameter;
			std::cout << "Pociatocne mesto: ";
			std::getline(std::cin, parameter);
			if ((pociatocneMesto = m_manMiest->getKonkretneMesto(parameter)) == nullptr)
			{
				std::cout << "Mesto " << parameter << " neexistuje! \n";
				return false;
			}
			std::cout << "Koncove mesto: ";
			std::getline(std::cin, parameter);
			if ((koncoveMesto = m_manMiest->getKonkretneMesto(parameter)) == nullptr)
			{
				std::cout << "Mesto " << parameter << " neexistuje! \n";
				return false;
			}
			std::cout << "Rychlost (120-130 km/h): ";
			std::getline(std::cin, parameter);
			for (int i = 0; i < parameter.length(); ++i)
			{
				std::locale loc;
				if (!std::isdigit(parameter[i], loc))
				{
					std::cout << "Rychlost musi byt cislo!\n";
					return false;
				}
			}
			rychlost = std::stoi(parameter);
			if (rychlost < 120 || rychlost > 130)
			{
				std::cout << "Zadali ste nespravnu rychlost pre dany typ cesty!\n";
				return false;
			}
			break;
	}
	if (m_manCiest->pridajCestu(typCesty, nazov, pociatocneMesto, koncoveMesto, rychlost))
	{
		std::cout << "Cesta bola pridana!\n";
		return true;
	}
	else
		return false;
}

bool Manazer::odstranMesto()
{
	std::string nazov;
	std::cout << "Zadajte nazov mesta, ktore chcete odstranit: ";
	std::cin >> nazov;
	std::cin.get();
	if (m_manMiest->getKonkretneMesto(nazov) != nullptr)
	{
		m_manCiest->odstranCestyDo(nazov);
		m_manMiest->odstranMesto(nazov);
		return true;
	}
	else
	{
		return false;
	}
}

void Manazer::zmazExistujucuSiet()
{
	m_manMiest->resetMiest();
	m_manCiest->resetCiest();
}

void Manazer::pridajCestu(TypCiest typ, std::string meno, Mesto * pociatocne, Mesto * koncove, int rychlost)
{
	m_manCiest->pridajCestu(typ, meno, pociatocne, koncove, rychlost);
}

void Manazer::usporiadanyVypisMiest()
{
	std::vector<std::string> usporiadanyVektor;
	std::map < std::string, Mesto*>* temp = m_manMiest->getMesta();
	for (auto &mesta : *temp)
	{
		usporiadanyVektor.push_back(mesta.first);
	}
	std::sort(usporiadanyVektor.begin(), usporiadanyVektor.end(), compare_by_nazov);
	for (auto &p : usporiadanyVektor)
	{
		std::cout << temp->at(p);
	}
}

void Manazer::usporiadanyVypisCiest()
{
	std::vector<std::string> usporiadanyVektorDialnic;
	std::vector<std::string> usporiadanyVektorCiest1T;
	std::vector<std::string> usporiadanyVektorJednosmeriek;
	std::map < std::string, Cesta*>* temp = m_manCiest->getCesty();
	for (auto &cesta : *temp)
	{
		switch (cesta.second->getTyp())
		{
			case DIALNICA:
				usporiadanyVektorDialnic.push_back(cesta.first);
				break;
			case CESTA1T:
				usporiadanyVektorCiest1T.push_back(cesta.first);
				break;
			case JEDNOSMERKA:
				usporiadanyVektorJednosmeriek.push_back(cesta.first);
				break;

		}
	}
	std::sort(usporiadanyVektorDialnic.begin(), usporiadanyVektorDialnic.end(), compare_by_nazov);
	for (auto &p : usporiadanyVektorDialnic)
	{
		std::cout << temp->at(p)->toString();
	}
	std::sort(usporiadanyVektorCiest1T.begin(), usporiadanyVektorCiest1T.end(), compare_by_nazov);
	for (auto &p : usporiadanyVektorCiest1T)
	{
		std::cout << temp->at(p)->toString();
	}
	std::sort(usporiadanyVektorJednosmeriek.begin(), usporiadanyVektorJednosmeriek.end(), compare_by_nazov);
	for (auto &p : usporiadanyVektorJednosmeriek)
	{
		std::cout << temp->at(p)->toString();
	}
}

bool Manazer::odstranCestu()
{
	std::string nazov;
	std::cout << "Zadajte nazov cesty, ktoru chcete odstranit: ";
	std::cin >> nazov;
	std::cin.get();
	std::map<std::string, Cesta*>* tempCesty = m_manCiest->getCesty();
	if (tempCesty->find(nazov) != tempCesty->end())
	{
		m_manCiest->odstranCestu(nazov);
		return true;
	}
	else
	{
		return false;
	}
}

void Manazer::nacitaj()
{
	std::ifstream inputFile("vystup.txt");
	if (inputFile.peek() == std::ifstream::traits_type::eof())
	{
		std::cout << "Subor je prazdny!\n";
	}
	else
	{
		zmazExistujucuSiet();
		int opakovanie;
		inputFile >> opakovanie;
		inputFile.get();
		for (int i = 0; i < opakovanie; ++i)
		{
			Mesto* temp = new Mesto();
			inputFile >> temp;
			m_manMiest->pridajMesto(temp);
		}
		inputFile >> opakovanie;
		inputFile.get();
		for (int i = 0; i < opakovanie; ++i)
		{
			std::string nazov;
			TypCiest typCesty;
			int rychlost;
			std::string pociatocneMesto;
			std::string koncoveMesto;
			std::string veta;
			std::getline(inputFile, veta);
			std::istringstream istring(veta);
			std::getline(istring, veta, ',');
			switch (std::stoi(veta))
			{
				case JEDNOSMERKA:
					typCesty = JEDNOSMERKA;
					break;
				case CESTA1T:
					typCesty = CESTA1T;
					break;
				case DIALNICA:
					typCesty = DIALNICA;
					break;
			}
			std::getline(istring, nazov, ',');
			std::getline(istring, pociatocneMesto, ',');
			std::getline(istring, koncoveMesto, ',');
			std::getline(istring, veta, ',');
			rychlost = std::stoi(veta);
			m_manCiest->pridajCestu(new Cesta(typCesty, nazov, m_manMiest->getKonkretneMesto(pociatocneMesto), m_manMiest->getKonkretneMesto(koncoveMesto), rychlost));
		}
		std::cout << "Nacitavanie dokoncene! \n";
	}
}


void Manazer::uloz()
{
	std::ofstream outputFile("vystup.txt");
	std::map<std::string, Mesto*>* tempVsMesta = m_manMiest->getMesta();
	outputFile << tempVsMesta->size() << std::endl;
	for (auto &p : *tempVsMesta)
	{
		outputFile << p.second;
	}
	std::map<std::string, Cesta*>* tempVsCesty = m_manCiest->getCesty();
	outputFile << tempVsCesty->size() << std::endl;
	for (auto &p : *tempVsCesty)
	{
		outputFile << p.second;
	}
}

void Manazer::najdiNajrychlejsiuCestu()
{
	std::map<std::string, Mesto*>* tempMesta = m_manMiest->getMesta();
	std::map<int, Mesto*> mapaPrevodu;
	std::map<std::string, int> mapaPrevoduBack;
	int size = tempMesta->size();
	double* vrcholyTi = new double[size];
	int* vrcholyXi = new int[size];

	std::cout << "Zadajte zaciatocny vrchol: ";
	std::string zaciatocnyVrchol;
	std::string koncovyVrchol;
	std::getline(std::cin, zaciatocnyVrchol);
	if (tempMesta->find(zaciatocnyVrchol) == tempMesta->end())
	{
		std::cout << "\nZadali ste nespravny vrchol \n";
		delete[] vrcholyTi;
		delete[] vrcholyXi;
		return;
	}
	std::cout << "Zadajte koncovy vrchol: ";
	std::getline(std::cin, koncovyVrchol);
	if (tempMesta->find(koncovyVrchol) == tempMesta->end())
	{
		std::cout << "\nZadali ste nespravny vrchol \n";
		delete[] vrcholyTi;
		delete[] vrcholyXi;
		return;
	}
	if (koncovyVrchol.compare(zaciatocnyVrchol) == 0)
	{
		std::cout << "Zadali ste rovnake mesto, najrychlejsia cesta neexistuje, lebo sa v nom uz nachadate \n";
		delete[] vrcholyTi;
		delete[] vrcholyXi;
		return;
	}
	int pocitadlo = 0;
	for (auto &p : *tempMesta)
	{
		mapaPrevodu.insert(std::make_pair(pocitadlo, p.second));
		mapaPrevoduBack.insert(std::make_pair(p.second->getNazov(), pocitadlo));
		++pocitadlo;
	}

	for (int i = 0; i < size; ++i)
	{
		if (i != mapaPrevoduBack.at(zaciatocnyVrchol))
		{
			vrcholyTi[i] = (DBL_MAX / 2) - 50;
		}
		else
			vrcholyTi[i] = 0;
		vrcholyXi[i] = -1;
	}

	Cesta*** hrany = new Cesta**[size];
	for (int i = 0; i < size; ++i)
	{
		hrany[i] = new Cesta*[size];
		for (int j = 0; j < size; ++j)
		{
			hrany[i][j] = nullptr;
		}
	}
	for (auto &vonkMesto : mapaPrevodu)
	{
		for (auto &vnutMesto : mapaPrevoduBack)
		{
			hrany[vonkMesto.first][vnutMesto.second] = vonkMesto.second->najrychlejsiaCesta(vnutMesto.first);
		}
	}
	std::vector<std::string> zasobnik;
	zasobnik.push_back(zaciatocnyVrchol);

	while (!zasobnik.empty())
	{
		int vrchol = mapaPrevoduBack.at(zasobnik.front());
		for (auto &peak : zasobnik)
		{
			if (vrcholyTi[mapaPrevoduBack.at(peak)] < vrcholyTi[vrchol])
			{
				vrchol = mapaPrevoduBack.at(peak);
			}
		}

		for (int i = 0; i < size; ++i)
		{
			if (hrany[vrchol][i] != nullptr)
			{
				double vysledok = (1.0 / hrany[vrchol][i]->getRychlost());
				if (vrcholyTi[i] > vrcholyTi[vrchol] + vysledok)
				{
					vrcholyTi[i] = vrcholyTi[vrchol] + vysledok;
					vrcholyXi[i] = vrchol;
					zasobnik.push_back(mapaPrevodu.at(i)->getNazov());
				}
			}
		}
		zasobnik.erase(std::remove(zasobnik.begin(), zasobnik.end(), mapaPrevodu.at(vrchol)->getNazov()), zasobnik.end());
	}
	std::string vrchol = koncovyVrchol;

	if (vrcholyTi[mapaPrevoduBack.at(koncovyVrchol)] != DBL_MAX / 2)
	{
		std::vector<std::string> vypis;
		std::cout << "Najkratsia cesta z " << zaciatocnyVrchol << " do " << koncovyVrchol << " ma tvar: ";
		do
		{
			Cesta* tempCesta = hrany[vrcholyXi[mapaPrevoduBack.at(vrchol)]][mapaPrevoduBack.at(vrchol)];
			if (tempCesta->getKoncove()->getNazov().compare(vrchol) == 0)
			{
				vypis.push_back(tempCesta->getKoncove()->getNazov());
				vypis.push_back(tempCesta->getNazov());
				//vypis.push_back(tempCesta->getPociatocne()->getNazov());
			}
			else
			{
				vypis.push_back(tempCesta->getPociatocne()->getNazov());
				vypis.push_back(tempCesta->getNazov());
				//vypis.push_back(tempCesta->getKoncove()->getNazov());
			}
			vrchol = mapaPrevodu.at(vrcholyXi[mapaPrevoduBack.at(vrchol)])->getNazov();
		} while (vrchol != zaciatocnyVrchol);
		vypis.push_back(zaciatocnyVrchol);
		std::reverse(vypis.begin(), vypis.end());
		for (auto &p : vypis)
		{
			std::cout << p;
			if (p.compare(koncovyVrchol) != 0)
				std::cout << " - ";
		}
		std::cout << std::endl;
	}
	else
	{
		std::cout << "Neexistuje spojenie medzi mestom " << zaciatocnyVrchol << " a " << koncovyVrchol << "!\n";
	}

	for (int i = 0; i < size; ++i)
	{
		delete[] hrany[i];
	}
	delete[] hrany;
	delete[] vrcholyTi;
	delete[] vrcholyXi;
}

Manazer::~Manazer()
{
	delete m_manMiest;
	delete m_manCiest;
}

