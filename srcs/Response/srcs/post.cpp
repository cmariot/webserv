#include "Response.hpp"


static	int	make_dir_if_not_exist(const string & path)
{
	if (is_a_dir(path))
	{
		print(ERR, "The upload folder was found");
		print(ERR, "Files about to be uploaded");
		return (0);
	}
	else
	{
		if(mkdir(("." + path).c_str(), 0777))
			return(1);
		print(INFO, "Upload folder created ");
		return (0);
	}
}


void    Response::post_method(void)
{
   _request.get_content();
   size_t i = 0;

	string folder = "." + _location.get_upload_path();

	if (make_dir_if_not_exist(_location.get_upload_path()))
		return(generate_error_page(500));

	while (i < _request.content.size())
	{
		string infile(_request.file_name[i]);
		std::ofstream fout;

		infile = folder + infile;
		cout << "file about to be added :" << infile << endl;
     if (is_a_file(infile) &&!check_file_rights(infile))
     {
         print(ERR, "The user can't open the file : Permission denied"); 
         print(ERR, "Files not uploaded");
         generate_error_page(403);
         return;
      }  
		fout.open(infile.c_str(), std::ios::out | std::ios::app | std::ios::binary);
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
	generate_error_page(201);
	print(INFO, "Files were succesfully uploaded to the server");
}

