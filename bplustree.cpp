// CLRS B Tree Code Extension to B+ tree
#include<bits/stdc++.h>
using namespace std;
int min_degree,M,B;
#define MAX_KEYS 2*min_degree-1
struct  node
{
    vector<int>keys;
    vector<node*>child;
    int n;
    int min_degree;      // Minimum degree (defines the range for number of keys)
    bool leaf;
    node * link ; // for making links between leaf nodes
    node(int degree, bool is_leaf)
    {
        min_degree = degree;
        leaf = is_leaf;
        keys.resize(MAX_KEYS);
        child.resize(2*min_degree);
        n = 0;
    }
    void insert_non_full(int k);
    // split the full child y
    void split_child(int i, node *y);
};

node *root=NULL;


void node::insert_non_full(int k)
{
    int i = n-1;
    if (leaf)
    {
        // leaf node
        while (i >= 0 && keys[i] > k)
        {
            keys[i+1] = keys[i];
            i--;
        }
        keys[i+1] = k;
        n = n+1;
    }
    else
    {
        // Find the child which is going to have the new key
        while (i >= 0 && keys[i] > k)
            i--;
        if (child[i+1]->n == MAX_KEYS)
        {
            split_child(i+1, child[i+1]);
            if (keys[i+1] < k)
                i++;
        }
        child[i+1]->insert_non_full(k);
    }
}
// y is full , hence splitting
void node::split_child(int i, node *y)
{
    // z stores right min_degree-1 of y
    node *z = new node(y->min_degree, y->leaf);
    z->n = min_degree - 1;
    for (int j = 0; j < min_degree-1; j++)
        z->keys[j] = y->keys[j+min_degree];
    if (y->leaf == false)
    {
        // children of y must be copied if not leaf
        for (int j = 0; j < min_degree; j++)
            z->child[j] = y->child[j+min_degree];
    }

    // FOR B+ case it is min_degree not min_degree-1 since leaves stores record
    y->n = min_degree ;

    // Since this node is going to have a new child,
    // create space of new child
    for (int j = n; j >= i+1; j--)
        child[j+1] = child[j];
    child[i+1] = z;
    for (int j = n-1; j >= i; j--)
        keys[j+1] = keys[j];
    keys[i] = y->keys[min_degree-1];

    n = n + 1;

    // create and update link
    if(y->leaf and z->leaf)
    {
        z->link=y->link;
        y->link=z;
    }

}

void insert(int key)
{
    if (!root)
    {
        root = new node(min_degree, true);
        root->link=NULL;
        root->keys[0] = key;
        root->n = 1;
    }
    else
    {
        if (root->n == MAX_KEYS)
        {
            node *temp_root = new node(min_degree, false);
            temp_root->child[0] = root;
            temp_root->split_child(0, root);
            int i = 0;
            if (temp_root->keys[0] < key)
                i++;
            temp_root->child[i]->insert_non_full(key);
            root = temp_root;
        }
        else
            root->insert_non_full(key);
    }
}

node* Find(node * root , int k)
{
    if (!root) return root;
    int i = 0;
    while (i < root->n && k > root->keys[i])
        i++;
    return root->keys[i]==k?root:(root->leaf==true?NULL:Find(root->child[i],k));
}

node* get_left_most_leaf(node * root)
{
    while(!root->leaf)
    {
        return get_left_most_leaf(root->child[0]);
    }
    return root;
}
int Count(node * root , int k)
{
    int ans=0;
    node * left = get_left_most_leaf(root);
    while(1)
    {
        for(int i=0;i<left->n;i++)
        {
            if(left->keys[i]==k)
                ans++;
        }
        if(left->link==NULL)
        {
            break;
        }
        left=left->link;
    }
    return ans;
}

int Range(node * root , int l,int r)
{
    int ans=0;
    node * left = get_left_most_leaf(root);
    while(1)
    {
        for(int i=0;i<left->n;i++)
        {
            if(left->keys[i]<=r and left->keys[i]>=l)
                ans++;
        }
        if(left->link==NULL)
        {
            break;
        }
        left=left->link;
    }
    return ans;
}

int to_integer(string s)
{
    stringstream ss(s);
    int res;
    ss>>res;
    return res;
}
vector<string> split(const string &s, char delim) {
    stringstream ss(s);
    string item;
    vector<string> tokens;
    while (getline(ss, item, delim)) {
        tokens.push_back(item);
    }
    return tokens;
}
int main(int argc,char *argv[])
{

    freopen(argv[1],"r",stdin);
    freopen("out.txt","w",stdout);
   string s;
   stringstream ss;
   vector<string>tokens;
   if(argc<3)
   {
       cout<<"Error\n";
       return 0;
   }
   M=to_integer(argv[2]);
   B=to_integer(argv[3]);
   // cout<<M<<" "<<B<<endl;
   min_degree=floor((B+4)/24);
   // cout<<"MD "<<min_degree<<endl;
   while(getline(cin,s))
   {
       tokens=split(s,' ');
       if(tokens[0]=="INSERT") // O(logn)
       {
           int val = to_integer(tokens[1]);
           insert(val);
       }
       else if(tokens[0]=="FIND") //  O(logn)
       {
           int key = to_integer(tokens[1]);
           Find(root,key)==NULL?cout<<"NO\n":cout<<"YES\n";
       }
       else if(tokens[0]=="COUNT") // O(n)
       {
           int val = to_integer(tokens[1]);
           cout<<Count(root,val)<<endl;
       }
       else if(tokens[0]=="RANGE") // O(n
       {
           int l = to_integer(tokens[1]),r=to_integer(tokens[2]);
           cout<<Range(root,l,r)<<endl;
       }
   }
}
