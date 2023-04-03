#ifndef RECCHECK
// For debugging
#include <iostream>
// For std::remove
#include <algorithm> 
#include <map>
#include <set>
#include <queue>
#endif

#include "wordle.h"
#include "dict-eng.h"
using namespace std;


// Add prototypes of helper functions here



void createCombo(string in, queue<char> floating, const set<string>& dict, set<string>& allCombos, size_t index){
		
			set<char> usedChars;

		//count blank spaces
		size_t blankspaces = 0;
		for(size_t i = 0; i < in.length(); i++){
			if(in[i] == '-'){
				blankspaces++;
			}
		}


		if(index == in.length()){
			
			set<string>::iterator it;
			it = dict.find(in);
			if(it != dict.end()){ //found
				allCombos.insert(in);
			}
			return;
		}
		// if(blankspaces == floating.size()){
		// 	if(in[index] != '-'){
		// 		createCombo(in, floating, dict, allCombos, index++);
		// 	}
		// 	else{
		// 		for(int i = 0; i < floating.size(); i++){//floating size
		// 			in[index] = floating.front();
		// 			string erasedChar = floating.front();
		// 			floating.pop();		
		// 			createCombo(in, floating, dict, allCombos, index++);
		// 			//append letter back
		// 			floating.push(erasedChar);
		// 		}
		// 	}
		// }
		if(in[index] == '-'){
			if(blankspaces < floating.size()){
				return;
			}
			for(size_t i = 0; i < floating.size(); i++){
				// set<char>::iterator it;
				char used = floating.front();
				// it = usedChars.find(floating.front());
				// if(it != usedChars.end()){ //found
				// 	return;
				// }
				// else{
					in[index] = floating.front();
					usedChars.insert(used);
					floating.pop();
					createCombo(in, floating, dict, allCombos, index+1);
					floating.push(used);
					in[index] = '-';

				// }
			}
			if(blankspaces == floating.size()){
				return;
			}
			for(size_t i = 97; i < 123; i++){//ascii values
				set<char>::iterator it;
				// char used = static_cast<char>(i);
				it = usedChars.find(static_cast<char>(i));
				if(it != usedChars.end()){ //found
					continue;
				}
				else{
					in[index] = static_cast<char>(i); 
					// usedChars.insert(used);
					createCombo(in, floating, dict, allCombos, index+1);
					in[index] = '-';

					// usedChars.remove(used);
				}
				// in[index] = static_cast<char>(i); 
				// //if i is in flaoting letters remove
				// bool inFloating = false;
				// if(floating.find(i) != string::npos){ //in floating
				// 	floating.erase(floating.find(i), 1);
				// 	inFloating = true;
				// }
				
				// createCombo(in, floating, dict, allCombos, index++);
				// if(inFloating == true){
				// 	floating.insert(floating.end(), i);
				// 	inFloating = false;
				// }
			}
		}
		// if(index - floating.length() <= floating.size()){
		// 	for(int i = 0; i < floating.size(); i++){//floating size
		// 		in[index] = floating[i];
		// 		floating.erase(floating[i]);
		// 		string erasedChar = floating[i];
		// 		createCombo(in, floating, dict, allCombos, index++);
		// 		//append letter back
		// 		floating.insert(floating.end(), erasedChar);
		// 	}
		// }
		else{ //hit the fixed letter
			createCombo(in, floating, dict, allCombos, index+1);
		}
	}

// Definition of primary wordle function
std::set<std::string> wordle(
    const std::string& in,
    const std::string& floating,
    const std::set<std::string>& dict)
{
    // Add your code here
		queue<char> floatingchars;

		for(size_t i = 0; i < floating.length(); i++){
			floatingchars.push(floating[i]);
		}

		
 	set<string> allCombos;
	createCombo(in, floatingchars, dict, allCombos, 0);

	return allCombos;

   

}

// Define any helper functions here
