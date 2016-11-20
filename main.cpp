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

int getCont(double &a);
int getPoint(double &x, double &y);
int wherePoint(double x, double y, double a);
void outResults(double x, double y, double a, int WhereP, double dist);
int determinant(pair < double, double > p1, pair < double, double > p2);
int scalar_product(pair < double, double > p1, pair < double, double > p2);
double distPointCont(double a, double x, double y, int WhereP);
void outPoint(double x, double y);
void outCont(double a);
double distPointPoint(double x1, double y1, pair < double, double > p);
double distPointSide(pair < double, double > p1, pair < double, double > p2, double a, int i);
void coordinates(pair < double, double > p[7][3], pair < double, double > p1[8], pair < double, double > coord[8], double a, double x, double y);
double det(pair < double, double > p1, pair < double, double > p2); // Вычисление определителя
void processCont(double a);

int main()
{
    ios_base::sync_with_stdio(0);

    double x,y,dist;
    int k = 0;
    double a;

    for (int i = 1; i > 0; i++)
    {
        k = getCont(a);
        if (k == 0)
        {
            cout << "<<<CONTOUR IS ABSENT>>>" << endl << "<<<END OF WORK>>>" << endl;
            return 0;
        }
        if (a > 0)
        {
            processCont(a);
            cout << "<<<END OF WORK>>>" << endl;
            return 0;
        }
    }

    return 0;
}

int getCont(double &a)
{
    cout << "Enter parametr a: ";
    bool f = cin >> a;
    return f;
}

int getPoint(double &x, double &y)
{
    cout << "Enter coordinates of point" << endl;
    cout << "x: ";
    bool f = cin >> x;
    if (!f) return -1;
    cout << "y: ";
    f = cin >> y;
    if (!f) return -1;
}

void processCont(double a)
{
    double x1, y1, x, y;
    for (int i = 1; i > 0; i++)
    {
        int k = getPoint(x, y);
        if (k == -1)
        {
            cout << "<<<END OF POINTS>>>" << endl;
            break;
        }
        if (x1 == x && y1 == y)
        {
            cout << "<<<POINT REPEAT>>>" << endl;
            break;
        }
        else
        {
            x1 = x;
            y1 = y;
        }
        int WhP = wherePoint(x, y, a);
        double d = distPointCont(a, x, y, WhP);
        outResults(x, y, a, WhP, d);
    }
}

int wherePoint(double x, double y, double a)
{
    pair < double, double > p[7][3];
    pair < double, double > p1[8];
    pair < double, double > coord[8];

    int mark[10]; // Знак ориентированой площади

    coordinates(p, p1, coord, a, x, y);

    int sum = 0;
    bool flag = false;

    for (int i = 1; i < 7; i++)
    {
        mark[i] = determinant(p[i][1], p1[i]);
        sum += mark[i];
        if (mark[i] == 0) flag = true;
    }

    if (sum == 6) return -1;
    if (!flag) return 1;
    if (sum == 5 || sum == 4) return 0;
    else return 1;
}

void outResults(double x, double y, double a, int WhereP, double dist)
{
    outPoint(x,y);

    switch(WhereP)
    {
    case -1:
        cout << "IN_C" << endl;
        break;
    case 0:
        cout << "ON_C" << endl;
        break;
    case 1:
        cout << "OUT_C" << endl;
        break;
    default:
        cout << "<<<WRONG DATA>>>" << endl;
        break;
    }

    outCont(a);

    cout << "DISTANCE=" << dist << endl;
}


int determinant(pair < double, double > p1, pair < double, double > p2) // Определение знака определителя
{
    double product = p1.first * p2.second - p2.first * p1.second;
    if (fabs(product) < 1e-9) return 0;
    return product < 0 ? -1 : 1;
}

double det(pair < double, double > p1, pair < double, double > p2) // Вычисление определителя
{
    double product = p1.first * p2.second - p2.first * p1.second;
    return fabs(product);
}

int scalar_product(pair < double, double > p1, pair < double, double > p2)
{
    double result;
    result = p1.first * p2.first + p1.second * p2.second;
    return result >= 0 ? 1 : -1;
}

double distPointCont(double a, double x, double y, int WhereP)
{
    if (WhereP == 0) return 0;

    pair < double, double > p[7][3];
    pair < double, double > p1[8];
    pair < double, double > coord[8];

    coordinates(p, p1, coord, a, x, y);

    double dist[8];
    double dist1 = 0;

    for (int i=1; i<=6; i++)
    {

        if ((scalar_product(p1[i], p[i][1]) == 1) &&
                (scalar_product(p1[i+1], p[i][2]) == 1))
        {
            dist[i] = distPointSide(p[i][1], p1[i], a, i);
        }

        else
            dist[i] = min(distPointPoint(x, y, coord[i]), distPointPoint(x, y, coord[i+1]));

        dist1 = dist[1];
        for (int i = 2; i <= 6; i++) dist1 = min(dist1, dist[i]);
    }

    return dist1;
}

void outPoint(double x, double y)
{
    cout << "(" << x<< "; " << y << ")" << endl;
}

void outCont(double a)
{
    cout << "[" << a << "]" << endl;
}

double distPointPoint(double x1, double y1, pair < double, double > p)
{
    return sqrt( ((p.first - x1) * (p.first - x1)) + ((p.second - y1) * (p.second - y1)) );
}

double distPointSide(pair < double, double > p1, pair < double, double > p2, double a, int i)
{
    double b[3];
    b[1] = a;
    b[2] = a * sqrt(2);
    return i % 3 == 0 ? det(p1, p2) / b[2] : det(p1, p2) / b[1];
}

void coordinates(pair < double, double > p[7][3], pair < double, double > p1[8], pair < double, double > coord[8], double a, double x, double y)
{

    // координаты векторов - сторон шестиугольника (против часовой стрелки)
    p[1][1] = mp(a,0);
    p[2][1] = mp(0,a);
    p[3][1] = mp(-a,a);
    p[4][1] = mp(-a,0);
    p[5][1] = mp(0,-a);
    p[6][1] = mp(a,-a);

    // координаты векторов - сторон шестиугольника (по часовой стрелке)
    p[1][2] = mp(-a,0);
    p[2][2] = mp(0,-a);
    p[3][2] = mp(a,-a);
    p[4][2] = mp(a,0);
    p[5][2] = mp(0,a);
    p[6][2] = mp(-a,a);

    // координаты векторов от вершины шестиугольника до данной
    p1[1] = mp(x-a,y);
    p1[2] = mp(x-2*a,y);
    p1[3] = mp(x-2*a,y-a);
    p1[4] = mp(x-a,y-2*a);
    p1[5] = mp(x,y-2*a);
    p1[6] = mp(x,y-a);
    p1[7] = p1[1];

    coord[1] = mp(a,0);
    coord[2] = mp(2*a,0);
    coord[3] = mp(2*a,a);
    coord[4] = mp(a,2*a);
    coord[5] = mp(0,2*a);
    coord[6] = mp(0,a);
    coord[7] = coord[1];

}
