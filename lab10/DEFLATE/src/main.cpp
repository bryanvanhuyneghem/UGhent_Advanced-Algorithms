#include <iostream>
#include <tuple>
#include "lz77.h"
#include "suffix_array.h"

int main()
{
	std::string voorbeeld = "hottentottententententoonstellingen";

	SuffixArray sa(voorbeeld);

	int lengte, afstand;
	std::tie(lengte, afstand) = sa.zoekHerhaling(0, 6, 29); //geen match
	std::cout << lengte << "," << afstand << "\n";
	std::tie(lengte, afstand) = sa.zoekHerhaling(0, 7, 28); //HOTTENT (match op OTTENT)
	std::cout << lengte << "," << afstand << "\n";
	std::tie(lengte, afstand) = sa.zoekHerhaling(0, 13, 22); //HOTTENTOTTENT (match op ENTENT)
	std::cout << lengte << "," << afstand << "\n";
	std::tie(lengte, afstand) = sa.zoekHerhaling(0, 19, 16); //HOTTENTOTTENTENTENT (match op ENTO, want search buffer groter dan in voorbeeld!)
	std::cout << lengte << "," << afstand << "\n";

	std::string compressed = compress_lz77(voorbeeld);
	std::cout << "Compressed: " << compressed << "\n";
	std::string decompressed = decompress_lz77(compressed);
	std::cout << "Decompressed: " << decompressed << "\n";

	std::cout << "Gecomprimeerd van " << voorbeeld.size() << " bytes naar " << compressed.size() << " bytes\n\n\n";

	std::string voorbeeld2(1000, 'a'); //1000x a na elkaar

	std::string compressed2 = compress_lz77(voorbeeld2);
	std::cout << "Compressed: " << compressed2 << "\n";
	std::string decompressed2 = decompress_lz77(compressed2);
	std::cout << "Decompressed: " << decompressed2 << "\n";

	std::cout << "Gecomprimeerd van " << voorbeeld2.size() << " bytes naar " << compressed2.size() << " bytes\n";
}
