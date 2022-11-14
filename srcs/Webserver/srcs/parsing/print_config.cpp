#include "Webserver.hpp"

static void	print(const std::string & str)
{
	const char	*cyan		= "\033[36;1m";
	const char	*reset		= "\033[0m";

	std::cout << cyan << "[webserv] (conf)  " << reset << str << std::endl;
};

static void	print_upload(const Location & location)
{
	if (location.upload_set)
	{
		if (location.upload_allowed() == true)
		{
			print("\t\tupload\t\ton;");
		}
		else
		{
			print("\t\tupload\t\toff;");
		}
	}
	if (location.upload_path_set)
	{
		print("\t\tupload_path\t" + location.get_upload_path() + ";");
	}
};

static void	print_cgi(const Location & location)
{
	if (location.cgi_set == true)
		print("\t\tcgi\t\t" + location.cgi() + ";");
};

static void	print_answer_directory(const Location & location)
{
	if (location.directory_file_set == true)
		print("\t\tdir_file\t" + location.get_directory_file() + ";");
};

static void	print_directory_listing(const Location & location)
{
	if (location.directory_listing_set)
	{
		if (location.directory_listing())
			print("\t\tdir_listing\ton;");
		else
			print("\t\tdir_listing\toff;");
	}
};

static void	print_index(const Location & location)
{
	for (size_t i = 0 ; i < location.index().size() ; ++i)
		print("\t\tindex\t\t" + location.index()[i] + ";");
};

static void	print_root(const Location & location)
{
	print("\t\troot\t\t" + location.root() + ";");
};

static void	print_redirections(const Location & location)
{
	if (location.redirection() == true)
		print("\t\tredirection\t" + itostring(location.get_redirection_code()) + " " + location.get_redirection_path() + ";");
};

static void	print_allowed_methods(const Location & location)
{
	if (location.get_allowed())
		print("\t\tallowed_method\tget;");
	if (location.post_allowed())
		print("\t\tallowed_method\tpost;");
	if (location.delete_allowed())
		print("\t\tallowed_method\tdelete;");
};

static void	print_locations(const Location & location)
{
	print("\tlocation " + location.get_uri());
	print("\t{");
	print_allowed_methods(location);
	print_redirections(location);
	print_root(location);
	print_index(location);
	print_directory_listing(location);
	print_answer_directory(location);
	print_cgi(location);
	print_upload(location);
	print("\t}");
};

static void	print_max_body_size(const double & max_body_size)
{
	const char	*cyan		= "\033[36;1m";
	const char	*reset		= "\033[0m";

	std::cout << cyan << "[webserv] (conf)  " << reset << "\tmax_body_size\t" << max_body_size << ";" << std::endl;
};

static void	print_error_pages(const Error_page & error_page)
{
	if (error_page.change_response() == false)
		print("\terror_page\t" + itostring(error_page.get_code()) + "\t " + error_page.get_path() + ";");
	else if (error_page.specified_response() == false)
		print("\terror_page\t" + itostring(error_page.get_code()) + " =\t " + error_page.get_path() + ";");
	else
		print("\terror_page\t" + itostring(error_page.get_code()) + " =" + itostring(error_page.get_changed_code()) + " "  + error_page.get_path() + ";");
};

static void	print_server_names(const std::set<std::string> & server_names)
{
	for (set<std::string>::iterator i = server_names.begin() ; i != server_names.end() ; ++i)
		print("\tserver_name\t" + *i + ";");
};

static void	print_listen(const std::string & host, const int & port)
{
	std::string	listen = "\tlisten\t\t" + host + ":" + itostring(port) + ";";
	print(listen);
};

void	Webserver::print_config(void) const
{
	std::map<int, Error_page>::const_iterator		error_page;
	std::map<std::string, Location>::const_iterator	location;

	for (size_t i = 0 ; i < server.size() ; ++i)
	{
		print("server");
		print("{");
		print_listen(server[i].get_host(), server[i].get_port());
		print_server_names(server[i].get_server_names());
		error_page = server[i].get_error_pages().begin();
		while (error_page != server[i].get_error_pages().end())
		{
			print_error_pages(error_page->second);
			++error_page;
		}
		print_max_body_size(server[i].get_max_size());
		location = server[i].get_locations().begin();
		while (location != server[i].get_locations().end())
		{
			print_locations(location->second);
			++location;
		}
		print("}");
	}
};
