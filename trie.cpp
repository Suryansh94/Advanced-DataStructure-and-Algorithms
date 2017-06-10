/*You are given a list of NN words. Find a subset of KK words such that:

There are no two strings in the subset such that one of them is a prefix of the other one.
The length of longest word is minimum.
*/

// Method 1 : Trie
#include <bits/stdc++.h>
using namespace std;
const int N = 1234567;
const int mod = 1e9+7;
typedef long long ll;
#define mp make_pair
#define pb push_back

int trie[N][26];
int counter = 0;
int e[N];
void _insert(string s)
{
  int l = s.length();
  int node =0;
  for(int i=0;i<l;i++)
  {
    int char_val = s[i]-'a';
    if(!trie[node][char_val])
      trie[node][char_val]=counter++;
    node=trie[node][char_val];
  }
  e[node]=true;
}

void reset(int n)
{
  for(int i=0;i<26;i++)
  {
    if(trie[n][i])
    {
      reset(trie[n][i]);
      trie[n][i]=0;
    }
  }
}

int dfs(int n)
{
  int res=0;
  for(int i=0;i<26;i++)
  {
    if(trie[n][i])
      res+=dfs(trie[n][i]);
  }
  if(e[n])
    res=max(res,1);
  return res;
}
int main()
{
  ios_base:: sync_with_stdio(false); cin.tie(0);
  // freopen ("inp","r",stdin);
  // freopen ("out","w",stdout);

  int n,k;
  cin>>n>>k;
  string s;
  vector<string>v(n);
  int mx = -1;
  for(int i=0;i<n;i++)
  {
    cin>>v[i];
    mx=max(mx,(int)v[i].size());
  }
  int low = 0 , high= mx,ans=-1;
  while(low<=high)
  {
    int mid  = (high-low)/2+low;
    for(int i=0;i<n;i++)
    {
      if((int)v[i].size()<=mid)
        _insert(v[i]);
    }
    int val = dfs(0);
    reset(0);
    if(val>=k)
    {
      ans=mid;
      high=mid-1;
    }
    else
      low=mid+1;
  }
  cout<<ans<<endl;
  return 0;
}



/***************************************************************************/
// Method 2 : hashing
#include <bits/stdc++.h>
using namespace std;
const int N = 1234567;
const int mod = 1e9+7;
typedef long long ll;
#define mp make_pair
#define pb push_back
const int base = 31;
bool cmp(string &a,string &b)
{
	return a.size()<b.size();
}
int main()
{
	// ios_base:: sync_with_stdio(false); cin.tie(0);
	// freopen ("inp","r",stdin);
	// freopen ("out","w",stdout);

	int n,k;
	cin>>n>>k;
	vector<string>v(n);
	for(int i=0;i<n;i++)
	{
		cin>>v[i];
	}	
	sort(v.begin(), v.end(),cmp);
	
	set<int>hash;
	for(int i=0;i<n;i++)
	{
		int hash_value=0;
		for(char c : v[i])
		{
			int d = c-'0';
			hash_value = (hash_value*base + d )%mod;

			if(hash.find(hash_value) != hash.end())
			{
				hash.erase(hash.find(hash_value));
			}
		}

		hash.insert(hash_value);
		if(hash.size()==k)
		{
			cout<<v[i].size()<<endl;
			// cout<<v[i]<<endl;
			return 0;
		}
			
	}
	cout<<-1<<endl;

	return 0;
}
