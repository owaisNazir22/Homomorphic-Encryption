#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <string>
#include <sstream>
#include <time.h>
#include <gmp.h>
#include <fstream>
#include <iostream>
#include "cgicc/CgiDefs.h"
#include "cgicc/Cgicc.h"
#include "cgicc/HTTPHTMLHeader.h"
#include "cgicc/HTMLClasses.h"
#include "cgicc/HTTPRedirectHeader.h"

//#include "styles.h"
static int MODULUS_SIZE,BLOCK_SIZE,BUFFER_SIZE;  

using namespace std;
using namespace cgicc;

typedef struct {
    mpz_t n; 
    mpz_t g;
} public_key;

typedef struct {
    mpz_t lambda;
    mpz_t g;
    mpz_t mu; 
    mpz_t p; /* Starting prime p */
    mpz_t q; /* Starting prime q */
    mpz_t n_square;
    mpz_t r;
} private_key;

void setSize(int bitSize) {
    
    MODULUS_SIZE = bitSize;                   /* This is the number of bits we want in the modulus*/      
    BLOCK_SIZE = (MODULUS_SIZE/8);            /* This is the size of a block that gets en decrypted at once */
    BUFFER_SIZE = ((MODULUS_SIZE/8) / 2);     /* This is the number of bytes in n and p */
}

