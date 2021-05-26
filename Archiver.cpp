#include "Archiver.h"
#include "stringHelpers.h"
#include "windows.h"
#include <cstdio>  
#include <filesystem>

#include<iostream>

void print_hex(const unsigned char* buffer, int size)
{
	std::string line = toHex( buffer, size );
	std::cout << line << std::endl;
}
void command_line::progress_bar(){
	float progress = 0.0;
	while (progress < 1.2) {
		int barWidth = 70;

		std::cout << "[";
		int pos = barWidth * progress;
		for (int i = 0; i < barWidth; ++i) {
			if (i < pos) std::cout << "=";
			else if (i == pos) std::cout << ">";
			else std::cout << " ";
		}
		std::cout << "] " << int(progress * 100.0) << " %\r";
		Sleep(100);
		std::cout.flush();
		progress += 0.2; 
	}
	std::cout << std::endl;
}
void command_line::print_command_list() {
	std::cout << "List of commands: " << std::endl;
	std::cout << "#---------------------------------------------------------------------------------------------#" << std::endl;
	std::cout << "|-a to add files to archive (-a tmp.arch tmp.txt) to add tmp.txt file into tmp.arch archive   |" << std::endl;
	std::cout << "|---------------------------------------------------------------------------------------------|" << std::endl;
	std::cout << "|-x to extract all files from archive (-x tmp.arch)                                           |" << std::endl;
	std::cout << "|---------------------------------------------------------------------------------------------|" << std::endl;
	std::cout << "|-d to delete files from archive (-d tmp.arch tmp.txt) to delete tmp.txt from archive tmp.arch|" << std::endl;
	std::cout << "|---------------------------------------------------------------------------------------------|" << std::endl;
	std::cout << "|-l to list all files in archive (-l tmp.arch)                                                |" << std::endl;
	std::cout << "#---------------------------------------------------------------------------------------------#" << std::endl;
}
bool command_line::parse(int argc, char* argv[])
{
	bool result = false;
	if (argc > 2)
	{
		std::string command = argv[1];
		m_archive_name = argv[2];

		if (command == "-a")
		{
			std::cout << "Add "; m_command = command_t::_add;
			result = true;
			parse_file_names(argc, argv);
		}
		else if (command == "-d")
		{
			std::cout << "Delete "; m_command = command_t::_delete;
			result = true;
			parse_file_names(argc, argv);
		}
		if (command == "-x")
		{
			std::cout << "Extract "; m_command = command_t::_extract;
			result = true;
			parse_file_names(argc, argv);
		}
		else if (command == "-l")
		{
			std::cout << "List "; m_command = command_t::_list;
			result = true;
		}
		else if(!result) {
			std::cout << "You've entered wrong command. Try this: " << std::endl;
			print_command_list();
		}
	}
	else if (argc == 1) {
		print_command_list();
	}
	return result;
}

void command_line::parse_file_names(int argc, char* argv[])
{
	for (int i = 3; i < argc; i++)
		m_file_names.push_back(argv[i]);	
	
}

void command_line::print()
{
	std::cout << "File_paths: " << std::endl;
	for (int i = 0; i < m_file_names.size(); i++)
	{
		std::cout << m_file_names[i] << std::endl;
	}
}

void archivator_info::get_file_info(const std::string& file_name, file_header& fh) // метод записи имени и размера файла
{
	std::string name = get_file_name(file_name);
	fh.set_name(name);
	fh.set_size(get_file_size(file_name));
}

// метод получения имени из пути файла
std::string archivator_info::get_file_name(std::string const& path) 
{ 
	return path.substr(path.find_last_of("/\\") + 1); 
} 

std::ifstream::pos_type archivator_info::get_file_size(const std::string& filename) 
{ 
	std::ifstream in(filename, std::ifstream::ate | std::ifstream::binary); return in.tellg(); 
}

