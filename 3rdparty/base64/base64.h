#pragma once

#include <string>

std::string encode_base64(const void* data, const size_t len);
std::string decode_base64(const void* data, const size_t len);
std::string decode_base64(const std::string& str64);
