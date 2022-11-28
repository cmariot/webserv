#include "Response.hpp"


void    Response::delet(void)
{

    string infile(_request.file_name[i]);
    // if (check_file_existance(infile))
    // {
    //     print(ERR, "File to be deleted does not exist");

    // }
    
    if (remove(infile.c_str()) != 0)
    {
        error("Error : while deleting the file", infile);
        print(ERR, "Error while deleting the file");
        print(ERR, "Files not deleted");
        generate_error_page(500);
        return ;
    }
    set_status_code(202);
    generate_error_page(202);
    print(INFO, "File was succesfully deleted from the server");
}