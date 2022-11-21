#ifndef RESPONSE_HPP
# define RESPONSE_HPP

# include "Utils.hpp"
# include "Request.hpp"
# include "Server.hpp"
# include <sys/stat.h>
# include <fstream>
# include <map>
# include <unistd.h>
# include <fcntl.h>
# include <sys/wait.h>
# include <stdlib.h>



/*		Reference : https://www.rfc-editor.org/rfc/rfc2616#section-6
**		- The Response class is used to store the response to the client
**		- It is also used to generate the response to the client
**		A http response is composed of :
**		* A Header : The header is composed of a status line, followed by a sequence of header fields
**		- Status-Line 			(mandatory) made of :	HTTP-Version SP Status-Code SP Reason-Phrase CRLF
**		- Response Headers		(optional) made of : general-header | response-header | entity-header
**		* line break
**		* Response Body			(optional) made of : entity-body
**
**		here an exqmple of a http response :

**		HTTP/1.1 space 200 space OK
**		Date: 7 nov 2020 12:00:00 GMT
**		Server: server_name
**		Content-Type: text/html
**		Content-Length: 88
**
**	 	<html>
*/
class Response
{

	public:

		Response(void);
		~Response(void);

		map<int, string>		init_status_code_map(void) const;
		void					update(Request &, Server &, char *const *env);
		void					create(int);
		int						get_location(void);
		int						path_construction(void);

		void 					get(void);
		void					post(void);

	private:

		Request					_request;
		Server					_server;
		Location				_location;

		char *const 			*_env;
		std::string				_file_path;

	public:

		void					init_response(Request request);

		void					post_response(Request request);
		void 					delete_response(Request request);

		int 					set_status_code(const int & status_code);
		// used for get_response
		bool  					check_file_existance(string & path);
		int						stored_file(string & path);
		int						build_cgi_response(string & path);
		bool					match_extension(void);
		char *const 	 		*get_env(void);
		void 					build_http_response(void);
		bool					execute_script(char **arg);

	private:

		// Which status code are mandatory ?
		const map<int, string>	_status_code_map;
		int 					_status_code;
		string					_status_line;
		string					_response_header;
		string					_response_body;
		string					_full_response;

		bool					_dir;

		void					generate_error_page(const int &);
		int						create_response_header(void);

		bool					is_a_directory(const std::string & path);
		int						list_directories(void);
};

#endif
