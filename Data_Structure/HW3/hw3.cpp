#include <iostream>
#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include <cmath>
#include <iomanip>
#include <algorithm>
#define size 10
#define N MAZE[x-1][y]	    /*定義北方的相對位置*/
#define E  MAZE[x][y+1]     /*定義東方的相對位置*/
#define S MAZE[x+1][y]	    /*定義南方的相對位置*/
#define W  MAZE[x][y-1]     /*定義西方的相對位置*/
using namespace std;

int MAZE[size][size]={0};
/*
int MAZE[size][size]={0,0,0,0,0,0,0,0,0,0,
						0,0,0,0,0,0,0,0,0,0,
						0,0,1,1,0,1,0,0,0,0,
						0,0,1,1,1,1,0,0,0,0,
						0,1,1,1,1,1,1,1,0,0,
						0,1,1,1,1,1,0,0,0,0,
						0,0,0,0,0,0,0,0,0,0,
						0,0,0,0,0,0,0,0,0,0,
						0,0,0,0,0,0,0,0,0,0,
						0,0,0,0,0,0,0,0,0,0};
*/
int depth[size][size]={0};            
int visit[size][size]={0};		//store if we have visit the point
int kind[size][size]; 
int num[4]={0};          
void random(int n);
void bfs_path();
void print();
typedef struct               //store the point information
{
	int row;
	int col;
	//int depth;	
	//int kind;	//0,1,2,3
	//int visit;
	//int ra;		//活點 0,1 
}vertex;
//void enque(vertex *que,int row,int col,int depth,int kind,int visit);     
//void deque(vertex *que,int &row,int &col,int &depth,int &kind,int &visit);  
void enque(vertex *que,int row,int col);	//implement enqueue
void deque(vertex *que,int &row,int &col);	//implement delete queue
int front, rear;
int top=0;
int priority[4][4]={4,3,2,1,
					1,4,3,2,
					2,1,4,3,
					3,2,1,4	};

int main()
{
	int n;
	cout<<"請輸入0~99的整數:";
	cin>>n;
	random(n);
	bfs_path();
	print();
	
	return 0;
} 

