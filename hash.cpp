#include <bits/stdc++.h>
using namespace std;
const float load_factor = 0.75;
int total_entries=0,buckets=2;
int mod_value(int n)
{
    return pow(2,ceil(log2(n)));
}
float calculate_load_factor(int total_entries,int buckets)
{
    return (total_entries)/(buckets*2.0);
}
int to_integer(string s)
{
    stringstream ss(s);
    int res;
    ss>>res;
    return res;
}
vector<set<int> > Hash;
int main(int argc,char *argv[])
{
    freopen(argv[1],"r",stdin);
    freopen("out.txt","w",stdout);
    Hash.push_back(set<int>());
    Hash.push_back(set<int>());
    int split_pointer=0,split_loop=2;
    string input;
    while(getline(cin,input))
    {
        int value = to_integer(input);
        // cout<<"value is "<<value<<endl;
        int mod = mod_value(buckets);
        // cout<<"mod is "<<mod<<endl;
        int index = value%mod;
        // cout<<"index is "<<index<<endl;
        while(index>=Hash.size())
        {
            index>>=1;
        }
        if(Hash[index].find(value)==Hash[index].end())
        {
            Hash[index].insert(value);
            total_entries++;
        }
        float lf = calculate_load_factor(total_entries,buckets);
        // cout<<"load factor is "<<lf <<endl;
        if(lf>load_factor)
        {
            // cout<<"Rehahisng\n";
            // increase the bucket size and reHash the split index_pointer
            Hash.push_back(set<int>());
            buckets++;
            vector<int>entries_to_reHash;
            for(auto i : Hash[split_pointer])
            {
                entries_to_reHash.push_back(i);
                Hash[split_pointer].erase(i);
            }
            for(int i=0;i<entries_to_reHash.size();i++)
            {
                int updated_mod =  mod_value(buckets);
                int updated_index = entries_to_reHash[i]%updated_mod;
                // cout<<"updated_index =? "<<updated_index<<" "<<entries_to_reHash[i]<<endl;
                while(Hash.size()<updated_index)
                {
                    updated_index>>=1;
                }
                Hash[updated_index].insert(entries_to_reHash[i]);
            }
            split_pointer++;
            if(split_pointer==split_loop)
            {
                split_pointer=0;
                split_loop*=2;
            }
            // after reHashing check split index
        }
    }
    for(int i=0;i<buckets;i++)
    {
        cout<<"Bucket "<<i<<" contains "<<endl;
        if(Hash[i].size())
        {
            for(auto it : Hash[i])
            {
                cout<<it<<" ";
            }
            cout<<endl;
        }
    }
}
