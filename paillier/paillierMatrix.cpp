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


using namespace std;
using namespace cgicc;


int main(int argc, char **argv)
{
  try {
    Cgicc formData;
       cout << HTTPHTMLHeader() << endl;           

       cout << HTMLDoctype(HTMLDoctype::eStrict) << endl;

       cout << html().set("lang", "EN").set("dir", "LTR") << endl;

       // Set up the HTML document
       cout << html() << head() << title("Paillier Matrix Encryption") << endl;

       cout <<"<style>div {word-wrap: break-word; width: 100%; color:white;}</style>"<<endl;
       cout <<"<style>h1{border-bottom: 6px solid;}</style>"<<endl;
       cout <<"<style>input{ width: 40%; height: 10%; color: brown; border-radius: 60px; background: none; cursor: pointer; border: 2px solid #4caf50; color: white;}</style>"<<endl;

       cout << head() << endl;

     cout << body().set("bgcolor","#191919").set("text","white").set("link","#0000ff").set("vlink","#000080") << endl;

       cout << h1("Paillier Matrix Encryption") << "<br>";

 cout << h3("Enter two matrices where elements in same row are sperated by commas and two different columns are sperated by forward slash.");
 cout << h3("Number of rows in matrix one i.e, M1 should be equal to number of rows in matrix two i.e, M2. Similarly number of columns in matrix one should be equal to number of columns in matrix two.");

    cout << "<form method=\"post\" action=\"/cgi-bin/paillier/encryptMatrixPaillier.cgi\">";
    cout << "<input type=\"text\" name=\"value1\">" << "</br>" << "</br>";
    cout << "<input type=\"text\" name=\"value2\">" << "</br>"; 
    cout << "<br>";
    cout << "<br>";
    cout << "<input type=\"submit\" value=\"Submit\">";
    cout << "</form>";

 
    cout << body() << html();
    }
    catch(exception& e) {
       // handle any errors here.
       cout << "ERROR!!" << endl;
    }	
}
    


