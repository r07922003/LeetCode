class Solution {
int adjacent[26][26];
public:
    long long minimumCost(string source, string target, vector<char>& original, vector<char>& changed, vector<int>& cost) {
        for(int i=0;i<26;i++){
            for(int j=0;j<26;j++){
                adjacent[i][j] = INT_MAX;
            }
            adjacent[i][i] = 0;
        }
        for(int i=0;i<original.size();i++){
            int x = original[i]-'a';
            int y = changed[i]-'a';
            adjacent[x][y] = min(adjacent[x][y],cost[i]);
        }
        
        for(int k=0;k<26;k++){
            for(int i=0;i<26;i++){
                for(int j=0;j<26;j++){
                    if(adjacent[i][k]>=INT_MAX-adjacent[k][j]) continue;
                    adjacent[i][j] = min(adjacent[i][j],adjacent[i][k] + adjacent[k][j]);
                }
            }
        }
        
        long long res = 0;
        int n = source.size();
        for(int i=0;i<n;i++){
            int x = source[i]-'a';
            int y = target[i]-'a';
            if(x==y) continue;
            if(adjacent[x][y]==INT_MAX) return -1;
            res += adjacent[x][y];
        }
        return res;
    }
};