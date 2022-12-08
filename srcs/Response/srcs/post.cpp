#include "Response.hpp"


// https://stackoverflow.com/questions/630453/what-is-the-difference-between-post-and-put-in-http -> post needs to modify the state of the server

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
		if(mkdir((path).c_str(), 0775))
		{
			print(ERR, "Error while creating the upload folder");
			return(1);
		}
		print(INFO, "Upload folder created");
		return (0);
	}
}

int		Response::post_files_creation(const string & path)
{
	size_t i = 0;
	_first_file = -1;

	if (!_location.upload_allowed() )
	{
		print(ERR, "The user can't upload files on this server");
		generate_error_page(403);
		return (1);
	}
	print(INFO, "The user can upload files on this server");
	while (i < _request.content.size())
	{
		string infile(_request.file_name[i]);

		std::ofstream fout;
		infile = path + infile;
		print(INFO, "File about to be uploaded");
		if (is_a_file(infile))
		{
			if (!check_file_rights(infile))
			{
				print(ERR, "The user can't open the file : Permission denied");
				print(ERR, "Files not uploaded");
				generate_error_page(403);
				return (1);
			}
		}
		else if (_first_file == -1)
			_first_file = i;

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
		print(INFO, "Files were succesfully uploaded to the server");
	}
	return(0);
}

void 	Response::generate_post_response(int	status_code)
{
	_body = "<style>";
	_body +=			"html{";
	_body +=				"height:100%;";
	_body +=				"width:100%;";
	_body += 			"}";
	_body += 			"body{";
	_body +=				"height:100%;";
	_body +=				"width:100%;";
	_body +=				"display:flex;";
	_body +=				"flex-direction:column;";
	_body +=				"justify-content:center;";
	_body +=				"align-content:center;";
	_body +=				"text-align:center;";
	_body += 			"}";
	_body += 		"</style>";

	_header  = _request.get_http_version() + " " + itostring(status_code) + " " + _status_code_map.find(status_code)->second + "\r\n";
	if (status_code == 201)
	{
		_header += "Location: " + _location.get_upload_path() + _request.file_name[0] + "\r\n";
		_body = "Your file has been uploaded ! Click <A href=";
		_body +=   _location.get_upload_path() + _request.file_name[_first_file] + ">here</A> to view it.";
	}
	else if (status_code == 200)
	{
		_body = "Your file has been modified ! Click <A href=";
		_body +=   _location.get_upload_path() + _request.file_name[0] + ">here</A> to view it.";
	}
	_header += "Content-type: text/html charset=utf-8 \r\n";
	_header += "Content-Length: " + itostring(_body.size()) + "\r\n\r\n";
	_response = _header + _body;
}

void	Response::post_response(void)
{
	if (_request.content.size() && _first_file != -1)
		generate_post_response(201);
	else if (_request.content.size() && _first_file == -1)
		generate_post_response(200);
	else
		generate_post_response(204);
}

void    Response::post_method(void)
{
   	_request.get_content();

	string folder_path = _location.root() + _location.get_upload_path();

	cout << "folder_upload : " << folder_path << endl;
	if (make_dir_if_not_exist(folder_path))
		return(generate_error_page(500));
	if (post_files_creation(folder_path) && _request.content.size())
		return;
	post_response();
}

