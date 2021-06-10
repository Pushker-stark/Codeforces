 
# Codeforces Beta Round #72 (Div. 1 Only)

# A. Magical Array
// time limit per test2 seconds
// memory limit per test256 megabytes
// inputstandard input
// outputstandard output


#include<iostream>
#include<vector>
#include<algorithm>
using namespace std;
int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);cin.tie(NULL);
    long long int n;long long int b;
    {
        cin>>n;vector<long long int> a(n);b=0;
        for (long long int i = 0; i < n; i++){cin>>a[i];}
        b=a[0];long long int c=0;
        vector<long long int> v;
        for(long long int i=1;i<n;i++)
        {
            if(a[i]==b)
            {
                c++;
                if((i+1)==n)
                {v.push_back(c+1);}
                else if(a[i+1]!=b)
                {v.push_back(c+1);}
            }
            else
            {b=a[i];c=0;}
        }
        c=0;
        for(int i=0;i<v.size();i++)
        {
            b=v[i];c+=(b*(b-1))/2;
        }
        cout<<c+n<<"\n";        
    }
}
