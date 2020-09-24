#include <iostream>
#include <vector>  
#include <string>  
#include <stdio.h>  
#include <stdlib.h> 

#include <cgicc/CgiDefs.h> 
#include <cgicc/Cgicc.h> 
#include <cgicc/HTTPHTMLHeader.h> 
#include <cgicc/HTMLClasses.h>

using namespace std;
using namespace cgicc;

int main () {
   Cgicc cgi;

   cout << "Content-type:text/html\r\n\r\n";
   cout << "<html>";
   cout << "<head>";
   cout<<"<style>h1{border-bottom: 6px solid;}</style>"<<endl;
   cout<<"<style>btn{ width: 40%; height: 10%; color: brown; border-radius: 60px; background: none; cursor: pointer; border: 2px solid #4caf50; color: white;}</style>"<<endl;
 cout << body().set("bgcolor","#191919").set("text","white").set("link","#0000ff").set("vlink","#000080") << endl;
   cout << "<title>Paillier Image Upload</title>";
   cout << "</head>";

   cout << h1("PAILLIER IMAGE ENCRYPTION");
   cout << h2("The PGM format is used for image encrypt ,to encrypt the image it should be in the pgm.");
   cout << h2("The name \"PGM\" is an acronym derived from \"Portable Gray Map.\" A PGM image represents a grayscale graphic image.");
   
   
   cout << "<body>";
   cout << "<form    method = \"post\"  enctype = \"multipart/form-data\" action = \"/cgi-bin/paillier/imageEncryption.cgi\" > File: <input type = \"file\" name = \"userfile\"> <div><input id = \"btn\" type = \"submit\" value = \"Upload\"></div>  </form> ";
    cout << "</body>\n";
   cout << "</html>\n";
   
   return 0;
}
