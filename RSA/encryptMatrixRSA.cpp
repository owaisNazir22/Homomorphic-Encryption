#include <iostream>
#include <string>
#include <sstream>
#include <time.h>
#include <gmp.h>
#include <fstream>

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
       cout << html() << head() << title("RSA Matrix Encryption.") << endl;
cout<<"<style>div {word-wrap: break-word; width: 100%; color:white;}</style>"<<endl;
cout<<"<style>h1{border-bottom: 6px solid;}</style>"<<endl;
cout<<"<style>input{ width: 40%; height: 10%; color: brown; border-radius: 60px; background: none; cursor: pointer; border: 2px solid #4caf50; color: white;}</style>"<<endl;
  cout<<head() << endl;
       cout << body().set("bgcolor","#191919").set("text","white").set("link","#0000ff").set("vlink","#000080") << endl;
       cout << h1("RSA Matrix Encryption. ") << endl;

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


       form_iterator fvalue1 = formData.getElement("dimension1");
       if( !fvalue1->isEmpty() && fvalue1 != (*formData).end()) {
         //cout << h1("ERROR : fill the size of matrix ist"); 
                          } 
             int m1,n1,m2,n2; //dimensions of two matrices
             string dimensionString = **fvalue1; 
             const char *dimension = dimensionString.c_str(); 
             char temp; string stemp; int j = 0,i = 0;
             


     while (1) {
      temp = dimension[i];
      if(temp != ',' && temp != '\0') {
             stemp.push_back(temp);
             i++;
             }
      else {
             if(j==0) {stringstream geek(stemp); geek>>m1; j++; stemp.clear();}
             else {stringstream peek(stemp); peek>>n1;}
             i++;
           }
      if(temp == '\0') break;
         }
 
     form_iterator fvalue2 = formData.getElement("dimension2");
       if( !fvalue2->isEmpty() && fvalue2 != (*formData).end()) {
          //cout << h1("ERROR : fill the dimensions of matrix second");
                          } 
       dimensionString = **fvalue2; 
       dimension = dimensionString.c_str(); 

      i = 0,j = 0;
      stemp.clear();
{
ofstream file;

file.open("matrixOneDimension.txt");
file<<m1<<endl<<n1;
file.close();
}
 
      while (1) {
      temp = dimension[i];
      if(temp != ',' && temp != '\0') {
             stemp.push_back(temp);
             i++;
             }
      else {
             if(j==0) {stringstream geek(stemp); geek>>m2; j++; stemp.clear();}
             else {stringstream peek(stemp); peek>>n2;}
             i++;
           }
      if(temp == '\0') break;
         }

{
ofstream file;

file.open("matrixTwoDimension.txt");
file<<m2<<endl<<n2;
file.close();
}

{

   
   int matrix1[m1][n1], matrix2[m2][n2];


    form_iterator fvalue3 = formData.getElement("matrix1");
       if( !fvalue1->isEmpty() && fvalue1 != (*formData).end()) {
          //cout << "Value1: " << **fvalue1 << endl; 
                          } 

             string matrix = **fvalue3; 
             const char *matrixString = matrix.c_str();
             string stringTemp;
             int M1 = 0, N1 = 0, M2 = 0, N2 = 0, inttemp; i = 0;

    while (1) {
      temp = matrixString[i]; 
      if(temp != ',' && temp != '/' && temp !='\0') {
             stringTemp.push_back(temp);
             i++;
             }
      else { 
             stringstream geek(stringTemp); geek >> inttemp;
             matrix1[M1][N1] = inttemp;
             stringTemp.clear();
             N1++; i++;
             if(M1 == n1) { N1 = 0; M1++;}
           }
      if(temp == '\0') break;
       }

    cout << h4("Matrices entered.");
    cout << "Matrix 1" << "</br>" << "</br>";
    for (int k=0;k<m1;k++) {
      for (int l=0;l<n1;l++) {
            cout << matrix1[k][l] << " ";
                   }
              cout << "</br>";
              }

    form_iterator fvalue4 = formData.getElement("matrix2");
       if( !fvalue1->isEmpty() && fvalue1 != (*formData).end()) {
          //cout << "Value1: " << **fvalue1 << endl; 
                          } 

             matrix = **fvalue4; 
             matrixString = matrix.c_str();
             i = 0; stringTemp.clear();

    while (1) {
      temp = matrixString[i]; 
      if(temp != ',' && temp != '/' && temp !='\0') {
             stringTemp.push_back(temp);
             i++;
             }
      else { 
             stringstream geek(stringTemp); geek >> inttemp;
             matrix2[M2][N2] = inttemp;
             stringTemp.clear();
             N2++; i++;
             if(M2 == n2) { N2 = 0; M2++;}
           }
      if(temp == '\0') break;
       }

    cout << "</br>" << "</br>";

    cout << "Matrix 2" << "</br>" << "</br>";
    for (int k=0;k<m2;k++) {
      for (int l=0;l<n2;l++) {
            cout << matrix2[k][l] << " ";
                   }
              cout << "</br>";
              } 

         cout << "</br>";
}

     form_iterator fvalue3 = formData.getElement("matrix1");
       if( !fvalue3->isEmpty() && fvalue3 != (*formData).end()) {
          //cout << "Value1: " << **fvalue1 << endl; 
                          } 

             string bits = **fvalue3; 
             const char *arrayString = bits.c_str();



