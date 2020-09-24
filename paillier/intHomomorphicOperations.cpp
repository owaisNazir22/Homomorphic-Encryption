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
       cout << html() << head() << title("Homomorphic Operations")<<endl;
cout<<"<style>h1{border-bottom: 6px solid;}</style>"<<endl;
cout<<"<style>input{ width: 40%; height: 10%; color: brown; border-radius: 60px; background: none; cursor: pointer; border: 2px solid #4caf50; color: white;}</style>"<<endl;
cout << head() << endl;
       cout << body().set("bgcolor","#191919").set("text","white").set("link","#0000ff").set("vlink","#000080") << endl;
       cout << h1("Homomorphic Properties") << "<br>"; //modify this text so that it looks better on a web page
        
       //Homomorphic addition of plaintexts
       cout << h4("A notable feature of the paillier crytosystem is its homomorphic properties. As the encryption function is additively homomorphic. ");
       cout << h3("Homomorphic addition of plaintexts");
       cout << h6("The product of two ciphertexts will decrypt to the sum of their corresponding plaintexts,");
      //Edited code
       cout << "<h2>D(E(m<sub>1</sub>,r<sub>1</sub>).E(m<sub>2</sub>,r<sub>2</sub>) mod n<sup>2</sup>) = m<sub>1</sub>+m<sub>2</sub> mod n.</h2>";
       cout << "<form method=\"post\" action=\"/cgi-bin/paillier/paillierSumInt.cgi\">";
       cout << "<input type=\"submit\" value=\"Perform\">";
       cout << "</form>";

       cout << h6("The product of ciphertext with a plaintext raising g will decrypt to the sum of the corresponding plaintexts,");
       cout << "<h2>D(E(m<sub>1</sub>,r<sub>1</sub>).g<sup>m<sub>2</sub></sup> mod n<sup>2</sup>) = m<sub>1</sub>+m<sub>2</sub> mod n.</h2>";
       
       cout << "<form method=\"post\" action=\"/cgi-bin/paillier/paillierSumRisingG.cgi\">"<<endl;
       cout << "<input type=\"submit\" value=\"Perform\">";
       cout << "</form>";
        
       //Homomorphic multiplication of plaintexts
       cout << h3("Homomorphic multiplication of plaintexts");
       cout << h6("An encrypted palintext raised to the power of another plaintext will decrypt to the product of the two plaintexts,");
        cout << "<h2>D(E(m<sub>1</sub>,r<sub>1</sub>)<sup>m<sub>2</sub></sup> mod n<sup>2</sup>) = m<sub>1</sub>.m<sub>2</sub> mod n.</h2>";
        cout << "<form method=\"post\" action=\"/cgi-bin/paillier/paillierMul1.cgi\">";
        cout << "<input type=\"submit\" value=\"Perform\">";
        cout << "</form>";

        cout << "<h2>D(E(m<sub>2</sub>,r<sub>2</sub>)<sup>m<sub>1</sub></sup> mod n<sup>2</sup>) = m<sub>1</sub>.m<sub>2</sub> mod n.</h2>";
        cout << "<form method=\"post\" action=\"/cgi-bin/paillier/paillierMul2.cgi\">";
        cout << "<input type=\"submit\" value=\"Perform\">";
        cout << "</form>";

        cout << h6("More generally, an encrypted plaintext raised to a constant <emp>k</emp> will devrypt to the product of the plaintext and the constant,");
        cout << "<h2>D(E(m<sub>1</sub>,r<sub>1</sub>)<sup>k</sup> mod n<sup>2</sup>) = k.m<sub>1</sub> mod n.</h2>";
        cout << "<form method=\"post\" action=\"/cgi-bin/paillier/paillierMulRisingK.cgi\">";
        cout << "<input type=\"submit\" value=\"Perform\">";
        cout << "</form>";

        cout << h6("However, given the paillier encrytions of two messages there is no known way to compute an encryption of the product of messages without knowing the pivate key.");
         
        cout << h4("Press the button below to go to previous page"); 
        cout << "<form method=\"post\" action=\"/cgi-bin/paillier/encryptIntPaillier.cgi\">";
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






















     
