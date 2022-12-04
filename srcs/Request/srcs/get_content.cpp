#include "Request.hpp"

// get the name of the file and store it in file_name vector
int Request::get_file_name(size_t i)
{
	size_t		pos;

	file_name.push_back("");
	pos = content[i].find("filename=");
	if (pos != std::string::npos)
	{
		pos += 10;
		while(content[i][pos] != '"')
			file_name.back() += content[i][pos++];
		if (file_name.back().empty())
			return (1);
		return (0);
	}
	else
		return (1);
};

// store content type of the file in the vector
int Request::get_content_type(size_t i)
{
	size_t		pos;
	content_type.push_back("");

	pos = content[i].find("Content-Type: ");

	if (pos != std::string::npos)
	{
		pos += 13;
		while(content[i][pos] != '\r' && content[i][pos] != '\n')
			content_type[i] += content[i][pos++];
	}
	return (0);
};

// store body content of the file in the vector
int Request::get_body_content(size_t i)
{
	size_t		pos;
	
	pos = content[i].find("\r\n");
	pos = content[i].find("\r\n", ++pos);
	pos = pos + 4;

	if (pos != std::string::npos)
	{
		body_content.push_back("");
		while (pos < content[i].size())
		{
			body_content[i] += content[i][pos++];
		}
	}
	cout << "size : "<<content[i].size() << endl;
	cout << body_content[i] << endl;
	return (0);
};

// This function stored the different uploaded files into a vector content
int	Request::get_boundary_content(void)
{
	size_t first_boundary;
	size_t second_boundary;
	size_t verif_last_boundary;
	string boundary_end;

	first_boundary = _request.find("Content-Type: multipart/form-data; boundary=");
	if (first_boundary != std::string::npos)
	{
		while(_request[first_boundary] != '\r' && _request[first_boundary] != '\n')
			boundary += _request[first_boundary++];
		boundary = boundary.substr((boundary.find("=") + 1), first_boundary);
		boundary = "--" + boundary;
		boundary_end = boundary + "--";
	}
	while (_request.find(boundary, first_boundary + 1) != std::string::npos)
	{
		first_boundary = _request.find(boundary, first_boundary);
		second_boundary = _request.find(boundary, first_boundary + 1);
		if (first_boundary != std::string::npos && second_boundary != std::string::npos)
			content.push_back(_request.substr((first_boundary + boundary.size() + 2),
			 (second_boundary - first_boundary - boundary.size() - 4)));
		verif_last_boundary = _request.find(boundary_end);
		if (second_boundary == verif_last_boundary)
			break;
		first_boundary = second_boundary;
	}
	return 0;
}

void Request::reset(void)
{
	content.clear();
	file_name.clear();
	content_type.clear();
	body_content.clear();
}

// This function stores the different infos of files in 3 vectors : name, type, content
// 1 stored the different contents of the form divided by the boundaries in a vector
// 2 get the name of the file 
// 3 if name="" it means no file was uploaded => delete this content from the vector
// 4 get the type of content 
// 5 get the content of the file
int Request::get_content(void)
{
	size_t i = 0;
	vector<string>::iterator pos_iterator;

	reset();
	get_boundary_content();
	while (i < content.size())
	{
		pos_iterator = content.begin() + i ;
		if(get_file_name(i))
		{
			content.erase(pos_iterator);
			file_name.pop_back();
			continue;
		}
		get_content_type(i);
		get_body_content(i);
		i++;
	}
	return (0);
}
