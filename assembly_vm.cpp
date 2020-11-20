#include <bits/stdc++.h>
using namespace std;
const int nulln=-2147483648,ramsize=1023,regsize=255;
struct ins{int com;int a;int b;}insr[regsize];
struct cins{string com;string a;string b;}cinsr[regsize];
int reg[regsize];
int ram[ramsize],disk[ramsize];
struct map{string name;int add;}jmp[regsize],vmap[regsize];
int njmp=-1,nvmap=-1;int n=-1;

/**0:int
 * 1:ld     2:st
 * 3:add    4:mul
 * 5:jmp    6:jc
 * 7:in     8:out
 * B:sub    
 * D:and    E:or
 * 暂未全部实现
 **/

inline int getadd(string na){
    if(na[0]<=int('9')&&na[0]>=int('0'))return stoi(na);
    for(int i=0;i<=nvmap;i++)
        if(!na.compare(vmap[i].name))
            return vmap[i].add;
    return -1;
}

inline void runcom(ins rins,int &pc){
    switch (rins.com){
    case 0:{
        int i=-1;
        while(i<=regsize)if(reg[++i]==nulln) break;
        if(i<=regsize){
            vmap[++nvmap].name=cinsr[pc].a;
            vmap[nvmap].add=i;
            reg[i]=0;
        }
        else cout<<"Register Exceeded"<<endl;
        break;
    }
    case 1:reg[rins.a]=ram[rins.b];break;
    case 2:ram[rins.a]=reg[rins.b];break;
    case 3:reg[rins.a]+=reg[rins.b];break;
    case 11:reg[rins.a]-=reg[rins.b];break;
    case 4:reg[rins.a]=reg[rins.a]*reg[rins.b];break;
    case 5:{
        for(int i=0;i<=njmp;i++){
            if (!cinsr[pc].a.compare(jmp[i].name)){
                pc=jmp[i].add-1;
                return;
            }
            cout<<"No Jump"<<endl;
        }
        break;
    }
    case 6:{
        if(rins.a<=0)return;
        for(int i=0;i<=njmp;i++){
            if (!cinsr[pc].b.compare(jmp[i].name)){
                pc=jmp[i].add-1;
                return;
            }
            cout<<"No Jump"<<endl;
        }
        break;
    }
    case 7:cin>>reg[rins.a];break;
    case 8:cout<<reg[rins.a]<<endl;break;
    default:cout<<"No This Instruct"<<endl;break;
    }
}

inline ins getins(cins a,int pc){
    ins ins;int l=(a.com.length());int hasj=-1;
    for(int i=0;i<l;i++)
        if(a.com[i]==':'){hasj=i;break;}
    if(hasj!=-1){
        string jmpn=(a.com).substr(0,hasj);
        jmp[++njmp].name=jmpn;
        jmp[njmp].add=pc;
        a.com=a.com.substr(hasj+1);
    }
    switch (a.com[0]){
    case 'I':ins.com=(a.com[2]=='T')?0:7;break;
    case 'L':ins.com=1;break;
    case 'S':ins.com=(a.com[1]=='T')?2:11;break;
    case 'A':ins.com=3;break;
    case 'M':ins.com=4;break;
    case 'J':ins.com=(a.com[1]=='M')?5:6;break;
    case 'O':ins.com=8;break;
    case 'P':ins.com=9;break;
    case 'R':ins.com=10;break;
    default:
        cout<<"Read error on "<<a.com<<endl;
        break;
    }
    if(ins.com!=0){
        ins.a=getadd(a.a);ins.b=getadd(a.b);}
    else runcom(ins,pc);
    return ins;
}

inline void initram(int *t,string name){
    int n,a,b,init[ramsize];
    for(int i=0;i<ramsize;i++)*(t+i)=nulln;
    cout<<"Please input the amount of "<<name<<" data:";cin>>n;
    if(n)cout<<"Please input the address and value:"<<endl;
    for(int i=0;i<n;i++){
        cin>>a>>b;
        *(t+a)=b;
    }
}

int main(){
    memset(insr,0,sizeof(insr));
    memset(jmp,0,sizeof(jmp));
    memset(vmap,0,sizeof(vmap));
    //for(int i=0;i<=ramsize;i++)ram[i]=0;//认为内存中值为nulln的为空地址
    initram(ram,"ram");
    initram(disk,"disk");
    for(int i=0;i<=regsize;i++)reg[i]=nulln;
    string readstr;
    cout<<"Please enter the number of statements:";cin>>n;
    for(int i=0;i<n;i++){
        getline(cin,readstr);int a=0,b=0;
        for(int i=0;i<readstr.length();i++)
            if(readstr[i]==' '||readstr[i]==','){a=i;break;};
        for(int i=a+1;i<readstr.length();i++)if(readstr[i]==' '||readstr[i]==','){b=i;break;};
        cinsr[i].com=readstr.substr(0,a);
        if(b!=0){
            cinsr[i].a=readstr.substr(a+1,b-a-1);
            cinsr[i].b=readstr.substr(b+1);
        }else cinsr[i].a=readstr.substr(a+1);

        insr[i]=getins(cinsr[i],i);
    }
    for(int i=0;i<=n;i++)
        if(insr[i].com!=0)runcom(insr[i],i);
    return 0;
}
