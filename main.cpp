// FIvanO
#include <iostream>
#include <fstream>
#include <math.h>
#include <algorithm>
#include <cstring>
#include <stdlib.h>
#include <stdio.h>
#include <vector>
#include <map>
#include <deque>
#define mp(x,y) make_pair(x,y)

using namespace std;

double getCont();
void getPoint(double &x, double &y);
int wherePoint(double x, double y, double a);
void outResults(int result);
int determinant(double x1, double y1, double x2, double y2);

int main()
{
    ios_base::sync_with_stdio(0);

    double x,y;
    double a=getCont();

    if (a<=0)
    {
        cout<<"<<<WRONG PARAMETER>>>"<<endl;
        return 0;
    }

    getPoint(x,y);
    outResults(wherePoint(x,y,a));

    return 0;
}

double getCont()
{
    double a;
    cout<<"Введите параметр а: ";
    cin>>a;
    return a;
}

void getPoint(double &x, double &y)
{
    cout<<"Введите координаты точки."<<endl;
    cout<<"x: ";
    cin>>x;
    cout<<"y: ";
    cin>>y;
}

int wherePoint(double x, double y, double a)
{
    pair < double, double > p[10];
    pair < double, double > p1[10];
    int mark[10]; // Знак ориентированой площади
    p[1]=mp(a,0);
    p[2]=mp(0,a);
    p[3]=mp(-a,a);
    p[4]=mp(-a,0);
    p[5]=mp(0,-a);
    p[6]=mp(a,-a);
    // координаты векторов - сторон шестиугольника
    p1[1]=mp(x-a,y);
    p1[2]=mp(x-2*a,y);
    p1[3]=mp(x-2*a,y-a);
    p1[4]=mp(x-a,y-2*a);
    p1[5]=mp(x,y-2*a);
    p1[6]=mp(x,y-a);
    // координаты векторов от точки шестиугольника до данной

    int sum=0;
    bool flag=false;
    for (int i=1; i<7; i++)
    {
        mark[i]=determinant(p[i].first, p[i].second, p1[i].first, p1[i].second);
        sum+=mark[i];
        if (mark[i]==0) flag=true;
    }

    if (sum==6) return -1;
    if (!flag) return 1;
    if (flag)
    {
        if (sum==5 || sum==4) return 0;
        else return 1;
    }
}

void outResults(int result)
{
    switch(result)
    {
    case -1:
        cout<<"IN_C"<<endl;
        break;
    case 0:
        cout<<"ON_C"<<endl;
        break;
    case 1:
        cout<<"OUT_C"<<endl;
        break;
    }
}

int determinant(double x1, double y1, double x2, double y2) // Определение знака определителя
{
    if ((x1*y2-x2*y1)>0) return 1;
    else if ((x1*y2-x2*y1)<0) return -1;
    else
        return 0;
}

