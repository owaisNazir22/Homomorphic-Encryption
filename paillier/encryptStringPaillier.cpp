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
       cout << html() << head() << title("Homomorphic String Encryption.") << endl;
cout<<"<style>div {word-wrap: break-word; width: 100%; color:white;}</style>"<<endl;
cout<<"<style>h1{border-bottom: 6px solid;}</style>"<<endl;
cout<<"<style>input{ width: 40%; height: 10%; color: brown; border-radius: 60px; background: none; cursor: pointer; border: 2px solid #4caf50; color: white;}</style>"<<endl;
  cout<<head() << endl;
       cout << body().set("bgcolor","#191919").set("text","white").set("link","#0000ff").set("vlink","#000080") << endl;

 cout << h1("Homomorphic String Encryption");
       cout << h3("The string is encrypted by converting each character into ascii value and encrypting that ascii value.");
 
clock_t encryptStart, encryptEnd;
encryptStart = clock();

       form_iterator fvalue1 = formData.getElement("value");
       if( !fvalue1->isEmpty() && fvalue1 != (*formData).end()) {
         //cout << h1("ERROR"); 
                          } 

        string stringValue = **fvalue1;
        const char *valueConst = stringValue.c_str();
        char temp; int i=0; 
  while(1) {
        temp = valueConst[i];
         if(temp == '\0') break;
        i++;
          }

 int charString[i+1];

 for (int j=0 ;j<i; j++) { temp = valueConst[j]; charString[j] = (int)temp; }


string sr,sn,sg,sn_square,sm;
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

const char *m;

ofstream file_;

file_.open("encryptedString.txt");
cout << h2("Encrypted string.");

 for (int j=0 ;j<i; j++) {
       sm = to_string(charString[j]); 
       m = sm.c_str();
       mpz_set_str(M,m,10);

    mpz_powm(tmp1,G,M,N_sqr);
    mpz_powm(tmp2,R,N,N_sqr);
    mpz_mul(C,tmp1,tmp2);
    mpz_powm_ui(C,C,1,N_sqr);
    cout << "<strong>Encrypted result of string character at position " << j << " is : </strong>" << "</br>" << "</br>" << "<div>" << mpz_get_str(NULL,16,C) << "</div>" << "</br>" << "</br>";
    file_ << mpz_get_str(NULL,16,C) << endl;
    
    sm.clear();
}

cout << "</br>" << "</br>";

file_.close();

encryptEnd = clock();
encryptEnd = encryptEnd - encryptStart;

 ifstream testFile;
 testFile.open("encryptedString.txt" ,ios_base::binary);
 testFile.seekg (0, ios_base::end);
 const auto end = testFile.tellg();
 testFile.close();

 int sizeFile = (int)end/2;

 cout << "Size of cipher string : "<< sizeFile << " bytes." << "</br>" << "</br>";

 cout << "Time required to encrypt the string is : ";
 cout << (double)encryptEnd/CLOCKS_PER_SEC << " sec." << "</br>" << "</br>";

    cout << h5("To decrypt the string press <emp><strong>Decrypt</emp></strong>.");
    
    cout << "<form method=\"post\" action=\"/cgi-bin/paillier/decryptStringPaillier.cgi\">";
    cout << "<input type=\"submit\" value=\"Decrypt\">";
    cout << "</form>";
    






cout << body() << html();


}
    catch(exception& e) {
       // handle any errors here.
       cout << "ERROR!!" << endl;
    }
   
    return 0;
}





