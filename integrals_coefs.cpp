#include<iostream>
#include<algorithm>
#include<fstream>
#include<cstring>
#include<vector>
#include<stdlib.h>
#include<stdio.h>
#include<iomanip>
#include"String_ops.h"

using namespace std;

int main(int argc, char *argv[])
{
 char tmp_char;
 int ichar,ichar1,iend,mindices,ncre,nanh,noperations;
 string int_coefs,indices_str,line,aux,aux1,result,deltas;
 ifstream file_reader;
 vector<char>indices;
 vector<string>operations;
 cout<<"--------------------------------------------"<<endl; 
 cout<<"--------------------------------------------"<<endl; 
 cout<<"---    INT, COEF & OPERATOS PROGRAM      ---"<<endl; 
 cout<<"--------------------------------------------"<<endl; 
 cout<<"--------------------------------------------"<<endl; 
 cout<<"-- Developed by: Dr. M. Rodriguez-Mayorga --"<<endl; 
 cout<<"--     email: marm3.14@gmail.com          --"<<endl; 
 cout<<"--------------------------------------------"<<endl; 
 cout<<"--------------------------------------------"<<endl;
 cout<<endl; 
 if(argc!=3)
 {
  cout<<"Include the name of the input file and the ops file"<<endl;
  cout<<"e.g."<<endl;
  cout<<"./integrals_coefs name.inp name.ops"<<endl;
  // Terminate screen output
  cout<<endl; 
  cout<<"--------------------------------------------"<<endl; 
  cout<<"--            Normal termination          --"<<endl;
  cout<<"---    INT, COEF & OPERATOS PROGRAM      ---"<<endl; 
  cout<<"--------------------------------------------"<<endl; 
  cout<<"--------------------------------------------"<<endl; 
  return 0;
 }
 else
 {
  // Read the coefs and integrals to use
  file_reader.open(argv[1]);
  getline(file_reader,int_coefs);
  cout<<endl;
  cout<<"Integrals and coefs read"<<endl;
  cout<<int_coefs<<endl;
  cout<<endl;
  mindices=0;
  do
  {
   tmp_char=' ';
   file_reader>>tmp_char;
   if(tmp_char!=' ')
   {
    mindices++;
    indices.push_back(tmp_char);
   }
  }while(tmp_char!=' ');
  cout<<endl;
  cout<<"Indices read"<<endl;
  indices_str="";
  for(ichar=0;ichar<mindices;ichar++)
  {
   cout<<indices[ichar]<<" ";
   indices_str=indices_str+indices[ichar];
  }
  for(ichar=0;ichar<mindices-1;ichar++)
  {
   for(ichar1=ichar;ichar1<mindices;ichar1++)
   {
    if(alphabetic(indices_str[ichar])>alphabetic(indices_str[ichar1]))
    {
     tmp_char=indices_str[ichar];
     indices_str[ichar]=indices_str[ichar1];
     indices_str[ichar1]=tmp_char;
    }
   }
  }
  cout<<endl;
  cout<<endl;
  file_reader.close(); 
  // Read operators file (i.e. name.ops)
  file_reader.open(argv[2]);
  cout<<endl;
  cout<<"Transformation from operators to density matrices"<<endl;
  cout<<endl;
  noperations=0;
  while(getline(file_reader,line))
  {
   iend=0;
   for(ichar=5;ichar<(int)line.length();ichar++)
   {
    if(line[ichar]=='*') iend=ichar;
   }
   aux=line.substr(5,iend-6);
   aux.erase(std::remove_if(aux.begin(),aux.end(),::isspace),aux.end());
   deltas=line.substr(iend+1,line.length()-iend-1);
   deltas.erase(std::remove_if(deltas.begin(),deltas.end(),::isspace),deltas.end());
   ncre=0;nanh=0;
   for(ichar=1;ichar<(int)aux.length();ichar=ichar+3)
   {
    if(aux[ichar]=='c') ncre++;
    if(aux[ichar]=='a') nanh++;
   }
   if(ncre!=0 && nanh!=0)
   {
    if(ncre==nanh)
    {
     aux1="";
     string String = static_cast<ostringstream*>( &(ostringstream() << ncre) )->str();
     result=String+"D_";
     for(ichar=0;ichar<ncre;ichar=ichar+3)
     {
      result=result+aux[ichar+2]; 
     } 
     result=result+",";
     for(ichar=0;ichar<nanh;ichar=ichar+3)
     {
      aux1=aux[aux.length()-1-ichar]; 
     } 
     result=result+aux1+" "+int_coefs;
     result=result+" * "+deltas;
    }
    else
    {
     cout<<"Error! The number of creation and annihilation operators is not equal in "<<argv[2]<<endl;
     return -1;
    }
   }
   else
   {
    cout<<"Error! The number of creation and annihilation operators is not equal in "<<argv[2]<<endl;
    return -1;
   }
   aux=line.substr(0,5)+" sum_"+indices_str+" "+result;
   operations.push_back(aux);
   cout<<operations[noperations]<<endl;
   noperations++;
  }
  file_reader.close(); 
 }
 // Reduce using deltas
 // Terminate screen output
 cout<<endl; 
 cout<<"--------------------------------------------"<<endl; 
 cout<<"--            Normal termination          --"<<endl;
 cout<<"---    INT, COEF & OPERATOS PROGRAM      ---"<<endl; 
 cout<<"--------------------------------------------"<<endl; 
 cout<<"--------------------------------------------"<<endl; 
 return 0;
}
