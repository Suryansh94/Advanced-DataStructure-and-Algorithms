// http://www.spoj.com/problems/GSS1/
// auther : geeky_coder 
// date : 2015-03-08 12:42:56
#include<bits/stdc++.h>
using namespace std;
struct node
{
	long long int segmentSum,bestPrefix,bestSuffix,bestSum;
	node split(node& l, node& r){}
	node(int a)
	{
        bestSum=segmentSum=bestPrefix=bestSuffix=a;
	}
	node()
    {
        bestSum=segmentSum=bestPrefix=bestSuffix=INT_MIN;
    }
	node merge(node& l, node& r)
	{
		segmentSum = l.segmentSum + r.segmentSum;
		bestPrefix = max( l.segmentSum + r.bestPrefix , l.bestPrefix );
		bestSuffix = max( r.segmentSum + l.bestSuffix , r.bestSuffix );
		bestSum    = max( max( l.bestSum , r.bestSum) , l.bestSuffix + r.bestPrefix );
	}
};
void update(node tree[],int pos)
{
    pos>>=1;
    while(pos)
    {
        tree[pos].merge(tree[pos*2],tree[pos*2 + 1]);
        pos>>=1;
    }
}
node range_query(node tree[],int root,int left_most,int right_most,int u,int v)
{
    if(u<=left_most && v>=right_most)
        return tree[root];
    else
    {
        long int mid=(left_most+right_most)/2,left_child=root*2,right_child=left_child+1;
        // use split() if updation
        node l,r;
        if(mid>u)
            l=range_query(tree,left_child,left_most,mid,u,v);
        if(mid<v)
            r=range_query(tree,right_child,mid,right_most,u,v);
        node ans;
        ans.merge(l,r);
        return ans;
    }
}
int main()
{
    //ios::sync_with_stdio(false);
    int q,r1,r2,m;
    scanf("%d",&m);
    long int a[m];
    long int n=ceil(log2(m));
    long int pos=(1<<n);
    node tree[1<<(n+1)];
    for(int i=0;i<m;i++)
    {
        scanf("%d",a+i);
        tree[pos+i]=node(a[i]);
        update(tree,pos+i);
    }
    cin>>q;
    while(q--)
    {
        scanf("%d %d",&r1,&r2);
        node ans=range_query(tree,1,1<<n,1<<(n+1),pos+r1-1,pos+r2); // indexing 1
        printf("%lld\n",ans.bestSum);
    }
}