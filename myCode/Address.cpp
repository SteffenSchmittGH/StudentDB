/*
 * Address.cpp
 *
 *  Created on: 10.01.2025
 *      Author: schmi
 */

#include "Address.h"
using namespace std;
Address::Address()
{
	// TODO Auto-generated constructor stub
	m_postalCode = 00000;
}

Address::Address(std::string street, unsigned short ZIP, std::string cityName,
		std::string additionalInfo)
{
	m_additionalInfo = additionalInfo;
	m_cityName = cityName;
	m_street = street;
	m_postalCode = ZIP;
}

Address::~Address()
{
	// TODO Auto-generated destructor stub
}

string Address::getStreet() const
{
	return m_street;
}

unsigned short Address::getPostalCode() const
{
	return m_postalCode;
}

string Address::getCityName() const
{
	return m_cityName;
}

string Address::getAdditionalInfo() const
{
	return m_additionalInfo;
}

void Address::write(ostream &out)
{
	out << m_street << ";" << m_postalCode << ";" << m_cityName << ";"
			<< m_additionalInfo;
	return;
}

void Address::read(std::istream &in)
{
	string streetName;
	getline(in, streetName, ';');
	m_street = streetName;
	string plz;
	getline(in, plz, ';');
	int i_plz = 0;
	i_plz = stoi(plz);
	unsigned short s_plz = static_cast<unsigned short>(i_plz);
	m_postalCode = s_plz;
	string city;
	getline(in, city, ';');
	m_cityName = city;
	string addInfo;
	if (getline(in, addInfo))
	{
		m_additionalInfo = addInfo;
	}
	else
	{
		m_additionalInfo = "No additional Info";
	}

	return;
}
