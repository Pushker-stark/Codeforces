# Useful Extra Edges

https://www.interviewbit.com/problems/useful-extra-edges/

Asked In:
CUREFIT,DIRECTI & JUSPAY

Problem Description:

Given a graph of A nodes. Also given the weighted edges in the form of array B.

You are also given starting point C and destination point D.

Also given are some extra edges in the form of vector E.

You need to find the length of the shortest path from C to D if you can use maximum one road from the given roads in E.

All roads are one way ie they go from B[i][0] to B[i][1].



Problem Constraints
1 <= A <= 100000

1 <= |B| <= 100000

1 <= C, D <= A

1 <= |E| <= 300

All lengths of the roads lie between 1 and 1000.



Input Format
First argument is the integer A.

Second argument is the vector of vectors B.

Third argument is the integer C.

Fourth argument is the integer D.

Fifth argument is the vector of vectors E.



Output Format
Return -1 if C is not reachable from D. Else return the shortest distance between them.



Example Input
Input 1:

 A = 3
B = [   [1, 2, 1]
        [2, 3, 2]
    ]
C = 1
D = 3
E = [   [1, 3, 2]
    ]
    
    
Input 2:

 A = 4
B = [   [1, 2, 1]
        [2, 3, 2]
        [3, 1, 4]
    ]
C = 1
D = 4
E = [   [1, 3, 2]
    ]


Example Output

Output 1:

 2
Output 2:

 -1


Example Explanation
Explanation 1:

 Use the direct edge from 1 to 3. It has shortest path from 1 to 3.
Explanation 2:

 4 cannot be reached from 1.
   
   
   
## Hint 1
   
You need to get shortest paths using any one of
the auxillary roads. Can you use dijkstra from C and D
to get some relation with the same?
   
## Solution Approach
   
Use dijkstra 2 times. Once with C as origin and another
with D as origin. Now for every node, you have the length of the shortest path from
C and from D. Now you can just iterate over each road and check if this road
helps you decreasing the existing distance between C and D.
whenever you get a better answer, you can update your answer to this
value and keep iterating on the auxillary roads.
  
  
  
## Complete Solution
  
### Editorial
  
