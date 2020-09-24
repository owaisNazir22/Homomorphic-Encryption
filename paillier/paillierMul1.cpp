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
       cout << html() << head() << title("Homomorphic multiplication of plaintexts") ;
cout<<"<style>div {word-wrap: break-word; width: 100%; color:white;}</style>"<<endl;
cout<<"<style>h1{border-bottom: 6px solid;}</style>"<<endl;
cout<<"<style>input{ width: 40%; height: 10%; color: brown; border-radius: 60px; background: none; cursor: pointer; border: 2px solid #4caf50; color: white;}</style>"<<endl;
cout<< head() << endl;
       cout << body().set("bgcolor","#191919").set("text","white").set("link","#0000ff").set("vlink","#000080") << endl;
       cout << h1("Homomorphic multiplication of palintexts") << endl;
       cout << h2("D(E(m<sub>2</sub>,r<sub>2</sub>)<sup>m<sub>1</sub></sup> mod n<sup>2</sup>) = m<sub>1</sub>.m<sub>2</sub> mod n.");

clock_t homomorphicStart, homomorphicEnd;
homomorphicStart = clock();
        
string slambda,sn,smu,sn_square,svalue,t1,t2;
mpz_t LAMBDA,N,MU,C,C1,C2,MD,N_sqr,tmp1,tmp2,tmp3,A,B,PT;
mpz_inits(LAMBDA,N,MU,C,C1,C2,MD,N_sqr,tmp1,tmp2,tmp3,A,B,PT,NULL);

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
file.open("plainTextInt1.txt");
file>>t1;
file.close(); 
const char *a = t1.c_str();

file.open("plainTextInt2.txt");
file>>t2;
file.close(); 
const char *b = t2.c_str();

file.open("value1.txt");
file>>svalue;
file.close(); 
const char *val = svalue.c_str(); 

mpz_set_str(C1,val,16); 

mpz_set_str(LAMBDA,lambda,10);
mpz_set_str(N,n,10);
mpz_set_str(MU,mu,10);
mpz_set_str(N_sqr,n_sqr,10);
mpz_set_str(A,a,10);
mpz_set_str(B,b,10);

file.open("plainTextInt2.txt");
file>>svalue;
file.close(); 
val = svalue.c_str();

mpz_set_str(C2,val,10);

mpz_powm(C,C1,C2,N_sqr); 
        

     //Homomorphic addition
     cout << h4("E(m<sub>1</sub>,r<sub>1</sub>)<sup>m<sub2</sub></sup> mod n<sup>2</sup>");
     cout << "<div>" << mpz_get_str(NULL,16,C)<< "<div>" "<br>"; 
     
     mpz_powm(tmp1,C,LAMBDA,N_sqr);
     mpz_sub_ui(tmp1,tmp1,1);
     mpz_cdiv_q(tmp1,tmp1,N);
     mpz_powm_ui(tmp2,MU,1,N);
     mpz_mul(tmp3,tmp1,tmp2);
     mpz_powm_ui(MD,tmp3,1,N);
     cout << h4("D(E(m<sub>1</sub>,r<sub>1</sub>).<sup>m<sub>2</sub></sup> mod n<sup>2</sup>)");
     cout << "<div>"<< mpz_get_str(NULL,10,MD)<< "<div>" "<br>"<<"<br>";
       mpz_mul(PT,A,B);
       cout << h4("m<sub>1</sub>.m<sub>2</sub> mod n");
        cout << "<div>" <<mpz_get_str(NULL,10,PT)<< "<div>" "<br>"<<"<br>";
     homomorphicEnd = clock();
     homomorphicEnd = homomorphicEnd - homomorphicStart;


     cout << "Time required to perform homomorphic operation and then decryption : ";
 cout << (double)homomorphicEnd/CLOCKS_PER_SEC << " sec." << "</br>";

     cout << h4("Press the button below to go to previous page");
     cout << "<form method=\"post\" action=\"/cgi-bin/paillier/intHomomorphicOperations.cgi\">";
     cout << "<input type=\"submit\" value=\"Back\">";
     cout << "</form>";

cout << body() << html();


}
    catch(exception& e) {
       // handle any errors here.
       cout << "ERROR!!" << endl;
    }
   
    return 0;
}







