#include "Response.hpp"


static	int	make_dir_if_not_exist(const string & path)
{
	if (is_a_dir(path))
	{
		print(INFO, "The upload folder was found");
		print(INFO, "Files about to be uploaded");
		return (0);
	}
	else
	{
		print(INFO, "The upload folder was not found");
		if(mkdir((path).c_str(), 0777))
		{
			print(ERR, "Error while creating the upload folder");
			return(1);
		}
		print(INFO, "Upload folder created ");
		return (0);
	}
}

int		Response::post_file_creation(const string & path)
{
	size_t i = 0;
	
	while (i < _request.content.size())
	{
		string infile(_request.file_name[i]);

		std::ofstream fout;
		infile = path + infile;
		print(INFO, "File(s) about to be uploaded");

		if (is_a_file(infile) && !check_file_rights(infile))
		{
			print(ERR, "The user can't open the file : Permission denied"); 
			print(ERR, "Files not uploaded");
			generate_error_page(403);
			return (1);
		}  

		fout.open(infile.c_str(), std::ios::out | std::ios::app | std::ios::binary);

		if (fout.is_open() == false)
		{
			error("Error : while opening the file", infile);
			print(ERR, "Error while opening the file");
			print(ERR, "Files not uploaded");
			generate_error_page(500);
			return (1);
		}
		fout << _request.body_content[i];
		fout.close();
		i++;
	}
	return(0);
}


void    Response::post_method(void)
{
   _request.get_content();

	string folder_path = "." + _location.get_upload_path();

	if (make_dir_if_not_exist(folder_path))
		return(generate_error_page(500));
	if (_location.upload_allowed() && post_file_creation(folder_path))
		return();

	generate_error_page(201);
	print(INFO, "Files were succesfully uploaded to the server");
}

