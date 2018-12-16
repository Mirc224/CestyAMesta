#define _CRTDBG_MAP_ALLOC
#include <crtdbg.h>
#include <iostream>
#include "ManazerMiest.h"
#include "ManazerCiest.h"
#include "Cesta.h"
#include "Mesto.h"
#include "Manazer.h"
#include <locale>
int Cesta::pocetCiest1T = 50;
int Cesta::pocetDialnic = 1;
void vypisMenu()
{
	std::cout << "\n";
	std::cout << "1. Pridat mesto\n";
	std::cout << "2. Odstrani mesto\n";
	std::cout << "3. Pridat cestu, so specifickym typom a parametrami\n";
	std::cout << "4. Odstranit cestu\n";
	std::cout << "5. Nacitat sie zo suboru - existujuca sa zmaze\n";
	std::cout << "6. Zapisat sie do suboru\n";
	std::cout << "7. Hladanie najrychlejsej cesty z mesta A do mesta B.\n";
	std::cout << "8. Zoradeny vypis vsetkych miest podla nazvu\n";
	std::cout << "9. Zoradeny vypis vsetkych ciest\n";
	std::cout << "0. Koniec\n";
	std::cout << "\n";
}
int main()
{
	Manazer manazerik = Manazer();
	//manazerik->nacitaj();
	//	Mesto* zilina = new Mesto("Zilina", 10000, 138.2);
	//	Mesto* cadca = new Mesto("Cadca", 2000, 100.2);
	//	Mesto* knm = new Mesto("KNM", 5600, 118.9);
	//	manazerik->pridajMesto(zilina);
	//	manazerik->pridajMesto(zilina);
	//	manazerik->pridajMesto(cadca);
	//	manazerik->pridajMesto(knm);
	////	manazerik->odstranMesto("Polsko");
	////	manazerik->odstranMesto("Cadca");
	//	manazerik->pridajCestu(DIALNICA, std::to_string(1), cadca, zilina, 120);
	//	manazerik->pridajCestu(DIALNICA, std::to_string(3), cadca, zilina, 120);
	//	manazerik->pridajCestu(CESTA1T, std::to_string(2), knm, cadca, 120);
	//	manazerik->pridajCestu(DIALNICA, std::to_string(3), knm, zilina, 120);
	//	manazerik->pridajCestu(CESTA1T, std::to_string(1), cadca, zilina, 90);
	//	manazerik->pridajCestu(JEDNOSMERKA, std::to_string(1), cadca, zilina, 130);
	//	manazerik->pridajCestu(JEDNOSMERKA, std::to_string(3), knm, zilina, 90);
	//	manazerik->pridajCestu(DIALNICA, std::to_string(3), knm, zilina, 130);
		//manazerik->odstranCestu("D1");
		//manazerik->odstranCestu("I/1");
		//manazerik->najdiNajrychlejsiuCestu();
		//manazerik->odstranMesto();
		//manazerik->najdiNajrychlejsiuCestu();
		//manazerik->uloz();
	manazerik.usporiadanyVypisMiest();
	manazerik.usporiadanyVypisCiest();
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
	bool test = true;
	while (test)
	{
		int volba = -1;
		std::string parameter;
		vypisMenu();
		std::getline(std::cin, parameter);
		{
			bool testTemp = true;
			for (int i = 0; i < parameter.length(); ++i)
			{
				std::locale loc;
				if (!std::isdigit(parameter[i], loc))
				{
					std::cout << "Nezadali ste cislo\n" << std::endl;
					testTemp = false;
					break;
				}
			}
			if (testTemp)
			{
				volba = std::stoi(parameter);
			}
		}
		switch (volba)
		{
			case 1:
				manazerik.pridajMestoKlavesnica();
				break;
			case 2:
				manazerik.odstranMesto();
				break;
			case 3:
				if (manazerik.pridajCestuKlavesnica())
				{
					std::cout << "Pridavanie uspesne! \n";
				}
				else
					std::cout << "Pridavanie neuspesne! \n";
				break;
			case 4:
				manazerik.odstranCestu();
				break;
			case 5:
				manazerik.nacitaj();
				break;
			case 6:
				manazerik.uloz();
				break;
			case 7:
				manazerik.najdiNajrychlejsiuCestu();
				break;
			case 8:
				manazerik.usporiadanyVypisMiest();
				break;
			case 9:
				manazerik.usporiadanyVypisCiest();
				break;
			case 0:
				test = false;
				std::cout << "Dovidenia.\n";
				break;
		}
	}
	return 0;
}