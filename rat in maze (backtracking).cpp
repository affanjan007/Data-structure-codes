#include <iostream>
#define N 4
using namespace std;

bool is_Valid(int maze[N][N], int row, int column){
	if(row<N && column<N && row>=0 && column>=0 && maze[row][column] == 1){
		return true;
	}
	else{
		return false;
	}
}

void print_maze(int maze[N][N]){
	for(int i=0 ; i<N ; i++){
		for(int j=0 ; j<N ; j++){
			cout<<maze[i][j]<<" ";
		}
		cout<<endl;
	}
}

bool solve(int maze[N][N], int sol[N][N], int row, int column){
	if(row == N-1 && column == N-1 && (is_Valid(maze,row,column) == true)){
		sol[row][column] = 1;
		return true;
	}
	else if(is_Valid(maze, row, column)){
		if (sol[row][column] == 1){
			return false;						//avoid revisiting a point
		}
		
		sol[row][column] = 1;
	
		if(solve(maze, sol, row, column+1) == true)			    //moving right
			return true;
		else if(solve(maze, sol, row, column-1) == true)		//moving left
			return true;
		else if(solve(maze, sol, row+1, column) == true)		//moving down
			return true;	
		else if(solve(maze, sol, row-1, column) == true)		//moving up
			return true;			
		else													//backtrack
			sol[row][column] = 0; 
			return false;
	}
	return false;
}

int main(){
	//A rat can only move vertically or horizontally
	
	int maze[N][N]={{1, 0, 0, 0},
					{1, 1, 1, 1},
			 		{1, 0, 0, 0},
			  		{1, 1, 0, 1}};
	
	int sol[N][N]= {{0, 0, 0, 0},
					{0, 0, 0, 0},
			  	    {0, 0, 0, 0},
			  	    {0, 0, 0, 0}};
	
	if(solve(maze,sol,0,0) == true){
		cout<<"Solution exist!"<<endl<<endl;
		print_maze(sol);
	}
	else{
		cout<<"Solution doesn't exist!";
	}
	return 0;			  
}