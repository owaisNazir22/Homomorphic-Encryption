#include <gmp.h>
#include <fstream>
#include <iostream>
#include <sstream>
#include <fstream>
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
       cout << h4("A notable feature of the RSA crytosystem is its homomorphic properties. As the encryption function is multiplicatively homomorphic. ");
       cout << h3("Homomorphic multiplication of plaintexs.");
       cout << h6("The product of two ciphertexts will decrypt to the product of their corresponding plaintexts,");
       cout << h2("D(E(m<sub>1</sub>),E(m<sub>2</sub>) mod n) = m<sub>1</sub>*m<sub>2</sub> mod n.");

clock_t homomorphicStart, homomorphicEnd;
homomorphicStart = clock();

string svalue1, svalue2, slambda,sn;
mpz_t C1,C2,PT,A,B,CT,LAMBDA,N,M;
mpz_inits(C1,C2,PT,A,B,CT,LAMBDA,N,M,NULL);
ifstream file;


file.open("privateKey.txt");
file>>slambda; 
file.close(); 
const char *lambda = slambda.c_str();

file.open("valueOfn.txt");
file>>sn; 
file.close(); 
const char *n = sn.c_str();

mpz_set_str(LAMBDA,lambda,16);
mpz_set_str(N,n,16);

string sm1, sn1, sm2, sn2; int m1, n1, m2, n2;

file.open("matrixOneDimension.txt");
file>>sm1;
file>>sn1;
file.close();

file.open("matrixTwoDimension.txt");
file>>sm2;
file>>sn2;
file.close();

stringstream peek(sm1); peek>>m1;
stringstream geek(sn2); geek>>n2;  

ifstream file_1,file_2;
file_1.open("encryptedMatrix1.txt");

const char *val1, *val2;
file_1>>svalue1;
val1 = svalue1.c_str();
int resultMatrix[m1][n2], temp_ = 0;

             for(int k=0;k<m1;k++) {
                            file_2.open("encryptedMatrix2.txt");
                            file_2>>svalue2;
                            val2 = svalue2.c_str();
                            mpz_set_str(C1,val1,16);

                      for(int l=0;l<n2;l++){

                                    mpz_set_str(C2,val2,16);
                                    mpz_mul(CT,C1,C2);
                                    cout << h4("(E(m<sub>1</sub>)*E(m<sub>2</sub>) mod n : ");
                                    cout << "<div>"<< mpz_get_str(NULL,16,CT)<< "</div>";

                                    mpz_powm(M,CT,LAMBDA,N);
                                    mpz_powm_ui(M,M,1,N); 
                                    cout << h4("D(E(m<sub>1</sub>)*E(m<sub>2</sub>) mod n : ");
                                    cout << "<div>"<< mpz_get_str(NULL,10,M)<< "</div>" << "</br>";
                                    string temp = mpz_get_str(NULL,10,M);
                                    stringstream geek_(temp); geek_>>temp_;
                                    resultMatrix[k][l] = temp_;
                                      
                                    file_2>>svalue2;
                                    val2 = svalue2.c_str();
                                 } 
                               file_1>>svalue1; file_1>>svalue1;
                               val1 = svalue1.c_str();
                               file_2.close();
                               }
                          file_1.close();


cout << h3("Resultant matrix.");

for (int K=0;K<m1;K++) {
      for (int L=0;L<n2;L++) {
            cout << resultMatrix[K][L] << " ";
                  }
              cout << "</br>";
              }

cout << "</br>" << "</br>";
                   


     homomorphicEnd = clock();
     homomorphicEnd = homomorphicEnd - homomorphicStart;


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








      
       
