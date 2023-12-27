class Solution {
public:
    int minCost(string colors, vector<int>& neededTime) {
        ios_base::sync_with_stdio(false);
        cin.tie(NULL);
        cout.tie(NULL);
        int n = neededTime.size();
        int i=0;
        int res = 0;
        while(i<n){
            auto& color = colors[i];
            int sum = 0;
            int MAX = INT_MIN;
            while(i<n && colors[i]==color){
                sum += neededTime[i];
                MAX = max(MAX,neededTime[i]);
                i++;
            }
            res += sum-MAX;
        }
        return res;
    }
};