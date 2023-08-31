#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN // This tells Doctest to provide a main() - only do this in one cpp file
#include "doctest/doctest.h"
#include "lzw.h"
#include <fstream>
#include <sstream>
using std::ifstream;
using std::ios_base;
using std::ostringstream;
using std::runtime_error;
using std::string;
using std::vector;


TEST_CASE("Compress and decompress")
{
	std::string voorbeeld = "hottentottententententoonstellingen";

	std::string compressed = compress_lzw(voorbeeld);
	std::string decompressed = decompress_lzw(compressed);

	REQUIRE(decompressed == voorbeeld);
	INFO("Compressed from  " << voorbeeld.size() << "bytes to " << compressed.size() << " bytes");
}

TEST_CASE("Compress a single character text")
{
	std::string singlecharactertext(10000,'a');

	std::string compressed = compress_lzw(singlecharactertext);
	std::string decompressed = decompress_lzw(compressed);

	REQUIRE((100 * compressed.size()) / decompressed.size() < 3); // compress to less than 2% of original size
	if (decompressed != singlecharactertext)
	{
		INFO("Decompressed and original text do not match");
		REQUIRE(false);
	}
}


string lees(string filename)
{
	ifstream stream("files/" + filename, ios_base::in | ios_base::binary);
	if (!stream.is_open())
	{
		throw runtime_error("Could not open '" + filename + "'");
	}
	ostringstream sstream;
	sstream << stream.rdbuf();

	stream.close();

	return sstream.str();
}

TEST_CASE("Compress lingtext")
{
	std::string lingtext = lees("lingtext");

	std::string compressed = compress_lzw(lingtext);
	std::string decompressed = decompress_lzw(compressed);

	int compressiefactor = (100 * compressed.size()) / decompressed.size(); 
	REQUIRE( compressiefactor < 60); // compress to less than 60% of original size
	if (decompressed != lingtext)
	{
		INFO("Decompressed and original text do not match");
		REQUIRE(false);
	}
	else{
		std::cout << "Compressiefactor [lingtext]: " << compressiefactor << std::endl; 
	}
}

TEST_CASE("Compress wgs_caam_env")
{
	std::string wgs_caam_env = lees("wgs_caam_env.seq");

	std::string compressed = compress_lzw(wgs_caam_env);
	std::string decompressed = decompress_lzw(compressed);

	int compressiefactor = (100 * compressed.size()) / decompressed.size(); 
	REQUIRE(compressiefactor < 31); // compress to less than 44% of original size
	if (decompressed != wgs_caam_env)
	{
		INFO("Decompressed and original text do not match");
		REQUIRE(false);
	}
	else{
		std::cout << "Compressiefactor [wgs_caam_env]: " << compressiefactor << std::endl; 
	}
}
