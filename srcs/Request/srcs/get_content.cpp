#include "Request.hpp"

// get the type of


int Request::get_file_name(void)
{
	size_t		pos;
	file_name = "";

	pos = content.find("filename=");
	if (pos != std::string::npos)
	{
		pos += 10;
		while(content[pos] != '"')
			file_name += content[pos++];
	}

	// cout << "This is our file name " << file_name << endl;
	return (0);
};

int Request::get_content_type(void)
{
	size_t		pos;
	content_type = "";

	pos = content.find("Content-Type: ");
	if (pos != std::string::npos)
	{
		pos += 13;
		while(content[pos] != '\r' && content[pos] != '\n')
			content_type += content[pos++];
	}
	return (0);
};

int Request::get_body_content(void)
{
	size_t		pos;

	// degueu mais fonctionnel
	pos = content.find("filename");
	pos = content.find("\n", ++pos);
	pos = content.find("\n", ++pos);
	pos = pos + 3;

	if (pos != std::string::npos)
	{
		while (content[pos])
		{
			body_content += content[pos++];
		}
	}
	cout << "This is our content " << body_content << endl;
	return (0);
};

int	Request::get_boundary_content(void)
{
	size_t first_boundary;
	size_t second_boundary;
	size_t verif_last_boundary;
	string boundary;
	string boundary_end;

	first_boundary = request.find("Content-Type: multipart/form-data; boundary=");
	if (first_boundary != std::string::npos)
	{
		while(request[first_boundary] != '\r' && request[first_boundary] != '\n')
			boundary += request[first_boundary++];
		boundary = boundary.substr((boundary.find("=") + 1), first_boundary);
		boundary = "--" + boundary;
		boundary_end = boundary + "--";
	}
	while (request.find(boundary, first_boundary + 1) != std::string::npos)
	{
		first_boundary = request.find(boundary, first_boundary);
		second_boundary = request.find(boundary, first_boundary + 1);
		if (first_boundary != std::string::npos && second_boundary != std::string::npos)
			boundary_content.push_back(request.substr((first_boundary + boundary.size() + 2), (second_boundary - first_boundary - boundary.size() - 4)));
		verif_last_boundary = request.find(boundary_end);
		if (second_boundary == verif_last_boundary)
			break;
		first_boundary = second_boundary;
	}
	// first_boundary = request.find(boundary);
	// size_t pos2 = request.find(boundary_end);
	
	std::cout << "++++\n" << boundary_content[0] << "++++" << std::endl;
	return 0;

}

int Request::get_content(void)
{
	get_boundary_content();
	get_content_type();
	get_file_name();
	get_body_content();
	return (0);
}

// to do multiple file creation
