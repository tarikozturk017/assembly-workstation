// Name: Tarik Ozturk
// Seneca Student ID: 155237209
// Seneca email: tozturk1@myseneca.ca
// Date of completion: 2022/08/07
//
// I confirm that I am the only author of this file
//   and the content was created entirely by me.

#ifndef SDDS_UTILITIES_H_
#define SDDS_UTILITIES_H_
#include <string>

namespace sdds {

	class Utilities {
		size_t m_widthField = 0u;
		static char m_delimiter;
	public:
		Utilities();
		void setFieldWidth(size_t newWidth);
		size_t getFieldWidth()const;
		std::string extractToken(const std::string& str, size_t& next_pos, bool& more);
		virtual ~Utilities();
		static void setDelimiter(char newDelimiter);
		static char getDelimiter();
		std::string trim(std::string& str) const; 
	};



}
#endif // !SDDS_UTILITIES_H_