class Solution {
class trie_node{
public:
    trie_node *next[26];
    int id;
    trie_node(){
        for(int i=0;i<26;i++) this->next[i]=NULL;
        this->id = -1;
    }
    void insert(const string& word,const int& id){
        int n = word.size();
        trie_node* node = this;
        for(int i=0;i<n;i++){
            int cur_ch = word[i]-'a';
            if(!node->next[cur_ch]) node->next[cur_ch] = new trie_node();
            node = node->next[cur_ch];
        }
        node->id = id;
    }
};

trie_node *root;

public:
    long long minimumCost(string source, string target, vector<string>& original, vector<string>& changed, vector<int>& cost) {
        /*
            1. Using trie to save reverse edge (why? because bottom-down algo.)
            2. Floyd-Warshall
            3. DP bottom-down algo.
        */
        for(auto& word:original) reverse(word.begin(),word.end());
        for(auto& word:changed) reverse(word.begin(),word.end());
        this->root = new trie_node();
        unordered_set<string> SET;
        SET.insert(original.begin(),original.end());
        SET.insert(changed.begin(),changed.end());
        unordered_map<string,int> string_to_id;
        for(auto& word:SET){
            root->insert(word,string_to_id.size());
            string_to_id[word] = string_to_id.size();
        }
        
        int n = string_to_id.size();
        long long adj[n][n];
        for(int i=0;i<n;i++){
            for(int j=0;j<n;j++) adj[i][j] = LLONG_MAX/2;
            adj[i][i] = 0;
        }
        for(int i=0;i<original.size();i++){
            int x = string_to_id[original[i]];
            int y = string_to_id[changed[i]];
            adj[x][y] = min(adj[x][y],(long long)cost[i]);
        }
        for(int k=0;k<n;k++){
            for(int i=0;i<n;i++){
                for(int j=0;j<n;j++){
                    adj[i][j] = min(adj[i][j],adj[i][k]+adj[k][j]);
                }
            }
        }
        /*
            let dp[i]: the minumum cost to convert s[0:i] to t[0:i]
            source: x x x x x [x x x x]
                               j     i
            target: x x x x x [x x x x]
            dp[i] = dp[j-1] + adj[cost(source[j:i]->target[j:i])]
        */
        int len = source.size();
        long long dp[len+1];
        dp[0] = 0ll;
        for(int i=1;i<=len;i++){
            dp[i] = LLONG_MAX/2;
            if(source[i-1]==target[i-1]) dp[i] = dp[i-1];
            trie_node* node1 = root;
            trie_node* node2 = root;
            for(int j=i;j>=1;j--){
                int source_index = source[j-1]-'a';
                int target_index = target[j-1]-'a';
                if (node1->next[source_index]==NULL) break;
                if (node2->next[target_index]==NULL) break;
                node1 = node1->next[source_index];
                node2 = node2->next[target_index];
                if (node1->id==-1 || node2->id==-1) continue;
                dp[i] = min(dp[i],dp[j-1]+adj[node1->id][node2->id]); 
            }
        }
        return dp[len]==LLONG_MAX/2 ?-1 :dp[len];
    }
};