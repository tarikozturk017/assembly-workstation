// Name: Tarik Ozturk
// Seneca Student ID: 155237209
// Seneca email: tozturk1@myseneca.ca
// Date of completion: 2022/08/07
//
// I confirm that I am the only author of this file
//   and the content was created entirely by me.

#include <iomanip>
#include <algorithm>
#include <exception>
#include <vector>
#include <deque>
#include <iostream>
#include "CustomerOrder.h"
#include "Utilities.h"


using namespace std;
namespace sdds {
   Utilities utility;
   size_t CustomerOrder::m_widthField = 0;
   CustomerOrder::CustomerOrder() {
      //
   }

   CustomerOrder::CustomerOrder(const std::string& str) {
      if (str != "") {
         std::deque<string> objs;
         size_t position = 0;
         bool more = true;
         while (more == true) {
            objs.push_back(utility.extractToken(str, position, more));
         }
         //get name
         m_name = objs.front();
         objs.pop_front();
         //get product
         m_product = objs.front();
         objs.pop_front();

         if (m_widthField < utility.getFieldWidth())  
             m_widthField = utility.getFieldWidth();
         m_cntItem = objs.size();
         m_lstItem = new Item* [m_cntItem];
         for (size_t i = 0; i < m_cntItem; i++) m_lstItem[i] = new Item(objs[i]);
      }
   }

   CustomerOrder::CustomerOrder(const CustomerOrder&) {
       throw "Copy constructor is not allowed!";
   }
   CustomerOrder::CustomerOrder(CustomerOrder&& co) noexcept {
      *this = move(co);
   }
   //CustomerOrder& operator=(const CustomerOrder& co) = delete;
   CustomerOrder& CustomerOrder::operator=(CustomerOrder&& co) noexcept {
      if (this != &co) {
         for (size_t i = 0; i < m_cntItem; i++) {
            delete m_lstItem[i];
            m_lstItem[i] = nullptr;
         }
         delete[] m_lstItem;
         m_lstItem = nullptr;
         m_lstItem = co.m_lstItem;
         m_name = co.m_name;
         m_product = co.m_product;
         m_cntItem = co.m_cntItem;
         co.m_name = "";
         co.m_product = "";
         co.m_lstItem = nullptr;
         co.m_cntItem = 0;
      }
      return *this;
   }

   CustomerOrder::~CustomerOrder() {
      for (size_t i = 0; i < m_cntItem; i++) {
         delete m_lstItem[i];
         m_lstItem[i] = nullptr;
      }
      delete [] m_lstItem;
      m_lstItem = nullptr;
   }

   bool CustomerOrder::isOrderFilled()const {
      bool isAllFilled = true;
      for (size_t i = 0; i < m_cntItem && isAllFilled; i++) {
         if (!m_lstItem[i]->m_isFilled) isAllFilled = false;
      }
      return isAllFilled;
   }

   bool CustomerOrder::isItemFilled(const std::string& itemName)const {
       bool isFound = false, result = true;
      std::vector<Item*> matches;
      for (size_t i = 0; i < m_cntItem; i++) {
         if (m_lstItem[i]->m_itemName == itemName) {
            isFound = true;
            matches.push_back(m_lstItem[i]);
         }
      }

      if (isFound == true) {
          result = all_of(matches.begin(), matches.end(), [](const Item* ptr) {
              return ptr->m_isHandled == true; 
              });
      }
      return result;
   }

   void CustomerOrder::fillItem(Station& station, std::ostream& os) {
      bool check = true;
      /*for (size_t i = 0; i < m_cntItem; i++) {
          if (m_lstItem[i]->m_itemName == station.getItemName()) {
              if (station.getQuantity() > 0) {
                  station.updateQuantity();
                  m_lstItem[i]->m_serialNumber = station.getNextSerialNumber();
                  m_lstItem[i]->m_isFilled = true;
                  os << "Filled " << m_name << ", " << m_product << " [" << m_lstItem[i]->m_itemName << "]" << endl;
              }
              else os << "Unable to fill " << m_name << ", " << m_product << " [" << m_lstItem[i]->m_itemName << "]" << endl;
          }
      }*/

      for (size_t i = 0; i < m_cntItem && check; i++) {
         if (m_lstItem[i]->m_itemName == station.getItemName() && m_lstItem[i]->m_isHandled == false) {
            check = false;
            if (station.getQuantity() > 0) {
               station.updateQuantity();
               m_lstItem[i]->m_isFilled = true;
               m_lstItem[i]->m_isHandled = true;
               m_lstItem[i]->m_serialNumber = station.getNextSerialNumber();
               os << "    Filled " << m_name << ", " << m_product << " [" 
                   << station.getItemName() << "]" << std::endl;
            }
            else {
               for (size_t k = 0; k < m_cntItem; k++) {
                  if (m_lstItem[k]->m_itemName == station.getItemName() && m_lstItem[k]->m_isHandled == false) {
                     m_lstItem[k]->m_isHandled = true;
                     os << "    Unable to fill " << m_name << ", " << m_product 
                         << " [" << station.getItemName() << "]" << std::endl;
                  }
               }
            }
         }
      }
   }


   void CustomerOrder::display(std::ostream& os) const {
      os << m_name << " - " << m_product << endl;
      for (size_t i = 0; i < m_cntItem; i++) {
         os << "[" << setw(6) << setfill('0') << m_lstItem[i]->m_serialNumber << "] " << setfill(' ');
         os.setf(ios::left);
         os << setw(m_widthField) << m_lstItem[i]->m_itemName << "   - ";
         os.unsetf(ios::left);
         if (m_lstItem[i]->m_isFilled) os << "FILLED" << endl;
         else os << "TO BE FILLED" << endl;
         
      }
   }


}