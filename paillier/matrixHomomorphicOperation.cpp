#include <gmp.h>
#include <fstream>
#include <iostream>
#include <sstream>
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
       cout << html() << head() << title("Matrix Homomorphic Operation") ;

cout<<"<style>div {word-wrap: break-word; width: 100%; color:white;}</style>"<<endl;
cout<<"<style>h1{border-bottom: 6px solid;}</style>"<<endl;
cout<<"<style>input{ width: 40%; height: 10%; color: brown; border-radius: 60px; background: none; cursor: pointer; border: 2px solid #4caf50; color: white;}</style>"<<endl;

       cout  <<  head() << endl;


       cout << body().set("bgcolor","#191919").set("text","white").set("link","#0000ff").set("vlink","#000080") << endl;
       cout << h1("Homomorphic Property") << "<br>"; //modify this text so that it looks better on a web page
        
       //Homomorphic addition of plaintexts
       cout << h4("A notable feature of the paillier crytosystem is its homomorphic properties. As the encryption function is additively homomorphic. ");
       cout << h3("Homomorphic addition of plaintexts");
       cout << h6("The product of two ciphertexts will decrypt to the sum of their corresponding plaintexts,");
       cout << h2("D(E(m1,r1).E(m2,r2) mod n^2) = m1+m2 mod n.");

clock_t homomorphicStart, homomorphicEnd;
homomorphicStart = clock();
       
       string slambda,sn,smu,sn_square,svalue1,svalue2;
mpz_t LAMBDA,N,MU,C,C1,C2,MD,N_sqr,tmp1,tmp2,tmp3;
mpz_inits(LAMBDA,N,MU,C,C1,C2,MD,N_sqr,tmp1,tmp2,tmp3,NULL);

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

mpz_set_str(LAMBDA,lambda,10);
mpz_set_str(N,n,10);
mpz_set_str(MU,mu,10);
mpz_set_str(N_sqr,n_sqr,10);

ifstream file_1,file_2;
file_1.open("encryptedMatrix1.txt");
file_2.open("encryptedMatrix2.txt");
const char *val;
file_1>>svalue1;
file_2>>svalue2;

string slashCheck;
slashCheck.push_back('/');

vector<int> matrix; string matrix_element; int matrix_int_element;
int k = 0, l = 0;


while (!file_1.eof()) {


val = svalue1.c_str();  
mpz_set_str(C1,val,16); 

val = svalue2.c_str();    
mpz_set_str(C2,val,16);  


 if(svalue1.compare(slashCheck)==0) { k++; l=0; file_1 >> svalue1; file_2 >> svalue2;}
 
 else {       
     //Homomorphic addition
     mpz_mul(C,C1,C2);
     cout << h4("E(m1,r1).E(m2,r2) mod n^2");
     cout << "<div>" << mpz_get_str(NULL,16,C) << "</div>" <<"<br>"; 
     
     mpz_powm(tmp1,C,LAMBDA,N_sqr);
     mpz_sub_ui(tmp1,tmp1,1);
     mpz_cdiv_q(tmp1,tmp1,N);
     mpz_powm_ui(tmp2,MU,1,N);
     mpz_mul(tmp3,tmp1,tmp2);
     mpz_powm_ui(MD,tmp3,1,N);
     cout << h4("D(E(m1,r1).E(m2,r2) mod n^2)");
     cout << mpz_get_str(NULL,10,MD) <<"<br>"<<"<br>";
     matrix_element = mpz_get_str(NULL,10,MD);
     stringstream peek(matrix_element); peek>>matrix_int_element;
     matrix.push_back(matrix_int_element);
     file_1>>svalue1;
     file_2>>svalue2;
     l++;
   }
}

     homomorphicEnd = clock();
     homomorphicEnd = homomorphicEnd - homomorphicStart;

int track = 0;

cout << h3("Resultant matrix.");

for (int K=0;K<=k;K++) {
      for (int L=0;L<l;L++) {
            cout << matrix[track] << " ";
                track++;
                  }
              cout << "</br>";
              }

cout << "</br>" << "</br>";

 cout << "Time required to perform homomorphic operation on matrix : ";
 cout << (double)homomorphicEnd/CLOCKS_PER_SEC << " sec." << "</br>";
    


file_1.close();
file_2.close();


cout << body() << html();


}
    catch(exception& e) {
       // handle any errors here.
       cout << "ERROR!!" << endl;
    }
   
    return 0;
}






