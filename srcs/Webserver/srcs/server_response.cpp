#include "Webserver.hpp"

int Webserver::server_response(int fd, char *request)
{
    std::vector<std::string>    data;
    std::string                 tmp(request);
    int                         pos = 0;
    char response[1024];

    while(!tmp.empty())
    {
        pos = tmp.find(' ');
        if (pos != -1)
        {
            data.push_back(tmp.substr(0,pos));
            tmp.erase(0, pos + 1);
        }
        else
        {
            data.push_back(tmp);
            tmp.clear();
        }
  
    }

    std::string GET;

    for (size_t i = 0 ; i < data.size() ; ++i)
    {
        if (data[i] == "GET")
        {
            GET = data[i + 1];
            break;
        }
    }

    std::cout << GET << std::endl;
    
    strcpy(response, "response : OK\n"); 
    
    if (GET == "/index")
        strcpy(response, "fuck fuck fuck\n");

    //HOW I F**** MAKE THE RESPONSE 
	
    send(fd, response, strlen(response), 0);
    return (0); 
}