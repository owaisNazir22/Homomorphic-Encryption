#include <iostream>
#include <iostream>
#include <iomanip>
#include <vector>
#include <string>
#include <chrono>
#include <random>
#include <thread>
#include <mutex>
#include <memory>
#include <limits>
#include <complex>
#include <iterator>
#include <fstream>
#include <sstream>
#include <time.h>
#include <string.h>

#include "cgicc/CgiDefs.h"
#include "cgicc/Cgicc.h"
#include "cgicc/HTTPHTMLHeader.h"
#include "cgicc/HTMLClasses.h"
#include "cgicc/HTTPRedirectHeader.h"

#include "seal/seal.h"

using namespace std;
using namespace seal;
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
        cout << html() << head() << title("Fully Homomorphic Matrix Encryption");
cout<<"<style>div {word-wrap: break-word; width: 100%; color:white;}</style>"<<endl;
cout<<"<style>h1{border-bottom: 6px solid;}</style>"<<endl;
cout<<"<style>input{ width: 40%; height: 8%; color: brown; border-radius: 60px; background: none; cursor: pointer; border: 2px solid #4caf50; color: white;}</style>"<<endl;
cout<<"<style>select{ width:40%; height:5%; border-radius: 30px; fontsize:10px; position: center; color: green;}</style>"<<endl;
       cout << head() << endl;
  cout << body().set("bgcolor","#191919").set("text","white").set("link","#0000ff").set("vlink","#000080") << endl;
       cout << h1("Fully Homomorphic Matrix Encryption");
 
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

    int poly_modulus_degree,coeff_modulus_degree;

    ifstream file_obj;
    file_obj.open("poly_modulus_degree"); 
    file_obj>> poly_modulus_degree;
    file_obj.close();
    
    file_obj.open("coeff_modulus_degree"); 
    file_obj>>coeff_modulus_degree; 
    file_obj.close();
   
    //Generate keys and set context
    clock_t keyStart, keyEnd;
    keyStart = clock();
    
    EncryptionParameters parms(scheme_type::BFV);

    parms.set_poly_modulus_degree(poly_modulus_degree);

    parms.set_coeff_modulus(coeff_modulus_128(coeff_modulus_degree));

    parms.set_plain_modulus(1 << 8);

    auto context = SEALContext::Create(parms);

    IntegerEncoder encoder(parms.plain_modulus());

    KeyGenerator keygen(context);

    PublicKey public_key = keygen.public_key();
    SecretKey secret_key = keygen.secret_key();
   
    Encryptor encryptor(context, public_key);

    Evaluator evaluator(context);

    Decryptor decryptor(context, secret_key);

    keyEnd = clock();
    keyEnd = keyEnd - keyStart;
   
   
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

      clock_t encryptStart, encryptEnd;
      Plaintext plainMatrixAdd1[m1][n1], plainMatrixAdd2[m2][n2];
      Ciphertext encryptedMatrixAdd1[m1][n1], encryptedMatrixAdd2[m2][n2];
        
      encryptStart = clock();  //counts the encryption time of the matrix


              for(int k=0;k<m1;k++) {
                  for(int l=0;l<n1;l++) {
                       plainMatrixAdd1[k][l] = encoder.encode(matrix1[k][l]);     
                       encryptor.encrypt(plainMatrixAdd1[k][l], encryptedMatrixAdd1[k][l]);
                      }
                    }
     
     cout << "Matrix 1 encrypted." << "</br>";
     cout << "size of encrpted matrix 1 : " << sizeof(encryptedMatrixAdd1) << " bytes." << "</br>" << "</br>";
     encryptEnd = clock();
     encryptEnd = encryptEnd - encryptStart;
      

              for(int k=0;k<m2;k++) {
                  for(int l=0;l<n2;l++) {
                       plainMatrixAdd2[k][l] = encoder.encode(matrix2[k][l]);     
                       encryptor.encrypt(plainMatrixAdd2[k][l], encryptedMatrixAdd2[k][l]);
                      }
                    }
     cout << "Matrix 2 encrypted." << "</br>";
     cout << "size of encrpted matrix 2 : " << sizeof(encryptedMatrixAdd2) << " bytes." << "</br>" << "</br>";
     
     cout << h3("Homomorphic addition on matrices.");
     cout << h4("Preforming homomorphic addition operation.");
      
     clock_t matrixStart,matrixEnd;
     matrixStart = clock();

     if(m1 == m2 && n1 == n2) {
              
              for(int k=0;k<m1;k++) {
                  for(int l=0;l<n1;l++) {
                         evaluator.add_inplace(encryptedMatrixAdd1[k][l], encryptedMatrixAdd2[k][l]);
                                       }
                                    }
                              
     matrixEnd = clock();
     matrixEnd = matrixEnd-matrixStart;
     
     Plaintext plain_result_addition[m1][n1];

    //Decryption of resultant matrix
    cout << "Decrypting result" << "..." << "</br>";
    cout << "Matrix sum after decryption : " << "</br>" << "</br>";
    clock_t decryptStart, decryptEnd;
    decryptStart = clock();

    for(int k=0;k<m1;k++) {
                  for(int l=0;l<n1;l++) {
                             decryptor.decrypt(encryptedMatrixAdd1[k][l], plain_result_addition[k][l]);
                             cout << encoder.decode_int32(plain_result_addition[k][l]) << "     ";
                                        }
                                     cout << "</br>";
                                      }
    decryptEnd = clock();
    decryptEnd = decryptEnd - decryptStart;
                             cout << "</br>" << "Decryption complete." << "</br>" ;
                            }    //closing if condition 
   else cout << h4("Matrix addition not possible.");


   

      Plaintext plainMatrixMul1[m1][n1], plainMatrixMul2[m2][n2];
      Ciphertext encryptedMatrixMul1[m1][n1], encryptedMatrixMul2[m2][n2];


              for(int k=0;k<m1;k++) {
                  for(int l=0;l<n1;l++) {
                       plainMatrixMul1[k][l] = encoder.encode(matrix1[k][l]);     
                       encryptor.encrypt(plainMatrixMul1[k][l], encryptedMatrixMul1[k][l]);
                      }
                    }


              for(int k=0;k<m2;k++) {
                  for(int l=0;l<n2;l++) {
                       plainMatrixMul2[k][l] = encoder.encode(matrix2[k][l]);     
                       encryptor.encrypt(plainMatrixMul2[k][l], encryptedMatrixMul2[k][l]);
                      }
                    }
     
     
     //Matrix multiplication
     cout << h3("Homomorphic multiplication on matrices.");
     cout << h4("Preforming homomorphic multiplication on operation.");
      
     Ciphertext matrixMulResult[m1][n2];
     clock_t matrixMulStart, matrixMulEnd, decryptMulStart, decryptMulEnd;;
     matrixMulStart = clock();
     
    if(n1 == m2) {
         Plaintext plainZero = encoder.encode(0);
         Plaintext plaintemp_;
         Ciphertext encryptedZero;
         encryptor.encrypt(plainZero, encryptedZero);
              
             for(int k=0;k<m1;k++) {
                  for(int l=0;l<n2;l++) {
                            Ciphertext multemp[m2];
                      for(int m=0;m<n1;m++){
                         evaluator.multiply(encryptedMatrixMul1[k][m], encryptedMatrixMul2[m][l],multemp[m]);
                               if(m != 0) { evaluator.add_inplace(multemp[m],multemp[m-1]); } 
                                    }
                        evaluator.add(multemp[n1-1],encryptedZero,matrixMulResult[k][l]); 
                                 } 
                               }
                              
                 
     matrixMulEnd = clock();
     matrixMulEnd = matrixMulEnd - matrixMulStart;
     
     Plaintext plain_result_multiplication[m1][n1];

    //Decryption of resultant matrix
    cout << "Decrypting result" << "..." << "</br>";
    cout << "Matrix product after decryption : " << "</br>" << "</br>";

   decryptMulStart = clock();

    for(int k=0;k<m1;k++) {
                  for(int l=0;l<n2;l++) {
                             decryptor.decrypt(matrixMulResult[k][l], plain_result_multiplication[k][l]);
                             cout << encoder.decode_int32(plain_result_multiplication[k][l]) << "     ";
                                        }
                                    cout << "</br>";
                                      }
                                    
    decryptMulEnd = clock();
    decryptMulEnd = decryptMulEnd - decryptMulStart;
                              cout << "</br>" << "Decryption complete." << "</br>";
                            }    //closing if condition 
   else cout << h4("Matrix multiplication not possible.");


     

          
                      
 cout << h3("Various Time Computations.");
 cout << "Time required to generate Keys : ";
 cout << (double)keyEnd/CLOCKS_PER_SEC << " sec." << "</br>";

 cout << "Time required to encrypt the matrix is : ";
 cout << (double)encryptEnd/CLOCKS_PER_SEC << " sec." << "</br>";

 cout << "Time required to perform addition operation on matrices : ";
 cout << (double)matrixEnd/CLOCKS_PER_SEC << " sec." << "</br>";
                      
 cout << "Time required to perform decryption operation on resultant matrix containing the sum : ";
 cout << (double)matrixEnd/CLOCKS_PER_SEC << " sec." << "</br>";

 cout << "Time required to perform multipication operation on matrices : ";
 cout << (double)matrixMulEnd/CLOCKS_PER_SEC << " sec." << "</br>";

 cout << "Time required to perform decryption operation on resultant matrix containing the product : ";
 cout << (double)decryptMulEnd/CLOCKS_PER_SEC << " sec." << "</br>";

             

 cout << body() << html();
    }
    catch(exception& e) {
       // handle any errors here.
       cout << "ERROR!!" << endl;
    }
return 0;	
}
   
    
    
