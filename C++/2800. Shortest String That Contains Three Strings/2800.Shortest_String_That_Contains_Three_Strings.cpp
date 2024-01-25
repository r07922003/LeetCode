class Solution {
public:
    string minimumString(string a, string b, string c) {
        /*
        Two Key concept
            1. KMP
            2. Find commom prefix and suffix of string A and string B
        */
        ios_base::sync_with_stdio(false);
        cin.tie(NULL);
        cout.tie(NULL);
        vector<string> possible;
        possible.push_back(merge(merge(a,b),c));
        possible.push_back(merge(merge(b,a),c));
        possible.push_back(merge(merge(a,c),b));
        possible.push_back(merge(merge(c,a),b));
        possible.push_back(merge(merge(b,c),a));
        possible.push_back(merge(merge(c,b),a));
        string res = "";
        int len = INT_MAX;
        for(auto& candidate:possible){
            if(len>candidate.size()){
                res = candidate;
                len = candidate.size();
            }
            else if(len==candidate.size()){
                for(int i=0;i<len;i++){
                    if(res[i]==candidate[i]) continue;
                    if(res[i]<candidate[i]) break;
                    else{
                        res = candidate;
                        break;
                    }
                }
            }
        }
        return res;
    }
    string merge(string a,string b){
        if(a==b) return a; 
        int m = a.size();
        int n = b.size();
        if(KMP(a,b)){
            if(m>n) return a;
            else return b;
        }
        int len = min(m,n);
        string sub_a = a.substr(m-len,len);
        string sub_b = b.substr(0,len);
        while(len){
            if(sub_a==sub_b) break;
            sub_a.erase(sub_a.begin());
            sub_b.pop_back();
            len--;
        }
        return a.substr(0,m-len) + sub_a + b.substr(len,n-len);
    }
    bool KMP(string& a,string &b){
        if(b.size()>a.size()) return KMP(b,a);
        int n = b.size();
        vector<int> dp(n,0);
        int p = 0;
        for(int i=1;i<n;i++){
            if(b[i]==b[p]) dp[i] = ++p;
            else if(p>0){
                p = dp[p-1];
                i--;
            }
        }

        p = 0;
        for(int i=0;i<a.size();i++){
            if(a[i]==b[p]){
                p++;
                if(p>=n) return true;
            }
            else if(p>0){
                p = dp[p-1];
                i--;
            }
        }
        return false;
    } 
};