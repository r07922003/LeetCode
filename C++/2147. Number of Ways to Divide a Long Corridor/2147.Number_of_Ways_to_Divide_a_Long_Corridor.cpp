class Solution {
public:
    int numberOfWays(string corridor) {
        /*
            'S' = seat
            'P' = plant
            each section has two seats and any number of plants
        */
        int n = corridor.size();
        int mod = 1e9+7;
        long long cnt = 1;
        int prev = -1;
        int seats = 0;
        for(int i=0;i<n;i++){
            if(corridor[i]=='S'){
                if(seats==0 && prev!=-1){
                    cnt *= (i-prev);
                    cnt %= mod;
                }
                seats++;
                if(seats==2){
                    seats = 0;
                    prev = i;
                }
            }
        }
        if(seats!=0 || prev==-1) return 0;
        return cnt;
    }
};