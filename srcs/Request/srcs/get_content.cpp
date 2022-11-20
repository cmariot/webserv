#include "Request.hpp"

// get the name of the different files and store them in file_name vector
int Request::get_file_name(size_t i)
{
	size_t		pos;
	cout << "sseg in file name" << endl ;

	file_name.push_back("");

	pos = content[i].find("filename=");
	if (pos != std::string::npos)
	{
		pos += 10;
		while(content[i][pos] != '"')
			file_name.back() += content[i][pos++];
		if (file_name.back == "")
			return (1);
	}
	cout << "sseg in file name2" << endl ;

	// cout << "This is our file name " << file_name[i] << " et " <<i <<endl;
	return (0);
};

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

int Request::get_body_content(size_t i)
{
	size_t		pos;

	// degueu mais fonctionnel
	pos = content[i].find("filename");
	pos = content[i].find("\n", ++pos);
	pos = content[i].find("\n", ++pos);
	pos = pos + 3;

	if (pos != std::string::npos)
	{
		body_content.push_back("");
		while (content[i][pos])
		{
			body_content[i] += content[i][pos++];
		}
	}
	cout << "This is our content : " << endl << body_content[i] << endl;
	return (0);
};

// This function stored the different uploaded files into a vector content
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
			content.push_back(request.substr((first_boundary + boundary.size() + 2),
			 (second_boundary - first_boundary - boundary.size() - 4)));
		verif_last_boundary = request.find(boundary_end);
		if (second_boundary == verif_last_boundary)
			break;
		first_boundary = second_boundary;
	}
	cout << "size = " << content.size() << endl;
	return 0;
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

	get_boundary_content();

	while (i < content.size())
	{

		pos_iterator = content.begin() + i ;

		cout << "size = " << content.size() << " i = " << i<< endl ;
		cout << "segfault" << endl;
		if(get_file_name(i))
		{
			content.erase(pos_iterator);
			file_name.erase(pos_iterator);
			cout << "segfault" << endl;
			continue;
		}
		cout << "segfault3" << endl;

		get_content_type(i);
		get_body_content(i);
		i++;
	}
	return (0);
}

// to do multiple file creation
