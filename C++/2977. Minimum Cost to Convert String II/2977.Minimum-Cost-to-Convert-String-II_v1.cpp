class Solution {
public:
    long long minimumCost(string source, string target, vector<string>& original, vector<string>& changed, vector<int>& cost) {
        /*
            1. Using hash to save edge
            2. Floyd-Warshall
            3. DP top-down algo (will TLE)
        */
        unordered_set<string> SET;
        SET.insert(original.begin(),original.end());
        SET.insert(changed.begin(),changed.end());
        unordered_map<string,int> string_to_id;
        for(auto& word:SET) string_to_id[word] = string_to_id.size();
        
        int n = string_to_id.size();
        int adj[n][n];
        for(int i=0;i<n;i++){
            for(int j=0;j<n;j++) adj[i][j] = INT_MAX;
            adj[i][i] = 0;
        }
        for(int i=0;i<original.size();i++){
            int x = string_to_id[original[i]];
            int y = string_to_id[changed[i]];
            adj[x][y] = min(adj[x][y],cost[i]);
        }
        for(int k=0;k<n;k++){
            for(int i=0;i<n;i++){
                for(int j=0;j<n;j++){
                    if(adj[i][k]>=INT_MAX-adj[k][j]) continue;
                    adj[i][j] = min(adj[i][j],adj[i][k]+adj[k][j]);
                }
            }
        }
        /*
            let dp[i]: the minumum cost to convert s[0:i] to t[0:i]
            source: x x x x x [x x x x]
                               j     i
            target: x x x x x [x x x x]
            dp[i] = dp[j-1] + adj[cost(source[j:i]->target[j:i])]
        */
        int len = source.size();
        long long dp[len+1];
        dp[0] = 0ll;
        for(int i=1;i<=len;i++){
            dp[i] = INT_MAX;
            for(int j=1;j<=i;j++){
                string s = source.substr(j-1,i-j+1);
                string t = target.substr(j-1,i-j+1);
                if(string_to_id.find(s)==string_to_id.end()) continue;
                if(string_to_id.find(t)==string_to_id.end()) continue;
                if(adj[string_to_id[s]][string_to_id[t]]==INT_MAX) continue;
                dp[i] = min(dp[i],dp[j-1]+adj[string_to_id[s]][string_to_id[t]]); 
            }
            if(source[i-1]==target[i-1]) dp[i] = min(dp[i],dp[i-1]);
        }
        return dp[len]==INT_MAX ?-1 :dp[len];
    }
};