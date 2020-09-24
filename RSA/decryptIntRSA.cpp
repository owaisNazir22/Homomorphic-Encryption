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
       cout << html() << head() << title("RSA Decryption.")<<endl;
cout<<"<style>h1{border-bottom: 6px solid;}</style>"<<endl;
cout<<"<style>input{ width: 40%; height: 10%; color: brown; border-radius: 60px; background: none; cursor: pointer; border: 2px solid #4caf50; color: white;}</style>"<<endl;
cout << head() << endl;
       cout << body().set("bgcolor","#191919").set("text","white").set("link","#0000ff").set("vlink","#000080") << endl;
       cout << h1("RSA Decryption. ") << endl;

clock_t decryptStart, decryptEnd;
decryptStart = clock();

string slambda,sn,svalue;
mpz_t LAMBDA,N,M,C;
mpz_inits(LAMBDA,N,M,C,NULL);

ifstream file;

file.open("privateKey.txt");
file>>slambda; 
file.close(); 
const char *lambda = slambda.c_str();

file.open("valueOfn.txt");
file>>sn; 
file.close(); 
const char *n = sn.c_str();


file.open("value1.txt");
file>>svalue;
file.close(); 
const char *val = svalue.c_str();

mpz_set_str(LAMBDA,lambda,16);
mpz_set_str(N,n,16);


mpz_set_str(C,val,16);

     mpz_powm(M,C,LAMBDA,N);
    mpz_powm_ui(M,M,1,N); 
     cout<<h3("Decryption of first integer : ") << "<div>" <<mpz_get_str(NULL,10,M)<< "<div>" "<br>"<<"<br>";

decryptEnd = clock();
decryptEnd = decryptEnd - decryptStart;


file.open("value2.txt");
file>>svalue;
file.close(); 
val = svalue.c_str();

mpz_set_str(C,val,16); 
     mpz_powm(M,C,LAMBDA,N);
       mpz_powm_ui(M,M,1,N); 
     cout<<h3("Decryption of second integer :") << "<div>" <<mpz_get_str(NULL,10,M)<< "<div>" "<br>"<<"<br>";

 cout << "Time required to perform decryption operation on given integer : ";
 cout << (double)decryptEnd/CLOCKS_PER_SEC << " sec." << "</br>";


    cout << h3("To perform \"Homomorphic Operations\" press Operations button below.");

  cout << "<form method=\"post\" action=\"/cgi-bin/RSA/intHomomorphicOperations.cgi\">";
    cout << "<input type=\"submit\" value=\"Homomorphic Multiplication\">";
    cout << "</form>";

cout << body() << html();


}
    catch(exception& e) {
       // handle any errors here.
       cout << "ERROR!!" << endl;
    }
   
    return 0;
}



