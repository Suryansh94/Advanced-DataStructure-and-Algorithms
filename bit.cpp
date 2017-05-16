

// Binary indexed tree
		
// Suryansh Agnihotri :)    


#include<cstdio>
#include<iostream>
#include<stack>
#include<queue>
#include<vector>
#include<algorithm>
#include<climits>
#include<cmath>
#include<string>
#include<map>
#define INF 10000000
#define pi 3.1415926536
using namespace std;
int arr[1000000],bit[10000000];
int n,q,a,b;
void update(int ind,int val)
{
	for(int i=ind;i<n+1;)
	{
		bit[i]+=val;
		i+=(i&(-i)); // get 2's complement , and with original and then add  (getting next)
	}
}

int getSum(int x)
{
	int val=0;
	while(x)
	{
		val+=bit[x];
		x-=(x&(-x));  //getting parent
	}
	return val;
}

int main()
{
	
	cin>>n;
	for(int i=0;i<n;i++)
	{
		cin>>arr[i];
	}

	// create the BIT ,Size of BIT = n+1 , 0 is dummy node
	for(int i=1;i<=n;i++)
	{
		update(i,arr[i-1]);
	}

	cout<<"Enter number of queries\n";
	cin>>q;
	while(q--)
	{
		cout<<"Get sum between\n";
		cin>>a>>b;
		cout<<getSum(b+1)-getSum(a+1)<<endl;
	}

}

