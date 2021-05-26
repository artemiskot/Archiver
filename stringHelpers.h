#pragma once 

#include <string>
#include <vector>
/** \brief ��������� �������� ����� � 16�� */
void bin2hex( unsigned char b, std::vector<unsigned char>& res );
/** \brief ��������� ���������� ��� � 16��*/
void uCharsToHex (unsigned char* aData, size_t aSize, std::string& res);
/**  \brief �������� � 16��� ����� */
std::string toHex (const unsigned char* aData, int aSize);
