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
        cout << html() << head() << title("Fully Homomorphic Integer Encryption");
cout<<"<style>div {word-wrap: break-word; width: 100%; color:white;}</style>"<<endl;
cout<<"<style>h1{border-bottom: 6px solid;}</style>"<<endl;
cout<<"<style>input{ width: 40%; height: 8%; color: brown; border-radius: 60px; background: none; cursor: pointer; border: 2px solid #4caf50; color: white;}</style>"<<endl;
cout<<"<style>select{ width:40%; height:5%; border-radius: 30px; fontsize:10px; position: center; color: green;}</style>"<<endl;
       cout << head() << endl;
  cout << body().set("bgcolor","#191919").set("text","white").set("link","#0000ff").set("vlink","#000080") << endl;
       cout << h1("Fully Homomorphic Integer Encryption");
 
       form_iterator fvalue1 = formData.getElement("value1");
       if( !fvalue1->isEmpty() && fvalue1 != (*formData).end()) {
          //cout << "Value1: " << **fvalue1 << endl; 
                          } 

             string bits = **fvalue1;
             stringstream geek(bits);
             int bit1,bit2;
             geek>>bit1; 

      form_iterator fvalue2 = formData.getElement("value2");
       if( !fvalue2->isEmpty() && fvalue2 != (*formData).end()) {
          //cout << "Value1: " << **fvalue1 << endl; 
                          } 

             bits = **fvalue2;
             stringstream peek(bits);
             peek>>bit2;

    int poly_modulus_degree,coeff_modulus_degree;

    ifstream file_obj;
    file_obj.open("poly_modulus_degree"); 
    file_obj>> poly_modulus_degree;
    file_obj.close();
    
    file_obj.open("coeff_modulus_degree"); 
    file_obj>>coeff_modulus_degree; 
    file_obj.close();
   
    clock_t keyStart, keyEnd, addStart, addEnd, mulStart, mulEnd, encryptStart, encryptEnd, decryptAddStart, decryptAddEnd, decryptMulStart, decryptMulEnd, encoderStart, encoderEnd;
   
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

    keyEnd = keyEnd-keyStart;

    encoderStart = clock();
       Plaintext plain1 = encoder.encode(bit1);
    cout << "Encoded " << bit1 << " as polynomial " << plain1.to_string() 
        << " (plain1)" << "</br>";
     encoderEnd = clock();

    
    Plaintext plain2 = encoder.encode(bit2);
    cout << "Encoded " << bit2 << " as polynomial " << plain2.to_string() 
        << " (plain2)" << "</br>" << "</br>";

    Ciphertext encrypted1, encrypted2;
   
    cout << "Encrypting plain1: ";
    encryptor.encrypt(plain1, encrypted1);
    cout << "Done (encrypted1)" << "</br>";
   
    encryptStart = clock();
    cout << "Encrypting plain2: ";
    encryptor.encrypt(plain2, encrypted2);
    cout << "Done (encrypted2)" << "</br>" << "</br>";
  
    cout << "Size of Encrypted Integer is : " << sizeof(encrypted1) << "</br>" << "</br>";

    encryptEnd = clock();
    encryptEnd = encryptEnd - encryptStart;

    cout << "Noise budget in encrypted1: " 
        << decryptor.invariant_noise_budget(encrypted1) << " bits" << "</br>";
    cout << "Noise budget in encrypted2: " 
        << decryptor.invariant_noise_budget(encrypted2) << " bits" << "</br>";

    cout << h3("Homomorphic Addition on integers.");

    addStart = clock();
   
    cout << "Performing Homomorphic Addition on encrypted integers as encrypted1+encrypted2" << "</br>";
    evaluator.add_inplace(encrypted1, encrypted2);

    addEnd = clock();
     
    cout << "Noise budget in encrypted1 + encrypted2: " 
        << decryptor.invariant_noise_budget(encrypted1) << " bits" << "</br>";
    cout<< "Homomorphic Addition done." << "</br>"; 

    decryptAddStart = clock();
    Plaintext plain_result_addition;
    cout << "Decrypting result: ";
    decryptor.decrypt(encrypted1, plain_result_addition);
    cout << "Done" << endl;
   
    decryptAddEnd = clock();
    decryptAddEnd = decryptAddEnd - decryptAddStart;
   
    cout << "</br>";


    /*
    Print the result plaintext polynomial.
    */
    cout << "Plaintext polynomial: " << plain_result_addition.to_string() << "</br>";

    /*
    Decode to obtain an integer result.
    */
    cout << "Decoded integer: " << "<strong>" << encoder.decode_int32(plain_result_addition) << "</strong>" << "</br>";
   
    cout << h3("Homomorphic Multiplication on integers as encrypted1*encrypted2");

    encryptor.encrypt(plain1, encrypted1);
  
    mulStart = clock();

    cout << "Performing Homomorphic Multiplication" << "</br>";
    evaluator.multiply_inplace(encrypted1, encrypted2);

    mulEnd = clock();

    mulEnd = mulEnd - mulStart;

    cout << "Noise budget in encrypted1 * encrypted2: "
        << decryptor.invariant_noise_budget(encrypted1) << " bits" << "</br>";
    cout << "Homomorphic Multiplication Done." << "</br>";

    /*
    Now we decrypt and decode our result.
    */
    decryptMulStart = clock();
    Plaintext plain_result;
    cout << "Decrypting result: ";
    decryptor.decrypt(encrypted1, plain_result);
    cout << "Done" << endl;
    decryptMulEnd = clock();
    decryptMulEnd = decryptMulEnd - decryptMulStart;

    /*
    Print the result plaintext polynomial.
    */
    cout << "Plaintext polynomial: " << plain_result.to_string() << "</br>";

    /*
    Decode to obtain an integer result.
    */
    cout << "Decoded integer: " << "<strong>" << encoder.decode_int32(plain_result) << "</strong>" << "</br>";

    cout << h3("Various Time Complexities");

    cout << "Time required to generate Keys and context setup : ";
    cout << (double)keyEnd/CLOCKS_PER_SEC << " sec." << "</br>";
 
    cout << "Time required to encode an integer : ";
    cout << (double)keyEnd/CLOCKS_PER_SEC << " sec." << "</br>";
    

    cout << "Time required to encrypt an integer : ";
    cout << (double)encryptStart/CLOCKS_PER_SEC << " sec." << "</br>";
    
    cout << "Time required to perform addition on encrypted integers : ";
    cout << (double)addEnd/CLOCKS_PER_SEC << " sec." << "</br>";

    cout << "Time required to perform decryption after homomorphic addition : ";
    cout << (double)decryptAddEnd/CLOCKS_PER_SEC << " sec." << "</br>";

    cout << "Time required to perform multiplication on encrypted integers : ";
    cout << (double)mulEnd/CLOCKS_PER_SEC << " sec." << "</br>";

    cout << "Time required to perform decryption after homomorphic multiplication : ";
    cout << (double)decryptMulEnd/CLOCKS_PER_SEC << " sec." << "</br>";
     
 cout << body() << html();
    }
    catch(exception& e) {
       // handle any errors here.
       cout << "ERROR!!" << endl;
    }
return 0;	
}
   
    
    
