#include<iostream>
#include<fstream>
#include<vector>
#include<tuple>
#include<algorithm>
using namespace std;
ifstream f("in.txt");
int n;
bool visited[105];
vector<tuple<int, int, int>> muchii;
vector<int>adc[2000];
vector<pair<int, int>> puncte;
bool sortbypondere(const tuple<int, int, int>& a, const tuple<int, int, int>& b)
{
    return (get<2>(a) < get<2>(b));
}
void citire()
{
    f >> n;
    for (int i = 1; i <= n; i++)
    {
        int x, y;
        f >> x >> y;
        puncte.push_back({ x,y });
    }
    for (int i = 0; i < n - 1; i++)
        for (int j = i + 1; j < n; j++) {
            int radical = sqrt((puncte[i].first - puncte[j].first)* (puncte[i].first - puncte[j].first) + (puncte[i].second - puncte[j].second)* (puncte[i].second - puncte[j].second));
            muchii.push_back({ i, j,radical });
        }
}
void sortare_muchii()
{
    //citire graf orientat in vector de tip tuple
    citire();
    sort(muchii.begin(), muchii.end(), sortbypondere);

}

void dfskruskal(int x, int y, bool& ok)
{
    if (x == y)
        ok = true;
    if (visited[x]) return;
    visited[x] = true;
    for (auto c : adc[x])
        dfskruskal(c, y, ok);

}
void ivisited()
{
    for (int i = 0; i <= n; i++)
        visited[i] = false;
}
void kruskal()
{
    int s = 0;
    sortare_muchii();
    for (auto e : muchii)
    {
        bool ok = false;
        ivisited();
        dfskruskal(get<0>(e), get<1>(e), ok);
        if (ok == false) {
            adc[get<0>(e)].push_back(get<1>(e));
            adc[get<1>(e)].push_back(get<0>(e));
            s = s + get<2>(e);
           
        }
    }
    cout << s << '\n';
}
int main() {
    kruskal();
    return 0;
}