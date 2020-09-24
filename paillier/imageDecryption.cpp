#include <iostream>
#include <cstdlib>
#include <gmp.h>
#include <fstream>
#include <gmp.h>

#include <cgicc/CgiDefs.h> 
#include <cgicc/Cgicc.h> 
#include <cgicc/HTTPHTMLHeader.h> 
#include <cgicc/HTMLClasses.h>
#define cimg_display 0
#include "CImg.h"

using namespace cgicc;
using namespace cimg_library;
using namespace std;


int main(int argc, char **argv)
{
  try {
    Cgicc cgi;
       // Send HTTP header: Content-type: text/html
       cout << HTTPHTMLHeader() << endl;           

       cout << HTMLDoctype(HTMLDoctype::eStrict) << endl;


       // Prlong long: <html lang="en" dir="LTR">
       cout << html().set("lang", "EN").set("dir", "LTR") << endl;

       // Set up the HTML document
       cout << html() << head() << title("PAILLIER Image Decryption") << endl;
cout<<"<style>h1{border-bottom: 6px solid;}</style>"<<endl;
   cout<<"<style>btn{ width: 40%; height: 10%; color: brown; border-radius: 60px; background: none; cursor: pointer; border: 2px solid #4caf50; color: white;}</style>"<<endl;
  cout<<head() << endl;
       cout << body().set("bgcolor","#191919").set("text","white").set("link","#0000ff").set("vlink","#000080") << endl;
       cout << h1("PAILLIER Image Decryption. ") << endl;


clock_t decryptStart, decryptEnd;
decryptStart = clock();

string slambda,sn,smu,sn_square,svalue;
mpz_t LAMBDA,N,MU,C,MD,N_sqr,tmp1,tmp2,tmp3;
mpz_inits(LAMBDA,N,MU,C,MD,N_sqr,tmp1,tmp2,tmp3,NULL);

ifstream file;

file.open("lambda.txt");
file>>slambda; 
file.close(); 
const char *lambda = slambda.c_str();

file.open("n.txt");
file>>sn; 
file.close(); 
const char *n = sn.c_str();

file.open("mu.txt");
file>>smu;
file.close(); 
const char *mu = smu.c_str();

file.open("n_square.txt");
file>>sn_square;
file.close(); 
const char *n_sqr = sn_square.c_str();

mpz_set_str(LAMBDA,lambda,10);
mpz_set_str(N,n,10);
mpz_set_str(MU,mu,10);
mpz_set_str(N_sqr,n_sqr,10);


file.open("encryptedImage"); 
string sval;
int width,height;
file>>width;
file>>height;

//ofstream f;
//f.open("decryptedImage.pgm", fstream::app);

unsigned int buff[height][width];
for(int x=0;x<height;x++){   
       for(int y=0;y<width;y++){  
file>>sval; 
const char *val = sval.c_str();
   mpz_set_str(C,val,10);                       //cout<<mpz_get_str(NULL,10,C);
   
     mpz_powm(tmp1,C,LAMBDA,N_sqr);
     mpz_sub_ui(tmp1,tmp1,1);
     mpz_cdiv_q(tmp1,tmp1,N);
     mpz_powm_ui(tmp2,MU,1,N);
     mpz_mul(tmp3,tmp1,tmp2);
     mpz_powm_ui(MD,tmp3,1,N); 
         
            
                      buff[x][y] = (unsigned int) mpz_get_ui(MD);
                      //f<<temp;
                          //cout << endl;   
                              //  cout << buff[x][y]<<" ";         
              

     }
  
   cout<<endl;
//f<<endl;

        }
    cout<< h2("IMAGE DECRYPTED SUCCESSFULLY");

decryptEnd = clock();
decryptEnd = decryptEnd - decryptStart;

 ifstream testFile,testFile_;
 testFile.open("result.pgm" ,ios_base::binary);
 testFile.seekg (0, ios_base::end);
 const auto end = testFile.tellg();
 
 int sizeFile = (int)end;

 cout << "Size of decrypted image file : "<< sizeFile << " bytes." << "</br>" << "</br>";


 cout << "Time required to perform decryption operation on given image : ";
 cout << (double)decryptEnd/CLOCKS_PER_SEC << " sec." << "</br>";


    auto hold_arr = (unsigned int*)&buff[0][0];
    cimg_library::CImg<unsigned int> img(hold_arr,width,height);
    img.save("result.pgm");

// f.close();
//cout<<"Content-Type: Image/pgm\r\n\r\n";
   
     // cout<< "<form method =\"post\" action = \"/cgi-bin/paillier/viewimage.html\" ><input type = \"submit\" /value = \"View Image \"> </form> ";
 

    cout << body() << html();

}
    catch(exception& e) {
       cout << "ERROR!!" << endl;
    }
   
    return 0;
}
     
     

