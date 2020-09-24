#include <iostream>
#include <string.h>
#include <string>
#include <sstream>
#include <time.h>
#include <gmp.h>
#include <fstream>
#include <vector>
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
    Cgicc cgi;
       // Send HTTP header: Content-type: text/html
       cout << HTTPHTMLHeader() << endl;           

       cout << HTMLDoctype(HTMLDoctype::eStrict) << endl;


       // Prlong long: <html lang="en" dir="LTR">
       cout << html().set("lang", "EN").set("dir", "LTR") << endl;

       // Set up the HTML document
       cout << html() << head() << title("Paillier Matrix Decryption") << endl;
cout<<"<style>h2 {font: 20px; color:white;}</style>"<<endl;
cout<<"<style>h1{border-bottom: 6px solid;}</style>"<<endl;
cout<<"<style>input{  position: absolute; r; width: 40%; height: 10%; color: brown; border-radius: 60px; background: none; cursor: pointer; border: 2px solid #4caf50; color: white;}</style>"<<endl;
  cout<<head() << endl;
       cout << body().set("bgcolor","#191919").set("text","white").set("link","#0000ff").set("vlink","#000080") << endl;
       cout << h1("Paillier Matrix Decryption. ") << endl;

clock_t decryptStart, decryptEnd;
decryptStart = clock();

string slambda,sn,smu,sn_square,svalue;
mpz_t LAMBDA,N,MU,C,MD,N_sqr,tmp1,tmp2,tmp3;
mpz_inits(LAMBDA,N,MU,C,MD,N_sqr,tmp1,tmp2,tmp3,NULL);

ifstream file;

file.open("lambda.txt");
file>>slambda; 
file.close(); 
const char *lambda = slambda.c_str();

file.open("n.txt");
file>>sn; 
file.close(); 
const char *n = sn.c_str();

file.open("mu.txt");
file>>smu;
file.close(); 
const char *mu = smu.c_str();

file.open("n_square.txt");
file>>sn_square; 
file.close(); 
const char *n_sqr = sn_square.c_str();


file.open("encryptedMatrix1.txt");
cout << h2("Decryption of Ist Matrix");
file>>svalue; 
const char *ival = svalue.c_str(); 


mpz_set_str(LAMBDA,lambda,10);
mpz_set_str(N,n,10);
mpz_set_str(MU,mu,10);
mpz_set_str(N_sqr,n_sqr,10); 

string slashCheck;
slashCheck.push_back('/');

vector<int> matrix; string matrix_element; int matrix_int_element;

int k=0,l=0; 
while(!file.eof()){ 
     if(svalue.compare(slashCheck)==0) { k++; l=0;file>>svalue;}
else {

mpz_set_str(C,ival,16);                    
   
     mpz_powm(tmp1,C,LAMBDA,N_sqr);
     mpz_sub_ui(tmp1,tmp1,1);
     mpz_cdiv_q(tmp1,tmp1,N);
     mpz_powm_ui(tmp2,MU,1,N);
     mpz_mul(tmp3,tmp1,tmp2);
     mpz_powm_ui(MD,tmp3,1,N); 
         
    cout<< "Decription of Encrypted number at position" << "[" << k << "]" << "[" << l << "]" << "</br>" << mpz_get_str(NULL,10,MD)<<"</br>"<<"</br>";
     matrix_element = mpz_get_str(NULL,10,MD);
     stringstream peek(matrix_element); peek>>matrix_int_element;
     matrix.push_back(matrix_int_element);
     file>>svalue;
     ival = svalue.c_str();
     l++;
}
} 

file.close(); 


decryptEnd = clock();
decryptEnd = decryptEnd - decryptStart;

int track = 0;

cout << h3("Resultant matrix.");

for (int K=0;K<=k;K++) {
      for (int L=0;L<l;L++) {
            cout << matrix[track] << " ";
                track++;
                  }
              cout << "</br>";
              }


file.open("encryptedMatrix2.txt");
cout << h2("Decryption of Second Marix");
file>>svalue;
l=0;
k=0;
matrix.clear();

while(!file.eof()){
const char *sval = svalue.c_str();
mpz_set_str(C,sval,16);
    
    if(svalue.compare(slashCheck)==0) { k++; l=0;file>>svalue;}
else {
     cout << "<br>";
     mpz_powm(tmp1,C,LAMBDA,N_sqr);
     mpz_sub_ui(tmp1,tmp1,1);
     mpz_cdiv_q(tmp1,tmp1,N);
     mpz_powm_ui(tmp2,MU,1,N);
     mpz_mul(tmp3,tmp1,tmp2);
     mpz_powm_ui(MD,tmp3,1,N);
     cout<< "Decription of Encrypted number at position" << "[" << k << "]" << "[" << l << "]" << "</br>" << mpz_get_str(NULL,10,MD)<<"</br>"<<"</br>";
     matrix_element = mpz_get_str(NULL,10,MD);
     stringstream peek(matrix_element); peek>>matrix_int_element;
     matrix.push_back(matrix_int_element);
     file>>svalue;
     l++;
     }
}

file.close(); 

cout << h3("Resultant matrix.");

track = 0;

for (int K=0;K<=k;K++) {
      for (int L=0;L<l;L++) {
            cout << matrix[track] << " ";
                track++;
                  }
              cout << "</br>";
              }

 cout << "</br>" << "</br>";

cout << "Time required to perform decryption operation on a matrix : ";
 cout << (double)decryptEnd/CLOCKS_PER_SEC << " sec." << "</br>" << "</br>";

    cout << "<form method=\"post\" action=\"/cgi-bin/paillier/matrixHomomorphicOperation.cgi\">";
    cout << "<input type=\"submit\" value=\"Homomorphic addition\">";
    cout << "</form>";


cout << body() << html();


}
    catch(exception& e) {
       // handle any errors here.
       cout << "ERROR!!" << endl;
    }
   
    return 0;
}