void generate_keys(private_key* ku, public_key* kp)
{
    char buf[BUFFER_SIZE];
    int i;
    mpz_t phi; mpz_init(phi);
    mpz_t tmp1; mpz_init(tmp1);
    mpz_t tmp2; mpz_init(tmp2);
    mpz_t tmp3; mpz_init(tmp3);

    mpz_set_ui(ku->r, 3); 

    srand(time(NULL));

    /* Select p and q */
    /* Start with p */
    // Set the bits of tmp randomly
    for(i = 0; i < BUFFER_SIZE; i++)
        buf[i] = rand() % 0xFF; 
    // Set the top two bits to 1 to ensure int(tmp) is relatively large
    buf[0] |= 0xC0;
    // Set the bottom bit to 1 to ensure int(tmp) is odd (better for finding primes)
    buf[BUFFER_SIZE - 1] |= 0x01;
    // Interpret this char buffer as an int
    mpz_import(tmp1, BUFFER_SIZE, 1, sizeof(buf[0]), 0, 0, buf);
    // Pick the next prime starting from that random number
    mpz_nextprime(ku->p, tmp1);

     /* Now select q */
    do {
        for(i = 0; i < BUFFER_SIZE; i++)
            buf[i] = rand() % 0xFF; 
        // Set the top two bits to 1 to ensure int(tmp) is relatively large
        buf[0] |= 0xC0;
        // Set the bottom bit to 1 to ensure int(tmp) is odd
        buf[BUFFER_SIZE - 1] |= 0x01;
        // Interpret this char buffer as an int
        mpz_import(tmp1, (BUFFER_SIZE), 1, sizeof(buf[0]), 0, 0, buf);
        // Pick the next prime starting from that random number
        mpz_nextprime(ku->q, tmp1);
        
    } while(mpz_cmp(ku->p, ku->q) == 0); /* If we have identical primes (unlikely), try again */


    /* Calculate n = p x q */
    mpz_mul(kp->n, ku->p, ku->q);
    
    /*Calculate p-1 and q-1 and store in tmp1 and tmp2*/
    mpz_sub_ui(tmp1,ku->p,1); 
    mpz_sub_ui(tmp2,ku->q,1); 

    /*Calulate lambda = lcm(p-1,q-1)*/
    mpz_lcm(ku->lambda,tmp1,tmp2);

    /*For easy encryption calculations let us keep g as 2*/
    mpz_set_ui(kp->g,5); 
    
    //Calculate n*n and store in n_square
    mpz_mul(ku->n_square,kp->n,kp->n); 
    /*Calculate g^lambda mod n and store in tmp1*/
    mpz_powm(tmp1,kp->g,ku->lambda,ku->n_square); 

    /*Calulate l(x) = (x-1)/n ,where x = g^lambda mod n = tmp2*/
    mpz_sub_ui(tmp2,tmp1,1);  
    mpz_cdiv_q(tmp3,tmp2,kp->n); 
 
    
    /*Compute mu */
    mpz_invert(ku->mu,tmp3,kp->n);   
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
       cout << html() << head() << title("Paillier Key Generation");
cout<<"<style>div {word-wrap: break-word; width: 100%; color:white;}</style>"<<endl;
cout<<"<style>h1{border-bottom: 6px solid;}</style>"<<endl;
cout<<"<style>input{ width: 40%; height: 8%; color: brown; border-radius: 60px; background: none; cursor: pointer; border: 2px solid #4caf50; color: white;}</style>"<<endl;
cout<<"<style>select{ width:40%; height:5%; border-radius: 30px; fontsize:10px; position: center; color: green;}</style>"<<endl;
       cout << head() << endl;
       cout << body().set("bgcolor","#191919").set("text","white").set("link","#0000ff").set("vlink","#000080") << endl;

       cout << h1("Keys of Paillier Algorithm ") << "<br>";

     
    //Generate key 
   form_iterator fvalue1 = formData.getElement("value1");
       if( !fvalue1->isEmpty() && fvalue1 != (*formData).end()) {
          //cout << "Value1: " << **fvalue1 << endl; 
                          } 

             string bits = **fvalue1;
             stringstream geek(bits);
             int bit;
             geek>>bit; 

    clock_t keyStart, keyEnd;
    keyStart = clock();

    setSize(bit);
    private_key ku;
    public_key kp;
    ofstream file;

    // Initialize public key
    mpz_init(kp.n);
    mpz_init(kp.g); 
    // Initialize private key
    mpz_init(ku.lambda); 
    mpz_init(ku.mu); 
    mpz_init(ku.p); 
    mpz_init(ku.q); 
    mpz_init(ku.n_square); 
    mpz_init(ku.r);

    generate_keys(&ku, &kp);
    
    keyEnd = clock();
    keyEnd = keyEnd - keyStart;

    file.open("n.txt");         
    file<<mpz_get_str(NULL, 10, kp.n);
    file.close();
    file.open("g.txt");
    file<<mpz_get_str(NULL, 10, kp.g);
    file.close();
    file.open("r.txt");
    file<<mpz_get_str(NULL, 10, ku.r);
    file.close();
    file.open("n_square.txt");
    file<<mpz_get_str(NULL, 10, ku.n_square);
    file.close();
    file.open("lambda.txt");
    file<<mpz_get_str(NULL, 10, ku.lambda);
    file.close();
    file.open("mu.txt");
    file<<mpz_get_str(NULL, 10, ku.mu);
    file.close();


    cout << h2("public key");
    cout << h3("value of n");
    cout << "<div>"<<mpz_get_str(NULL, 16, kp.n)<<"</div>" << "<br>";
    cout << h3("value of g");
    cout << "<div>"<<mpz_get_str(NULL, 16, kp.g)<<"</div>" << "<br>"<<"<br>";

    cout << h2("private key");
    cout << h3("value of lambda");
    cout << "<div>"<<mpz_get_str(NULL, 16, ku.lambda)<<"</div>"<< "<br>";
    cout << h3("value of mu");
    cout << "<div>" <<mpz_get_str(NULL, 16, ku.mu)<<"</div>" << "<br>"<<"<br>";

    cout << "Time taken to generate the keys : " ;
    cout << (double)keyEnd/CLOCKS_PER_SEC << " sec." << "</br>" << "</br>";  

    cout << "<form> <h2> Select a Datatype :</h2> <select class=\"dataType\" id=\"list\"> <option value=\"paillierInteger.cgi\"> Integer </option> <option value= \"paillierString.cgi\"> String </option> <option value=\"paillierMatrix.cgi\"> Matrix </option> <option value=\"paillierImage.cgi\"> Image </option> </select>  <br> <br> <br><input type=\"button\" value=\"submit\" class=\"submitEncryption\" onclick=\"goToNewPage()\"> </form>";


    cout << "<script type=\"text/javascript\"> function goToNewPage()                                   { var url = document.getElementById('list').value; if(url != 'none') { window.location = url; } } </script>";

   
    cout << body() << html();
    }
    catch(exception& e) {
       // handle any errors here.
       cout << "ERROR!!" << endl;
    }	
}
    
 
   
    


