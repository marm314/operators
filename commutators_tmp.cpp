#include<iostream>
#include<cstring>

using namespace std;

string path="PATH";
string command;

int main(int argc, char *argv[])
{
 cout<<"--------------------------------------------"<<endl; 
 cout<<"--------------------------------------------"<<endl; 
 cout<<"---          COMMUTATORS PROGRAM         ---"<<endl; 
 cout<<"--------------------------------------------"<<endl; 
 cout<<"--------------------------------------------"<<endl; 
 cout<<"-- Developed by: Dr. M. Rodriguez-Mayorga --"<<endl; 
 cout<<"--     email: marm3.14@gmail.com          --"<<endl; 
 cout<<"--------------------------------------------"<<endl; 
 cout<<"--------------------------------------------"<<endl;
 cout<<endl; 
 string input_file; 
 command=path+"/op_strings";
 if(argc!=2)
 {
  cout<<"Include the name of the input file"<<endl;
  cout<<"e.g."<<endl;
  cout<<"./commutators name.inp"<<endl;
  // Terminate screen output
  cout<<endl; 
  cout<<"--------------------------------------------"<<endl; 
  cout<<"--            Normal termination          --"<<endl;
  cout<<"--------------------------------------------"<<endl; 
  cout<<"--------------------------------------------"<<endl; 
  return 0;
 }
 else
 {
  input_file=argv[1];
 }
 
 // Terminate screen output
 cout<<endl; 
 cout<<"--------------------------------------------"<<endl; 
 cout<<"--            Normal termination          --"<<endl;
 cout<<"--------------------------------------------"<<endl; 
 cout<<"--------------------------------------------"<<endl; 
 return 0;
}
