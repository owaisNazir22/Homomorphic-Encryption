#include <string.h>
#include <string>
#include <sstream>
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
       cout << html() << head() << title("Homomorphic multiplication of plaintexts") ;
cout<<"<style>div {word-wrap: break-word; width: 100%; color:white;}</style>"<<endl;
cout<<"<style>h1{border-bottom: 6px solid;}</style>"<<endl;
cout<<"<style>input{ width: 40%; height: 10%; color: brown; border-radius: 60px; background: none; cursor: pointer; border: 2px solid #4caf50; color: white;}</style>"<<endl;
cout<< head() << endl;
       cout << body().set("bgcolor","#191919").set("text","white").set("link","#0000ff").set("vlink","#000080") << endl;
       cout << h1("Homomorphic multiplication") << endl;
       cout <<h2("The product of two cipher texts equals the product of two plain texts after decryption.");
       cout << h2("D(E(m<sub>1</sub>)*(m<sub>2</sub>)) mod n) = m<sub>1</sub>.m<sub>2</sub> mod n.");


clock_t homomorphicStart, homomorphicEnd;
homomorphicStart = clock();

string ct1,ct2,t1,t2,slambda,sn;
mpz_t C1,C2,PT,A,B,CT,LAMBDA,N,M;
mpz_inits(C1,C2,PT,A,B,CT,LAMBDA,N,M,NULL);
ifstream file;

file.open("value1.txt");
file>>ct1; 
file.close(); 
const char *val1 = ct1.c_str();

file.open("value2.txt");
file>>ct2; 
file.close(); 
const char *val2 = ct2.c_str();
file.open("plaintext1.txt");
file>>t1;
file.close(); 
const char *a = t1.c_str();

file.open("plaintext2.txt");
file>>t2;
file.close(); 
const char *b = t2.c_str();

file.open("privateKey.txt");
file>>slambda; 
file.close(); 
const char *lambda = slambda.c_str();

file.open("valueOfn.txt");
file>>sn; 
file.close(); 
const char *n = sn.c_str();


mpz_set_str(A,a,10);
mpz_set_str(B,b,10);
mpz_set_str(C1,val1,16);
mpz_set_str(C2,val2,16);
mpz_set_str(LAMBDA,lambda,16);
mpz_set_str(N,n,16);


      
       mpz_mul(CT,C1,C2);
       mpz_powm(M,CT,LAMBDA,N);
    mpz_powm_ui(M,M,1,N); 
 cout << h4("D(E(m<sub>1</sub>)*E(m<sub>2</sub>) mod n");
     cout << "<div>"<< mpz_get_str(NULL,10,M)<< "<div>" "<br>"<<"<br>";

       mpz_mul(PT,A,B);
       cout << h4("(m<sub>1</sub>*m<sub>2</sub>) mod n");
        cout << "<div>" <<mpz_get_str(NULL,10,PT)<< "<div>" "<br>"<<"<br>";

     homomorphicEnd = clock();
     homomorphicEnd = homomorphicEnd - homomorphicStart;


{
ofstream file;
file.open("homomorphicOperationResult.txt");
file<<mpz_get_str(NULL,16,CT);
file.close();
}

 ifstream testFile;
 testFile.open("homomorphicOperationResult.txt" ,ios_base::binary);
 testFile.seekg (0, ios_base::end);
 const auto end = testFile.tellg();
 
 float sizeFile = (float)end/2;

 cout << "Size of E(m<sub1</sub>).E(m<sub>2</sub>) mod n : "<< sizeFile << " bytes" << "</br>" << "</br>";

     cout << "Time required to perform homomorphic operation and then decryption : ";
 cout << (double)homomorphicEnd/CLOCKS_PER_SEC << " sec." << "</br>";
    


     cout << h4("Press the button below to go to previous page");
     cout << "<form method=\"post\" action=\"/cgi-bin/RSA/decryptIntRSA.cgi\">";
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







