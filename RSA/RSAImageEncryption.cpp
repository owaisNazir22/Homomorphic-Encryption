#include <iostream>
#include <vector>  
#include <string>  
#include <stdio.h>  
#include <stdlib.h> 
#include <fstream>
#include <gmp.h>

#include <cgicc/CgiDefs.h> 
#include <cgicc/Cgicc.h> 
#include <cgicc/HTTPHTMLHeader.h> 
#include <cgicc/HTMLClasses.h>
#define cimg_display 0
#include "CImg.h"

using namespace std;
using namespace cgicc;
using namespace cimg_library;

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
       cout << html() << head() << title("Paillier Image Encryption") << endl;
cout<<"<style>h2 {font: 20px; color:white;}</style>"<<endl;
cout<<"<style>h1{border-bottom: 6px solid;}</style>"<<endl;
cout<<"<style>input{  position: absolute; r; width: 40%; height: 10%; color: brown; border-radius: 60px; background: none; cursor: pointer; border: 2px solid #4caf50; color: white;}</style>"<<endl;
  cout<<head() << endl;
       cout << body().set("bgcolor","#191919").set("text","white").set("link","#0000ff").set("vlink","#000080") << endl;
       cout << h1("Paillier Image Encryption. ") << endl;

 clock_t encryptStart, encryptEnd;
encryptStart = clock();
    
  
   ofstream f;
   f.open("inputImage.pgm");
 

   // get list of files to be uploaded
   const_file_iterator file_ = cgi.getFile("userfile");
   if(file_ != cgi.getFiles().end()) {
    
       file_->writeToStream(f);
   }
   f.close();

 CImg<unsigned char> img("inputImage.pgm");

    // Get width, height, number of channels
    int w=img.width();
    int h=img.height();
    int c=img.spectrum();
    int ar[w][h];

    // Dump all pixels
    for(int y=0;y<h;y++){
       for(int x=0;x<w;x++){
           ar[x][y] = (int)img(x,y);
       }
    }


string pu,sn;
mpz_t C,M; mpz_inits(C,M,NULL);

ifstream file;

file.open("publicKey.txt");
file>>pu;
file.close(); 
const char *e = pu.c_str();

file.open("valueOfn.txt");
file>>sn;
file.close();
const char *n = sn.c_str();

mpz_t N; mpz_init(N);
mpz_t E; mpz_init(E);


mpz_set_str(N,n,16);
mpz_set_str(E,e,16);

{
ofstream file;
file.open("encryptedImage"); 
int val;
file<<w<<endl;
file<<h<<endl;


unsigned int buff[h][w];
for(int y=0;y<h;y++){
       for(int x=0;x<w;x++){  
val = ar[x][y];
mpz_set_ui(M,val); 
   
  
mpz_powm(C, M, E, N);
mpz_powm_ui(C,C,1,N); 
            buff[x][y] = (unsigned int) mpz_get_ui(C);   
            file<<mpz_get_str(NULL, 10, C)<<endl;
}
}
            file.close();
      
  
     cout << h2("Image Encrypted Sucessfully"); 

    auto hold_arr = (unsigned int*)&buff[0][0];
    cimg_library::CImg<unsigned int> img(hold_arr,w,h);
    img.save("showEncryptedImage.pgm");

encryptEnd = clock();
encryptEnd = encryptEnd - encryptStart;

 ifstream testFile,testFile_;
 testFile.open("inputImage.pgm" ,ios_base::binary);
 testFile.seekg (0, ios_base::end);
 const auto end = testFile.tellg();
 
 int sizeFile = (int)end;

 cout << "Size of image file : "<< sizeFile << " bytes." << "</br>" << "</br>";

testFile_.open("encryptedImage" ,ios_base::binary);
 testFile_.seekg (0, ios_base::end);
 const auto end_ = testFile_.tellg();
 
 sizeFile = (int)end_;

 cout << "Size of encrypted image file : "<< sizeFile << " bytes." << "</br>" << "</br>";

 cout << "Time required to encrypt the integer is : ";
 cout << (double)encryptEnd/CLOCKS_PER_SEC << " sec." << "</br>" << "</br>";
   
      cout<< "<form method =\"post\" action = \"/cgi-bin/RSA/RSAImageDecryption.cgi\" ><input type = \"submit\" value = \"Decrypt\"> </form> ";
 
 cout << body() << html();

}
}
    catch(exception& e) {
       cout << "ERROR!!" << endl;
    }
   
    return 0;
}


