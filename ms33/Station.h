// Name: Tarik Ozturk
// Seneca Student ID: 155237209
// Seneca email: tozturk1@myseneca.ca
// Date of completion: 2022/08/07
//
// I confirm that I am the only author of this file
//   and the content was created entirely by me.


#ifndef SDDS_STATION_H_
#define SDDS_STATION_H_
#include <string>
namespace sdds {

	class Station {
		int m_id = {};
		std::string m_name = {};
		std::string m_desc = {};
		size_t m_nexSerNum = {};
		size_t m_numOfItem = {};

		static size_t m_widthField;
		static size_t id_generator;
	public:
		Station();
		Station(const std::string& str);
		const std::string& getItemName() const;
		size_t getNextSerialNumber();
		size_t getQuantity() const;
		void updateQuantity();
		void display(std::ostream& os, bool full) const;
		virtual ~Station();
	};


}

#endif	// !SDDS_STATION_H_