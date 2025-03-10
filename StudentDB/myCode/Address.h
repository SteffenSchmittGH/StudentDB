/*
 * Address.h
 *
 *  Created on: 10.01.2025
 *      Author: schmi
 */

#ifndef ADDRESS_H_
#define ADDRESS_H_
#include <string>
#include <iostream>
class Address
{
private:
	/**
	 * @brief Street address of the location.
	 *
	 * This member variable holds the street name of the address.
	 */
	std::string m_street;

	/**
	 * @brief Postal code of the address.
	 *
	 * This member variable stores the postal code (ZIP code) of the address as
	 * an unsigned short.
	 */
	unsigned short m_postalCode;

	/**
	 * @brief Name of the city.
	 *
	 * This member variable contains the name of the city associated with the
	 * address.
	 */
	std::string m_cityName;

	/**
	 * @brief Additional information related to the address.
	 *
	 * This member variable holds any extra details regarding the address,
	 * such as suite or apartment number.
	 * If no additional info is provided, it may store a default value.
	 */
	std::string m_additionalInfo;
public:
	Address();

	/**
	 * @brief Constructs an Address object with provided details.
	 *
	 * This constructor initializes the address with the given street,
	 * postal code, city name, and any additional information such as apartment
	 * numbers or special instructions.
	 * It assigns the provided values to the respective member variables of
	 * the Address object.
	 */
	Address(std::string street, unsigned short ZIP, std::string cityName,
												    std::string additionalInfo);
	virtual ~Address();

	/**
	 * @brief Retrieves the street name of the address.
	 *
	 * This function returns the street name as a string.
	 */
	std::string getStreet() const;

	/**
	 * @brief Retrieves the postal Code of the address.
	 *
	 * This function returns postalCode as an unsigned int.
	 */
	unsigned short getPostalCode() const;

	/**
	 * @brief Retrieves the city name of the address.
	 *
	 * This function returns city naem as an string.
	 */
	std::string getCityName() const;

	/**
	 * @brief Retrieves the additional Info of the address.
	 *
	 * This function returns additional  as an string.
	 */
	std::string getAdditionalInfo() const;

	/**
	 * @brief Writes the address information to the output stream.
	 *
	 * This function formats and outputs the street, postal code, city name,
	 * and additional information of the address to the provided output stream.
	 *
	 * @param[out] out The output stream to which the address information will
	 * be written.
	 */
	void write(std::ostream& out);

	/**
	 * @brief Reads address information from an input stream.
	 *
	 * This function extracts the street, postal code, city name, and additional
	 * information from the input  stream, and assigns them to the
	 * corresponding member variables of the Address object.
	 * If no additional information is provided, a default message is used.
	 *
	 * @param[in] in The input stream from which the address information will be
	 * read.
	 */
	void read(std::istream& out);
};

#endif /* ADDRESS_H_ */
