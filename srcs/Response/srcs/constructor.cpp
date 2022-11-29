#include "Response.hpp"

// basic http response status code
std::map<int, std::string> 	Response::init_status_code_map(void) const
{
	std::map<int, std::string>	tmp;

	tmp.insert(pair<int, string>(200, "OK"));
	tmp.insert(pair<int, string>(201, "Created"));
	tmp.insert(pair<int, string>(202, "Accepted"));
	tmp.insert(pair<int, string>(203, "Non-Authoritative Information"));
	tmp.insert(pair<int, string>(204, "No Content"));
	tmp.insert(pair<int, string>(205, "Reset Content"));
	tmp.insert(pair<int, string>(206, "Partial Content"));
	tmp.insert(pair<int, string>(300, "Multiple Choices"));
	tmp.insert(pair<int, string>(301, "Moved Permanently"));
	tmp.insert(pair<int, string>(302, "Found"));
	tmp.insert(pair<int, string>(303, "See Other"));
	tmp.insert(pair<int, string>(304, "Not Modified"));
	tmp.insert(pair<int, string>(305, "Use Proxy"));
	tmp.insert(pair<int, string>(307, "Temporary Redirect"));
	tmp.insert(pair<int, string>(400, "Bad Request"));
	tmp.insert(pair<int, string>(401, "Unauthorized"));
	tmp.insert(pair<int, string>(402, "Payment Required"));
	tmp.insert(pair<int, string>(403, "Forbidden"));
	tmp.insert(pair<int, string>(404, "Not Found"));
	tmp.insert(pair<int, string>(405, "Method Not Allowed"));
	tmp.insert(pair<int, string>(406, "Not Acceptable"));
	tmp.insert(pair<int, string>(407, "Proxy Authentication Required"));
	tmp.insert(pair<int, string>(408, "Request Time-out"));
	tmp.insert(pair<int, string>(409, "Conflict"));
	tmp.insert(pair<int, string>(410, "Gone"));
	tmp.insert(pair<int, string>(411, "Length Required"));
	tmp.insert(pair<int, string>(412, "Precondition Failed"));
	tmp.insert(pair<int, string>(413, "Request Entity Too Large"));
	tmp.insert(pair<int, string>(414, "Request-URI Too Large"));
	tmp.insert(pair<int, string>(415, "Unsupported Media Type"));
	tmp.insert(pair<int, string>(416, "Requested range not satisfiable"));
	tmp.insert(pair<int, string>(417, "Expectation Failed"));
	tmp.insert(pair<int, string>(500, "Internal Server Error"));
	tmp.insert(pair<int, string>(501, "Not Implemented"));
	tmp.insert(pair<int, string>(502, "Bad Gateway"));
	tmp.insert(pair<int, string>(503, "Service Unavailable"));
	tmp.insert(pair<int, string>(504, "Gateway Time-out"));
	tmp.insert(pair<int, string>(505, "HTTP Version not supported"));
	return (tmp);
};

Response::Response(void) :
	_file_path(""),
	_status_code_map(init_status_code_map()),
	_status_code(0)
{
	return ;
};
