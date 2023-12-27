class Solution {
public:
    long long incremovableSubarrayCount(vector<int>& nums) {
        ios_base::sync_with_stdio(false);
        cin.tie(NULL);
        cout.tie(NULL);
        //three cases
        int n = nums.size();
        int left_index = 0;
        int right_index = n-1;
        long long res = 0;
        while(left_index+1<n && nums[left_index+1]>nums[left_index]) left_index++;
        while(right_index-1>=0 && nums[right_index-1]<nums[right_index]) right_index--;
        
        //All is increasing
        if(left_index>=right_index) return (n*(n+1))>>1;

        //left no select
        res += n-right_index+1;

        //left select
        for(int i=0;i<=left_index;i++){
            auto iter = upper_bound(nums.begin()+right_index,nums.end(),nums[i]);
            res += nums.end()-iter+1;
        }

        return res;
    }
    void debug(vector<int>& nums){
        for(auto& num:nums) printf("%d,",num);
        printf("\n");
    }
};