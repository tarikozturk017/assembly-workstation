// Name: Tarik Ozturk
// Seneca Student ID: 155237209
// Seneca email: tozturk1@myseneca.ca
// Date of completion: 2022/08/07
//
// I confirm that I am the only author of this file
//   and the content was created entirely by me.

#include <iostream>
#include <exception>
#include <string>
#include "Utilities.h"


using namespace std;
namespace sdds {
    char Utilities::m_delimiter{};

    Utilities::Utilities() {
        m_widthField = 1;
    }
    Utilities::~Utilities() {
        //
    }

	std::string Utilities::trim(std::string& str) const {
		while (str[0] == ' ') {
			str.erase(0, str.find_first_not_of(' '));
		}
		while (str[str.size() - 1] == ' ') {
			str.erase(str.find_last_not_of(' ') + 1);
		}
		return str;
	}

    void Utilities::setFieldWidth(size_t newWidth) {
        m_widthField = newWidth;
    }

    size_t Utilities::getFieldWidth()const {
        return m_widthField;
    }


    std::string Utilities::extractToken(const std::string& str, size_t& next_pos, bool& more) {
	int delPos;
	string str2 = "";
	if (str[next_pos] != m_delimiter) {
		string str1 = str.substr(next_pos);		//from next_pos to the end
		if (str1.find_first_of(m_delimiter) != string::npos) {
			delPos = str1.find_first_of(m_delimiter);
			str2 = str1.substr(0, delPos);
			trim(str2);
			next_pos += delPos + 1;	// ?? or next_pos = delPos+1;
			more = true;
		}
		else {
			str2 = trim(str1);
			more = false;
		}
		if (str2.length() > m_widthField) m_widthField = str2.length();
	}
	else {	//otherwise throw error
		more = false;
		throw invalid_argument("Next position is the delimiter");
	}
	return str2;
}

    void Utilities::setDelimiter(char newDelimiter) {
        m_delimiter = newDelimiter;
    }
    char Utilities::getDelimiter() {
        return m_delimiter;
    }
}