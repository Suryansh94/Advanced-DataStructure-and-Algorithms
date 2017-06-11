/*
You are given a tree with NN nodes. Answer QQ queries of the type:
Given three distinct nodes AA, BB, and CC, find the node DD such that the sum of distances from DD to AA, BB and CC is minimum.
*/
#include <bits/stdc++.h>
using namespace std;
const int N = 1234567;
const int LGN = 18;
const int mod = 1e9+7;
typedef long long ll;
#define mp make_pair
#define pb push_back
int depth[N];
int P[N][LGN];
vector<int>g[N];

void dfs(int n,int p,int d)
{
	depth[n]=d;
	P[n][0]=p;
	for(int next : g[n])
	{
		if(next!=p)
			dfs(next,n,d+1);
	}
}

void init(int n)
{
	for(int j=1;j<LGN;j++)
	{
		for(int i=1;i<=n;i++)
		{
			if(P[i][j-1]!=-1)
				P[i][j]=P[P[i][j-1]][j-1];
		}
	}
}
int lca(int a,int b)
{
	if(depth[a]<depth[b])
		swap(a,b);
	for(int i=LGN-1;i>=0;i--)
	{
		if(depth[a]- (1<<i) >=depth[b])
			a=P[a][i];
	}

	if(a==b)
		return a;
	for(int i=LGN-1;i>=0;i--)
	{
		if(P[a][i]!=-1 and P[a][i]!=P[b][i])
		{
			b=P[b][i];
			a=P[a][i];
		} 
	}
	return P[a][0];
}
int dist(int x, int y) {
  return depth[x] + depth[y] - 2 * depth[lca(x,y)];
}
int main()
{
	ios_base:: sync_with_stdio(false); cin.tie(0);
	// freopen ("inp","r",stdin);
	// freopen ("out","w",stdout);
	int n,q,a,b,c;
	cin>>n>>q;
	for(int i=0;i<n-1;i++)
	{
		cin>>a>>b;
		g[a].pb(b);
		g[b].pb(a);
	}

	depth[0]=-1;
	dfs(1,-1,0);		
	init(n);
	while(q--)
	{
		cin>>a>>b>>c;
		int ans = lca(a,b);
		int l = lca(b,c);
		if(depth[l]>depth[ans])
			ans=l;
		l = lca(a,c);
		if(depth[l]>depth[ans])
			ans=l;
		cout<<ans<<" "<<dist(a,ans)+dist(b,ans)+dist(c,ans)<<endl;
	}	
	return 0;
}
