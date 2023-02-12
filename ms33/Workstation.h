// Name: Tarik Ozturk
// Seneca Student ID: 155237209
// Seneca email: tozturk1@myseneca.ca
// Date of completion: 2022/08/07
//
// I confirm that I am the only author of this file
//   and the content was created entirely by me.

#ifndef SDDS_WORKSTATION_H_
#define SDDS_WORKSTATION_H_
#include <deque>
#include "CustomerOrder.h"
#include "Station.h"
namespace sdds {

	extern std::deque<CustomerOrder> g_pending;
	extern std::deque<CustomerOrder> g_completed;
	extern std::deque<CustomerOrder> g_incomplete;

	class Workstation : public Station {
		std::deque<CustomerOrder> m_orders;
		Workstation* m_pNextStation = nullptr;

	public:
		Workstation();
		Workstation(const std::string& str);
		Workstation(const Workstation&) = delete;
		Workstation& operator=(const Workstation&) = delete;
		Workstation(Workstation&&) = delete;
		Workstation& operator=(Workstation&&) = delete;
		void fill(std::ostream& os);
		bool attemptToMoveOrder();
		void setNextStation(Workstation* station = nullptr);
		Workstation* getNextStation()const;
		void display(std::ostream& os)const;
		Workstation& operator+=(CustomerOrder&& newOrder);
		virtual ~Workstation();
	};
}

#endif	// !SDDS_WORKSTATION_H_