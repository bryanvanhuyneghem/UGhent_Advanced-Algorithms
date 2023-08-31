#pragma once

#include <string>

std::string compress_lzw(const std::string& input);
std::string decompress_lzw(const std::string& input);