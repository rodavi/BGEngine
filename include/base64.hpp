#pragma once
#include <string>
#include <vector>

/**
 * Decodifica una cadena en formato Base64.
 * Utilizada por el LevelParser para leer los IDs de los tiles [2].
 */
std::string base64_decode(std::string const& s);

/**
 * Codifica una cadena de texto a formato Base64.
 */
std::string base64_encode(unsigned char const* bytes_to_encode, unsigned int in_len);

