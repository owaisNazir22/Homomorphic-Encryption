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
       // Send HTTP header: Content-type: text/html
       cout << HTTPHTMLHeader() << endl;           

       cout << HTMLDoctype(HTMLDoctype::eStrict) << endl;


       // Prlong long: <html lang="en" dir="LTR">
       cout << html().set("lang", "EN").set("dir", "LTR") << endl;

       // Set up the HTML document
        cout << html() << head() << title("Homomorphic Matrix Encryption");
cout<<"<style>div {word-wrap: break-word; width: 100%; color:white;}</style>"<<endl;
cout<<"<style>h1{border-bottom: 6px solid;}</style>"<<endl;
cout<<"<style>input{ width: 40%; height: 8%; color: brown; border-radius: 60px; background: none; cursor: pointer; border: 2px solid #4caf50; color: white;}</style>"<<endl;
cout<<"<style>select{ width:40%; height:5%; border-radius: 30px; fontsize:10px; position: center; color: green;}</style>"<<endl;
       cout << head() << endl;
  cout << body().set("bgcolor","#191919").set("text","white").set("link","#0000ff").set("vlink","#000080") << endl;
       cout << h1("Homomorphic Matrix Encryption");
    cout << h3("Enter the elements of matrix as in such a way that matrix multiplication is possible i.e matrix one say M1 should be column matrix and matrix two should be row matrix. ");
    cout << h3("The constraint that M1 should be column matrix and M2 should be row matrix is due to the fact that RSA is homomorphic with respect to multiplication only i.e, We can perform E(m<sub>1</sub>)*E(m<sub>2</sub>) mod n = m<sub>1</sub>*m<sub>2</sub> mod n on the elements of given matrices but that is not the case with addition.");
    cout << h3("Enter the dimension of matrix M1 in size of M1 as \"a,1\" where \"a\" is number of rows in M1 and \"1\" is number of columns. Similarly fill the size of M2 for matrix M2 as \"1,b\".");
    cout << h3("Inside the matrix M1 enter the matrix as a string in such way that elements inside a row are seperated by commas and columns are seperated by forward slash."); 

    cout << "<form  method=\"post\" action=\"/cgi-bin/RSA/encryptMatrixRSA.cgi\">";
    cout << "<input id=\"val1\" type=\"text\" name=\"dimension1\" placeholder=\"SIZE OF M1\">" << "</br>"<<"</br>";
    cout << "<input id=\"val1\" type=\"text\" name=\"dimension2\" placeholder=\"SIZE OF M2\">" << "</br>"<<"</br>";
    
    cout << "<input id=\"val1\" type=\"text\" name=\"matrix1\" placeholder=\"M1\">" << "</br>"<<"</br>";
    cout << "<input id=\"val1\" type=\"text\" name=\"matrix2\" placeholder=\"M2\">";
    cout << "<br>";
    cout << "<br>";
    cout << "<input type=\"submit\" value=\"Submit\"> </form>";

 cout << body() << html();
    }
    catch(exception& e) {
       // handle any errors here.
       cout << "ERROR!!" << endl;
    }
return 0;	
}
 

