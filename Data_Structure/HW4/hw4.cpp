#include<iostream>
#include<fstream>
#include<string>
#include<ctime>
#include<algorithm>
using namespace std;

typedef struct               
{
	string ss;
	int num[24]={0};
	double avg;	
}vertex;


typedef struct               
{
	string name;
	int day=0;	
}place;

string del(string data);
void bubblesort(vertex a[],int n);
void bubblesortday(place a[],int n);
void quicksort(vertex ar[],int left,int right);	
void mergesort(vertex a[], int low, int high);
void merge(vertex a[], int low, int high, int mid);

int i=-1;	//第幾筆資料 
int j=0;	//第幾個數字 


string s[30000];

string title;

vertex indata[30000];
vertex indata2[30000];
vertex indata3[30000];
place indata4[30000];
vertex e[30000];
int c=-1;	//幾筆place資料 

int main(){
	
	ifstream fileptr;
	fstream fileptr2;
	fstream fileptr3;
	fstream fileptr4;
	fstream fileptr5;
	fstream fileptr6;
	fileptr.open("./data.txt", ios::in);		//讀入input 
	fileptr2.open("./PM2.5.txt", ios::app);
	fileptr3.open("./PM2.5_avgsort_bubble.txt", ios::app);
	fileptr4.open("./PM2.5_avgsort_quick.txt", ios::app);
	fileptr5.open("./PM2.5_avgsort_merge.txt", ios::app);
	fileptr6.open("./PM2.5_daysort.txt", ios::app);
	string data;
	if (!fileptr || !fileptr2 || !fileptr3 || !fileptr4 || !fileptr5 || !fileptr6){
		cout << "Error!!" << endl;
		system("pause");
		exit (1);
	}
	int b=0;	
	while (getline(fileptr,data)){
		if(b==0)		//跳過第一行 
		{
			b=1;
			title=data;
			fileptr2<<data<<endl;
			continue;
		}
		
		if(data[16]=='P'&&data[17]=='M'&&data[18]=='2'&&data[19]=='.'&&data[20]=='5')
		{	
			i++;
			data=del(data);
			if(data!="0")
			{
				 
				fileptr2<<data<<endl;
			}

		}           
	}
	i++;
	
	clock_t before,after;
	double seconds;
	cout<<"執行時間:(請耐心等候)"<<endl; 
	
	before = clock();
	bubblesort(indata,i);
	after = clock();
	seconds =(double)(after-before)/CLOCKS_PER_SEC;
	cout<<"boublesort: "<<seconds<<"s"<<endl;
	
	
	before = clock();
	quicksort(indata2,0,i-1);			
	after = clock();
	seconds =(double)(after-before)/CLOCKS_PER_SEC;
	cout<<"quicksort: "<<seconds<<"s"<<endl;
	
	before = clock();
	mergesort(indata3, 0, i-1);
	after = clock(); 
	seconds =(double)(after-before)/CLOCKS_PER_SEC;
	cout<<"mergesort: "<<seconds<<"s"<<endl;
	
	//輸出平均值排序 
	fileptr3<<title<<",平均值"<<endl;
	for(int n=0;n<i;n++)
	{
		fileptr3<<indata[n].ss<<","<<indata[n].avg;
		if(n<i-1) fileptr3<<endl;		
	}
	
	fileptr4<<title<<",平均值"<<endl;
	for(int n=0;n<i;n++)
	{
		fileptr4<<indata2[n].ss<<","<<indata2[n].avg;
		if(n<i-1) fileptr4<<endl;		
	}
	
	fileptr5<<title<<",平均值"<<endl;
	for(int n=0;n<i;n++)
	{
		fileptr5<<indata3[n].ss<<","<<indata3[n].avg;
		if(n<i-1) fileptr5<<endl;		
	}
	
	//紫爆天數排序 
	bubblesortday(indata4,c+1);
	fileptr6<<"紫爆天數(0次的沒有輸出):"<<endl;
	for(int n=c;n>=0;n--)
	{	
		if(indata4[n].day != 0)
		{
			fileptr6<<indata4[n].name<<" "<<indata4[n].day;
			if(n>0) fileptr6<<endl;
		}
				
	}
	
	
	fileptr.close();
	fileptr2.close();
	fileptr3.close();
	fileptr4.close();
	fileptr5.close();
	fileptr6.close();

	return 0;
}


