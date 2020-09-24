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
       cout << html() << head() << title("Paillier Decryption.")<<endl;
cout<<"<style>h1{border-bottom: 6px solid;}</style>"<<endl;
cout<<"<style>input{ width: 40%; height: 10%; color: brown; border-radius: 60px; background: none; cursor: pointer; border: 2px solid #4caf50; color: white;}</style>"<<endl;
cout << head() << endl;
       cout << body().set("bgcolor","#191919").set("text","white").set("link","#0000ff").set("vlink","#000080") << endl;
       cout << h1("Paillier Decryption. ") << endl;

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

file.open("value1.txt");
file>>svalue;
file.close(); 
const char *val = svalue.c_str();

mpz_set_str(LAMBDA,lambda,10);
mpz_set_str(N,n,10);
mpz_set_str(MU,mu,10);
mpz_set_str(N_sqr,n_sqr,10);

mpz_set_str(C,val,16);

    cout << "<br>";
     mpz_powm(tmp1,C,LAMBDA,N_sqr);
     mpz_sub_ui(tmp1,tmp1,1);
     mpz_cdiv_q(tmp1,tmp1,N);
     mpz_powm_ui(tmp2,MU,1,N);
     mpz_mul(tmp3,tmp1,tmp2);
     mpz_powm_ui(MD,tmp3,1,N);
     cout<<h3("Decryption of first integer")<<mpz_get_str(NULL,10,MD)<<"<br>"<<"<br>";

decryptEnd = clock();
decryptEnd = decryptEnd - decryptStart;

file.open("value2.txt");
file>>svalue;
file.close(); 
val = svalue.c_str();

mpz_set_str(C,val,16); 

     cout << "<br>";
     mpz_powm(tmp1,C,LAMBDA,N_sqr);
     mpz_sub_ui(tmp1,tmp1,1);
     mpz_cdiv_q(tmp1,tmp1,N);
     mpz_powm_ui(tmp2,MU,1,N);
     mpz_mul(tmp3,tmp1,tmp2);
     mpz_powm_ui(MD,tmp3,1,N);
     cout<<h3("Decryption of second integer")<<mpz_get_str(NULL,10,MD)<<"<br>"<<"<br>";

 cout << "Time required to perform decryption operation on given integer : ";
 cout << (double)decryptEnd/CLOCKS_PER_SEC << " sec." << "</br>";

    cout << h3("To perform \"Homomorphic Operations\" press Operations button below.");

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



