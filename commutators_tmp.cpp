#include<iostream>
#include<algorithm>
#include<fstream>
#include<cstring>
#include<vector>
#include<stdlib.h>
#include<stdio.h>
#include<iomanip>

using namespace std;

string path="PATH";
string command;

int main(int argc, char *argv[])
{
 int ichar,ichar1,init,iend,istring,nstrings=0;
 bool nested;
 vector<int>factors;
 vector<string>op_strings;
 string input_file,line,aux,aux1,aux2;
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
  cout<<"---          COMMUTATORS PROGRAM         ---"<<endl; 
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
 cout<<"Commutator read:"<<endl;
 cout<<line<<endl;
 line.erase(std::remove_if(line.begin(),line.end(),::isspace),line.end());
 cout<<endl;
 op_strings.push_back(line);
 factors.push_back(1);
 cout<<endl;
 nstrings++;
 do
 {
  nested=false;
  for(istring=0;istring<nstrings;istring++)
  {
   line=op_strings[istring];
   init=0;iend=0;
   for(ichar=0;ichar<(int)line.length();ichar++)
   {
    if(line[ichar]=='[')
    {
     init=ichar;
    }
    if(line[ichar]==']')
    {
     iend=ichar;
     aux=line.substr(init+1,iend-init-1);
     for(ichar1=0;ichar1<(int)aux.length();ichar1++)
     {
      if(aux[ichar1]==',')
      {
       aux1=aux.substr(0,ichar1);
       aux2=aux.substr(ichar1+1,aux.length()-ichar1-1);
       ichar1=aux.length();
      }
     }
     aux=aux1+aux2;
     aux=line.substr(0,init)+aux+line.substr(iend+1,line.length()-iend+1);
     aux.erase(std::remove_if(aux.begin(),aux.end(),::isspace),aux.end());
     op_strings[istring]=aux;
     aux=aux2+aux1;
     aux=line.substr(0,init)+aux+line.substr(iend+1,line.length()-iend+1);
     aux.erase(std::remove_if(aux.begin(),aux.end(),::isspace),aux.end());
     op_strings.push_back(aux);
     factors.push_back(-factors[istring]);
     ichar=line.length();
     nstrings++;
     istring=nstrings;
     nested=true;
    }
   }
  } 
 }while(nested); 
 // Prepare op_string input
 ofstream op_str(("ops_"+input_file).c_str()); 
 for(istring=0;istring<nstrings;istring++)
 {
  op_str<<showpos<<setw(5)<<factors[istring]<<" ";
  aux=op_strings[istring];
  for(ichar=0;ichar<(int)aux.length();ichar=ichar+3)
  {
   op_str<<aux.substr(ichar,3)<<" ";
  }
  op_str<<endl;
 }
 op_str.close();
 // Normal order
 cout<<endl;
 cout<<"Calling normal ordering program"<<endl;
 cout<<endl;
 system((command+" "+"ops_"+input_file).c_str());
 // Pring the result
 cout<<endl;
 cout<<"Simplified commutator"<<endl;
 cout<<endl;
 file_reader.open(("ops_"+input_file.substr(0,input_file.length()-3)+"ops").c_str());
 while(getline(file_reader,line))
 {
  cout<<line<<endl;
 }
 file_reader.close();
 cout<<endl;
 // Terminate screen output
 cout<<endl; 
 cout<<"--------------------------------------------"<<endl; 
 cout<<"--            Normal termination          --"<<endl;
 cout<<"---          COMMUTATORS PROGRAM         ---"<<endl; 
 cout<<"--------------------------------------------"<<endl; 
 cout<<"--------------------------------------------"<<endl; 
 return 0;
}
