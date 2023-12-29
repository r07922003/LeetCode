class Solution {
public:
    int minDifficulty(vector<int>& jobDifficulty, int d) {
        ios_base::sync_with_stdio(false);
        cin.tie(NULL);
        cout.tie(NULL);
        /*
        The difficulty of a job schedule = sum(difficulties of each day of d days)
        */
        int n = jobDifficulty.size();
        if(n<d) return -1;
        /*
        let dp[i][d] = min_sum_of_diff with jobDifficulty[0:i] in d days
        dp[i][d]: dp[j-1][d-1] + max(jobDifficulty[j:i])
                : dp[0][d-1] + max(jobDifficulty[1:i]);
                : dp[1][d-1] + max(jobDifficulty[2:i]);
                ...
                : dp[i][d-1] + max(jobDifficulty[i:i]);
        [6 5 4 3 2 1] d=3
        d=0 0 6 5 4 3 2 1
        d=1 & 6 6 6 6 6 6
        d=2 & 6 11 10 
        */

        //vector<vector<int>> dp(n+1,vector<int>(d+1,INT_MAX/2));
        constexpr int X = 301;
        constexpr int Y = 11;
        int dp[X][Y];
        for(int i=0;i<X;i++){
            for(int j=0;j<Y;j++){
                dp[i][j] = INT_MAX/2;
            }
        }
        dp[0][0] = 0;
        for(int day=1;day<=d;day++){
            for(int i=1;i<=n;i++){
                int job_diff = jobDifficulty[i-1];
                for(int j=i;j>=1;j--){
                    job_diff = max(job_diff,jobDifficulty[j-1]);
                    dp[i][day] = min(dp[i][day],dp[j-1][day-1]+job_diff);
                }
            }
        }
        return dp[n][d];
    }
};