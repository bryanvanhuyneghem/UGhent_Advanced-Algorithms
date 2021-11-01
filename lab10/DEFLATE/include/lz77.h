#pragma once

#include <string>

std::string compress_lz77(const std::string& input);
std::string decompress_lz77(const std::string& input);
