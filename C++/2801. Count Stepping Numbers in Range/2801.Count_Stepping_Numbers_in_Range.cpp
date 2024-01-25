class Solution {
    int mod = 1e9+7;
    int dp[101][11][2];
public:
    int countSteppingNumbers(string low, string high) {
        int low_is_valid = 1;
        for(int i=1;i<low.size();i++){
            if(abs(low[i-1]-low[i])==1) continue;
            else{
                low_is_valid = 0;
                break;
            }
        }
        memset(dp,-1,sizeof(dp));
        int h = helper(high,0,-1,true);
        memset(dp,-1,sizeof(dp));
        int l = helper(low,0,-1,true);
        return ((h - l + low_is_valid)%mod+mod) % mod;
    }
    int helper(string& num,int cur,int prev,bool match){
        if(cur>=num.size()) return prev==-1 ?0 :1;
        if(dp[cur][prev+1][(match ?1:0)]!=-1) return dp[cur][prev+1][(match ?1:0)];
        int cur_num = num[cur]-'0';
        int res = 0;
        if(match){
            if(prev==-1){
                res = (res + helper(num,cur+1,prev,false)) % mod;
                for(int i=1;i<cur_num;i++){
                    res = (res + helper(num,cur+1,i,false)) % mod;
                }
                res = (res + helper(num,cur+1,cur_num,true)) % mod;
            }
            else{
                int lower = prev - 1;
                int higher = prev + 1;
                if(lower>=0 && lower<=cur_num){
                    if(lower<cur_num) res = (res + helper(num,cur+1,lower,false)) % mod;
                    else if(lower==cur_num) res = (res + helper(num,cur+1,lower,true)) % mod;
                }

                if(higher>=0 && higher<=cur_num){
                    if(higher<cur_num) res = (res + helper(num,cur+1,higher,false)) % mod;
                    else if(higher==cur_num) res = (res + helper(num,cur+1,higher,true)) % mod;
                }
            }
        }
        else{
            if(prev==-1){
                res = (res + helper(num,cur+1,prev,false)) % mod;
                for(int i=1;i<=9;i++) res = (res + helper(num,cur+1,i,false)) % mod;
            }
            else{
                int lower = prev - 1;
                int higher = prev + 1;
                if(lower>=0 && lower<=9) res = (res + helper(num,cur+1,lower,false)) % mod;
                if(higher>=0 && higher<=9) res = (res + helper(num,cur+1,higher,false)) % mod;
            }
        }
        return dp[cur][prev+1][(match ?1:0)] = res;
    }
};