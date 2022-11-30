#include "Response.hpp"

bool    Response::init_post(void)
{
    if (get_location())
	{
		generate_error_page(404);
		return (0);
	}
    if (!_location.upload_allowed())
    {
        generate_error_page(403);
        return (0);
    }
    if (!_location.post_allowed())
    {
        generate_error_page(405);
        return (0);
    }
    if (path_construction())
	{
		generate_error_page(404);
		return (0);
	}
    return (1); 
}

void	Response::post(void)
{
    std::cout <<_request.uri << std::endl;
    if (!init_post())
        return ;

    size_t i = 0;

    string folder = "." + _location.get_upload_path();
	std::cout << folder << std::endl;
	if (is_a_directory(_location.get_upload_path()))
	{
		print(2, "The upload folder was not found");
		print(2, "Files not uploaded");
		generate_error_page(500);
		return ;
	}
	else
	{
		mkdir(("." + _location.get_upload_path()).c_str(), 0777);
		print(INFO, "Upload folder created ");
	}
	
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
			print(2, "Error while opening the file");
			print(2, "Files not uploaded");
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