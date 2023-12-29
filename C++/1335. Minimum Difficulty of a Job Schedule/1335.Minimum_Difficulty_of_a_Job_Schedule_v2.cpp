class Solution {
public:
    int minDifficulty(vector<int>& jobDifficulty, int d) {
        /*
            using scrolling array to improve sapce from O(n*d) => O(n);
        */
        ios_base::sync_with_stdio(false);
        cin.tie(NULL);
        cout.tie(NULL);

        int n = jobDifficulty.size();
        if(n<d) return -1;

        constexpr int X = 301;
        int *prev_dp = new int[X];
        for(int i=1;i<n;i++) prev_dp[i] = INT_MAX/2;
        prev_dp[0] = 0;

        for(int day=1;day<=d;day++){
            int *cur_dp = new int[X];
            for(int i=0;i<=n;i++) cur_dp[i] = INT_MAX/2;
            for(int i=1;i<=n;i++){
                int job_diff = jobDifficulty[i-1];
                for(int j=i;j>=1;j--){
                    job_diff = max(job_diff,jobDifficulty[j-1]);
                    cur_dp[i] = min(cur_dp[i],prev_dp[j-1]+job_diff);
                }
            }
            prev_dp = cur_dp;
        }
        return prev_dp[n];
    }
};