#include <iostream>
#include <tuple>
#include "lzw.h"
#include <cstring>

int main()
{
	std::cout << "\n\t\tVoorbeeld 1\n" << std::endl;
	std::string voorbeeld = "ABRACADABRABRABRA";
	std::cout << "invoer      : " << voorbeeld << "\n";
	std::string compressed = compress_lzw(voorbeeld);
	std::cout  << "Compressed: " << compressed << "\n";
	std::string decompressed = decompress_lzw(compressed);
	std::cout << "Decompressed: " << decompressed << "\n";
	
	std::cout << "Gecomprimeerd van " << voorbeeld.size() << " bytes naar " << compressed.size() << " bytes\n";
	if(voorbeeld.compare(decompressed)!= 0){
		std::cout << "Voorbeeld 1 decompressie is nog niet juist " << std::endl;
	}

	std::cout << "\n\t\tVoorbeeld 2\n" << std::endl;
	std::string voorbeeld2 = "TOBEORNOTTOBE";
	std::cout << "invoer      : " << voorbeeld2 << "\n";
	std::string compressed2 = compress_lzw(voorbeeld2);
	std::cout  << "Compressed: " << compressed2 << "\n";
	std::string decompressed2 = decompress_lzw(compressed2);
	std::cout << "Decompressed: " << decompressed2 << "\n";
	std::cout << "Gecomprimeerd van " << voorbeeld2.size() << " bytes naar " << compressed2.size() << " bytes\n";
	if(voorbeeld2.compare(decompressed2)!= 0){
		std::cout << "Voorbeeld 2 decompressie is nog niet juist " << std::endl;
	}

	std::cout << "\n\t\tVoorbeeld 3\n" << std::endl;
	std::string voorbeeld3(1000, 'a'); //1000x a na elkaar
	std::string compressed3 = compress_lzw(voorbeeld3);
	std::cout << "Compressed: " << compressed3 << "\n";
	std::string decompressed3 = decompress_lzw(compressed3);
	std::cout << "Decompressed: " << decompressed3 << "\n";
	std::cout << "Gecomprimeerd van " << voorbeeld3.size() << " bytes naar " << compressed3.size() << " bytes\n";
	if(voorbeeld3.compare(decompressed3)!= 0){
		std::cout << "Voorbeeld 3 decompressie is nog niet juist " << std::endl;
	}
}
