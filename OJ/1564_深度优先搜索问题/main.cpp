#include <iostream>
using namespace std;

int minResult=0;

void dfs_1(int matrix[6][6], int ax, int ay, int bx, int by, int state, int result)
{
    if (ax>bx || ay>by)
        return;
    else if (ax==bx && ay==by)
    {
        if (minResult==0)
            minResult = result;
        else
            minResult = (result<minResult) ? result : minResult;
    }
    else
    {
        int cost_x = matrix[ax+1][ay]*state;
        dfs_1(matrix, ax+1, ay, bx, by, (cost_x%4)+1, result+cost_x);
        int cost_y = matrix[ax][ay+1]*state;
        dfs_1(matrix, ax, ay+1, bx, by, (cost_y%4)+1, result+cost_y);
    }
}

void dfs_2(int matrix[6][6], int ax, int ay, int bx, int by, int state, int result)
{
    if (ax>bx || ay<by)
        return;
    else if (ax==bx && ay==by)
    {
        if (minResult==0)
            minResult = result;
        else
            minResult = (result<minResult) ? result : minResult;
    }
    else
    {
        int cost_x = matrix[ax+1][ay]*state;
        dfs_2(matrix, ax+1, ay, bx, by, (cost_x%4)+1, result+cost_x);
        int cost_y = matrix[ax][ay+1]*state;
        dfs_2(matrix, ax, ay+1, bx, by, (cost_y%4)+1, result+cost_y);
    }
}

void dfs_3(int matrix[6][6], int ax, int ay, int bx, int by, int state, int result)
{
    if (ax<bx || ay>by)
        return;
    else if (ax==bx && ay==by)
    {
        if (minResult==0)
            minResult = result;
        else
            minResult = (result<minResult) ? result : minResult;
    }
    else
    {
        int cost_x = matrix[ax+1][ay]*state;
        dfs_3(matrix, ax+1, ay, bx, by, (cost_x%4)+1, result+cost_x);
        int cost_y = matrix[ax][ay+1]*state;
        dfs_3(matrix, ax, ay+1, bx, by, (cost_y%4)+1, result+cost_y);
    }
}

void dfs_4(int matrix[6][6], int ax, int ay, int bx, int by, int state, int result)
{
    if (ax<bx || ay<by)
        return;
    else if (ax==bx && ay==by)
    {
        if (minResult==0)
            minResult = result;
        else
            minResult = (result<minResult) ? result : minResult;
    }
    else
    {
        int cost_x = matrix[ax+1][ay]*state;
        dfs_4(matrix, ax+1, ay, bx, by, (cost_x%4)+1, result+cost_x);
        int cost_y = matrix[ax][ay+1]*state;
        dfs_4(matrix, ax, ay+1, bx, by, (cost_y%4)+1, result+cost_y);
    }
}

int main()
{
    int n;
    int matrix[6][6];
    int ax, ay, bx, by; //a-start, b-end
    int state=1, result=0;

    cin >> n;
    for (int k=0; k<n; ++k)
    {
        for (int i=0; i<6; ++i)
            for (int j=0; j<6; ++j)
                cin >> matrix[i][j];
        cin >> ax >> ay >> bx >> by;
        if (ax<=bx||ay<=by)
            dfs_1(matrix, ax, ay, bx, by, state, result);
        if (ax<=bx||ay>=by)
            dfs_2(matrix, ax, ay, bx, by, state, result);
        if (ax>=bx||ay<=by)
            dfs_3(matrix, ax, ay, bx, by, state, result);
        if (ax>=bx||ay>=by)
            dfs_4(matrix, ax, ay, bx, by, state, result);
        cout << minResult << endl;
    }
}
