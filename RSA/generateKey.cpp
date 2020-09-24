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


using namespace std;
using namespace cgicc;



static int MODULUS_SIZE , BLOCK_SIZE , BUFFER_SIZE;           
  

typedef struct {
    mpz_t n; /* Modulus */
    mpz_t e; /* Public Exponent */
} public_key;

typedef struct {
    mpz_t n; /* Modulus */
    mpz_t e; /* Public Exponent */
    mpz_t d; /* Private Exponent */
    mpz_t p; /* Starting prime p */
    mpz_t q; /* Starting prime q */
} private_key;



void setSize(int bitSize) {
    
    MODULUS_SIZE = bitSize;                   /* This is the number of bits we want in the modulus*/      
    BLOCK_SIZE = (MODULUS_SIZE/8);            /* This is the size of a block that gets en decrypted at once */
    BUFFER_SIZE = ((MODULUS_SIZE/8) / 2);     /* This is the number of bytes in n and p */
}

    

void print_hex(char* arr, int len)
{
    int i;
    for(i = 0; i < len; i++)
        printf("%02x", (unsigned char) arr[i]); 
}

/* NOTE: Assumes mpz_t's are initted in ku and kp */
void generate_keys(private_key* ku, public_key* kp)
{
    char buf[BUFFER_SIZE];
    int i;
    mpz_t phi; mpz_init(phi);
    mpz_t tmp1; mpz_init(tmp1);
    mpz_t tmp2; mpz_init(tmp2);

    srand(time(NULL));

    /* Insetead of selecting e st. gcd(phi, e) = 1; 1 < e < phi, lets choose e
     * first then pick p,q st. gcd(e, p-1) = gcd(e, q-1) = 1 */
    // We'll set e globally.  I've seen suggestions to use primes like 3, 17 or 
    // 65537, as they make coming calculations faster.  Lets use 3.
    mpz_set_ui(ku->e, 3); 

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
    /* Make sure this is a good choice*/
    mpz_mod(tmp2, ku->p, ku->e);        /* If p mod e == 1, gcd(phi, e) != 1 */
    while(!mpz_cmp_ui(tmp2, 1))         
    {
        mpz_nextprime(ku->p, ku->p);    /* so choose the next prime */
        mpz_mod(tmp2, ku->p, ku->e);
    }

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
        mpz_mod(tmp2, ku->q, ku->e);
        while(!mpz_cmp_ui(tmp2, 1))
        {
            mpz_nextprime(ku->q, ku->q);
            mpz_mod(tmp2, ku->q, ku->e);
        }
    } while(mpz_cmp(ku->p, ku->q) == 0); /* If we have identical primes (unlikely), try again */

    /* Calculate n = p x q */
    mpz_mul(ku->n, ku->p, ku->q);

    /* Compute phi(n) = (p-1)(q-1) */
    mpz_sub_ui(tmp1, ku->p, 1);
    mpz_sub_ui(tmp2, ku->q, 1);
    mpz_mul(phi, tmp1, tmp2);

    /* Calculate d (multiplicative inverse of e mod phi) */
    if(mpz_invert(ku->d, ku->e, phi) == 0)
    {
        mpz_gcd(tmp1, ku->e, phi);
        printf("gcd(e, phi) = [%s]\n", mpz_get_str(NULL, 16, tmp1));
        printf("Invert failed\n");
    }

    /* Set public key */
    mpz_set(kp->e, ku->e);
    mpz_set(kp->n, ku->n);

    return;
}


int main()
{

try 
{
    Cgicc formData;
       // Send HTTP header: Content-type: text/html
       cout << HTTPHTMLHeader() << endl;           

       cout << HTMLDoctype(HTMLDoctype::eStrict) << endl;


       // Prlong long: <html lang="en" dir="LTR">
       cout << html().set("lang", "EN").set("dir", "LTR") << endl;

       // Set up the HTML document
       cout << html() << head() << title("RSA Key Generation");
cout<<"<style>div {word-wrap: break-word; width: 100%; color:white;}</style>"<<endl;
cout<<"<style>h1{border-bottom: 6px solid;}</style>"<<endl;
cout<<"<style>input{ width: 40%; height: 8%; color: brown; border-radius: 60px; background: none; cursor: pointer; border: 2px solid #4caf50; color: white;}</style>"<<endl;
cout<<"<style>select{ width:40%; height:5%; border-radius: 30px; fontsize:10px; position: center; color: green;}</style>"<<endl;
       cout << head() << endl;
       cout << body().set("bgcolor","#191919").set("text","white").set("link","#0000ff").set("vlink","#000080") << endl;

       cout << h1("Keys of RSA Algorithm ") ;
  //generate keys
    form_iterator fvalue1 = formData.getElement("value1");
       if( !fvalue1->isEmpty() && fvalue1 != (*formData).end()) {
          //cout << "Value1: " << **fvalue1 << endl; } //modify

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
    mpz_init(kp.e); 
    
    mpz_init(ku.n); 
    mpz_init(ku.e); 
    mpz_init(ku.d); 
    mpz_init(ku.p); 
    mpz_init(ku.q); 
   
    generate_keys(&ku, &kp);

    file.open("valueOfn.txt");         
    file<<mpz_get_str(NULL, 16, ku.n);
    file.close();
    file.open("publicKey.txt");
    file<<mpz_get_str(NULL, 16, kp.e);
    file.close();
    file.open("privateKey.txt");
    file<<mpz_get_str(NULL, 16, ku.d);
    file.close();

    cout << h2("public key");
     cout << h3("value of n");
     cout << "<div>"<<mpz_get_str(NULL, 16, ku.n)<<"</div>" << "<br>";
     cout << h3("value of e");
     cout << "<div>"<<mpz_get_str(NULL, 16, kp.e)<<"</div>" << "<br>";
    
    cout << h2("private Key");
      cout << h3("value of n");
     cout << "<div>"<<mpz_get_str(NULL, 16, ku.n)<<"</div>" << "<br>";
     cout << h3("value of d");
     cout << "<div>"<<mpz_get_str(NULL, 16, ku.d)<<"</div>" << "<br>" << "</br>";

    keyEnd = clock();
    keyEnd = keyEnd - keyStart;


    cout << "Time taken to generate the keys : " ;
    cout << (double)keyEnd/CLOCKS_PER_SEC << " sec." << "</br>" << "</br>";  

  cout << "<form> <h2> Select a Datatype :</h2> <select class=\"dataType\" id=\"list\"> <option value=\"RSAInteger.cgi\"> Integer </option> <option value= \"RSAString.cgi\"> String </option> <option value=\"RSAMatrix.cgi\"> Matrix </option> <option value=\"RSAImage.cgi\"> Image </option> </select>  <br> <br> <br><input type=\"button\" value=\"submit\" class=\"submitEncryption\" onclick=\"goToNewPage()\"> </form>";


    cout << "<script type=\"text/javascript\"> function goToNewPage()                                   { var url = document.getElementById('list').value; if(url != 'none') { window.location = url; } } </script>";

    cout << body() << html();
     }
}
    catch(exception& e) {
       // handle any errors here.
       cout << "ERROR!!" << endl;
      }
  }

