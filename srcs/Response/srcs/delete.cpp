#include "Response.hpp"


void    Response::delet(void)
{

    // if (check_file_existance(infile))
    // {
    //     print(ERR, "File to be deleted does not exist");
    //     set_status_code(404);
    // }
    cout << _request.uri << endl;
    if (remove(_request.uri.c_str()) != 0)
    {
        strerror(errno);
        error("Error : while deleting the file", _request.uri.c_str());
        print(ERR, "Error while deleting the file");
        print(ERR, "Files not deleted");
        generate_error_page(500);
        return ;
    }
    set_status_code(202);
    generate_error_page(202);
    print(INFO, "File was succesfully deleted from the server");
}