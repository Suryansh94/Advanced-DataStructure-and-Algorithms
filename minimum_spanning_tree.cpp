// icst and i'll ngu { you know it :) }  
// https://www.hackerearth.com/practice/algorithms/graphs/minimum-spanning-tree/practice-problems/algorithm/grid-of-many-xors-de84b766/description/
#include <bits/stdc++.h>
using namespace std;
const int N = 1234567;
const int mod = 1e9+7;
typedef long long ll;
#define mp make_pair
#define pb push_back
struct edge{
	int s,e,w;
};
int pa[N],sz[N];
int find(int n)
{
	while(n!=pa[n])
	{
		pa[n]=pa[pa[n]];
		n=pa[n];
	}
	return n;
}
int join(int a,int b)
{
	int p_a= find(a);
	int p_b =find(b);
	if(p_a==p_b)
		return 0 ;
	if(sz[p_a]<sz[p_b])
		swap(a,b);
	pa[p_b]=p_a;
	sz[p_a]+=sz[p_b];
	return 1;
}
bool func(edge & a,edge &b)
{
	return a.w<b.w;
}
int main()
{
	// ios_base:: sync_with_stdio(false); cin.tie(0);
	// freopen ("inp","r",stdin);
	// freopen ("out","w",stdout);
	int t,n,m,a,b,c,d;
	cin>>t;
	while(t--)
	{
		cin>>n>>m;
		cin>>a>>b>>c>>d;
		vector<vector<int> >G(n, vector<int>(m));
		vector<edge>E;
		map<pair<int,int>, int> C;
        int cnt = 0;
		for(int i=0;i<n;i++)
		{
			for(int j=0;j<m;j++)
			{
				cin>>G[i][j];
				C[{i,j}] = cnt++;
				if(i-1 >= 0) {
                    E.push_back({C[{i-1,j}], C[{i,j}], G[i][j]^G[i-1][j] });
                }
                if(j-1 >= 0) {
                    E.push_back({C[{i,j-1}], C[{i,j}], G[i][j]^G[i][j-1] });
                }
			}
		}
		sort(E.begin(),E.end(),func);
        for(int j=0;j<cnt;j++) {
            pa[j] = j;
            sz[j] = 1;
        }
        int ans = 0;
        for(auto e:E) {
            if(join(e.s,e.e)) ans += e.w;
        }
        cout << ans << "\n";
	}
	
	return 0;
}
