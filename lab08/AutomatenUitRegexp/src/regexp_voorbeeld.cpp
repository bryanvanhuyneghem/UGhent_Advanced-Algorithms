#include "regexp.h"
#include <iostream>
#include <string>
#include "automaten.h"
using namespace std;

int main(int argc, char *argv[])
{
    Regexp r("(a|b)*a(a|b)");
	DA da(r);

	std::cout << (true == da.zitInTaal("aab")) << "\n";
	
    return 0;
}