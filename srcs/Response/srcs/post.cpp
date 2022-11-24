#include "Response.hpp"

void	Response::post(void)
{
	size_t i = 0;

	string folder = "." + _location.get_upload_path();
	if (is_a_directory(_location.get_upload_path()))
	{
		print(ERR, "The upload folder was not found");
		print(ERR, "Files not uploaded");
		generate_error_page(500);
		return ;
	}
	else
		mkdir(("." + _location.get_upload_path()).c_str(), 0777);


	print(INFO, "Upload folder created ");

	while (i < _request.content.size())
	{
		string infile(_request.file_name[i]);
		std::ofstream fout;

		infile = folder + infile;
		cout << "file about to be added :" << infile << endl;
		fout.open(infile.c_str(), std::ios::out | std::ios::app);
		if (fout.is_open() == false)
		{
			error("Error : while opening the file", infile);
			print(ERR, "Error while opening the file");
			print(ERR, "Files not uploaded");
			generate_error_page(500);
			return ;
		}
		fout << _request.body_content[i];
		fout.close();
		i++;
	}
	set_status_code(201);
	_full_response = "HTTP/1.1 201 Created\r\n\r\n Created";
	print(INFO, "Files were succesfully uploaded to the server");
}
