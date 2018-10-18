#include<iostream>
#include<cstdlib>
#include<ctime>
#include<iomanip>
using namespace std;
void make_Maze();
void BFS_Path();
void print_Path();

int maze[15][15];            //store the maze 
int path[15][15];            //store the lenth of path at each point
int visit[15][15];           //store if we have visit the point
const int dir[8][2]={ {0,1},{1,0},{0,(-1)},{(-1),0},{1,1},{1,(-1)},{(-1),1},{(-1),(-1)}};  //eight direction we might go
typedef struct               //store the point information
{
	int row;
	int col;
	int val;
}vertex;
int front=0, rear=0;                                 //queue's front position ,queue's rear position
void enque(vertex *que,int row,int col,int val);     //implement enqueue
void deque(vertex *que,int &row,int &col,int &val);  //implement delete queue
int top=0;                                           //stack's top position
void push(vertex *stk,int row,int col,int val);      //implement stack push
void pop(vertex *stk,int &row,int &col,int &val);    //implement stack pop

int main()
{
	string ch;
	do
	{
		make_Maze();          //make a maze
		BFS_Path();           //use BFS method to find path
		print_Path();         //print one of the possible path
		
		cout<<"要繼續下一個maze嗎?(按Y確認)"<<endl;  // ask if want to make another maze
		cin>>ch;  
	}while(ch=="Y"||ch=="y");                        //if ch="Y"or"y" then continue
	return 0;
} 

void make_Maze()
{
	srand((unsigned)time(NULL));                     //make the maze by random(seed :time(null))
	for(int i=0;i<15;i++)                            //the size of the maze
	{
		for(int j=0;j<15;j++)                        //the size of the maze
		{
			maze[i][j]=rand()%3;                     //each of vertex of maze is 0~3
			if(i==0&&j==0)                           //because if maze[0][0] is 1 will be no path, we force it to 0
				maze[i][j]=0;
			cout<<setw(3)<<maze[i][j];               //print the maze with width 3
		}
		cout<<endl;
	}	
	cout<<endl;
}
void BFS_Path()
{
	for(int i=0;i<15;i++)                            //initialize visit[][] to all 0
		for(int j=0;j<15;j++)
			visit[i][j]=0;
	for(int i=0;i<15;i++)                            //initialize path[][] to all 0
		for(int j=0;j<15;j++)
			path[i][j]=0;
	front=0, rear=0;                                 //comfirm queue store begin from 0
	vertex que[255];                                 //queue
	enque(que,0,0,maze[0][0]);                       //store the first point information
	path[0][0]=1;                                    //the length of first point is 1
	visit[0][0]=1;                                   //we have visited
	while(front!=rear)                               //while queue is not empty
	{
		int v,row,col;
		deque(que,row,col,v);                        //get the first point infromation in queue 
		if(v==0)                                     //if the value of point is 1
		{
			for(int i=0;i<8;i++)                     //we try to meet eight direction from the point
			{
				if( row+dir[i][0]<0 || col+dir[i][1]<0 || row+dir[i][0]>=15 || col+dir[i][1]>=15)  //if the move will be out of boundary then continue
					continue;
				if(maze[row+dir[i][0]][col+dir[i][1]]!=1&&visit[row+dir[i][0]][col+dir[i][1]]!=1)  //if the point we want to move to is not "0" 
				{                                                                                  //and the point we have not visited
					visit[row+dir[i][0]][col+dir[i][1]]=1;                      //mark the point to 1(we have visited)
					enque(que,row+dir[i][0],col+dir[i][1],maze[row+dir[i][0]][col+dir[i][1]]);     //put the point information into queue                  
					path[row+dir[i][0]][col+dir[i][1]]=path[row][col]+1;        //mark the point length to recent point length+1
				}
			}
		}
		else if(v==2)                                //if the value of point is 2
		{
			for(int i=0;i<4;i++)                     //we try to meet four direction from the point
			{
				if( row+dir[i][0]<0 || col+dir[i][1]<0 || row+dir[i][0]>=15 || col+dir[i][1]>=15)  //if the move will be out of boundary then continue
					continue;
				if(maze[row+dir[i][0]][col+dir[i][1]]!=1&&visit[row+dir[i][0]][col+dir[i][1]]!=1)  //if the point we want to move to is not "0" 
				{                                                                                  //and the point we have not visited
					visit[row+dir[i][0]][col+dir[i][1]]=1;                      //mark the point to 1(we have visited)
					enque(que,row+dir[i][0],col+dir[i][1],maze[row+dir[i][0]][col+dir[i][1]]);     //put the point information into queue
					path[row+dir[i][0]][col+dir[i][1]]=path[row][col]+1;        //mark the point length to recent point length+1
				} 
			}
		}
	}
	for(int i=0;i<15;i++)                           //print the path[][]
	{
		for(int j=0;j<15;j++)
		{
			cout<<setw(3)<<path[i][j];
		}
		cout<<endl;
	}
}
void enque(vertex *que,int row,int col,int val)     //add element into queue
{
	que[rear].row=row;                              //store information into queue   
	que[rear].col=col;
	que[rear++].val=val;
}
void deque(vertex *que,int &row,int &col,int &val)  //delete element from queue
{
	val=que[front].val;                             //get the queue information  
	row=que[front].row;
	col=que[front++].col;
}
void print_Path()
{
	if(path[14][14]==0)                             //if the length of maze[14][14] is 0, we know it has no path
	{
		cout<<"There is no path!!"<<endl<<endl;     //print the message
		return;
	}	
	cout<<"The shortest path of the maze is "<<path[14][14]<<endl;//print the message of the shortest length
	vertex stk[10];                                 //implement a stack which store the points of path 
	top=0;                                          //confirm stack begin from 0
	push(stk,14,14,path[14][14]);                   //we put the path message from the back forward
	maze[14][14]=3;                                 //change the maze position to 3 if the position is in the path
	while(stk[top-1].val!=1)                        //loop until we find the position which is length 1(initial position)
	{
		int v,row,col;
		pop(stk,row,col,v);                         //pop the stack 
		for(int i=7;i>=0;i--)                       //try to meet eight direction from the point
		{
			if(row+dir[i][0]<0 || col+dir[i][1]<0 || row+dir[i][0]>=15 || col+dir[i][1]>=15)  //if the move will be out of boundary then continue
				continue;
			if(path[row+dir[i][0]][col+dir[i][1]]==(v-1))         //when we find the possible previous path
			{
				if(i>=4&&maze[row+dir[i][0]][col+dir[i][1]]==2)   //when i>=4, the move direction is just for point value 0
					continue;                                     //must continue if point value is 2
				push(stk,row+dir[i][0],col+dir[i][1],v-1);        //push the path information to stack
				maze[row+dir[i][0]][col+dir[i][1]]=3;             //mark the position to 3
				break;                                            //we just have to find one path, so we can break now
			}
		}
	}
	for(int i=0;i<15;i++)                           //print the path
	{
		for(int j=0;j<15;j++)
		{
			if(maze[i][j]!=3)
				cout<<setw(3)<<"*";
			else cout<<setw(3)<<"3";
		}
		cout<<endl;
	}
	cout<<endl;
}
void push(vertex *stk,int row,int col,int val)      //stack push
{                                                   //because the stack will never be full, we don't check stackfull
	stk[top].row=row;                               //store information to stack
	stk[top].col=col;
	stk[top++].val=val;
}
void pop(vertex *stk,int &row,int &col,int &val)    //stack pop
{                                                   //because the stack will never be empty, we don't check stackempty
	row=stk[--top].row;                             //get the information from stack
	col=stk[top].col;
	val=stk[top].val;
}
