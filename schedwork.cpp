#ifndef RECCHECK
#include <set>
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <map>
#include <algorithm>
#endif

// add or remove necessary headers as you please
#include "schedwork.h"

using namespace std;

// a constant that can be used to indicate an INVALID 
// worker ID if that is useful to your implementation.
// Feel free to not use or delete.
static const Worker_T INVALID_ID = (unsigned int)-1;


// Add prototypes for any helper functions here


// Add your implementation of schedule() and other helper functions here

bool scheduleHelper(const AvailabilityMatrix& avail, const size_t dailyNeed, const size_t maxShifts, DailySchedule& sched, int day, int slot, map<int, int>& workerShifts){
	if(day == avail.size()){
		return true;
	}
	for(int i = 0; i < avail[0].size(); i++){
		if(avail[day][i] == 1 && workerShifts[i] < maxShifts){
			workerShifts[i]++;
			sched[day][slot] = i; 

			bool pastRec = false; 
			if(slot + 1 == dailyNeed){
				// haveTheyWorked[i] = true;
				pastRec = scheduleHelper(avail, dailyNeed, maxShifts, sched, day + 1, 0, workerShifts);	
				// haveTheyWorked[i] = false;
				

			}
			else{
				// haveTheyWorked[i] = false;
				pastRec = scheduleHelper(avail, dailyNeed, maxShifts, sched, day, slot + 1, workerShifts);
				// haveTheyWorked[i] = true;
				
			}
			if(pastRec == true){ //check if to stop
				return true;
			}
			else{
				workerShifts[i]--;
				sched[day][slot] = INVALID_ID; 
			}
		}

	}
	return false;
	
	// for(int i = 0; i < avail[0].size(); i++){ //iterate thru the workers
	// 	for(int i = 0; i < avail.size(); j++){
	// 		if(avail[i][j] = 1){ //worker is avaiable
	// 			if(workerShifts[i] < maxShifts){ //worker hasn't passed maxShifts
	// 				workerShifts[i]++; //increment days worked
	// 				scheduleHelper(avail, dailyNeed, maxShifts, sched, day, slot + 1, workerShifts);

	// 			}
	// 			else{
	// 				break;
	// 			}
	// 	}
	// 	else{
	// 		continue; 
	// 	}
	// 	continue; 
	// 	}
	// }
}

bool schedule(
    const AvailabilityMatrix& avail,
    const size_t dailyNeed,
    const size_t maxShifts,
    DailySchedule& sched
)
{
    if(avail.size() == 0U){
        return false;
    }
    sched.clear();
    // Add your code below
		map<int, int> workerShifts;


		for(int i = 0; i < avail.size(); i++){
			vector<Worker_T> slot(dailyNeed, INVALID_ID);
			sched.push_back(slot);
		}


		for(int i = 0; i < avail[0].size(); i++){
			workerShifts[i] = 0; 
		}

		return scheduleHelper(avail, dailyNeed, maxShifts, sched, 0, 0, workerShifts);
}

