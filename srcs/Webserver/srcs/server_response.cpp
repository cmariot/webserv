#include "Webserver.hpp"

void parse_response(std::vector<std::string> & data, char *request)
{
    std::string tmp(request);
    int pos = 0;
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
}

int Webserver::server_response(int fd, char *request)
{
    std::vector<std::string>    data;
    char response[1024];
    std::string GET;
    std::string METHOD;

    parse_response(data, request);
    METHOD = data[0];
    for (size_t i = 0 ; i < data.size() ; ++i)
    {
        if (data[i] == METHOD)
        {
            GET = data[i + 1];
            break;
        }
    }
    
    strcpy(response, "basic response\n"); 
    
    if (GET == "/index")
        strcpy(response, "HTTP/1.1 200 OK\nContent-Type:text/html\nContent-Length: 16\n\n<h1>testing</h1>");

	
    send(fd, response, strlen(response), 0);
    return (0); 
}