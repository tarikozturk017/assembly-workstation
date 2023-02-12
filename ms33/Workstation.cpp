// Name: Tarik Ozturk
// Seneca Student ID: 155237209
// Seneca email: tozturk1@myseneca.ca
// Date of completion: 2022/08/07
//
// I confirm that I am the only author of this file
//   and the content was created entirely by me.

#include <iostream>
#include "Workstation.h"

using namespace std;
namespace sdds {
    std::deque<CustomerOrder> g_pending{};
    std::deque<CustomerOrder> g_completed{};
    std::deque<CustomerOrder> g_incomplete{};

    Workstation::Workstation() {
        //
    }

    Workstation::Workstation(const std::string& str) : Station(str) {
        // station initialized with string
    }
   

    void Workstation::fill(std::ostream& os) {
        if (!m_orders.empty())
            m_orders.front().fillItem(*this, os);
    }

    
    // check if this function works in all conditions??
    bool Workstation::attemptToMoveOrder() {
        bool toReturn = false;
        if (!m_orders.empty()) {
            //toReturn = true;
            if (m_orders.front().isItemFilled(getItemName()) || this->getQuantity() == 0) {
                if (m_pNextStation)
                    m_pNextStation->m_orders.push_back(move(m_orders.front()));
                else if (m_orders.front().isOrderFilled())
                    g_completed.push_back(move(m_orders.front()));
                else
                    g_incomplete.push_back(move(m_orders.front()));
                m_orders.pop_front();
                toReturn = true; // set to true here ???
            }
            else toReturn = false;
        }
        return toReturn;
    }

    void Workstation::setNextStation(Workstation* station) {
        m_pNextStation = station;
    }

    Workstation* Workstation::getNextStation()const {
        return m_pNextStation;
    }

    void Workstation::display(std::ostream& os)const {
        os << getItemName() << " --> ";
        if (getNextStation()) os << getNextStation()->getItemName() << endl;
        else os << "End of Line" << endl;
    }

    Workstation& Workstation::operator+=(CustomerOrder&& newOrder) {
        m_orders.push_back(move(newOrder));
        return *this;
    }
    Workstation::~Workstation() {
        // do nothing
    }
}