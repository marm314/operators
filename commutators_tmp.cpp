#include<iostream>
#include<fstream>
#include<cstring>

using namespace std;

string path="PATH";
string command;

int main(int argc, char *argv[])
{
 string input_file,line;
 command=path+"/op_strings";
 ifstream file_reader;
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
 // Read the commutator (can be nested)
 file_reader.open(input_file);
 getline(file_reader,line);
 file_reader.close();
 // Find number of nested commutators
 cout<<line<<endl;

  
 // Terminate screen output
 cout<<endl; 
 cout<<"--------------------------------------------"<<endl; 
 cout<<"--            Normal termination          --"<<endl;
 cout<<"--------------------------------------------"<<endl; 
 cout<<"--------------------------------------------"<<endl; 
 return 0;
}
