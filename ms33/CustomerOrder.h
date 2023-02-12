// Name: Tarik Ozturk
// Seneca Student ID: 155237209
// Seneca email: tozturk1@myseneca.ca
// Date of completion: 2022/08/07
//
// I confirm that I am the only author of this file
//   and the content was created entirely by me.

#ifndef SDDS_CUSTOMERORDER_H_
#define SDDS_CUSTOMERORDER_H_
#include <string>
#include "Station.h"
namespace sdds {

	struct Item {
		std::string m_itemName = {};
		size_t m_serialNumber = { 0 };
		bool m_isFilled = false;
		bool m_isHandled = false;
		Item(const std::string& str) : m_itemName{ str } {	};
	};

	class CustomerOrder {
		std::string m_name = {};
		std::string m_product = {};
		size_t m_cntItem = { 0 };
		Item** m_lstItem = {};
		static size_t m_widthField;

	public:
		CustomerOrder();
		CustomerOrder(const std::string& str);
		CustomerOrder(const CustomerOrder&);
		CustomerOrder& operator=(const CustomerOrder&) = delete;
		CustomerOrder(CustomerOrder&& co) noexcept;
		CustomerOrder& operator=(CustomerOrder&& co) noexcept;
		virtual ~CustomerOrder();
		bool isOrderFilled()const;
		bool isItemFilled(const std::string& itemName)const;
		void fillItem(Station& station, std::ostream& os);
		void display(std::ostream& os)const;
	};
}

#endif	// !SDDS_CUSTOMERORDER_H_