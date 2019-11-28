/***************************************
 * Author: Emilio E. G. Cantón Bermúdez
 * Date: 14/09/2019
***************************************/


/***************Compile**************/
	// g++ (GCC) 8.3.1
	// g++ example.cpp LanguageGenerator.cpp
/***************Run**************/
	//a.out

#include "LanguageGenerator.h"

int main(int argc, char const *argv[])
{
	LanguageGenerator g = LanguageGenerator();
	g.find_strings("example.txt");
	return 0;
}
