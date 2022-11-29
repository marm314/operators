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

void sort_operators();
void normal_order(string input_file);
void clean_sort_deltas();
void reduce_op_str(string output_file);
void copy_string_ops(OP *opin,OP *opout,int &nops);
void permute_ops(OP *op,int &iop);
void switchoff_ops(OP *op,int &iop);
void print_string(OP *op,int &n_operators,int factor);
void update_deltas(OP *opin,int &nops, string &delta_new);

int main(int argc, char *argv[])
{
 cout<<"--------------------------------------------"<<endl; 
 cout<<"--------------------------------------------"<<endl; 
 cout<<"---        NORMAL ORDERING PROGRAM       ---"<<endl; 
 cout<<"--------------------------------------------"<<endl; 
 cout<<"--------------------------------------------"<<endl; 
 cout<<"-- Developed by: Dr. M. Rodriguez-Mayorga --"<<endl; 
 cout<<"--     email: marm3.14@gmail.com          --"<<endl; 
 cout<<"--------------------------------------------"<<endl; 
 cout<<"--------------------------------------------"<<endl;
 cout<<endl; 
 string input_file,output_file;
 if(argc!=2)
 {
  cout<<"Include the name of the input file"<<endl;
  cout<<"e.g."<<endl;
  cout<<"./op_strings name.inp"<<endl;
  // Terminate screen output
  cout<<endl; 
  cout<<"--------------------------------------------"<<endl; 
  cout<<"--            Normal termination          --"<<endl;
  cout<<"---        NORMAL ORDERING PROGRAM       ---"<<endl; 
  cout<<"--------------------------------------------"<<endl; 
  cout<<"--------------------------------------------"<<endl; 
  return 0;
 }
 else
 {
  input_file=argv[1];
 }
 // Normal order string
 normal_order(input_file);
 // Clean deltas file (remove x and 1, but add *) and sort alphabetically
 clean_sort_deltas();
 // Alphabetic sort operators strings (including change of sign due to permutations!)
 sort_operators();
 // Paste operators.txt and deltas.txt files
 output_file=input_file.substr(0,input_file.length()-3)+"ops";
 system(("paste operators.txt deltas.txt >"+output_file).c_str());
 system("/bin/rm -rf deltas.txt");
 system("/bin/rm -rf operators.txt");
 // Reduced repeated strings
 reduce_op_str(output_file);
 cout<<endl;
 cout<<"See the file "<<output_file<<" for the result."<<endl; 
 cout<<endl; 
 // Terminate screen output
 cout<<endl; 
 cout<<"--------------------------------------------"<<endl; 
 cout<<"--            Normal termination          --"<<endl;
 cout<<"---        NORMAL ORDERING PROGRAM       ---"<<endl; 
 cout<<"--------------------------------------------"<<endl; 
 cout<<"--------------------------------------------"<<endl; 
 return 0;
}

