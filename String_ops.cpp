#include"String_ops.h"
bool compare(string original, string input)
{
 unsigned int i;
 char c;
 bool res=false;
 string str1,str2;
 str1=original;
 str2=input;
 for(i=0;i<str1.length();i++)
 {
  c=str1[i];
  str1[i]=tolower(c);
 }
 for(i=0;i<str2.length();i++)
 {
  c=str2[i];
  str2[i]=tolower(c);
 }
 if(str1==str2){res=true;}
 return res;
}
void lowercase(string &original)
{
 unsigned int i;
 char c;
 for(i=0;i<original.length();i++)
 {
  c=original[i];
  original[i]=tolower(c);
 }
}
int alphabetic(char &input)
{
 int val=0;
 switch(input){
  case 'a':
   val=1;
   break;
  case 'b':
   val=2;
   break;
  case 'c':
   val=3;
   break;
  case 'd':
   val=4;
   break;
  case 'e':
   val=5;
   break;
  case 'f':
   val=6;
   break;
  case 'g':
   val=7;
   break;
  case 'h':
   val=8;
   break;
  case 'i':
   val=9;
   break;
  case 'j':
   val=10;
   break;
  case 'k':
   val=11;
   break;
  case 'l':
   val=12;
   break;
  case 'm':
   val=13;
   break;
  case 'n':
   val=14;
   break;
  case 'o':
   val=15;
   break;
  case 'p':
   val=16;
   break;
  case 'q':
   val=17;
   break;
  case 'r':
   val=18;
   break;
  case 's':
   val=19;
   break;
  case 't':
   val=20;
   break;
  case 'u':
   val=21;
   break;
  case 'v':
   val=22;
   break;
  case 'w':
   val=23;
   break;
  case 'x':
   val=24;
   break;
  case 'y':
   val=25;
   break;
  case 'z':
   val=26;
   break;
  default :
   cout<<"You did wrong selecting int for char"<<endl;
 }
 return val;
}
