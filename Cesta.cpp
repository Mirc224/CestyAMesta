#include "Cesta.h"
#include "Mesto.h"

Cesta::Cesta(TypCiest typ, std::string meno, Mesto* pociatocne, Mesto* koncove, int rychlost) : m_pociatocne(pociatocne), m_koncove(koncove), m_typCesty(typ), m_nazov(meno), m_rychlost(rychlost)
{
}

std::string Cesta::toString()
{
	std::string vypis;
	vypis = m_pociatocne->getNazov() + " - " + m_koncove->getNazov() + ", " + m_nazov + ", " + std::to_string(m_rychlost) + ", ";
	if (m_typCesty == JEDNOSMERKA)
		vypis += "jednosmerka\n";
	else
		vypis += "obojsmerka\n";
	return vypis;
}

void Cesta::vypis(std::ostream & os)
{
	os << m_typCesty << "," << m_nazov << ","<< m_pociatocne->getNazov() << "," << m_koncove->getNazov() << "," << m_rychlost << std::endl;
}

Cesta::~Cesta()
{

}
