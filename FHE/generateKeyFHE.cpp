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
#include <stdio.h>

#include "cgicc/CgiDefs.h"
#include "cgicc/Cgicc.h"
#include "cgicc/HTTPHTMLHeader.h"
#include "cgicc/HTMLClasses.h"
#include "cgicc/HTTPRedirectHeader.h"

#include "seal/seal.h"

using namespace std;
using namespace seal;
using namespace cgicc;


void print_parameters(const shared_ptr<SEALContext> &context)
{
    auto &context_data = *context->context_data();

    /*
    Which scheme are we using?
    */
    string scheme_name;
    switch (context_data.parms().scheme())
    {
    case scheme_type::BFV:
        scheme_name = "BFV";
        break;
    case scheme_type::CKKS:
        scheme_name = "CKKS";
        break;
    default:
        throw invalid_argument("unsupported scheme");
    }

    cout << "/ Encryption parameters:" << endl;
    cout << "| scheme: " << scheme_name << endl;
    cout << "| poly_modulus_degree: " << 
        context_data.parms().poly_modulus_degree() << endl;

    /*
    Print the size of the true (product) coefficient modulus.
    */
    cout << "| coeff_modulus size: " << context_data.
        total_coeff_modulus().significant_bit_count() << " bits" << endl;

    /*
    For the BFV scheme print the plain_modulus parameter.
    */
    if (context_data.parms().scheme() == scheme_type::BFV)
    {
        cout << "| plain_modulus: " << context_data.
            parms().plain_modulus().value() << endl;
    }

    cout << "\\ noise_standard_deviation: " << context_data.
        parms().noise_standard_deviation() << endl;
    cout << endl;
}



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
        cout << html() << head() << title("Fully Homomorphic Encryption");
cout<<"<style>div {word-wrap: break-word; width: 100%; color:white;}</style>"<<endl;
cout<<"<style>h1{border-bottom: 6px solid;}</style>"<<endl;
cout<<"<style>input{ width: 40%; height: 8%; color: brown; border-radius: 60px; background: none; cursor: pointer; border: 2px solid #4caf50; color: white;}</style>"<<endl;
cout<<"<style>select{ width:40%; height:5%; border-radius: 30px; fontsize:10px; position: center; color: green;}</style>"<<endl;
       cout << head() << endl;
  cout << body().set("bgcolor","#191919").set("text","white").set("link","#0000ff").set("vlink","#000080") << endl;
       cout << h1("Fully Homomorphic Encryption");
 
       form_iterator fvalue1 = formData.getElement("poly_modulus_degree");
       if( !fvalue1->isEmpty() && fvalue1 != (*formData).end()) {
          //cout << "Value1: " << **fvalue1 << endl; 
                          } 

             string bits = **fvalue1;
             stringstream geek(bits);
             int bit;
             geek>>bit; 

    clock_t keyStart, keyEnd;

    keyStart = clock();

    ofstream file;
    file.open("poly_modulus_degree");
    file<<bit;
    file.close();
    
    EncryptionParameters parms(scheme_type::BFV);

    parms.set_poly_modulus_degree(bit);

       form_iterator fvalue2 = formData.getElement("coeff_modulus_degree");
       if( !fvalue2->isEmpty() && fvalue2 != (*formData).end()) {
          //cout << "Value1: " << **fvalue1 << endl; 
                          } 

             bits = **fvalue2;
             stringstream peek(bits);
             bit;
             peek>>bit; 
    file.open("coeff_modulus_degree");
    file<<bit;
    file.close();

    parms.set_coeff_modulus(coeff_modulus_128(bit));

    parms.set_plain_modulus(1 << 8);

    auto context = SEALContext::Create(parms);

    print_parameters(context);

    IntegerEncoder encoder(parms.plain_modulus());

    KeyGenerator keygen(context);
    PublicKey public_key = keygen.public_key();
    SecretKey secret_key = keygen.secret_key();
   
    keyEnd = clock();
    keyEnd = keyEnd - keyStart;

   cout << h2("Keys generated sucessfully.");

   cout << "Time taken to generate the keys : " ;
   cout << (double)keyEnd/CLOCKS_PER_SEC << " sec." << "</br>" << "</br>";  

cout << "<form> <select class=\"dataType\" id=\"list\"> <option value='none' selected> Select data type you wish to encrypt </option> <option value=\"FHEInteger.cgi\"> Integer </option> <option value= \"FHEString.cgi\"> String </option> <option value=\"FHEMatrix.cgi\"> Matrix </option> </select>  <br> <br> <input type=\"button\" value=\"submit\" class=\"submitEncryption\" onclick=\"goToNewPage()\"> </form>";

cout << "<script type=\"text/javascript\"> function goToNewPage()                                              { var url = document.getElementById('list').value; if(url != 'none') { window.location = url; } } </script>";

 
       

 cout << body() << html();
    }
    catch(exception& e) {
       // handle any errors here.
       cout << "ERROR!!" << endl;
    }
return 0;	
}
   
   
