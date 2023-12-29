class Solution {
public:
    int minDifficulty(vector<int>& jobDifficulty, int d) {
        //using monotonic stack reduce time complexity from O(n*n*d) => O(n*d)
        ios_base::sync_with_stdio(false);
        cin.tie(NULL);
        cout.tie(NULL);

        int n = jobDifficulty.size();
        if(n<d) return -1;

        constexpr int X = 301;
        int *prev_dp = new int[X];
        for(int i=1;i<=n;i++) prev_dp[i] = INT_MAX/2;
        prev_dp[0] = 0;
        
        stack<int> s;
        for(int day=1;day<=d;day++){
            int *cur_dp = new int[X];
            clear_stack(s);
            for(int i=0;i<=n;i++) cur_dp[i] = INT_MAX/2;
            for(int i=day;i<=n;i++){
                cur_dp[i] = prev_dp[i-1] + jobDifficulty[i-1];
                while(!s.empty() && jobDifficulty[s.top()-1]<=jobDifficulty[i-1]){
                    int index = s.top(); s.pop();
                    int diff = jobDifficulty[i-1] - jobDifficulty[index-1];
                    cur_dp[i] = min(cur_dp[i],cur_dp[index]+diff);
                }
                if(!s.empty()) cur_dp[i] = min(cur_dp[i],cur_dp[s.top()]);
                s.push(i);
            }
            prev_dp = cur_dp;
            //for(int i=0;i<=n;i++) printf("%d,",prev_dp[i]);
            //printf("\n");
        }
        return prev_dp[n];
    }
    void clear_stack(stack<int>& s){
        while(!s.empty()) s.pop();
    }
};