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
#include <time.h>

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
        cout << html() << head() << title("Fully Homomorphic String Encryption");
cout<<"<style>div {word-wrap: break-word; width: 100%; color:white;}</style>"<<endl;
cout<<"<style>h1{border-bottom: 6px solid;}</style>"<<endl;
cout<<"<style>input{ width: 40%; height: 8%; color: brown; border-radius: 60px; background: none; cursor: pointer; border: 2px solid #4caf50; color: white;}</style>"<<endl;
cout<<"<style>select{ width:40%; height:5%; border-radius: 30px; fontsize:10px; position: center; color: green;}</style>"<<endl;
       cout << head() << endl;
  cout << body().set("bgcolor","#191919").set("text","white").set("link","#0000ff").set("vlink","#000080") << endl;
       cout << h1("Fully Homomorphic String Encryption");
       cout << h3("The string is encrypted by converting each character into ascii value and encrypting that ascii value.");
 
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


 int poly_modulus_degree,coeff_modulus_degree;

    ifstream file_obj;
    file_obj.open("poly_modulus_degree"); 
    file_obj>> poly_modulus_degree;
    file_obj.close();
    
    file_obj.open("coeff_modulus_degree"); 
    file_obj>>coeff_modulus_degree; 
    file_obj.close();
   
    
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

    Plaintext plainCharacterString[i+1];
    Ciphertext cipherCharacterString[i+1];
      
    clock_t encryptStart, encryptEnd;
    encryptStart = clock(); 
      
    for (int j=0;j<i;j++) {  
                 plainCharacterString[j] = encoder.encode(charString[j]);     
                 encryptor.encrypt(plainCharacterString[j], cipherCharacterString[j]);
                  }

    encryptEnd = clock();
    encryptEnd = encryptEnd-encryptStart;

    cout << "Given string encrypted." << "</br>";
     cout << "size of encrypted string : " << sizeof(cipherCharacterString) << " bytes." << "</br>" << "</br>";
   clock_t decryptStart, decryptEnd;

    decryptStart = clock();
    Plaintext plainResult[i];
 
    cout << "Decrypting result: ";
    
  for(int j=0; j<i; j++) {
    decryptor.decrypt(cipherCharacterString[j], plainResult[j]); }

    cout << "Done" << "</br>" << "</br>";
   
    decryptEnd = clock();
    decryptEnd = decryptEnd - decryptStart;
 
  char result[i];

 for (int j=0; j<i; j++) {
        
    cout << "Plaintext polynomial : " << plainResult[j].to_string() << "</br>";

   
    cout << "Decoded ascii value: " << "<strong>" << encoder.decode_int32(plainResult[j]) << "</strong>" << "</br>";
    result[j] = (char) encoder.decode_int32(plainResult[j]);
     
   }


 cout << h3("Resultant string after decryption :");
 for(int j=0; j<i; j++) {
         cout << result[j];
         }
       cout << "</br>" << "</br>";
                     


  cout << h3("Various Time Computations.");
  cout << "Time required to encrypt the string is : ";
  cout << (double)encryptEnd/CLOCKS_PER_SEC << " sec." << "</br>";


  cout << "Time required to decrypt the string is : ";
  cout << (double)decryptEnd/CLOCKS_PER_SEC << " sec." << "</br>";


  cout << body() << html();
    }
    catch(exception& e) {
       // handle any errors here.
       cout << "ERROR!!" << endl;
    }
return 0;	
}
   
    
    
    
    
  
         
