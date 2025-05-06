// ---------------------------------------------------------------Backtracking------------------------------------------------------------------------------------------------
#include<bits/stdc++.h>
using namespace std;

//safe function 
bool isSafe(int row, int col, vector<vector<int>>board, int n){
    //creating duplicates 
    int dupRow = row;
    int dupCol = col;

    //right bottom to left top up 
    while(row>=0 && col>=0){
        if(board[row][col]==1) return false;
        row--;
        col--;
    }
    row=dupRow;
    col= dupCol;

    //right top to left bottom down 
    while(row<n && col>=0){
        if(board[row][col]==1) return false;
        row++;
        col--;
    }
    row=dupRow;
    col= dupCol;

    while(col>=0){
        if(board[row][col]==1) return false;
        col--;
    }

    return true;

}

//solve function
void solve(int col,int n, vector<vector<int>>&board, vector<vector<vector<int>>>&ans){
    //base case
    if(col==n){
         
        ans.push_back(board);
        return;
    }
    //calling out all the rows 
    for(int row=0;row<n;row++){
        //if safe then place it 
        if(isSafe(row,col,board,n)){
            //place it 
            board[row][col] = 1;
            solve(col+1,n,board,ans);
            board[row][col] = 0; //backtracking 
        }
    }

}

//backtracking code 
int main(){
    vector<vector<vector<int>>> ans;
    int n; 
    cout<<"Enter n: "; cin>>n;
    cout<<endl;
    vector<vector<int>> board(n,vector<int>(n,0));
    solve(0,n,board,ans);
    
    for(int i=0;i<ans.size();i++){
        //this is matrix below 
        vector<vector<int>> b = ans[i];
        for(int j=0;j<n;j++){
            for(int k=0;k<n;k++){
                cout<<b[j][k]<<" ";
            }
            cout<<endl;
        }
        cout<<endl;
        cout<<"------------------------------------------------------"<<endl;
        cout<<endl;
    }
    
}

// --------------------------------------------------------------------Branch and Bound--------------------------------------------------------------------------------------
#include <bits/stdc++.h>
using namespace std;

// safe function
bool isSafe(vector<bool> &left_diagonal, vector<bool> &right_diagonal, vector<bool> &rows, int n, int row, int col)
{
    if (rows[row] == true || left_diagonal[row + col] == true || right_diagonal[col + n - row - 1] == true)
        return false;
    return true;
}

void solve(vector<bool> &left_diagonal, vector<bool> &right_diagonal, vector<bool> &rows, int n, vector<vector<int>> &board, int col, vector<vector<vector<int>>> &ans)
{
    // base case
    if (col == n)
    {
        ans.push_back(board);
        return;
    }
    for (int row = 0; row < n; row++)
    {
        if (isSafe(left_diagonal, right_diagonal, rows, n, row, col))
        {
            // insert then and mark diagonals true
            board[row][col] = 1;
            left_diagonal[row + col] = true;
            right_diagonal[col + n - row - 1] = true;
            rows[row] = true;

            solve(left_diagonal, right_diagonal, rows, n, board, col+1,ans);

            //bnactracking
            board[row][col] = 0;
            left_diagonal[row + col] = false;
            right_diagonal[col + n - row - 1] = false;
            rows[row] = false;

        }
    }
}

int main()
{
    vector<vector<vector<int>>> ans;
    int n;
    cout << "Enter n: ";
    cin >> n;
    cout << endl;
    vector<vector<int>> board(n, vector<int>(n, 0));
    vector<bool> left_diagonal(2 * n - 1, false);
    vector<bool> right_diagonal(2 * n - 1, false);
    vector<bool> rows(n, false);

    solve(left_diagonal,right_diagonal,rows,n,board,0,ans);

    for (int i = 0; i < ans.size(); i++)
    {
        // this is matrix below
        vector<vector<int>> b = ans[i];
        for (int j = 0; j < n; j++)
        {
            for (int k = 0; k < n; k++)
            {
                cout << b[j][k] << " ";
            }
            cout << endl;
        }
        cout << endl;
        cout << "------------------------------------------------------" << endl;
        cout << endl;
    }
}