```cpp
int dijkstra(vector<vector<pair<int,int>>> &adj,int src, int dest){
    int n = adj.size();
    vector<int> cost(n+1, INT_MAX);//cost to reach upto each node from src
    cost[src] = 0;
    
    vector<int> vis(n+1, false);
    
    priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq;//min heap
    pq.push({0, src});
    
    while(pq.size()){
        auto curr = pq.top();pq.pop();
        
        int u = curr.second;
        int parentCost = curr.first;
        if(u == dest){return parentCost;}
        
        if(vis[u]){continue;}
        vis[u] = true;
        
        for(auto &child : adj[u]){
            int v = child.second;
            int childCost = child.first;
//cost to reach src->v node is not less than parent and child cost then update and push in queue
            if(cost[v] > parentCost + childCost){
                cost[v] = parentCost + childCost;
                pq.push({cost[v], v});
            }
        }
    }
    
    return INT_MAX;
}

int Solution::solve(int n, vector<vector<int> > &ed, int src, int dest, vector<vector<int> > &extra) {
    vector<vector<pair<int, int>>> adj(n+2);//adjacency list to store edges

    for(auto &x : ed)//given edges it is directed
    {adj[x[0]].push_back({x[2], x[1]});}
    
    int ans = INT_MAX;//minimizing ans

    //try all extra edges to get min distance by calling dijkstra 2 times
    for(int i=0;i<extra.size();i++)
    {
        //using ith extra edge for direction src to dest 
        adj[extra[i][0]].push_back({ extra[i][2], extra[i][1] });//inseting edge
        ans = min(ans, dijkstra(adj, src, dest));//using ith extra edge we call dijkstra to get min distance and updating it
        adj[extra[i][0]].pop_back();//removing edge

        //using ith extra edge for direction dest to src 
        adj[extra[i][1]].push_back({ extra[i][2], extra[i][0] });//inserting edges
        ans = min(ans, dijkstra(adj, src, dest));//using ith extra edge we call dijkstra to get min distance and updating it
        adj[extra[i][1]].pop_back();//removing edge
    }
    
    return ans == INT_MAX? -1 : ans;
}

```
  
  
 ## fastest
 ```cpp 
 int Solution::solve(int n, vector<vector<int> > &a, int c, int d, vector<vector<int> > &e) {
  int m=1+max(n,300);
   vector<pair<int,int>> v[m];
   if(n==90000)
    return 4740440;
   for(int i=0;i<a.size();i++)
   {
       v[a[i][0]].push_back({a[i][1],a[i][2]});
       //v[a[i][1]].push_back({a[i][0],a[i][2]});
   }
   vector<pair<int,int>> vec[m];
   for(int i=0;i<e.size();i++)
   {
       vec[e[i][0]].push_back({e[i][1],e[i][2]});
       vec[e[i][1]].push_back({e[i][0],e[i][2]});
   }
   int ans=INT_MAX;
   priority_queue<pair<int,pair<int,bool>>,vector<pair<int,pair<int,bool>>>,greater<pair<int,pair<int,bool>>>> q;
   q.push({0,{c,true}});
   vector<bool> vis(n+1,false);
   while(!q.empty())
   {
     pair<int,pair<int,bool>> t=q.top();
     int cost=t.first;
     int src=t.second.first;
     //cout << src <<" ";
     int flag=t.second.second;
     q.pop();
     if(src==d)
     {
       ans=cost;
       break;
     }
     if(vis[src])
     continue;
     vis[src]=true;
     for(int i=0;i<v[src].size();i++)
     {
        q.push({cost+v[src][i].second,{v[src][i].first,flag}});
     }
     if(flag)
     {
       for(int i=0;i<vec[src].size();i++)
       {
        q.push({cost+vec[src][i].second,{vec[src][i].first,false}});
       }
     }
    }
    while(!q.empty())
    {
      q.pop();
    }
    q.push({0,{d,true}});
   vector<bool> viss(n+1,false);
   while(!q.empty())
   {
     pair<int,pair<int,bool>> t=q.top();
     int cost=t.first;
     int src=t.second.first;
     //cout << src <<" ";
     int flag=t.second.second;
     q.pop();
     if(src==c)
     {
       ans=min(ans,cost);
       break;
     }
     if(viss[src])
     continue;
     viss[src]=true;
     for(int i=0;i<v[src].size();i++)
     {
        q.push({cost+v[src][i].second,{v[src][i].first,flag}});
     }
     if(flag)
     {
       for(int i=0;i<vec[src].size();i++)
       {
        q.push({cost+vec[src][i].second,{vec[src][i].first,false}});
       }
     }
    }
    if(ans!=INT_MAX)
    return ans;
   return -1;

}
```
## Mine
```cpp
int dijkstra(int n,vector<vector<pair<int,int>>> &adj,int src, int dest){
    vector<int> cost(n+1, INT_MAX);//cost to reach upto each node from src
    cost[src] = 0;
    
    vector<int> vis(n+1, false);
    
    priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq;//min heap
    pq.push({0, src});
    
    while(pq.size()){
        auto curr = pq.top();pq.pop();
        
        int u = curr.second;
        int parentCost = curr.first;
        if(u == dest){return parentCost;}
        
        if(vis[u]){continue;}
        vis[u] = true;
        
        for(auto &child : adj[u]){
            int v = child.second;
            int childCost = child.first;
    //cost to reach src->v node is not less than parent and child cost then update and push in queue
            if(cost[v] > parentCost + childCost){
                cost[v] = parentCost + childCost;
                pq.push({cost[v], v});
            }
        }
    }
    
    return INT_MAX;
}

int Solution::solve(int n, vector<vector<int> > &ed, int src, int dest, vector<vector<int> > &extra) {
    vector<vector<pair<int, int>>> adj(n+1);//adjacency list to store edges

    for(auto &x : ed)//given edges it is directed
    {adj[x[0]].push_back({x[2], x[1]});}
    
    int ans = INT_MAX;//minimizing ans

    //try all extra edges as bidirectional edge to get min distance by calling dijkstra 
    for(auto &x:extra)
    {
        if(x[0]>n||x[1]>n){continue;}//if extra nodes present in extra edges dont add those edges
        
        adj[x[0]].push_back({ x[2], x[1]});//using each extra edge for in forward direction
        adj[x[1]].push_back({ x[2],x[0]});//using each extra edge in reversed direction
        
        //using extra edge as bidirectional we call dijkstra to get min distance and updating it
        ans = min(ans, dijkstra(n,adj, src, dest));
        
        adj[x[0]].pop_back();//removing forward edge
        adj[x[1]].pop_back();//removing backward edge
    }
    
    return ans == INT_MAX? -1 : ans;
}

```

  
  
  
  
  
