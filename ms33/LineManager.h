// Name: Tarik Ozturk
// Seneca Student ID: 155237209
// Seneca email: tozturk1@myseneca.ca
// Date of completion: 2022/08/07
//
// I confirm that I am the only author of this file
//   and the content was created entirely by me.
#ifndef SDDS_LINEMANAGER_H_
#define SDDS_LINEMANAGER_H_

#include <vector>
#include "Workstation.h"
namespace sdds {
	class LineManager {
		std::vector<Workstation*> m_activeLine;
		size_t m_cntCustomerOrder = 0u;
		Workstation* m_firstStation = nullptr;

	public:
		LineManager();
		LineManager(const std::string& file, const std::vector<Workstation*>& stations);
		void reorderStations();
		bool run(std::ostream& os);
		void display(std::ostream& os)const;
		virtual ~LineManager();
	};


}
#endif	// !SDDS_LINEMANAGER_H_