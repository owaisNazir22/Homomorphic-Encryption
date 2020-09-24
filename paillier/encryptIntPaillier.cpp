#include <string.h>
#include <string>
#include <sstream>
#include <gmp.h>
#include <fstream>
#include <iostream>
#include <time.h>

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
       cout << html() << head() << title("Paillier Encryption.") << endl;
cout<<"<style>div {word-wrap: break-word; width: 100%; color:white;}</style>"<<endl;
cout<<"<style>h1{border-bottom: 6px solid;}</style>"<<endl;
cout<<"<style>input{ width: 40%; height: 10%; color: brown; border-radius: 60px; background: none; cursor: pointer; border: 2px solid #4caf50; color: white;}</style>"<<endl;
  cout<<head() << endl;
       cout << body().set("bgcolor","#191919").set("text","white").set("link","#0000ff").set("vlink","#000080") << endl;
       cout << h1("Paillier Encryption. ") << endl;

     
    //Generate key 
       form_iterator fvalue1 = formData.getElement("value1");
       if( !fvalue1->isEmpty() && fvalue1 != (*formData).end()) {
          //cout << "Value1: " << **fvalue1 << endl; 
                          } 

             string bits = **fvalue1;
             const char *bit = bits.c_str();
             
string sr,sn,sg,sn_square;
mpz_t R,N,G,C,M,N_sqr,tmp1,tmp2; mpz_inits(R,N,G,C,M,N_sqr,tmp1,tmp2,NULL);

ifstream file;

file.open("r.txt");
file>>sr; 
file.close(); 
const char *r = sr.c_str();

file.open("n.txt");
file>>sn; 
file.close(); 
const char *n = sn.c_str();

file.open("g.txt");
file>>sg;
file.close(); 
const char *g = sg.c_str();

file.open("n_square.txt");
file>>sn_square;
file.close(); 
const char *n_sqr = sn_square.c_str();

mpz_set_str(R,r,10);
mpz_set_str(N,n,10);
mpz_set_str(G,g,10);
mpz_set_str(N_sqr,n_sqr,10);

mpz_set_str(M,bit,10); 
    cout << "<br>";
    //Encryption of the Message
    mpz_powm(tmp1,G,M,N_sqr);
    mpz_powm(tmp2,R,N,N_sqr);
    mpz_mul(C,tmp1,tmp2);
    mpz_powm_ui(C,C,1,N_sqr);
    cout<<h3("Encrypted result of first number : ")<<endl;

cout<<"<div>"<<mpz_get_str(NULL,16,C)<<"</div>";

     //This block saves the cipher text in value text file and plain text in plainTextInt text file.
     {
          ofstream file;

            file.open("value1.txt");         
            file<<mpz_get_str(NULL, 16, C);
            file.close();
            
            file.open("plainTextInt1.txt");         
            file<<mpz_get_str(NULL, 10, M);
            file.close();
            
        }


form_iterator fvalue2 = formData.getElement("value2");
       if( !fvalue2->isEmpty() && fvalue2 != (*formData).end()) {
          //cout << "Value2: " << **fvalue2 << endl; 
                          } 

             bits = **fvalue2;
             bit = bits.c_str();
mpz_set_str(M,bit,10); 

clock_t encryptStart, encryptEnd;
encryptStart = clock();
    
    //Encryption of the Message
    cout << "<br>"<< "<br>";
    mpz_powm(tmp1,G,M,N_sqr);
    mpz_powm(tmp2,R,N,N_sqr);
    mpz_mul(C,tmp1,tmp2);
    mpz_powm_ui(C,C,1,N_sqr);
    cout<<h3("Encrypted result of second number : ")<<"<div>"<<mpz_get_str(NULL,16,C)<<"</div>"<<"<br>";

encryptEnd = clock();
encryptEnd = encryptEnd - encryptStart;

        //This block saves the cipher text in value text file and plain text in plainTextInt text file.
        {
          ofstream file;

            file.open("value2.txt");         
            file<<mpz_get_str(NULL, 16, C);
            file.close();
      
            file.open("plainTextInt2.txt");         
            file<<mpz_get_str(NULL, 10, M);
            file.close();
        }

 ifstream testFile;
 testFile.open("value1.txt" ,ios_base::binary);
 testFile.seekg (0, ios_base::end);
 const auto end = testFile.tellg();
 
 int sizeFile = (int)end/2;

 cout << "Size of cipher text : "<< sizeFile << " bytes." << "</br>" << "</br>";

 cout << "Time required to encrypt the integer is : ";
 cout << (double)encryptEnd/CLOCKS_PER_SEC << " sec." << "</br>";

    cout << h5("To decrypt the numbers press <emp><strong>Decrypt</emp></strong> button or to perform \"Homomorphic Operations\" press <emp><strong>Operations</emp></strong>.");
    
    cout << "<form method=\"post\" action=\"/cgi-bin/paillier/decryptIntPaillier.cgi\">";
    cout << "<input type=\"submit\" value=\"Decrypt\">";
    cout << "</form>";
    
    cout << "<form method=\"post\" action=\"/cgi-bin/paillier/intHomomorphicOperations.cgi\">";
    cout << "<input type=\"submit\" value=\"Operations\">";
    cout << "</form>";

cout << body() << html();


}
    catch(exception& e) {
       // handle any errors here.
       cout << "ERROR!!" << endl;
    }
   
    return 0;
}








