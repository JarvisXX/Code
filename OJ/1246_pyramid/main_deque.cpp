#include <iostream>
using namespace std;

int m, n, a, b, c, d;
int input;
int field[1010][1010];
int deque[1010];
int head, tail;
int tombRow[1010][1010];
int tomb[1010][1010];
int X_que[1010];
int Y_que[1010];
int XR[1010][1010];
int YR[1010][1010];
int X[1010][1010];
int Y[1010][1010];
int value, maxValue;
int pyramidX, pyramidY, tombX, tombY;

int getT(int i, int j)
{
    return field[i+c-1][j+d-1]-field[i-1][j+d-1]-field[i+c-1][j-1]+field[i-1][j-1];
}

int getP(int i, int j)
{
    return field[i+a-1][j+b-1]-field[i-1][j+b-1]-field[i+a-1][j-1]+field[i-1][j-1];
}

int main()
{
    cin >> m >> n >> a >> b >> c >> d;
    for (int j=1; j<=n; ++j)
    {
        for (int i=1; i<=m; ++i)
        {
            cin >> input;
            field[i][j] = field[i-1][j] + field[i][j-1] - field[i-1][j-1] +input;
        }
    }

    for (int j=2; j<=n-d; ++j)
    {
        head = tail = 0;
        for (int i=2; i<=m-c; ++i)
        {
            int num=getT(i, j);
            while (head!=tail && deque[tail-1]>num)
                --tail;
            X_que[tail] = i;
            Y_que[tail] = j;
            deque[tail++] = num;
            if (i-a+c+1>=1)
            {
                if (i-a+c+1>1 && getT(i-a+c+1, j)==deque[head])
                    ++head;
                tombRow[i-a+c+1][j-1] = deque[head];
                XR[i-a+c+1][j-1] = X_que[head];
                YR[i-a+c+1][j-1] = Y_que[head];
            }
        }
    }

    for (int i=1; i<=m-a+1; ++i)
    {
        head = tail = 0;
        for (int j=1; j<=n-d-1; ++j)
        {
            int num=tombRow[i][j];
            while (head!=tail && deque[tail-1]>num)
                --tail;
            X_que[tail] = XR[i][j];
            Y_que[tail] = YR[i][j];
            deque[tail++] = num;
            if (j-b+d+2>=1)
            {
                if (j-b+d+2>1 && tombRow[i][j-b+d+1]==deque[head])
                    ++head;
                tomb[i][j-b+d+2] = deque[head];
                X[i][j-b+d+2] = X_que[head];
                Y[i][j-b+d+2] = Y_que[head];
            }
        }
    }

    maxValue = 0;
    for (int i=1; i+a-1<=m; ++i)
    {
        for (int j=1; j+b-1<=n; ++j)
        {
            value = getP(i, j)-tomb[i][j];
            if (value>maxValue)
            {
                maxValue = value;
                pyramidX = i;
                pyramidY = j;
                tombX = X[i][j];
                tombY = Y[i][j];
            }
        }
    }
    cout << pyramidX <<' '<< pyramidY <<endl;
    cout << tombX <<' '<< tombY <<endl;
}
