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
       cout << html() << head() << title("RSA Image Decryption") << endl;
cout<<"<style>h2 {font: 20px; color:white;}</style>"<<endl;
cout<<"<style>h1{border-bottom: 6px solid;}</style>"<<endl;
cout<<"<style>input{  position: absolute; r; width: 40%; height: 10%; color: brown; border-radius: 60px; background: none; cursor: pointer; border: 2px solid #4caf50; color: white;}</style>"<<endl;
  cout<<head() << endl;
       cout << body().set("bgcolor","#191919").set("text","white").set("link","#0000ff").set("vlink","#000080") << endl;
       cout << h1("RSA Image Decryption. ") << endl;

clock_t decryptStart, decryptEnd;
decryptStart = clock();

string slambda,sn,svalue;
mpz_t LAMBDA,N,M,C;
mpz_inits(LAMBDA,N,M,C,NULL);

ifstream file;

file.open("privateKey.txt");
file>>slambda; 
file.close(); 
const char *lambda = slambda.c_str();

file.open("valueOfn.txt");
file>>sn; 
file.close(); 
const char *n = sn.c_str();




mpz_set_str(LAMBDA,lambda,16);
mpz_set_str(N,n,16);


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
   
     mpz_powm(M,C,LAMBDA,N);
       mpz_powm_ui(M,M,1,N); 
         
            
                      buff[x][y] = (unsigned int) mpz_get_ui(M);
                      //f<<temp;
                          //cout << endl;   
                               // cout << buff[x][y]<<" ";         
              

     }

        }

 cout<< h2("Image Decrypted Sucessfully");

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
    return 0;

    cout << body() << html();

}
    catch(exception& e) {
       cout << "ERROR!!" << endl;
    }
   
    return 0;
}
     

