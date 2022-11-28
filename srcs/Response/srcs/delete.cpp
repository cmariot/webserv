#include "Response.hpp"


void    Response::delet(void)
{
    string file = "." + _location.get_path() + _request.uri;
    if (remove(file.c_str()) != 0)
    {
        print(ERR, "Error while deleting the file");
        generate_error_page(500);
        return ;
    }
    set_status_code(204);
    _full_response = "HTTP/1.1 204 No Content\r\n\r\n";
    print(INFO, "File was succesfully deleted from the server");
}