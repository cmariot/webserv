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

int Request::get_content(void)
{
	size_t pos;
	string boundary;
	string boundary_end;

	pos = request.find("Content-Type: multipart/form-data; boundary=");
	if (pos != std::string::npos)
	{
		while(request[pos] != '\r' && request[pos] != '\n')
			boundary += request[pos++];
		boundary = boundary.substr((boundary.find("=") + 1), pos);
		boundary = "--" + boundary;
		boundary_end = boundary + "--";
	}
	pos = request.find(boundary);
	size_t pos2 = request.find(boundary_end);
	if (pos != std::string::npos && pos2 != std::string::npos)
		content = request.substr((pos + boundary.size() + 2), (pos2 - pos - boundary.size() - 4));
	// std::cout << "++++\n" << content << "++++" << std::endl;
	get_content_type();
	get_file_name();
	get_body_content();
	return (0);
}

// to do multiple file creation