void archivator_info::construct_header(std::vector<std::string>& file_paths,std::vector<file_header>& headers, bool flag)
{
	if(flag)
	file_amount = file_paths.size();
	file_header fh;
	for (int i = 0; i < file_paths.size(); i++)
	{
		get_file_info(file_paths[i], fh);
		file_info.push_back(fh);
		headers.push_back(fh);
	}
	int64_t file_header_size = sizeof(signature) - 1 + sizeof(file_amount);

	for (int i = 0; i < headers.size(); i++)
	{
		fh = file_info[i];
		file_header_size += sizeof(fh.get_name().length()) - 2 + fh.get_name().length() + sizeof(fh.get_size()) + sizeof(fh.get_first_byte());
	}
	for (int i = 0; i < headers.size(); i++)
	{
		int64_t first_byte = file_header_size + 1;
		if (i > 0)
		{
			file_header prev_file = file_info[i - 1];
			first_byte = prev_file.get_first_byte() + prev_file.get_size() + 1;
		}
		file_info[i].set_first_byte(first_byte);
		headers[i].set_first_byte(first_byte);
	}
}


void archivator_info::pack(const command_line& cl)
{
	std::string archive_name = cl.get_archive_name();
	std::string archive_name_tmp = archive_name + "tmp";
	std::vector<std::string> file_names; 
	file_names.assign(cl.get_file_names().begin(), cl.get_file_names().end());
	check_add_file_paths(file_names);
	std::vector<file_header> headers;
	
	std::fstream check_file;
	check_file.open(archive_name, std::ios_base::out | std::ios_base::in);
	if (!check_file.is_open())
	{
		check_file.clear();
		check_file.open(archive_name, std::ios_base::binary);
		construct_header(file_names,headers, true);

		std::ofstream archive;
		archive.open(archive_name, std::ios_base::binary);
		if (archive.is_open())
		{
			write_header(archive, file_info);
			for (int i = 0; i < file_names.size(); ++i)
			{
				std::string file_name = file_names[i];
				write_file(archive, file_name);
			}
		}
	}
	else {
		std::vector<file_header> old_headers;
		check_file.close();
		std::ifstream archive(archive_name);
		file_header tmp_header;
		std::ofstream archive_tmp;
		int tmp;
		archive_tmp.open(archive_name_tmp, std::ios_base::binary);
		int current_index = 0; 
		get_header_info(archive, headers);
		old_headers.assign(headers.begin(), headers.end());
		tmp = headers.size();
		for (int i = 0; i < file_names.size(); i++)
		{
			get_file_info(file_names[i], tmp_header);
		}
		file_amount = headers.size()+file_names.size();
		file_info.assign(headers.begin(), headers.end());
		construct_header(file_names,headers,false);

		write_header(archive_tmp, headers);
		for(int i = 0; i < tmp; i++)
		{
			archive.seekg(old_headers[i].get_first_byte()-1, archive.beg);	
			rewrite_files(archive, archive_tmp, headers[i], false);
		}
		archive.close();
		std::remove(archive_name.c_str());

		for (int i = tmp; i < file_amount; i++)
		{
			std::ifstream new_file(headers[i].get_name(), std::ios_base::binary);
			rewrite_files(new_file, archive_tmp, headers[i], true);
			new_file.close();
		}
		archive_tmp.close();
		std::rename(archive_name_tmp.c_str(), archive_name.c_str());
	}
}

void archivator_info::unpack(const command_line& cl)
{
	std::string archive_name = cl.get_archive_name();
	std::vector<file_header> files;
	const char* buf = archive_name.c_str();
	std::ifstream archive(archive_name, std::ifstream::binary);
	if (archive.is_open())
	{
		get_header_info(archive, files);

		for (int i = 0; i < files.size(); i++)
		{
			std::ofstream file;
			file.open(files[i].get_name(), std::ios_base::binary);
			if(i==0)
				archive.seekg(files[i].get_first_byte() - 1, archive.beg);
			rewrite_files(archive, file, files[i], true);
			file.close();
		}
	}
	archive.close();
	std::remove(buf);
	std::cout << "Sucessfully unpacked files!" << std::endl;
}

