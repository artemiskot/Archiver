
#include <ctime>
#include <iostream>
#include <string>
#include <vector>
#include <clocale>
#include <fstream>
#include <charconv>

#include "Archiver.h"

//-a file.arch testdata.sql script+insert.sql tmp.txt
//-x file.arch
//-l file.arch
//-d file.arch testdata.sql
//-a file.arch D:\DISK_D\Artem_new\Физика\kollokvium_po_fizike_dinamika.docx D:\DISK_D\Artem_new\C++\Archivator\v2\script+insert.sql D:\DISK_D\Artem_new\C++\Archivator\v2\testdata.sql
int main(int argc, char* argv[])
{
	command_line cl;	
	if (cl.parse(argc, argv))
	{
		cl.print();
		try
		{
			archivator_info arch;
			command_t command = cl.get_command();
			switch (command)
			{
				case command_t::_add:
				{
					command_line::progress_bar();
					arch.pack(cl);
					break;
				}
				case command_t::_extract:
				{
					command_line::progress_bar();
					arch.unpack(cl);
					break;
				}
				case command_t::_delete:
				{
					command_line::progress_bar();
					arch.delete_file(cl);
					break;
				}
				case command_t::_list:
				{
					command_line::progress_bar();
					arch.list(cl);
					break;
				}
			}
		}
		catch (const std::string* e)
		{
			std::cerr << e << std::endl;
		}
	}
}