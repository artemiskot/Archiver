#pragma once

#include <string>
#include <vector>
#include <iostream>
#include <iomanip>
#include <fstream>
/** \brief ������� � 16�� ������� ��������� */
void print_hex(const unsigned char* buffer, int size); 

enum class command_t
{
	/** \brief ���������� ������ � �����*/
	_add,
	/** \brief ������������ ������*/
	_extract,
	/** \brief �������� ������ �� ������*/
	_delete,
	/** \brief ������ ������, ������� ���� � ������*/
	_list
};

class command_line
{
public:
	/** \brief ����������� */
	command_line()
		:m_command(command_t::_add)
	{

	}
	/** \brief �������� ������ ��������*/
	command_t get_command()
	{
		return m_command;
	}
	/** \brief �������� ��� ������ */
	const std::string& get_archive_name() const
	{
		return m_archive_name;
	}
	/** \brief �������� ����� ������*/
	const std::vector<std::string>& get_file_names() const
	{
		return m_file_names;
	}
	/** \brief ��������� ������ ������� ������, ��� ������ � ����*/
	void set_file_names(std::vector<std::string> file_names)
	{
		m_file_names = file_names;
	}
	/** \brief ������������� ��� ������*/
	void set_archive_name(std::string archive_name)
	{
		m_archive_name = archive_name;
	}

	bool parse(int argc, char* argv[]);
	/** \brief ��������� ����� ������*/
	void parse_file_names(int argc, char* argv[]);
	void print();
	/** \brief ������� ������ ������*/
	void print_command_list();
	/** \brief ������� ������� ��������*/
	static void progress_bar();
private:
	/** \brief ����� ������� �������*/
	command_t					m_command;
	/** \brief ��� ������*/
	std::string					m_archive_name;
	/** \brief ����� ������*/
	std::vector<std::string>	m_file_names;
};

class file_header
{
public:
	/** \brief ������������� ��� �����*/
	void set_name(const std::string& name)
	{
		m_name = name;
	}
	/** \brief �������� ��� �����*/
	const std::string& get_name()
	{
		return m_name;
	}
	/** \brief ������������� ������ �����*/
	void set_size(int64_t size)
	{
		m_size = size;
	}
	/** \brief �������� ������ �����*/
	int64_t get_size()
	{
		return m_size;
	}
	/** \brief ���������� � ����� ������ ���� ����� � ������*/
	void set_first_byte(int64_t first_byte)
	{
		m_first_byte = first_byte;
	}
	/** \brief �������� �� ������ ������ ���� �����*/
	int64_t get_first_byte()
	{
		return m_first_byte;
	}
private:
	/** \brief ��� �����*/
	std::string m_name;
	/** \brief ������ �����*/
	int64_t m_size;
	/** \brief ������ ���� �����*/
	int64_t m_first_byte;
};

class archivator_info
{
public:
	/**
	* \brief ��������� ���������� � �����, ������, ��� 
	*/
	void get_file_info(const std::string& file_name, file_header& fh); 
	/** \brief ����� ��������� ����� �� ���� �����*/
	std::string get_file_name(std::string const& path);
	/** \brief �������� ������ �����*/
	std::ifstream::pos_type get_file_size(const std::string& filename);

	/** \brief ��������� �������*/
	void construct_header(std::vector<std::string>& file_paths,std::vector<file_header>& headers, bool flag);
	/** \brief ��������� ������*/
	void pack(const command_line& cl); 
	/** \brief ������������ ������*/
	void unpack(const command_line& cl); 
	/** \brief �������� ������*/
	void delete_file(const command_line& cl); 
	/** \brief ������ ������ � ������*/
	void list(const command_line& cl); 

	/** \brief ����� ��������� �����*/
	void write_header(std::ofstream& out, const std::vector<file_header>& headers); 
	/** \brief ����� ������ �� ����� � �����*/
	void write_file(std::ofstream& out,std::string file_name); 
	/** \brief ����� �������� ������������� �����*/
	static void check_file(std::string file_name); 
	/** \brief ��������� ���������� �� ���������*/
	void get_header_info(std::ifstream& in, std::vector<file_header>& files); 
	/** \brief ������ ������ �� ������*/
	void rewrite_files(std::ifstream& in, std::ofstream& out, file_header file, bool action); 
	/** \brief ������� �� int64 � ����������� ����*/
	void int64ToChar(unsigned char mesg[], int64_t num);
	/** \brief ����� XOR ����������*/
	void XOR_cipher_decipher(char& orignal_char);
	/** \brief ������� �� ����������� ���� � int64*/
	int64_t charTo64bitNum(unsigned char a[]);
private:
	/** \brief �������� ������������� ������*/
	void check_add_file_paths(const std::vector<std::string>& file_names);
private:
	/** \brief ������, �������� ���������� � ������*/
	std::vector<file_header> file_info;
	std::string name = "";
	/** \brief ���-�� ������*/
	int file_amount = 0; 
	/** \brief ��������� ������*/
	char signature[6] = "art25"; 

};
