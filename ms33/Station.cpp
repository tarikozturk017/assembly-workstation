// Name: Tarik Ozturk
// Seneca Student ID: 155237209
// Seneca email: tozturk1@myseneca.ca
// Date of completion: 2022/08/07
//
// I confirm that I am the only author of this file
//   and the content was created entirely by me.

#include <iomanip>
#include <string>
#include "Utilities.h"
#include "Station.h"


using namespace std;
namespace sdds {
    size_t Station::m_widthField = 0;
    size_t Station::id_generator = 0;

    Station::Station() {
        // when no arg Station created, increment id-gen
        id_generator++;
    }
    

    Station::Station(const std::string& str) {
        //every time Station created, increment  the id - gen
        id_generator++;
        if (str != "") {
            bool more = true;
            size_t position = 0;
            Utilities utility{};
            
            m_id = id_generator;
            m_name = utility.extractToken(str, position, more);
            m_nexSerNum = stoul(utility.extractToken(str, position, more));
            m_numOfItem = stoul(utility.extractToken(str, position, more));
            if (m_widthField < utility.getFieldWidth())  
                m_widthField = utility.getFieldWidth();
            m_desc = utility.extractToken(str, position, more);
        }
    }
    

    void Station::display(std::ostream& os, bool full) const {
        os << setw(3) << setfill('0') <<  m_id << " | ";
        os.setf(ios::left);
        os << setfill(' ') << setw(m_widthField+1) << m_name << " | ";
        os.unsetf(ios::left);
        os << setw(6) << setfill('0')  << m_nexSerNum << setfill(' ');
        if (full) os << " | " << setw(4) << m_numOfItem << " | " << m_desc << endl;
        else os << " | " << endl;
    }

    const std::string& Station::getItemName() const {
        return m_name;
    }

    size_t Station::getNextSerialNumber() {
        return m_nexSerNum++;
    }

    size_t Station::getQuantity() const {
        return m_numOfItem;
    }

    void Station::updateQuantity() {
        if (m_numOfItem > 0) m_numOfItem--;
    }
    Station::~Station() {
        // do nothing
    }

}