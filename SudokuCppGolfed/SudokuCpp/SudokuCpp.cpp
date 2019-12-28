#include <iostream>
#define F return false
#define T return true
#define Z bool d[10] = { false }
#define X for(int i=

using namespace  std;int        G[81];int S[9][9]={             {0,1,2,9,
 10,11,18,19,20},{3,4,5,12,     13,14,21,22,23},{6,7,8,        15,16,17,24,25
,26},{27,28,29,36,37,38,45,     46,47},{30,31,32,39,40,41,    48,49,50},{33,34,
35,42,43     ,44,51,52,53},     {54,55,56,63,64,65,72,73,74  },{57,58,59,66,67,
68,75,76             ,77},{60,  61,62   ,69,70,    71,78,79 ,80}};     void pg()
{X 0;i<             81;i++)     {if(!(i   %9)&&i    !=0)cout<<endl;     cout<<G
 [i]<<" ";          }cout<<     endl;}    bool vr(     int r){Z;X 9*r     ;i<9*r+
  9;i++)if(!d[G     [i]]||!     G[i])d[   G[i]]=      true;else F;T;}     bool vc
    (int c){Z;X c   ;i<81;i     +=9)if(   !d[G[i]     ]||!G[i])d[G[i     ]]=true
       ;else F;T;}  bool vs     (int s)   {Z;X 0;     i<9;i++){int j     =S[s][i
            ];if(!d [G[j]]||    !G[j])   d[G[j]]     =true;else F;}     T;}bool
             ps(){X  0;i<9;i   ++)if(!  vr(i)||!    vc(i)|| !vs(i))F   ;T;}void
 s(int      k=0){if (k>=81)return pg(); if(G[k]==0){X 1;i<=  9;i++){G[k]=i;if(ps
())s(k+1);G[k]=0;}}  else s(k+1);}int   main(int n,char*b[    ]){X 0;i<81;i++)G
[i]=b[1][i]-48;s()     
;}

