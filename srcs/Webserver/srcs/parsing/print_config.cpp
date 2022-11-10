#include "Webserver.hpp"

static void	print(std::string str)
{
	const char	*cyan		= "\033[36;1m";
	const char	*reset		= "\033[0m";

	std::cout << cyan << "[webserv] (conf)  " << reset << str << std::endl;
}

void	print_upload(Location location)
{
	if (location.upload_allowed() == true)
	{
		print("\t\tupload\t\ton;");
		print("\t\tupload_path\t" + location.get_upload_path() + ";");
	}
};

void	print_cgi(Location location)
{
	print("\t\tcgi\t\t" + location.cgi() + ";");
};

void	print_answer_directory(Location location)
{
	print("\t\tdir_file\t" + location.get_directory_file() + ";");
};

void	print_directory_listing(Location location)
{
	if (location.directory_listing())
		print("\t\tdir_listing\ton;");
	else
		print("\t\tdir_listing\toff;");
};


void	print_index(Location location)
{
	for (size_t i = 0 ; i < location.index().size() ; ++i)
		print("\t\tindex\t\t" + location.index()[i] + ";");
};

void	print_root(Location location)
{
	print("\t\troot\t\t" + location.root() + ";");
};

void	print_redirections(Location location)
{
	if (location.redirection() == true)
		print("\t\tredirection\t" + itostring(location.get_redirection_code()) + " " + location.get_redirection_path() + ";");
};

void	print_allowed_methods(Location location)
{
	if (location.get_allowed())
		print("\t\tallowed_method\tget;");
	if (location.post_allowed())
		print("\t\tallowed_method\tpost;");
	if (location.delete_allowed())
		print("\t\tallowed_method\tdelete;");
}

void	print_locations(std::map<std::string, Location> locations)
{
	for (std::map<std::string, Location>::iterator i = locations.begin() ; i != locations.end() ; ++i)
	{
		print("\tlocation " + i->first);
		print("\t{");
		print_allowed_methods(i->second);
		print_redirections(i->second);
		print_root(i->second);
		print_index(i->second);
		print_directory_listing(i->second);
		print_answer_directory(i->second);
		print_cgi(i->second);
		print_upload(i->second);
		print("\t}");
	}
};

void	print_max_body_size(double max_body_size)
{
	print("\tmax_body_size\t" + itostring(static_cast<int>(max_body_size)) + ";");
}

void	print_error_pages(std::map<int, Error_page> error_pages)
{
	for (std::map<int, Error_page>::iterator i = error_pages.begin() ; i != error_pages.end() ; ++i)
	{
		if (i->second.change_response() == false)
			print("\terror_page\t" + itostring(i->first) + "\t " + i->second.get_path() + ";");
		else if (i->second.specified_response() == false)
			print("\terror_page\t" + itostring(i->first) + " =\t " + i->second.get_path() + ";");
		else
			print("\terror_page\t" + itostring(i->first) + " =" + itostring(i->second.get_changed_code()) + " " + i->second.get_path() + ";");
	}
};

void	print_server_names(std::set<std::string> server_names)
{
	for (set<std::string>::iterator i = server_names.begin() ; i != server_names.end() ; ++i)
		print("\tserver_name\t" + *i + ";");
};

void	print_listen(std::string host, int port)
{
	std::string	listen = "\tlisten\t\t" + host + ":" + itostring(port) + ";";
	print(listen);
};

void	Webserver::print_config(void) const
{
	for (size_t i = 0 ; i < server.size() ; ++i)
	{
		print("server");
		print("{");
		print_listen(server[i].get_host(), server[i].get_port());
		print_server_names(server[i].get_server_names());
		print_error_pages(server[i].get_error_pages());
		print_max_body_size(server[i].get_max_size());
		print_locations(server[i].get_locations());
		print("}");
	}
};
