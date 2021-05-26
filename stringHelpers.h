#pragma once 

#include <string>
#include <vector>
/** \brief переводит двоичное число в 16ое */
void bin2hex( unsigned char b, std::vector<unsigned char>& res );
/** \brief переводит символьный тип в 16ый*/
void uCharsToHex (unsigned char* aData, size_t aSize, std::string& res);
/**  \brief приводит к 16ому числу */
std::string toHex (const unsigned char* aData, int aSize);
