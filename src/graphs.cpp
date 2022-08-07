#include<iostream>
#include<fstream>
#include<string>
using namespace std;

int min(int a, int b) {
    if (a < b) {
        return a;
    }
    return b;
}
int lev_dist(string& s1, string& s2)
{
    int l1 = s1.size(), l2 = s2.size();
    int dist[l1 + 1][l2 + 1];
    dist[0][0] = 0;

    for (int i = 1; i <= l1; ++i) {
        dist[i][0] = i;
    }
    for (int i = 1; i <= l2; ++i) {
        dist[0][i] = i;
    }

    int num;
    for (int i = 1; i <= l1; ++i)
        for (int j = 1; j <= l2; ++j) {
            if (s1[i - 1] == s2[j - 1]) num = 0;
            else num = 1;
            dist[i][j] = min(min(dist[i - 1][j] + 1, dist[i][j - 1] + 1), dist[i - 1][j - 1] + num);
        }
    return dist[l1][l2];
}
int main() {
    cout << lvAlgo("hello hi", 8, "hello hi", 8);
}