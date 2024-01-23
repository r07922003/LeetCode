class Solution {
    int res;
public:
    int longestPath(vector<int>& parent, string s) {
        /*
            node 0 = root, parent[0] = -1
        */
        int n = parent.size();
        vector<vector<int>> g(n);
        for(int node=0;node<n;node++){
            if(parent[node]==-1) continue;
            g[parent[node]].push_back(node);
        }
        return max(res,helper(g,s,0,-1));
    }
    int helper(vector<vector<int>>& g,string& s,int cur,int parent){
        int first = 0;
        int second = 0;
        for(auto& child:g[cur]){
            if(child==parent) continue;
            auto child_length = helper(g,s,child,cur);
            res = max(res,child_length);
            if(s[child]==s[cur]) continue;
            if(child_length>first){
                swap(first,second);
                first = child_length;
            }
            else if(child_length>second){
                second = child_length;
            }
        }
        res = max(res,first+second+1);
        return first+1;
    }
};