string del(string data){
	string newdata;
	int num=0;
	double a=0;
	
	j=0;
	for(int n=0;n<=21;n++)
	{
		newdata=newdata+data[n];	
	}

	for(int n=22;n<data.length();n++)
	{
		if(data[n]>='0'&&data[n]<='9')
		{
			newdata=newdata+data[n];
			num=num*10+data[n]-'0';
		}
		else if(data[n]==',')
		{	
			if(data[n-1]==',')
			{
				newdata=newdata+'0';
			}
			newdata=newdata+data[n];
			if(n==data.length()-1)
			{
				newdata=newdata+'0';
			}
			indata[i].num[j]=num;
			indata2[i].num[j]=num;
			indata3[i].num[j]=num;
			
			a=a+num;
			num=0;
			j++;
		}
		else
		{	
			i--;
			return "0";
			
		}
	}
	
	indata[i].num[j]=num;
	indata2[i].num[j]=num;
	indata3[i].num[j]=num;
	
	a=a+num;
	indata[i].avg=a/24;
	indata2[i].avg=a/24;
	indata3[i].avg=a/24;
	indata[i].ss=newdata;
	indata2[i].ss=newdata;
	indata3[i].ss=newdata;
	
	string check;
	string newdata2(newdata);
	check=newdata2.assign(newdata2,11,4);
	if(indata[i].avg>60)
	{
		if(c==-1)
		{	
			c++;
			indata4[c].name=check;
			indata4[c].day++;
		}
		else if(indata4[c].name==check)
		{
			indata4[c].day++;
		}
		else if(indata4[c].name!=check)
		{
			c++;
			indata4[c].name=check;
			indata4[c].day++;
		}
		
	}
	
	return newdata;
}

//sort

void bubblesort(vertex a[],int n){
	
	for (int i=0;i<n-1;i++){
		for(int j=0;j<n-1-i;j++){
			if(a[j+1].avg<a[j].avg){
				swap(a[j],a[j+1]);
				
			}
		}
	}
}

void quicksort(vertex data[], int left, int right)
{
    int  i, j;
    double pivot;
    if (left >= right) { return; }
    pivot = data[left].avg;
    i = left + 1;
    j = right;
    while (1)
    {
        while (i<=right)
        {
            if (data[i].avg > pivot) break;
            i=i+1;
        }

        while (j > left)
        {
            if (data[j].avg < pivot) break;
            j=j-1;
        }
        if (i>j)  break; 
        swap(data[i], data[j]);
    }
    swap(data[left], data[j]);

    quicksort(data, left, j - 1);
    quicksort(data, j + 1, right);
}


void mergesort(vertex a[], int low, int high)
{
    int mid;
    if (low < high)
    {	
        mid=(low+high)/2;
        mergesort(a,low,mid);
        mergesort(a,mid+1,high);

		merge(a,low,high,mid);
       
    }
    return;
}
void merge(vertex a[], int low, int high, int mid)
{	

    int p, j, k;

    p = low;
    k = low;
    j = mid + 1;
    while (p <= mid && j <= high)
    {
    	
        if (a[p].avg < a[j].avg)
        {
            e[k] = a[p];
            k++;
            p++;
        }
        else
        {
            e[k] = a[j];
            k++;
            j++;
        }
    }
    while (p <= mid)
    {
    
        e[k] = a[p];
        k++;
        p++;
    }
    while (j <= high)
    {
    	
        e[k] = a[j];
        k++;
        j++;
    }
   
    for (p = low; p < k; p++)
    {	
    
        a[p] = e[p];
        
	}

}
void bubblesortday(place a[],int n){
	
	for (int i=0;i<n-1;i++){
		for(int j=0;j<n-1-i;j++){
			if(a[j+1].day<a[j].day){
				swap(a[j],a[j+1]);
				
			}
		}
	}
}
