#include "Response.hpp"

void	Response::post(void)
{
	size_t i = 0;
	
	// struct stat buff;
	// string folder = _location.get_upload_path();
	// if (stat(folder.c_str(), &buff) != 0)
	// 	mkdir(folder.c_str(), 0777);
	string folder = "/html/test/";
	// cout << folder << endl;
	if(mkdir(folder.c_str(), 0777))
	{
		folder = "mkdir " + folder;
		cout << folder << endl;
		system(folder.c_str());
		print(INFO, "Upload folder created :");
	}


	while (i < _request.content.size())
	{
		string infile(_request.file_name[i]);
		std::ofstream fout;

		infile = _location.get_upload_path() + infile;
		fout.open(infile.c_str(), std::ios::out | std::ios::app);
		if (fout.is_open() == false)
		{
			error("Error : while opening the file ", infile);
			_full_response = "HTTP/1.1 201 OK\r\n\r\n";;
		}
		fout << _request.body_content[i];
		fout.close();
		_full_response = "HTTP/1.1 201 Created\r\n\r\n Created";
		i++;
	}
}