void archivator_info::delete_file(const command_line& cl)
{
	std::string archive_name = cl.get_archive_name();
	std::vector<std::string> file_names;
	file_names.assign(cl.get_file_names().begin(), cl.get_file_names().end());
	std::vector<file_header> files;
	std::vector<file_header> old_headers;
	file_header tmp_header;

	char byte[1];
	bool flag = false;
	std::string archive_name_tmp = archive_name + "tmp";
	uint64_t tmp;

	std::ifstream archive;
	std::cout << archive_name << std::endl;
	archive.open(archive_name, std::ifstream::binary);
	if (archive.is_open())
	{
		std::ofstream archive_tmp;
		archive_tmp.open(archive_name + "tmp", std::ofstream::binary);

		/* get_header_info(archive, files);
		file_names.assign(cl.get_file_names().begin(), cl.get_file_names().end());
		for (int i = 0; i < file_amount; i++)
			for (int j = 0; j < file_names.size(); j++)
				if (files[i].get_name() == file_names[j])
				{
					files.erase(files.begin() + i);
					file_amount--;
				}
		archive.close(); */
		get_header_info(archive, files);
		old_headers.assign(files.begin(), files.end());
		tmp = files.size();
		for (int i = 0; i < file_names.size(); i++)
		{
			get_file_info(file_names[i], tmp_header);
		}
		for (int i = 0; i < file_amount; i++)
			for (int j = 0; j < file_names.size(); j++)
				if (files[i].get_name() == file_names[j])
				{
					files.erase(files.begin() + i);
					file_amount--;
				}
		//file_amount = files.size() - file_names.size();
		file_info.assign(files.begin(), files.end());
		file_names.clear();
		construct_header(file_names, file_info, false);

		write_header(archive_tmp, file_info);
		for (int i = 0; i < file_amount; i++)
		{
			if(i == 0)
				archive.seekg(files[i].get_first_byte() - 2, archive.beg);
			rewrite_files(archive, archive_tmp, file_info[i], flag);
		}
		archive.close();
		archive_tmp.close();
		std::remove(archive_name.c_str());
		std::rename(archive_name_tmp.c_str(), archive_name.c_str());
	}
	archive.close();
}

void archivator_info::list(const command_line& cl)
{
	std::string archive_name = cl.get_archive_name();
	std::vector<file_header> files;
	std::ifstream in(archive_name, std::ifstream::binary);
	if (in.is_open())
	{
		get_header_info(in, files);
		for (int i = 0; i < files.size(); i++)
		{
			std::cout << "File number " << i+1 << " name: " << files[i].get_name() << std::endl;
			std::cout << "Size in bytes: " << files[i].get_size() << std::endl;
			std::cout << "---------------------------------" << std::endl;
		}
	}
	in.close();
}

void archivator_info::write_header( std::ofstream& out, const std::vector<file_header>& headers) // метод архивации файла
{
	std::string tmp;
		out.write(signature, 5);
		out.write(reinterpret_cast<const char*>(&file_amount), sizeof(file_amount));

		for (int i = 0; i < headers.size(); i++)
		{
			file_header fh = headers[i];
			std::cout << "--------------------" << std::endl;
			std::cout << fh.get_name() << std::endl;

			short lenght = fh.get_name().length();
			out.write(reinterpret_cast<const char*>(&lenght), 2);
			out << fh.get_name();
			int64_t first_byte = fh.get_first_byte();
			unsigned char buf[8];
			
			int64ToChar(buf, first_byte);
			out.write((char*)buf, sizeof(int64_t));
			std::cout << "first_byte : " << first_byte << std::endl;
			print_hex(buf, sizeof(int64_t));
			
			int64_t file_size = fh.get_size();
			int64ToChar(buf, file_size);
			out.write((char*)buf, sizeof(int64_t));
			std::cout << "file_size : " << file_size << std::endl;
			print_hex(buf, sizeof(int64_t));
		}

}

