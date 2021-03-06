#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <string>
#include <sstream>
#include <time.h>
#include <gmp.h>
#include <fstream>
#include <iostream>
#include "cgicc/CgiDefs.h"
#include "cgicc/Cgicc.h"
#include "cgicc/HTTPHTMLHeader.h"
#include "cgicc/HTMLClasses.h"
#include "cgicc/HTTPRedirectHeader.h"

static int MODULUS_SIZE,BLOCK_SIZE,BUFFER_SIZE;  

using namespace std;
using namespace cgicc;

int main(int argc, char **argv)
{
  
  try {
    Cgicc formData;
       // Send HTTP header: Content-type: text/html
       cout << HTTPHTMLHeader() << endl;           

       cout << HTMLDoctype(HTMLDoctype::eStrict) << endl;


       // Prlong long: <html lang="en" dir="LTR">
       cout << html().set("lang", "EN").set("dir", "LTR") << endl;

       // Set up the HTML document
       cout << html() << head() << title("RSA Algorithm");
cout<<"<style>div {word-wrap: break-word; width: 100%; color:white;}</style>"<<endl;
cout<<"<style>h1{border-bottom: 6px solid;}</style>"<<endl;
cout<<"<style>input{ width: 40%; height: 8%; color: brown; border-radius: 60px; background: none; cursor: pointer; border: 2px solid #4caf50; color: white;}</style>"<<endl;
cout<<"<style>select{ width:40%; height:5%; border-radius: 30px; fontsize:10px; position: center; color: green;}</style>"<<endl;
       cout << head() << endl;
       cout << body().set("bgcolor","#191919").set("text","white").set("link","#0000ff").set("vlink","#000080") << endl;

       cout << h1("RSA Algorithm ") ;
       
       cout << h3("RSA algorithm is asymmetric cryptography algorithm. Asymmetric actually means that it works on two different keys i.e. Public Key and Private Key. As the name describes that the Public Key is given to everyone and Private key is kept private. The scheme is multiplicative homomorphic cryptosystem.");


       cout << "<form method=\"post\" action=\"/cgi-bin/RSA/generateKey.cgi\"><h2>Key generation</h2> <input type=\"text\" name=\"value1\"> </br> </br> <input type=\"submit\" value=\"Submit\"> </form> " << "</br>" << "</br>";
         

        cout << body() << html();
    }
    catch(exception& e) {
       // handle any errors here.
       cout << "ERROR!!" << endl;
    }	
}
