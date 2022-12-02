#include "Request.hpp"

const std::string		& Request::get_request(void) const
{
	return (_request);
};

const std::string		& Request::get_request_line(void) const
{
	return (_request_line);
};

const std::string		& Request::get_method(void) const
{
	return (_method);
};

const std::string		& Request::get_uri(void) const
{
	return (_uri);
};

const std::string		& Request::get_http_version(void) const
{
	return (_http_version);
};

const std::string		& Request::get_host(void) const
{
	return (_address.first);
};

const int		& Request::get_port(void) const
{
	return (_address.second);
};

const std::pair<std::string, int>		& Request::get_address(void) const
{
	return (_address);
};

const multimap<string, string>		& Request::get_header(void) const
{
	return (_header);
};

const size_t 		& Request::get_header_size(void) const
{
	return (_header_size);
};