void archivator_info::int64ToChar(unsigned char mesg[], int64_t num) {
	for (int i = 0; i < 8; i++) mesg[i] = num >> (8 - 1 - i) * 8;
}

int64_t archivator_info::charTo64bitNum(unsigned char a[]) {
	int64_t n = 0;
	n = (((int64_t)a[0] << 56) & 0xFF00000000000000U)
		| (((int64_t)a[1] << 48) & 0x00FF000000000000U)
		| (((int64_t)a[2] << 40) & 0x0000FF0000000000U)
		| (((int64_t)a[3] << 32) & 0x000000FF00000000U)
		| ((a[4] << 24) & 0x00000000FF000000U)
		| ((a[5] << 16) & 0x0000000000FF0000U)
		| ((a[6] << 8) & 0x000000000000FF00U)
		| (a[7] & 0x00000000000000FFU);
	return n;
}
void archivator_info::get_header_info(std::ifstream& in, std::vector<file_header>& files)
{
	std::string line;
	std::vector <std::string> file_names;
	file_header fh;
	int current_byte = 0;
	unsigned char buf[100];
	short tmp_short = 0;

	in.read((char*)&buf[0], 5);//чтение сигнатуры
	line.assign((char*)&buf[0],5);
	current_byte += 5;
	if(line == "art25")
	{
		in.read((char*)buf, 4);//кол-во файлов
		current_byte += 4;
		file_amount = (buf[0] + buf[1] + buf[2] + buf[3]);
		for (int i = 0; i < file_amount; i++)
		{
			in.read((char*)&buf[0], 2);	//кол-во символов имени файла
			current_byte += 2;
  
			tmp_short = (int)(buf[0]+buf[1]);
			in.read((char*)&buf[0], tmp_short);	//имя файла
			current_byte += (int)buf;
			line.assign((char*)&buf[0], tmp_short);
			fh.set_name(line);

			in.read((char*)&buf[0], sizeof(int64_t));		//первый байт
			uint64_t value = charTo64bitNum(buf);
			fh.set_first_byte(value);

			in.read((char*)&buf[0], sizeof(int64_t));		//размер файла
			value = charTo64bitNum(buf);
			fh.set_size(value);
			files.push_back(fh);
		}
	}	
}
void archivator_info::rewrite_files(std::ifstream& in, std::ofstream& out, file_header file, bool action)
{
	char byte[1];
	unsigned int written_bytes = 0;
	if (out.is_open())
	{
		for (int i = 0; i < file.get_size(); i++)
		{
			in.read(byte,1);
			//if (action) XOR_cipher_decipher(byte[0]);
			//std::cout << byte[0];
			out << byte[0];
			written_bytes++;
		}
		std::cout << "--------------------------------------------------" << std::endl;
		std::cout << "Written " << written_bytes << " bytes out of " << file.get_size() << std::endl;
		std::cout << "--------------------------------------------------" << std::endl;
	}
}
void archivator_info::write_file(std::ofstream& out, std::string file_name)
{
	std::string line;

	std::ifstream in(file_name, std::ios_base::binary); // окрываем файл для чтения
	if (in.is_open())
	{
		char b;
		while (in.get(b)) {
			//XOR_cipher_decipher(b);
			out << b;
		}
	}
	in.close();
}
void archivator_info::check_add_file_paths(const std::vector<std::string>& file_names)
{
	for (int i = 0; i < file_names.size(); ++i)
	{
		archivator_info::check_file(file_names[i]);
	}
}

void archivator_info::XOR_cipher_decipher(char& orignal_char) {
	char xorKey = 'T';
	orignal_char = orignal_char ^ xorKey;
}

void archivator_info::check_file(std::string file_name) { 	//метод проверки существования файла
	std::ifstream file;
	file.open(file_name, std::ios::app);
	if (!file)
		throw "File doesn't exist";
	file.close();
}