encryptEnd = clock();
encryptEnd = encryptEnd - encryptStart;

temp = 1;
i = 0;
const char *m;
string sm;

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

    mpz_powm(C, M, E, N); 
    cout << "Encrypted Number of position  ["<< k << "]"<< "[" << l << "]" << ":" << "</br>" << "<div>" << mpz_get_str(NULL,16,C) << "</div>" << "</br>" << "</br>";
    l++;
    if (temp == '/') { file_<< mpz_get_str(NULL,16,C) << endl; file_ << "/" << endl; k++; l=0; }
    else file_  << mpz_get_str(NULL,16,C)  << endl;
    
    sm.clear();
    i++;
   }
     if(temp == '\0') break;      
}
file_.close();

encryptEnd = clock();
encryptEnd = encryptEnd - encryptStart;


form_iterator fvalue4 = formData.getElement("matrix2");
       if( !fvalue4->isEmpty() && fvalue4 != (*formData).end()) {
          //cout << "Value2: " << **fvalue2 << endl; 
                          } 

             bits = **fvalue4;
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

    mpz_powm(C, M, E, N); 
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
 float sizeFile = (float)end;

 cout << "Size of encrypted matrix one : "<< sizeFile << " bytes." << "</br>" << "</br>";

 testFile.open("encryptedMatrix2.txt" ,ios_base::binary);
 testFile.seekg (0, ios_base::end);
 const auto end_ = testFile.tellg();
 testFile.close();
 sizeFile = (float)end_;
 

 cout << "Size of encrypted matrix two : "<< sizeFile << " bytes." << "</br>" << "</br>";

 cout << "Time required to encrypt the matrix is : ";
 cout << (double)encryptEnd/CLOCKS_PER_SEC << " sec." << "</br>";


    cout << h5("To decrypt the numbers press <emp><strong>Decrypt</emp></strong> button or to perform \"Homomorphic Multiplication\" press <emp><strong>Operations</emp></strong>., if \"Homomorphic Multiplication\" button is then the dimension you entered could not satisfy the homomorphic multiplication contrain.");
    
    cout << "<form method=\"post\" action=\"/cgi-bin/RSA/decryptMatrixRSA.cgi\">";
    cout << "<input type=\"submit\" value=\"Decrypt\">";
    cout << "</form>";
    
    if(n1 == 1 && m2 == 1) {

    cout << "<form method=\"post\" action=\"/cgi-bin/RSA/matrixHomomorphicOperation.cgi\">";
    cout << "<input type=\"submit\" value=\"Homomorphic Multiplication\">";
    cout << "</form>"; 
    }
    else cout << h2("Homomorphic Multiplication not possible.");


 cout << body() << html();
    }
    catch(exception& e) {
       // handle any errors here.
       cout << "ERROR!!" << endl;
    }
return 0;	
}
   


