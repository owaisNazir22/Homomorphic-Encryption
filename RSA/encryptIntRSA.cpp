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

int main() {
try 
{ Cgicc formData;
       // Send HTTP header: Content-type: text/html
       cout << HTTPHTMLHeader() << endl;           

       cout << HTMLDoctype(HTMLDoctype::eStrict) << endl;


       // Prlong long: <html lang="en" dir="LTR">
       cout << html().set("lang", "EN").set("dir", "LTR") << endl;

       // Set up the HTML document
       cout << html() << head() << title("RSA Encryption.") << endl;
cout<<"<style>div {word-wrap: break-word; width: 100%; color:white;}</style>"<<endl;
cout<<"<style>h1{border-bottom: 6px solid;}</style>"<<endl;
cout<<"<style>input{ width: 40%; height: 10%; color: brown; border-radius: 60px; background: none; cursor: pointer; border: 2px solid #4caf50; color: white;}</style>"<<endl;
  cout<<head() << endl;
       cout << body().set("bgcolor","#191919").set("text","white").set("link","#0000ff").set("vlink","#000080") << endl;
       cout << h1("RSA Encryption. ") << endl;

clock_t encryptStart, encryptEnd;
encryptStart = clock();
    

string pu,sn;
mpz_t C,M; mpz_inits(C,M,NULL);

ifstream file;

file.open("publicKey.txt");
file>>pu;
file.close(); 
const char *e = pu.c_str();

file.open("valueOfn.txt");
file>>sn;
file.close();
const char *n = sn.c_str();

mpz_t N; mpz_init(N);
mpz_t E; mpz_init(E);


mpz_set_str(N,n,16);
mpz_set_str(E,e,16);


    form_iterator fvalue1 = formData.getElement("value1");
       if( !fvalue1->isEmpty() && fvalue1 != (*formData).end()) {
          //cout << "Value1: " << **fvalue1 << endl; } //modify

             string bits = **fvalue1;
             stringstream geek(bits);
             int bit;
             geek>>bit;

mpz_set_ui(M,bit);
mpz_powm(C, M, E, N);
mpz_powm_ui(C,C,1,N); 
 cout<<h3("Encrypted result of first number : ")<<"<div>"<<mpz_get_str(NULL,16,C)<<"</div>"<<"<br>";
{

ofstream file;
file.open("plaintext1.txt");         
    file<<mpz_get_str(NULL, 10, M);
    file.close();

file.open("value1.txt");         
    file<<mpz_get_str(NULL, 16, C);
    file.close();
}

encryptEnd = clock();
encryptEnd = encryptEnd - encryptStart;
 


    form_iterator fvalue2 = formData.getElement("value2");
       if( !fvalue1->isEmpty() && fvalue2 != (*formData).end()) {
          //cout << "Value1: " << **fvalue1 << endl; } //modify

             string bits = **fvalue2;
             stringstream geek(bits);
             int bit;
             geek>>bit;

mpz_set_ui(M,bit);
mpz_powm(C, M, E, N); 
 cout<<h3("Encrypted result of second number : ")<<"<div>"<<mpz_get_str(NULL,16,C)<<"</div>"<<"<br>";
{

ofstream file;
file.open("plaintext2.txt");         
    file<<mpz_get_str(NULL, 10, M);
    file.close();


file.open("value2.txt");         
    file<<mpz_get_str(NULL, 16, C);
    file.close();
}

 ifstream testFile;
 testFile.open("value1.txt" ,ios_base::binary);
 testFile.seekg (0, ios_base::end);
 const auto end = testFile.tellg();
 testFile.close();
 
 float sizeFile = (float)end/2;

 cout << "Size of cipher text 1 : "<< sizeFile << " bytes." << "</br>" << "</br>";

 testFile.open("value2.txt" ,ios_base::binary);
 testFile.seekg (0, ios_base::end);
 const auto end_ = testFile.tellg();
 testFile.close();
 sizeFile = (float)end_/2;

 cout << "Size of cipher text 2 : "<< sizeFile << " bytes." << "</br>" << "</br>";

 cout << "Time required to encrypt the integer is : ";
 cout << (double)encryptEnd/CLOCKS_PER_SEC << " sec." << "</br>";


    cout << h5("To decrypt the numbers press <emp><strong>Decrypt</emp></strong> button or to perform \"Homomorphic Operations\" press <emp><strong>Operations</emp></strong>.");
    
    cout << "<form method=\"post\" action=\"/cgi-bin/RSA/decryptIntRSA.cgi\">";
    cout << "<input type=\"submit\" value=\"Decrypt\">";
    cout << "</form>";
    
    cout << "<form method=\"post\" action=\"/cgi-bin/RSA/intHomomorphicOperations.cgi\">";
    cout << "<input type=\"submit\" value=\"Homomorphic Multiplication\">";
    cout << "</form>";


cout << body() << html();
    }
}
}
    catch(exception& e) {
       // handle any errors here.
       cout << "ERROR!!" << endl;
    }
   
}

