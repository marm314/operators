#include<iostream>
#include<algorithm>
#include<fstream>
#include<stdlib.h>
#include<stdio.h>
#include<iomanip>
#include<cstring>
#include"String_ops.h"

using namespace std;

ofstream print_file,print_deltas;
struct OP
{
 char label;    // We may use a, b, c, etc. for labeling the operators
 char index;    // p, q, r, s, etc. are orb. indices 
 bool creation; // True for creation, false for annihilation
 bool on=true;
};

void normal_order();
void copy_string_ops(OP *opin,OP *opout,int &nops);
void permute_ops(OP *op,int &iop);
void switchoff_ops(OP *op,int &iop);
void print_string(OP *op,int &n_operators,int factor);
void update_deltas(OP *opin,int &nops, string &delta_new);


int main()
{
 int idelta;
 string read_line;
 ifstream file_reader;
 // Normal order string
 normal_order();
 // Clean deltas file (remove xs and 1s)
 file_reader.open("deltas_x1.txt");
 print_deltas.open("deltas.txt");
 while(getline(file_reader,read_line))
 {
  for(idelta=0;idelta<(int)read_line.length();idelta++)
  {
   if(read_line[idelta]=='x' || read_line[idelta]=='1') read_line[idelta]=' ';
  }
  read_line.erase(std::remove_if(read_line.begin(),read_line.end(),::isspace),read_line.end());
  print_deltas<<read_line<<endl;
 } 
 file_reader.close();
 print_deltas.close();
 system("/bin/rm -rf deltas_x1.txt");
 // Alphabetic sort strings and deltas

 // Paste operators.txt and deltas.txt files
 system("paste operators.txt deltas.txt > output.txt");
 system("/bin/rm -rf deltas.txt");
 system("/bin/rm -rf operators.txt");
 
 return 0;
}

void normal_order()
{
 bool not_ordered,is_ordered;
 int iop,iline,iter=0;
 int n_lines;
 int *factors,*n_operators;
 string read_line,delta_str,*deltas_string;
 ifstream file_reader;
 OP **op_string_in,*op_string_out;
 do
 {
  not_ordered=false;
  n_lines=0;
  // Read strings
  if(iter==0)
  {
   file_reader.open("input.txt");
   while(getline(file_reader,read_line)){n_lines++;};
   file_reader.close();
   n_operators=new int[n_lines];  
   factors=new int[n_lines];  
   op_string_in=new OP*[n_lines];
   deltas_string=new string[n_lines];
   file_reader.open("input.txt");
   for(iline=0;iline<n_lines;iline++)
   {
    getline(file_reader,read_line);
    stringstream ss(read_line.substr(0,5));
    ss>>factors[iline];
    read_line=read_line.substr(5,read_line.length()-5); 
    read_line.erase(std::remove_if(read_line.begin(),read_line.end(),::isspace),read_line.end());
    lowercase(read_line);
    n_operators[iline]=read_line.length()/3;
    op_string_in[iline]=new OP[n_operators[iline]];
    for(iop=0;iop<n_operators[iline];iop++)
    {
     op_string_in[iline][iop].label=read_line[3*iop];  
     if(read_line[3*iop+1]=='c')
     {
      op_string_in[iline][iop].creation=true;
     }
     else
     {
      op_string_in[iline][iop].creation=false;
     }  
     op_string_in[iline][iop].index=read_line[3*iop+2];  
    }
   }
   file_reader.close();
  }
  else
  {
   file_reader.open("operators.txt");
   while(getline(file_reader,read_line)){n_lines++;};
   file_reader.close();   
   n_operators=new int[n_lines];  
   factors=new int[n_lines];  
   op_string_in=new OP*[n_lines];  
   deltas_string=new string[n_lines];
   file_reader.open("operators.txt");
   for(iline=0;iline<n_lines;iline++)
   {
    getline(file_reader,read_line);
    stringstream ss(read_line.substr(0,5));
    ss>>factors[iline];
    read_line=read_line.substr(5,read_line.length()-5); 
    read_line.erase(std::remove_if(read_line.begin(),read_line.end(),::isspace),read_line.end());
    lowercase(read_line);
    n_operators[iline]=read_line.length()/3;
    op_string_in[iline]=new OP[n_operators[iline]];
    for(iop=0;iop<n_operators[iline];iop++)
    {
     op_string_in[iline][iop].label=read_line[3*iop];  
     if(read_line[3*iop+1]=='c')
     {
      op_string_in[iline][iop].creation=true;
     }
     else
     {
      op_string_in[iline][iop].creation=false;
     }  
     op_string_in[iline][iop].index=read_line[3*iop+2];  
    }
   }
   file_reader.close();   
   file_reader.open("deltas_x1.txt");
   for(iline=0;iline<n_lines;iline++)
   {
    getline(file_reader,read_line);
    deltas_string[iline]=read_line;
   } 
   file_reader.close();   
  }
  // Permute and print strings 
  print_file.open("operators.txt");
  print_deltas.open("deltas_x1.txt");
  for(iline=0;iline<n_lines;iline++)
  {
   is_ordered=false;
   op_string_out=new OP[n_operators[iline]];
   copy_string_ops(op_string_in[iline],op_string_out,n_operators[iline]);
   for(iop=0;iop<n_operators[iline]-1;iop++)
   {
    if(!op_string_out[iop].creation && op_string_out[iop+1].creation) // anh-cre pair 
    {
     permute_ops(op_string_out,iop);
     print_string(op_string_out,n_operators[iline],-factors[iline]);
     update_deltas(op_string_out,n_operators[iline],delta_str);
     print_deltas<<delta_str+deltas_string[iline]<<endl;
     if(op_string_out[iop].label==op_string_out[iop+1].label) // electron-electron or positro-positron anh-cre pair
     {
      switchoff_ops(op_string_out,iop);
      print_string(op_string_out,n_operators[iline],factors[iline]);
      update_deltas(op_string_out,n_operators[iline],delta_str);
      print_deltas<<delta_str+deltas_string[iline]<<endl;
     }
     is_ordered=false;
     not_ordered=true;
     iop=n_operators[iline];
    }
    else
    {
     is_ordered=true;
    }
   }
   if(is_ordered || n_operators[iline]<2) // Print for one/zero operators or if it is already normal-ordered
   {
    print_string(op_string_out,n_operators[iline],factors[iline]);
    update_deltas(op_string_out,n_operators[iline],delta_str);
    print_deltas<<delta_str+deltas_string[iline]<<endl;
   }
   delete[] op_string_out;op_string_out=NULL;
  }
  print_deltas.close();
  print_file.close();
  // Deallocate arrays before next iteration 
  for(iline=0;iline<n_lines;iline++)
  {
   delete[] op_string_in[iline];op_string_in[iline]=NULL;
  }
  delete[] deltas_string;deltas_string=NULL; 
  delete[] n_operators;n_operators=NULL; 
  delete[] factors;factors=NULL;
  delete[] op_string_in;op_string_in=NULL;
  iter++;
  cout<<"Iter. "<<setw(10)<<iter<<endl;
 }while(not_ordered);
}

