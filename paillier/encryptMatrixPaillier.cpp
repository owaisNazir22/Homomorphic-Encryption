#include <iostream>
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

cout<<"<style>div {word-wrap: break-word; width: 100%; color:white;}</style>"<<endl;
cout<<"<style>h1{border-bottom: 6px solid;}</style>"<<endl;
cout<<"<style>input{ width: 40%; height: 10%; color: brown; border-radius: 60px; background: none; cursor: pointer; border: 2px solid #4caf50; color: white;}</style>"<<endl;

       // Set up the HTML document
       cout << html() << head() << title("Paillier Matrix Encryption") << head() << endl;
      cout << body().set("bgcolor","#191919").set("text","white").set("link","#0000ff").set("vlink","#000080") << endl;

       cout << h1("Encrypted Matrix values") << "<br>";


       form_iterator fvalue1 = formData.getElement("value1");
       if( !fvalue1->isEmpty() && fvalue1 != (*formData).end()) {
          //cout << "Value1: " << **fvalue1 << endl; 
                          } 

             string bits = **fvalue1; 
             const char *arrayString = bits.c_str();

clock_t encryptStart, encryptEnd;
encryptStart = clock();

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

char temp = 1;
int i = 0;
const char *m;

ofstream file_;

file_.open("matrix1.txt");
file_<<bits;
file_.close();

file_.open("encryptedMatrix1.txt");
cout << h2("Encrypted Matrix Ist");
int k=0,l=0;
while (1) {
      temp = arrayString[i];
      if(temp != ',' && temp != '\0' && temp != '/') {
             sm.push_back(temp);
             i++;
             }
      else {
           m = sm.c_str();
           mpz_set_str(M,m,10);

    mpz_powm(tmp1,G,M,N_sqr);
    mpz_powm(tmp2,R,N,N_sqr);
    mpz_mul(C,tmp1,tmp2);
    mpz_powm_ui(C,C,1,N_sqr);
    cout << "Encrypted Number of position  ["<< k << "]"<< "[" << l << "]" << ":" << "</br>" << "<div>" << mpz_get_str(NULL,16,C) << "</div>" << "</br>" << "</br>";
    l++;
    if (temp == '/') { file_<< mpz_get_str(NULL,16,C) << endl; file_ << "/" << endl; k++; l=0;}
    else file_  << mpz_get_str(NULL,16,C)  << endl;
    
    sm.clear();
    i++;
   }
     if(temp == '\0') break;      
}
file_.close();

encryptEnd = clock();
encryptEnd = encryptEnd - encryptStart;


form_iterator fvalue2 = formData.getElement("value2");
       if( !fvalue2->isEmpty() && fvalue2 != (*formData).end()) {
          //cout << "Value2: " << **fvalue2 << endl; 
                          } 

             bits = **fvalue2;
             arrayString = bits.c_str();

file_.open("matrix2.txt");
file_<<bits;
file_.close();

file_.open("encryptedMatrix2.txt");
cout << h2("Encrypted Matrix Second");

i = 0;
k = 0;
l = 0;

while (1) {
      temp = arrayString[i];
      if(temp != ',' && temp != '\0' && temp != '/') {
             sm.push_back(temp);
             i++;
             }
      else {
           m = sm.c_str();
           mpz_set_str(M,m,10);

    mpz_powm(tmp1,G,M,N_sqr);
    mpz_powm(tmp2,R,N,N_sqr);
    mpz_mul(C,tmp1,tmp2);
    mpz_powm_ui(C,C,1,N_sqr);
    cout << "Encrypted Number of position  ["<< k << "]"<< "[" << l << "]" << ":" << "</br>" << "<div>" << mpz_get_str(NULL,16,C) << "</div>" << "</br>" << "</br>";
    l++;
    if (temp == '/') { file_ << mpz_get_str(NULL,16,C) << endl; file_ << "/" << endl; k++; l=0; }
    else file_  << mpz_get_str(NULL,16,C) << endl;
    
    sm.clear();
    i++;
   }
     if(temp == '\0') break;      
}
file_.close();

ifstream testFile;
 testFile.open("encryptedMatrix1.txt" ,ios_base::binary);
 testFile.seekg (0, ios_base::end);
 const auto end = testFile.tellg();
 testFile.close();
 
 int sizeFile = (int)end/2;

 cout << "Size of encrypted matrix : "<< sizeFile << " bytes" << "</br>" << "</br>";

 cout << "Time required to encrypt the matrix is : ";
 cout << (double)encryptEnd/CLOCKS_PER_SEC << " sec." << "</br>";

 cout << h5("To decrypt the numbers press <emp><strong>Decrypt</emp></strong> button or to perform \"Homomorphic Operations\" press <emp><strong>Operations</emp></strong>.");
    
    cout << "<form method=\"post\" action=\"/cgi-bin/paillier/decryptMatrixPaillier.cgi\">";
    cout << "<input type=\"submit\" value=\"Decrypt\">";
    cout << "</form>";
    
    cout << "<form method=\"post\" action=\"/cgi-bin/paillier/matrixHomomorphicOperation.cgi\">";
    cout << "<input type=\"submit\" value=\"Homomorphic Addition\">";
    cout << "</form>";




      cout << body() << html();


}
    catch(exception& e) {
       // handle any errors here.
       cout << "ERROR!!" << endl;
    }
   
    return 0;
}








