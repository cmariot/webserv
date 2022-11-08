#ifndef RESPONSE_HPP
# define RESPONSE_HPP

# include "Utils.hpp"
# include "Request.hpp"
// useful for stat function
#include <sys/stat.h>
#include <fstream>
#include <map>

using std::map;
using std::string;
using std::vector;
using std::cout;
using std::pair;

// Reference : https://www.rfc-editor.org/rfc/rfc2616#section-6

/*
**		- The Response class is used to store the response to the client
**		- It is also used to generate the response to the client
**
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
class	Response
{

	public:
		// Constructor and destructor
		Response(void);
		~Response(void);
		
		int 					get_response(Request request);
		int						post_response(Request request);
		int 					delete_response(Request request);

		void 					init_status_code_map(void);
		void 					set_status_code(int status_code);
// used for get_response
		bool  					check_file_existance(string &path);
		int						stored_file(string path);

		void 					create_http_response(string method, string path);
	private:
		// Which status code are mandatory ?
		map 		<int, string>	_status_code_map;
		int 						_status_code;
		string						_status_line;
		string						_response_header;
		string						_response_body;
		string						_full_response;

};

#endif
