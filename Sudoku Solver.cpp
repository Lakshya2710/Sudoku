#include<bits/stdc++.h>
using namespace std;

bool is_valid_entry(vector<vector<int>>& grid,int row,int col,int num){
    for(int i=0;i<9;++i) if(grid[row][i]==num) return false;
    for(int i=0;i<9;++i) if(grid[i][col]==num) return false;
    int a = row/3;
    int b = col/3;
    for(int i=0;i<3;++i){
        for(int j=0;j<3;++j){
            if(grid[a*3+i][b*3+j] == num) return false;
        }
    }
    return true;
}

int generate_grid(vector<vector<int>>& grid){
    int n = 20+rand()%20;
    for(int i=0;i<n;++i){
        int num = rand()%9;
        int row = rand()%9;
        int col = rand()%9;
        while(!is_valid_entry(grid,row,col,num)) num = rand()%9;
        grid[row][col] = num;
    }
    return 81-n;
    
}
bool empty_pos(vector<vector<int>>& grid,int& row,int& col){
    for(int i=0;i<9;++i){
        for(int j=0;j<9;++j){
            if(grid[i][j]==0){
                row=i;
                col=j;
                return true;
            }
        }
    }
    return false;
}

bool Sudoku_solver(vector<vector<int>>& grid){
    int row,col;
    /*for(int i=0;i<9;++i){
        for(int j=0;j<9;++j){
            if(grid[i][j]==0){
                row=i;
                col=j;
                break;
            }
        }
    }
    if(row==-1) return true;*/
    if(!empty_pos(grid,row,col)) return true;
    for(int i=1;i<=9;++i){
        if(is_valid_entry(grid,row,col,i)){
            grid[row][col]=i;
            if(Sudoku_solver(grid)) return true;
            grid[row][col]=0;
        }
    }
    return false;
}

void printGrid(vector<vector<int>>& grid){
    cout<<endl;
    cout<<"-------------------------------------\n";
    for(int i=0;i<9;++i){
        cout<<"|";
        for(int j=0;j<9;++j){
            if(grid[i][j]==0) cout<<"   |";
            else cout<<" "<<grid[i][j]<<" |";
        }
        cout<<endl;
        cout<<"-------------------------------------\n";
    }
    cout<<endl;
}

int main(){
    char s;
    cout<<"WELCOME!!!\n";
    while(true){
        vector<vector<int>> grid;
        grid.resize(9,vector<int> (9,0));
        cout<<"Enter mode (Enter 's' if you have a sudoku and want the solution to it else \nPress 'g' to solve a random sudoku by yourself)\n";
        cin>>s;
        int n;
        if(s=='s'){
            cout<<"Enter Sudoku board row by row";
            for(int i=0;i<9;++i){
                for(int j=0;j<9;++j)cin>>grid[i][j];
            }

            printGrid(grid);
            Sudoku_solver(grid);
            printGrid(grid);
        }
        else{
            n=generate_grid(grid);
            printGrid(grid);
            int row,col,num;
            while(n>0){
                cout<<"Enter row, column and number you want to enter: ";
                cin>>row>>col>>num;
                if(grid[row-1][col-1]!=0) cout<<"Position already occupied\n";
                else if(is_valid_entry(grid,row-1,col-1,num)){
                    grid[row-1][col-1]=num;
                    printGrid(grid);
                    --n;
                    if(n==0) cout<<"\nYou WON!!!\n";
                    continue;
                }
                else{
                    cout<<"Invalid number\nDo you want to see the solution?(y/n):";
                    char c;
                    cin>>c;
                    if(c=='y'){
                        Sudoku_solver(grid);
                        printGrid(grid);
                        break;
                    }
                    printGrid(grid);
                }
            }
        }
        cout<<"\nDo you want to solve another Sudoku? (y/n)\n";
        cin>>s;
        if(s=='n') break;
    }
    cout<<"THANKS FOR PLAYING!!!";
}