#pragma once

#include <string>
#include <vector>
#include <iostream>
#include <iomanip>
#include <fstream>
/** \brief выводит в 16ой системе счисления */
void print_hex(const unsigned char* buffer, int size); 

enum class command_t
{
	/** \brief добавление файлов в архив*/
	_add,
	/** \brief разархивация файлов*/
	_extract,
	/** \brief удаление файлов из архива*/
	_delete,
	/** \brief список файлов, которые есть в архиве*/
	_list
};

class command_line
{
public:
	/** \brief конструктор */
	command_line()
		:m_command(command_t::_add)
	{

	}
	/** \brief получает нужную комманду*/
	command_t get_command()
	{
		return m_command;
	}
	/** \brief получает имя архива */
	const std::string& get_archive_name() const
	{
		return m_archive_name;
	}
	/** \brief получает имена файлов*/
	const std::vector<std::string>& get_file_names() const
	{
		return m_file_names;
	}
	/** \brief заполняет вектор именами файлов, для работы с ними*/
	void set_file_names(std::vector<std::string> file_names)
	{
		m_file_names = file_names;
	}
	/** \brief устанавливает имя архива*/
	void set_archive_name(std::string archive_name)
	{
		m_archive_name = archive_name;
	}

	bool parse(int argc, char* argv[]);
	/** \brief считывает имена файлов*/
	void parse_file_names(int argc, char* argv[]);
	void print();
	/** \brief выводит список команд*/
	void print_command_list();
	/** \brief выводит полоску загрузки*/
	static void progress_bar();
private:
	/** \brief какая команда выбрана*/
	command_t					m_command;
	/** \brief имя архива*/
	std::string					m_archive_name;
	/** \brief имена файлов*/
	std::vector<std::string>	m_file_names;
};

class file_header
{
public:
	/** \brief устанавливает имя файла*/
	void set_name(const std::string& name)
	{
		m_name = name;
	}
	/** \brief получает имя файла*/
	const std::string& get_name()
	{
		return m_name;
	}
	/** \brief устанавливает размер файла*/
	void set_size(int64_t size)
	{
		m_size = size;
	}
	/** \brief получает размер файла*/
	int64_t get_size()
	{
		return m_size;
	}
	/** \brief записывает в хедер первый байт файла в архиве*/
	void set_first_byte(int64_t first_byte)
	{
		m_first_byte = first_byte;
	}
	/** \brief получает из хедера первый байт файла*/
	int64_t get_first_byte()
	{
		return m_first_byte;
	}
private:
	/** \brief имя файла*/
	std::string m_name;
	/** \brief размер файла*/
	int64_t m_size;
	/** \brief первый байт файла*/
	int64_t m_first_byte;
};

class archivator_info
{
public:
	/**
	* \brief получение информации о файле, размер, имя 
	*/
	void get_file_info(const std::string& file_name, file_header& fh); 
	/** \brief метод получения имени из пути файла*/
	std::string get_file_name(std::string const& path);
	/** \brief получает размер файла*/
	std::ifstream::pos_type get_file_size(const std::string& filename);

	/** \brief принимает команды*/
	void construct_header(std::vector<std::string>& file_paths,std::vector<file_header>& headers, bool flag);
	/** \brief архивация файлов*/
	void pack(const command_line& cl); 
	/** \brief разархивация файлов*/
	void unpack(const command_line& cl); 
	/** \brief удаление файлов*/
	void delete_file(const command_line& cl); 
	/** \brief список файлов в архиве*/
	void list(const command_line& cl); 

	/** \brief метод архивации файла*/
	void write_header(std::ofstream& out, const std::vector<file_header>& headers); 
	/** \brief метод записи из файла в архив*/
	void write_file(std::ofstream& out,std::string file_name); 
	/** \brief метод проверки существования файла*/
	static void check_file(std::string file_name); 
	/** \brief получение информации из заголовка*/
	void get_header_info(std::ifstream& in, std::vector<file_header>& files); 
	/** \brief запись файлов из архива*/
	void rewrite_files(std::ifstream& in, std::ofstream& out, file_header file, bool action); 
	/** \brief перевод из int64 к символьному типу*/
	void int64ToChar(unsigned char mesg[], int64_t num);
	/** \brief метод XOR шифрования*/
	void XOR_cipher_decipher(char& orignal_char);
	/** \brief перевод из символьного типа к int64*/
	int64_t charTo64bitNum(unsigned char a[]);
private:
	/** \brief проверка существования файлов*/
	void check_add_file_paths(const std::vector<std::string>& file_names);
private:
	/** \brief вектор, хранящий информацию о файлах*/
	std::vector<file_header> file_info;
	std::string name = "";
	/** \brief кол-во файлов*/
	int file_amount = 0; 
	/** \brief сигнатура архива*/
	char signature[6] = "art25"; 

};
