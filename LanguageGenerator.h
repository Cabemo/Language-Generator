/***************************************
 * Author: Emilio E. G. Cantón Bermúdez
 * Date: 14/09/2019
***************************************/
#ifndef __LANGUAGEGENERATOR_H_INCLUDED__
#define __LANGUAGEGENERATOR_H_INCLUDED__

//dependencies
#include <math.h>
#include <stdlib.h>
#include <stdio.h>
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <map>

class LanguageGenerator
{
private:
	char valid[6] = {'u', 'v', 'w', 'x', 'y', 'z'};
	std::vector<std::string> R;
	std::map<std::string, int> language;

	void print_language(u_int N);
	std::vector<std::vector<std::string>> generate_combinations(std::vector<std::string>);
	std::string replace_lambda(std::string s);
	void r(u_int N);
	void applyRS(u_int N);
public:
	LanguageGenerator();
	void find_strings(std::string file);
};
#endif