#include <iostream>
#include <vector>
#include <map>
#include <fstream>
#include <utility>
#include <algorithm>
#include <iomanip>
#include <string>
#include <bitset>
using namespace std;

int sortnum=1;
float MAX=0;
map<char,float> arr; // 摮?:?箇甈⊥

map<char,string>com; // 摮?:隞?Ⅳ
map<string,char>com2;// 隞?Ⅳ:摮?

map<string,char> ia; // binary:ASCII
map<char,string> ia2; //ASCII:binary   
vector<char> data;
vector<char> datac;

struct huf
{
    float pro;
    char ch;
    string huffnum ;
    string dcom;
    int t=-1;
    bool leaf=0;
    huf* ln;
    huf* rn;
};

void parser(char* input);
void makehuf();
void traversal(huf* root);
void setASCIIcode();
void compreser(char* output);
void decomoreser(char* input,char* output);
bool test(char* case1,char* case2);
void cout_data();
map<float,huf*> sor;  //璈?:璅寧?暺?

int main()
{
	char file1[]="input.txt";
	char file2[]="output.txt";
    char file3[]="input1.txt";
    parser(file1);
    makehuf();
    traversal((--sor.end())->second);
    setASCIIcode();
    compreser(file2);
    decomoreser(file2,file3);

    cout_data();

    cout << "decomposer : ";
    if(test(file1,file3))cout<<" same !! ";
    else cout<<" different !!";
}

void cout_data()
{
    cout << "number of words :" <<endl;
    for(auto &x:arr)   //摮蝯梯?
        cout<<"( "<< x.first<<" )->"<<x.second<<endl; 
    cout <<"\n\nHuffman code :\n";
    for(auto &x:com)
        cout<< "( "<<x.first << " )->" << x.second << endl;
    cout << "\n\nfinal output code :\n";
    for(auto &x:ia2)
        cout<< "( "<<x.second << " )->" << x.first << endl;

}
bool test(char* case1,char* case2)
{
    fstream c1,c2;
    c1.open(case1,ios::in);
    c2.open(case2,ios::in);
    bool a=1;
    char ch,cl;
    vector<char> a1;
    vector<char> a2;    
    while(c1.get(ch))a1.push_back(ch);
    while(c2.get(cl))a2.push_back(cl);        

    if(a1.size()==a2.size())
        for(int i=0;i<a1.size();i++)
        {
            if(a1[i] != a2[i])a=0;    
        }
    else
        a=0;
    c1.close();
    c2.close();   
    return a; 
}
void decomoreser(char* input,char* output)
{
    fstream in,ou;
    in.open( input,ios::in);
    ou.open( output,ios::out);

    char ch;

    vector<char>  cc;
    vector<string> ss;
    int i=0;
    while(in.get(ch))
    {
        if(ch!='0'&&ch!='1')
            for(auto &x:ia2[ch])
                cc.push_back(x);
        else 
            cc.push_back(ch);
    }
    string k="";
    for(auto &x:cc)
    {
        k+=x;
        if(com2.count(k))
        {
            ou << com2[k];
            k="";
        }
        
    }
    in.close();
    ou.close();
}
void setASCIIcode()
{
    for(auto &x:com)
        com2[x.second]=x.first;
    
    for(auto &x:data)
      for(auto &y:com[x])  
        datac.push_back(y);          

    for(int i=0;i<64;i++)
    {
        bitset<6> s(i);
        string k="";
        for(int i=0;i<6;i++)
            {
                k+=(s[i]+48);
            }
        ia[k]=char(i+50);
        ia2[char(i+50)]=k;
    }
    int i=0;
}
void compreser(char* output)
{
    fstream ou;
    ou.open(output, ios::out);
    vector<char> kk;
    bool end=0;
    for(int i=0;i<datac.size();)
    {
        string k="";
        for(int j=0;j<6;j++)
        {
            k+=datac[i++];
            if(i==(datac.size()-1))
            {
                k+=datac[i++];
                end=1;break;
            }
        }
        if(!end)
            kk.push_back(ia.find(k)->second);
        else
            for(auto &g:k)kk.push_back(g);
    }
    for(auto &x:kk)
        ou<< x; 
    ou.close();
}

void traversal(huf* root)
{
    if(root->leaf)
    {
        root->ln->huffnum += (root->huffnum +"0");
        root->rn->huffnum += (root->huffnum +"1");

        traversal(root->ln);
        traversal(root->rn);
    }
    else
        com[root->ch] = root->huffnum;
    return;
}

void makehuf()
{
    int i=1;
    for(map<float,huf*>::iterator it=sor.begin();it!=(--sor.end());it++)
    {
        huf* a= new huf;
        a->leaf=1;
        a->pro=it->second->pro;
        a->ln=it->second;
        it++;
        a->pro+=it->second->pro;
        a->rn=it->second;
        while(sor.count(a->pro))a->pro+=0.0000001;
        a->t=i;

        sor [a->pro] = a;

        i++;
    }
}
void parser(char* input )
{
	fstream in,ou;
    in.open(input , ios::in);

    if(!in)
    {
    	cout<<"Error Input!!\n";
    	return;
    }

    char ch;
    while(in.get(ch))
    {
        data.push_back(ch);
    	if(!arr.count(ch))
        {
    		arr.insert(pair<char,float>(ch,1));
            MAX++;
        }
    	else
        {
			arr.find(ch)->second++;    		
            MAX++;
        }
    }
    for(auto &x:arr)
    {
        huf* a = new huf;
        a->pro= x.second/MAX;
        a->ch = x.first;
        while(sor.count(a->pro)){a->pro+=0.0000001;}
        sor.insert(pair<float,huf*>(a->pro,a));
        // cout << sor.size()<<" "<< a->pro<<" "<<a->ch<<endl;
    }

    // cout << arr.size() << " " << sor.size()<<endl;
    // for(auto &x:sor)cout << x.second->ch<< "   " << x.first <<endl;
    // for(auto &x:arr)   //摮蝯梯?
    //     cout<< x.first<<" "<<x.second<<endl;
    // cout << MAX;
    in.close();
}
