class Solution {
public:
    vector<int> replaceNonCoprimes(vector<int>& nums) {
        ios_base::sync_with_stdio(false);
        cin.tie(NULL);
        cout.tie(NULL);
        stack<int> s;
        for(auto num:nums){
            while(!s.empty() && gcd(s.top(),num)!=1){
                num = lcm(s.top(),num);
                s.pop();
            }
            s.push(num);
        }
        vector<int> res;
        while(!s.empty()){
            res.push_back(s.top());
            s.pop();
        }
        reverse(res.begin(),res.end());
        return res;
    }
    int gcd(int x,int y){
        if(y==0) return x;
        return gcd(y,x%y);
    }
    int lcm(int x,int y){
        return x/gcd(x,y)*y;
    }
};