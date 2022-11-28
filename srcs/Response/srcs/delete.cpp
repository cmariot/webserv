#include "Response.hpp"


void    Response::delet(void)
{
    // if (remove(file.c_str()) != 0)
    // {
    //     print(ERR, "Error while deleting the file");
    //     generate_error_page(500);
    //     return ;
    // }
    set_status_code(204);
    generate_error_page(200);
    print(INFO, "File was succesfully deleted from the server");
}