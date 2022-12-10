
#include<string.h>
#include <unistd.h>
#include <fstream>
#include<iostream>
using namespace std;

const char *storedfile(string path)
{
   std::ifstream fichier(path, std::ios::in);  // on ouvre en lecture

   if(fichier)
   {
      //L'ouverture s'est bien passée, on peut donc lire

      std::string ligne; //Une variable pour stocker les lignes lues
      std::string file_txt;
      file_txt =	"HTTP/1.0 200 OK\r\n\r\n";
      while(getline(fichier, ligne)) //Tant qu'on n'est pas à la fin, on lit
          file_txt = file_txt + ligne + '\n';
      fichier.close();  // on ferme le fichier   
      char * cstr = new char [file_txt.length()+1];
      strcpy (cstr, file_txt.c_str());
      return cstr;
   }
   else
   {
       std::cout << "ERREUR: Impossible d'ouvrir le fichier en lecture." << std::endl;
       return NULL;
   }
}

int main()
{
   const char *file = storedfile("index.html");
   printf("%s",file);

   return 0;
}