void copy_string_ops(OP *opin,OP *opout,int &nops)
{
 int iop;
 for(iop=0;iop<nops;iop++)
 {
  opout[iop].creation=opin[iop].creation;
  opout[iop].label=opin[iop].label;
  opout[iop].index=opin[iop].index;
 }
}

void switchoff_ops(OP *op,int &iop)
{
 op[iop].on=false;
 op[iop+1].on=false;
}

void permute_ops(OP *op,int &iop)
{
 OP temp_op;
 temp_op.label=op[iop].label;
 temp_op.creation=op[iop].creation;
 temp_op.index=op[iop].index;
 op[iop].label=op[iop+1].label;
 op[iop].creation=op[iop+1].creation;
 op[iop].index=op[iop+1].index;
 op[iop+1].label=temp_op.label;
 op[iop+1].creation=temp_op.creation;
 op[iop+1].index=temp_op.index;
}

void update_deltas(OP *opin,int &nops, string &delta_new)
{
 bool all_on=true;
 int iop;
 for(iop=0;iop<nops-1;iop++)
 {
  if(!opin[iop].on && !opin[iop+1].on)
  {
   string aux0="1",aux1="1";
   aux0[0]=opin[iop].index;
   aux1[0]=opin[iop+1].index;
   delta_new="x delta_"+aux0+aux1+" ";
   all_on=false;
   iop=nops;
  }
 }
 if(all_on) delta_new="x 1 ";
}

void print_string(OP *op, int & n_operators, int factor)
{
 int iop;
 print_file<<setw(5)<<showpos<<factor<<" ";
 for(iop=0;iop<n_operators;iop++)
 {
  if(op[iop].on)
  {
   print_file<<op[iop].label;  
   if(op[iop].creation)
   {
    print_file<<"c";
   }
   else
   {
    print_file<<"a";
   }  
   print_file<<op[iop].index<<" ";  
  }
 }
 print_file<<endl;
}