void bfs_path()
{	
	int row,col;
	vertex que[size*size];		  //queue
	enque(que,5,5);
	visit[5][5]=1;
	deque(que,row,col); 
	front=0, rear=0;
	
	if(MAZE[row-1][col]==1)		//上 
	{
		kind[row-1][col]=0;
		visit[row-1][col]=1;
		depth[row-1][col]=1;
		num[0]++;
		enque(que,row-1,col);
		
	}						
	if(MAZE[row][col+1]==1)		//右 
	{
		kind[row][col+1]=1;
		visit[row][col+1]=1;
		depth[row][col+1]=1;
		num[1]++;
		enque(que,row,col+1);
	} 				
	if(MAZE[row+1][col]==1)		//下
	{	
		kind[row+1][col]=2;
		visit[row+1][col]=1;
		depth[row+1][col]=1;
		num[2]++;
		enque(que,row+1,col);
	}					 
	if(MAZE[row][col-1]==1)		//左 
	{
		kind[row][col-1]=3;	
		visit[row][col-1]=1;
		depth[row][col-1]=1;
		num[3]++;
		enque(que,row,col-1);				
	}
	
	while(front!=rear)                               //while queue is not empty
	{
		deque(que,row,col);
		
		if(row-1>=0&&MAZE[row-1][col]==1)		//上 
		{
			if(visit[row-1][col]==0)		//沒有拜訪過 
			{
				kind[row-1][col]=kind[row][col];
				visit[row-1][col]=1;
				depth[row-1][col]=depth[row][col]+1;
				num[kind[row-1][col]]++;
				enque(que,row-1,col);
			}
			
			else					//拜訪過 
			{
				if(depth[row-1][col] > depth[row][col]+1)
				{
					num[kind[row-1][col]]--;
					kind[row-1][col]=kind[row][col];
					num[kind[row-1][col]]++;
					depth[row-1][col]=depth[row][col]+1;	
				}
				else if(depth[row-1][col] == depth[row][col]+1)
				{
					if(num[kind[row-1][col]]-1 > num[kind[row][col]])
					{
						num[kind[row-1][col]]--;
						kind[row-1][col]=kind[row][col];
						num[kind[row-1][col]]++;
						depth[row-1][col]=depth[row][col]+1;
					}
					
					else if(num[kind[row-1][col]]-1 == num[kind[row][col]])
					{	
						if(row-1<5 && col<=5)	//左上 
						{
							if(priority[0][kind[row-1][col]] < priority[0][kind[row][col]])
							{
								num[kind[row-1][col]]--;
								kind[row-1][col]=kind[row][col];
								num[kind[row-1][col]]++;
								depth[row-1][col]=depth[row][col]+1;
							}
							 
						}
						else if(row-1<=5 && col>5)	//右上 
						{
							if(priority[1][kind[row-1][col]] < priority[1][kind[row][col]])
							{
								num[kind[row-1][col]]--;
								kind[row-1][col]=kind[row][col];
								num[kind[row-1][col]]++;
								depth[row-1][col]=depth[row][col]+1;
							}
						}
						else if(row-1>5 && col>=5)	//右下 
						{
							if(priority[2][kind[row-1][col]] < priority[2][kind[row][col]])
							{
								num[kind[row-1][col]]--;
								kind[row-1][col]=kind[row][col];
								num[kind[row-1][col]]++;
								depth[row-1][col]=depth[row][col]+1;
							}
						}	 
						else if(row-1>=5 && col<5)	//左下 
						{
							if(priority[3][kind[row-1][col]] < priority[3][kind[row][col]])
							{
								num[kind[row-1][col]]--;
								kind[row-1][col]=kind[row][col];
								num[kind[row-1][col]]++;
								depth[row-1][col]=depth[row][col]+1;
							}
						}
						
					}
				}
			}
		}							
		if(col+1<10&&MAZE[row][col+1]==1)		//右 
		{
			if(visit[row][col+1]==0)
			{
				kind[row][col+1]=kind[row][col];
				visit[row][col+1]=1;
				depth[row][col+1]=depth[row][col]+1;
				num[kind[row][col+1]]++;
				enque(que,row,col+1);
			}	
			else
			{
				if(depth[row][col+1] > depth[row][col]+1)
					{
						num[kind[row][col+1]]--;
						kind[row][col+1]=kind[row][col];
						num[kind[row][col+1]]++;
						depth[row][col+1]=depth[row][col]+1;
						
					}
					else if(depth[row][col+1] == depth[row][col]+1)
					{
						if(num[kind[row][col+1]]-1 > num[kind[row][col]])
						{
							num[kind[row][col+1]]--;
							kind[row][col+1]=kind[row][col];
							num[kind[row][col+1]]++;
							depth[row][col+1]=depth[row][col]+1;
						}
						
						else if(num[kind[row][col+1]]-1== num[kind[row][col]])
						{

							if(row<5 && col+1<=5)	//左上 
							{
								if(priority[0][kind[row][col+1]] < priority[0][kind[row][col]])
								{
									num[kind[row][col+1]]--;
									kind[row][col+1]=kind[row][col];
									num[kind[row][col+1]]++;
									depth[row][col+1]=depth[row][col]+1;
								}
							}
							else if(row<=5 && col+1>5)	//右上 
							{
								if(priority[1][kind[row][col+1]] < priority[1][kind[row][col]])
								{
									num[kind[row][col+1]]--;
									kind[row][col+1]=kind[row][col];
									num[kind[row][col+1]]++;
									depth[row][col+1]=depth[row][col]+1;
								}
							}
							else if(row>5 && col+1>=5)	//右下 
							{
								if(priority[2][kind[row][col+1]] < priority[2][kind[row][col]])
								{
									num[kind[row][col+1]]--;
									kind[row][col+1]=kind[row][col];
									num[kind[row][col+1]]++;
									depth[row][col+1]=depth[row][col]+1;
								}
							}
							else if(row>=5 && col+1<5)	//左下 
							{
								if(priority[3][kind[row][col+1]] < priority[3][kind[row][col]])
								{
									num[kind[row][col+1]]--;
									kind[row][col+1]=kind[row][col];
									num[kind[row][col+1]]++;
									depth[row][col+1]=depth[row][col]+1;
								}
							}
						
						}	
					}	
			}
		} 				
		if(row+1<10&&MAZE[row+1][col]==1)		//下
		{	
			if(visit[row+1][col]==0)
			{
				kind[row+1][col]=kind[row][col];
				visit[row+1][col]=1;
				depth[row+1][col]=depth[row][col]+1;
				num[kind[row+1][col]]++;
				enque(que,row+1,col);
			}
			else{
				
				if(depth[row+1][col] > depth[row][col]+1)
				{
					num[kind[row+1][col]]--;
					kind[row+1][col]=kind[row][col];
					num[kind[row+1][col]]++;
					depth[row+1][col]=depth[row][col]+1;
						
				}
				else if(depth[row+1][col] == depth[row][col]+1)
				{
					if(num[kind[row+1][col]]-1 > num[kind[row][col]])
					{
						num[kind[row+1][col]]--;
						kind[row+1][col]=kind[row][col];
						num[kind[row+1][col]]++;
						depth[row+1][col]=depth[row][col]+1;
					}
					
					else if(num[kind[row+1][col]]-1 == num[kind[row][col]])
					{
						if(row+1<5 && col<=5)	//左上 
						{
							if(priority[0][kind[row+1][col]] < priority[0][kind[row][col]])
							{
								num[kind[row+1][col]]--;
								kind[row+1][col]=kind[row][col];
								num[kind[row+1][col]]++;
								depth[row+1][col]=depth[row][col]+1;
							}
								 
						}
						else if(row+1<=5 && col>5)	//右上 
						{
							if(priority[1][kind[row+1][col]] < priority[1][kind[row][col]])
							{
								num[kind[row+1][col]]--;
								kind[row+1][col]=kind[row][col];
								num[kind[row+1][col]]++;
								depth[row+1][col]=depth[row][col]+1;
							}
						}
						else if(row+1>5 && col>=5)	//右下 
						{
							if(priority[2][kind[row][col+1]] < priority[2][kind[row][col]])
							{
								num[kind[row+1][col]]--;
								kind[row+1][col]=kind[row][col];
								num[kind[row+1][col]]++;
								depth[row+1][col]=depth[row][col]+1;
							}
						}
						else if(row+1>=5 && col<5)	//左下 
						{
							if(priority[3][kind[row+1][col]] < priority[3][kind[row][col]])
							{
								num[kind[row+1][col]]--;
								kind[row+1][col]=kind[row][col];
								num[kind[row+1][col]]++;
								depth[row+1][col]=depth[row][col]+1;
							}
						}
						
					}
				}	
			}
		}					 
		if(col-1>=0&&MAZE[row][col-1]==1)		//左 
		{	
			if(visit[row][col-1]==0)
			{
				kind[row][col-1]=kind[row][col];
				visit[row][col-1]=1;
				depth[row][col-1]=depth[row][col]+1;
				num[kind[row][col-1]]++;
				enque(que,row,col-1);
			}
			else
			{
				
				if(depth[row][col-1] > depth[row][col]+1)
				{
					num[kind[row][col-1]]--;
					kind[row][col-1]=kind[row][col];
					num[kind[row][col-1]]++;
					depth[row][col-1]=depth[row][col]+1;
						
				}
				else if(depth[row][col-1] == depth[row][col]+1)
				{
					if(num[kind[row][col-1]]-1 > num[kind[row][col]])
					{
						num[kind[row][col-1]]--;
						kind[row][col-1]=kind[row][col];
						num[kind[row][col-1]]++;
						depth[row][col-1]=depth[row][col]+1;
					}
					
					else if(num[kind[row][col-1]]-1 == num[kind[row][col]])
					{
					
						if(row<5 && col-1<=5)	//左上 
						{
							if(priority[0][kind[row][col-1]] < priority[0][kind[row][col]])
							{
								num[kind[row][col-1]]--;
								kind[row][col-1]=kind[row][col];
								num[kind[row][col-1]]++;
								depth[row][col-1]=depth[row][col]+1;
							}
								 
						}
						else if(row<=5 && col-1>5)	//右上 
						{
							if(priority[1][kind[row][col-1]]<priority[1][kind[row][col]])
							{
								num[kind[row][col-1]]--;
								kind[row][col-1]=kind[row][col];
								num[kind[row][col-1]]++;
								depth[row][col-1]=depth[row][col]+1;
							}
						}
						else if(row>=5 && col-1<5)	//左下 
						{
							if(priority[3][kind[row][col-1]] < priority[3][kind[row][col]])
							{
								num[kind[row][col-1]]--;
								kind[row][col-1]=kind[row][col];
								num[kind[row][col-1]]++;
								depth[row][col-1]=depth[row][col]+1;
							}
						}
						else if(row>5 && col-1>=5)	//右下 
						{
							if(priority[2][kind[row][col-1]] < priority[2][kind[row][col]])
							{
								num[kind[row][col-1]]--;
								kind[row][col-1]=kind[row][col];
								num[kind[row][col-1]]++;
								depth[row][col-1]=depth[row][col]+1;
							}
						}
					}
				}		
			}			
		}	
	}
}