void normal_order(string input_file)
{
 bool not_ordered,is_ordered;
 int iop,iline,iter=0;
 int n_lines;
 int *factors,*n_operators;
 string read_line,delta_str,*deltas_string;
 ifstream file_reader;
 cout<<"Starting normal ordering iterations"<<endl;
 OP **op_string_in,*op_string_out;
 do
 {
  not_ordered=false;
  n_lines=0;
  // Read strings
  if(iter==0)
  {
   file_reader.open(input_file.c_str());
   while(getline(file_reader,read_line)){n_lines++;};
   file_reader.close();
   n_operators=new int[n_lines];  
   factors=new int[n_lines];  
   op_string_in=new OP*[n_lines];
   deltas_string=new string[n_lines];
   file_reader.open(input_file.c_str());
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
 cout<<"Normal ordering iterations done"<<endl;
}

void clean_sort_deltas()
{
 bool sorted;
 char tmp_char,tmp_char2;
 int index1,index2,idelta,idelta1;
 string read_line;
 ifstream file_reader;
 file_reader.open("deltas_x1.txt");
 print_deltas.open("deltas.txt");
 cout<<"Starting deltas sorting"<<endl;
 while(getline(file_reader,read_line))
 {
  for(idelta=0;idelta<(int)read_line.length();idelta++)
  {
   if(read_line[idelta]=='x' || read_line[idelta]=='1') read_line[idelta]=' ';
   if(read_line[idelta]=='_')
   {
    index1=alphabetic(read_line[idelta+1]);
    index2=alphabetic(read_line[idelta+2]);
    if(index1>index2)
    {
     tmp_char=read_line[idelta+1];
     read_line[idelta+1]=read_line[idelta+2];
     read_line[idelta+2]=tmp_char;
    }
   }
  }
  read_line.erase(std::remove_if(read_line.begin(),read_line.end(),::isspace),read_line.end());
  if(read_line.length()>8)
  {
   do
   {
    sorted=true;
    for(idelta=0;idelta<(int)read_line.length()/8-1;idelta++)
    {
     for(idelta1=idelta+1;idelta1<(int)read_line.length()/8;idelta1++)
     {
      if(alphabetic(read_line[idelta*8+6])>alphabetic(read_line[idelta1*8+6]))
      {
       sorted=false;
       tmp_char=read_line[idelta*8+6];
       tmp_char2=read_line[idelta*8+7];
       read_line[idelta*8+6]=read_line[idelta1*8+6];
       read_line[idelta*8+7]=read_line[idelta1*8+7];
       read_line[idelta1*8+6]=tmp_char;
       read_line[idelta1*8+7]=tmp_char2;
      }
      if(alphabetic(read_line[idelta*8+6])==alphabetic(read_line[idelta1*8+6])) // If both 1st indices are equal, sort using the second index
      {
       if(alphabetic(read_line[idelta*8+7])>alphabetic(read_line[idelta1*8+7]))
       {
        sorted=false;
        tmp_char=read_line[idelta*8+6];
        tmp_char2=read_line[idelta*8+7];
        read_line[idelta*8+6]=read_line[idelta1*8+6];
        read_line[idelta*8+7]=read_line[idelta1*8+7];
        read_line[idelta1*8+6]=tmp_char;
        read_line[idelta1*8+7]=tmp_char2;
       }
      }
     }
    }
   }while(!sorted); 
  }
  if(read_line.length()==0)
  {
   print_deltas<<read_line<<endl;
  }
  else
  {
   print_deltas<<"* "<<read_line<<endl;
  }
 } 
 file_reader.close();
 print_deltas.close();
 system("/bin/rm -rf deltas_x1.txt");
 cout<<"Deltas sorting done"<<endl;
}

void sort_operators()
{
 bool not_sorted;
 int iop,iline=0,noperators,ncre,nanh,factor,permutations;
 string read_line,ops_str,str_aux;
 OP *op_string_in;
 ifstream file_reader;
 file_reader.open("operators.txt");
 print_file.open("operators_tmp.txt");
 while(getline(file_reader,read_line))
 {
  str_aux=read_line;
  stringstream ss(read_line.substr(0,5));
  ss>>factor;
  ops_str=read_line.substr(5,read_line.length()-5);
  ops_str.erase(std::remove_if(ops_str.begin(),ops_str.end(),::isspace),ops_str.end());
  lowercase(ops_str);
  noperators=ops_str.length()/3;
  op_string_in=new OP[noperators];
  if(noperators>2)
  {
   ncre=0;nanh=0;
   for(iop=0;iop<noperators;iop++)
   {
    op_string_in[iop].label=ops_str[3*iop];  
    if(ops_str[3*iop+1]=='c')
    {
     op_string_in[iop].creation=true;
     ncre++;
    }
    else
    {
     op_string_in[iop].creation=false;
     nanh++;
    }
    op_string_in[iop].index=ops_str[3*iop+2];
   }
   permutations=0;
   do
   {
    not_sorted=false;
    for(iop=0;iop<ncre-1;iop++)
    {
     if(alphabetic(op_string_in[iop].index)>alphabetic(op_string_in[iop+1].index))
     {
      permutations++; 
      permute_ops(op_string_in,iop);
      not_sorted=true;
     }
    }
    for(iop=ncre;iop<ncre+nanh-1;iop++)
    {
     if(alphabetic(op_string_in[iop].index)<alphabetic(op_string_in[iop+1].index))
     {
      permutations++; 
      permute_ops(op_string_in,iop);
      not_sorted=true;
     }
    }
   }while(not_sorted);
   if(permutations%2!=0){factor=-factor;}
   print_string(op_string_in,noperators,factor);
  }  
  else
  {
   print_file<<str_aux<<endl;
  }
  delete[] op_string_in;op_string_in=NULL;
  iline++;
 }
 print_file.close();
 file_reader.close();
 system("mv operators_tmp.txt operators.txt");
}

void reduce_op_str(string output_file)
{
 int iline,iline1,nlines=0;
 int *factors;
 string *lines,read_line,line_aux,line_aux1;
 ifstream file_reader;
 file_reader.open(output_file);
 while(getline(file_reader,read_line)){nlines++;}
 file_reader.close(); 
 lines=new string[nlines];
 factors=new int[nlines];
 file_reader.open(output_file);
 iline=0;
 while(getline(file_reader,read_line))
 {
  stringstream ss(read_line.substr(0,5));
  ss>>factors[iline];
  lines[iline]=read_line.substr(5,read_line.length()-5);
  iline++;
 }
 file_reader.close();
 for(iline=0;iline<nlines-1;iline++)
 {
  line_aux=lines[iline];
  line_aux.erase(std::remove_if(line_aux.begin(),line_aux.end(),::isspace),line_aux.end());
  for(iline1=iline+1;iline1<nlines;iline1++)
  {
   line_aux1=lines[iline1];
   line_aux1.erase(std::remove_if(line_aux1.begin(),line_aux1.end(),::isspace),line_aux1.end());
   if(line_aux==line_aux1 && factors[iline1]!=0)
   {
    factors[iline]=factors[iline]+factors[iline1];
    factors[iline1]=0;
   }
  }
 } 
 print_file.open(output_file);
 for(iline=0;iline<nlines;iline++)
 {
  if(factors[iline]!=0)
  {
   print_file<<setw(5)<<showpos<<factors[iline]<<lines[iline]<<endl;
  }
 }
 print_file.close();
 delete[] lines;lines=NULL;
 delete[] factors;factors=NULL;
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
 if(all_on){delta_new="x 1 ";}
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
