class Solution {
    struct SET{
        multiset<int> positive;
        multiset<int> negative;
    };
    unordered_map<int,vector<int>> g;
    int n;
    vector<long long> res;
public:
    vector<long long> placedCoins(vector<vector<int>>& edges, vector<int>& cost) {
        this->n = edges.size()+1;
        this->res.resize(n,0);
        for(int i=0;i<edges.size();i++){
            auto& x = edges[i][0];
            auto& y = edges[i][1];
            g[x].push_back(y);
            g[y].push_back(x);
        }
        helper(0,-1,cost);
        return res;
    }
    SET helper(int node,int parent,vector<int>& cost){
        int child_count = g[node].size();
        multiset<int> pos;
        multiset<int> neg;
        SET coin_set = {pos,neg};

        if(cost[node]>0) coin_set.positive.insert(cost[node]);
        else coin_set.negative.insert(cost[node]);

        for(auto& neighbor:g[node]){
            if(parent==neighbor) continue;
            SET childe_coin_set = helper(neighbor,node,cost);

            update(coin_set,childe_coin_set);
        }
        
        if(coin_set.positive.size()+coin_set.negative.size()<3) res[node] = 1;
        if(coin_set.positive.size()>=3){
            auto iter = coin_set.positive.rbegin();
            int size = 0;
            long long positive_multi = 1;
            while(size<3 && iter!=coin_set.positive.rend()){
                positive_multi *= *iter;
                iter++;
                size++;
            }
            res[node] = max(res[node],positive_multi);
        }
        if(coin_set.positive.size()>=1 && coin_set.negative.size()>=2){
            auto iter = coin_set.negative.begin();
            long long one = *iter;
            iter++;
            long long two = *iter;
            res[node] = max(res[node],one*two*(*coin_set.positive.rbegin()));
        }
        res[node] = max(res[node],0ll);
        return coin_set;
    }
    void update(SET& coin_set,SET& childe_coin_set){
        int size = 0;
        auto iter1 = childe_coin_set.positive.rbegin();
        while(size<3 && iter1 != childe_coin_set.positive.rend()){
            coin_set.positive.insert(*iter1);
            iter1++;
            size++;
        }

        size = 0;
        auto iter2 = childe_coin_set.negative.begin();
        while(size<3 && iter2!=childe_coin_set.negative.end()){
            coin_set.negative.insert(*iter2);
            iter2++;
            size++;
        }
    }
};