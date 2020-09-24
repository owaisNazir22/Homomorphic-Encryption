#include <iostream>

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
       cout << html() << head() << title("Fully Homomorphic Encryption");
cout<<"<style>div {word-wrap: break-word; width: 100%; color:white;}</style>"<<endl;
cout<<"<style>h1{border-bottom: 6px solid;}</style>"<<endl;
cout<<"<style>input{ width: 40%; height: 8%; color: brown; border-radius: 60px; background: none; cursor: pointer; border: 2px solid #4caf50; color: white;}</style>"<<endl;
cout<<"<style>select{ width:40%; height:5%; border-radius: 30px; fontsize:10px; position: center; color: green;}</style>"<<endl;
       cout << head() << endl;
  cout << body().set("bgcolor","#191919").set("text","white").set("link","#0000ff").set("vlink","#000080") << endl;

       cout << h1("Fully Homomorphic Encryption");
      
       cout << h4("Fully  homomorphic  encryption  (FHE)  allows  evaluation  of  arbitrary  functions  on encrypted data, and as such has a myriad of potential applications such as private cloud computing.Craig Gentry  in september 2009 was the first to show that FHE is theoretically possible.");

       cout << h4("In this demostration we are using seal library (BFV Scheme) to demonstrate fully homomorphic encryption scheme.");

       cout << h4("In this example we demonstrate setting up encryption parameters and other relevant objects for performing simple computations on encrypted integers.");
       
       cout << h3("The first task is to set up an instance of the EncryptionParameters class.It is critical to understand how these different parameters behave, how they affect the encryption scheme, performance, and the security level. There are three encryption parameters that are necessary to set:");
  
       cout << h3("- poly_modulus_degree (degree of polynomial modulus)");

       cout << h3("- coeff_modulus ([ciphertext] coefficient modulus)");
        
       cout << h3(" - plain_modulus (plaintext modulus)");

       cout << h3("- A fourth parameter -- noise_standard_deviation -- has a default value 3.19.");

       cout << h4("The first parameter we set is the degree of the polynomial modulus. This must be a positive power of 2, representing the degree of a power-of-2 cyclotomic polynomial; it is not necessary to understand what this means. The polynomial modulus degree should be thought of mainly affecting the security level of the   scheme: larger degree makes the scheme more secure. Larger degree also makes  ciphertext sizes larger, and consequently all operations slower. Recommended degrees are 1024, 2048, 4096, 8192, 16384, 32768, but it is also possible to go beyond this. In this example we use a relatively small polynomial modulus.");
     
      cout << "<form method=\"post\" action=\"/cgi-bin/FHE/generateKeyFHE.cgi\">";
      cout << "<h4>Set the polynomial modulus degree.</h4>";
      cout << "<input type=\"text\" name=\"poly_modulus_degree\">";

      cout << h4(" Next we set the [ciphertext] coefficient modulus (coeff_modulus). The size of the coefficient modulus should be thought of as the most significant factor in determining the noise budget in a freshly encrypted ciphertext: bigger means more noise budget, which is desirable. On the other hand, a larger coefficient modulus lowers the security level of the scheme. Thus,if a large noise budget is required for complicated computations, a large coefficient modulus needs to be used, and the reduction in the security level must be countered by simultaneously increasing the polynomial modulus. Overall, this will result in worse performance.In this example we use the default coefficient modulus for a 128-bit security level. Concretely, this coefficient modulus consists of only one 54-bit prime factor: 0x3fffffff000001.");
     
      cout << h4("Set the cofficient modulus degree.");
      
      cout << h6("Recommended degrees are 1024, 2048, 4096, 8192, 16384, 32768, but it is also possible to go beyond this.It is better to stick with the above given value.");

      cout << "<input type=\"text\" name=\"coeff_modulus_degree\">";

      cout << h4("The plaintext modulus can be any positive integer, even though here we take it to be a power of two. In fact, in many cases one might instead want it to be a prime number. The plaintext modulus determines the size of the plaintext data type but it also affects the noise budget in a freshly encrypted ciphertext and the consumption of noise budget in homomorphic (encrypted) multiplications. Thus, it is essential to try to keep the plaintext data type as small as possible for best performance. The noise budget in a freshly encrypted ciphertext is : ");
    
      cout << h2(" ~ log2(coeff_modulus/plain_modulus) (bits)");

      cout << h4("It is set to default value for efficience considerations");
 
      cout << "<input type=\"submit\" value=\"Submit\">";
      cout << "</form>";

     

 cout << body() << html();
    }
    catch(exception& e) {
       // handle any errors here.
       cout << "ERROR!!" << endl;
    }
return 0;	
}
    
 
   
    