void print(){
	
	cout<<"1.Rorted Paths :"<<endl;
	
	int hub[4]={0};
	int d[4]={0};
	cout<<"***Path0 Hub links:";
	for(int i=0;i<size;i++)
	{
		for(int j=0;j<size;j++)
		{
			if(visit[i][j]==1&&kind[i][j]==0 )
			{	
				if(!(i==5&&j==5))
				{
					cout<<"<"<<i<<","<<j<<">";
					hub[0]++;
				
					if(depth[i][j]>d[0])
					{
						d[0]=depth[i][j];
					}
				}
			}
		}
	}
	cout<<endl;
	cout<<"Path0 Hub數="<<hub[0]<<","<<"Max Depth="<<d[0]<<endl;
	cout<<endl;
	cout<<"***Path1 Hub links:";
	for(int i=0;i<size;i++)
	{
		for(int j=0;j<size;j++)
		{
			if(visit[i][j]==1&&kind[i][j]==1)
			{
				cout<<"<"<<i<<","<<j<<">";
				hub[1]++;
				
				if(depth[i][j]>d[1])
				{
					d[1]=depth[i][j];
				}
			}
		}
	}
	cout<<endl;
	cout<<"Path1 Hub數="<<hub[1]<<","<<"Max Depth="<<d[1]<<endl;
	cout<<endl;
	cout<<"***Path2 Hub links:";
	for(int i=0;i<size;i++)
	{
		for(int j=0;j<size;j++)
		{
			if(visit[i][j]==1&&kind[i][j]==2)
			{
				cout<<"<"<<i<<","<<j<<">";
				hub[2]++;
				
				if(depth[i][j]>d[2])
				{
					d[2]=depth[i][j];
				}
			}
		}
	}
	cout<<endl;
	cout<<"Path2 Hub數="<<hub[2]<<","<<"Max Depth="<<d[2]<<endl;
	cout<<endl;
	cout<<"***Path3 Hub links:";
	for(int i=0;i<size;i++)
	{
		for(int j=0;j<size;j++)
		{
			if(visit[i][j]==1&&kind[i][j]==3)
			{
				cout<<"<"<<i<<","<<j<<">";
				hub[3]++;
				
				if(depth[i][j]>d[3])
				{
					d[3]=depth[i][j];
				}
			}
		}
	}
	cout<<endl;
	cout<<"Path3 Hub數="<<hub[3]<<","<<"Max Depth="<<d[3]<<endl;
	cout<<endl;
	cout<<"2.Isolated Node :";

	int iso=0;
	for(int i=0;i<size;i++)
	{
		for(int j=0;j<size;j++)
		{
			if(MAZE[i][j]==1&&visit[i][j]==0)
			{
				iso++;
				cout<<"<"<<i<<","<<j<<">";
			}
			
		}
	}
	cout<<endl;
	cout<<"Isolated 數="<<iso<<endl;
	cout<<endl;
	double ave=0;
	double num=1;
	for(int i=0;i<size;i++)
	{
		for(int j=0;j<size;j++)
		{
			if(depth[i][j]!=0)
			{
				ave=ave+depth[i][j];
				num++;
			}
			
		}
	}
	
	cout<<"3.Average Depth:"<<ave/num<<endl;
	cout<<endl;
	sort(d,d+4);
	cout<<"4.Max Depth:"<<d[3]<<endl;
	cout<<endl;
	cout<<"5.Map :"<<endl;
	for(int i=0;i<size;i++)
	{
		for(int j=0;j<size;j++)
		{
			if(i==5&&j==5) cout<<" o ";
			else if(visit[i][j]==0 && MAZE[i][j]==1)cout<<"iso";
			else if(MAZE[i][j]==0) cout<<" - ";
			else cout<<" "<<kind[i][j]<<" ";
			
		}
		cout<<endl;
	}
	cout<<endl;
	cout<<"6.Depth :"<<endl;
	
	for(int i=0;i<size;i++)
	{
		for(int j=0;j<size;j++)
		{
			cout<<setw(3)<<depth[i][j];
			
		}
		cout<<endl;
	}
	
	
}

//void enque(vertex *que,int row,int col,int depth,int kind,int visit)     
void enque(vertex *que,int row,int col)				//add element into queue
{
	que[rear].row=row;                              //store information into queue   
	que[rear++].col=col;
	//que[rear].depth=depth;                               
	//que[rear].kind=kind;
	//que[rear++].visit=visit;
}
//void deque(vertex *que,int &row,int &col,int &depth,int &kind,int &visit) 
void deque(vertex *que,int &row,int &col)			 //delete element from queue
{
	row=que[front].row;                             //get the queue information  
	col=que[front++].col;
	//depth=que[front].depth;                              
	//kind=que[front].kind;
	//visit=que[front++].visit;
}

void random(int n)
{	
	MAZE[5][5]=1;
	int ran;
	int r,c;
	srand(time(NULL));

		for(int i=0;i<n;)
		{	
			ran=rand()%(size*size);
			//cout<<ran;
			r=ran/size;
			c=ran%size;
			if(MAZE[r][c]==0)
			{
				MAZE[r][c]=1;
				i++;
			}
		}
	
	/*
	for(int m=0;m<10;m++){
		for(int n=0;n<10;n++)
		cout<<MAZE[m][n];
		cout<<endl;
		
	}
	*/	
}
