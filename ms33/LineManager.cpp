// Name: Tarik Ozturk
// Seneca Student ID: 155237209
// Seneca email: tozturk1@myseneca.ca
// Date of completion: 2022/08/07
//
// I confirm that I am the only author of this file
//   and the content was created entirely by me.

#include <iostream>
#include <algorithm>
#include <fstream>
#include <string>
#include "LineManager.h"
#include "Utilities.h"


using namespace std;

namespace sdds {
    LineManager::LineManager() {
        //
    }
    LineManager::~LineManager() {
        //
    }

    LineManager::LineManager(const std::string& file, const std::vector<Workstation*>& stations) {
        Utilities utility;

        ifstream f(file);
        if (!f) 
            throw string("Unable to open the file");
        else {
            string line;
            vector<string> lines;
            while (!f.eof()) {
                std::getline(f, line);
                lines.push_back(line);
            }
            f.close();

            string current = "", next = "";
        
            std::vector<string> n_objs;
            for (auto& l : lines) {
                size_t position = 0;
                bool more = true;
                current = utility.extractToken(l, position, more);
                next = more ? utility.extractToken(l, position, more) : "";
                auto curIterator = find_if(stations.begin(), stations.end(), [=](const Workstation* ptr) {
                    return ptr->getItemName() == current; 
                    });
                auto nextItr = find_if(stations.begin(), stations.end(), [=](const Workstation* ptr) {
                    return ptr->getItemName() == next; 
                    });

                // if current iterator is not end stations
                if (curIterator != stations.end()) {
                    //push current
                    m_activeLine.push_back(*curIterator);
                    (*curIterator)->setNextStation((nextItr != stations.end()) ? *nextItr : nullptr);
                }
                if (next != "") n_objs.push_back(next);
            }

            for (auto& active : m_activeLine) {
                if (none_of(n_objs.begin(), n_objs.end(), [&](const string str) {
                    return str == active->getItemName(); 
                    })) {
                    m_firstStation = active;
                }
            }
        }
        m_cntCustomerOrder = g_pending.size();
    }


    void LineManager::reorderStations() {
        vector<Workstation*> l_reorder;
        /*Workstation* station = m_firstStation;*/
        l_reorder.push_back(m_firstStation);

        while (l_reorder.back()->getNextStation()) {
            auto i = find(m_activeLine.begin(), m_activeLine.end(), l_reorder.back()->getNextStation());
            l_reorder.push_back(*i);
        }
        m_activeLine = l_reorder;
    }
    

    bool LineManager::run(std::ostream& os) {
        bool toReturn = false;
        static size_t count = 0;

        os << "Line Manager Iteration: " << ++count << endl;
        
        if (!g_pending.empty()) {
            *m_firstStation += move(g_pending.front());
            g_pending.pop_front();
        }
        
        for (size_t i = 0u; i < m_activeLine.size(); i++)
            m_activeLine[i]->fill(os);
        for (size_t i = 0u; i < m_activeLine.size(); i++)
            m_activeLine[i]->attemptToMoveOrder();
                
        if (g_completed.size() + g_incomplete.size() == m_cntCustomerOrder)     toReturn = true;
        else    toReturn = false;
        return toReturn;
    }
        

    void LineManager::display(std::ostream& os) const {
        for (auto& i : m_activeLine) i->display(os);
    }



}