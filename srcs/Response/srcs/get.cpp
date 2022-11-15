#include "Response.hpp"

// get the body of the response which is the html file
int		Response::stored_file(string & path)
{
	std::ifstream	file;
	string			buf;

	file.open(path.c_str(), std::ios::in);
	if (file.is_open() == false)
		return (set_status_code(404));
	_response_body.clear();
	while (!file.eof())
	{
		getline(file, buf);
		_response_body += buf;
		if (!file.eof())
			_response_body += '\n';
	}
	file.close();
	return (set_status_code(200));
};

void 	Response::get(void)
{
	_response_body.clear();
	if (get_location() == 0)
	{
		path_construction();
		stored_file(_file_path);
		build_http_response();
	}
	else
	{
		set_status_code(404);
		build_http_response();
	}
};
