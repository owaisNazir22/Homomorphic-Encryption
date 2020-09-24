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
       // Send HTTP header: Content-type: text/html
       cout << HTTPHTMLHeader() << endl;           

       cout << HTMLDoctype(HTMLDoctype::eStrict) << endl;


       // Prlong long: <html lang="en" dir="LTR">
       cout << html().set("lang", "EN").set("dir", "LTR") << endl;

       // Set up the HTML document
       cout << html() << head() << title("RSA Interger Encryption");
       cout<<"<style>h1{border-bottom: 6px solid;}</style>"<<endl;
cout<<"<style>input{ width: 40%; height: 10%; color: brown; border-radius: 60px; background: none; cursor: pointer; border: 2px solid #4caf50; color: white;}</style>"<<endl; 
      cout<< head() << endl;
       cout << body().set("bgcolor","#191919").set("text","white").set("link","#0000ff").set("vlink","#000080") << endl;

       cout << h1("Enter two numbers you wish to encrypt") << "<br>";

    cout << "<form  method=\"post\" action=\"/cgi-bin/RSA/encryptIntRSA.cgi\">";
    cout << "<h2>Enter two numbers</h2>";
    cout << "<input id=\"val1\" type=\"text\" name=\"value1\" placeholder=\"       INTEGER  1\">""<br>"<<"<br>";
    cout << "<input id=\"val1\" type=\"text\" name=\"value2\" placeholder=\"       INTEGER  2\">";
    cout << "<br>";
    cout << "<br>";
    cout << "<input type=\"submit\" value=\"Submit\" onclick=\"validateform()\"> </form>";

     cout << "<script type=\"text/javascript\"> function validateform()                             {  var x = document.getElementById('val1').value; if(x == 'null' || x == \"\") { alert('Enter the numbers first'); return false; }     if(isNaN(x)){ alert('provide only numeric values'); } {  return true; } } </script>"; 
//cout << "<script type=\"text/javascript\"> function validateform()                                       {  var x =  document.getelementById('val2').value; if(x == null || x == "")  { alert('Enter the number first'); return false; } else {  return true; } } </script>"; 
 
    cout << body() << html();
    }
    catch(exception& e) {
       // handle any errors here.
       cout << "ERROR!!" << endl;
    }	
}
  
