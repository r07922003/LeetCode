class Encrypter {
    unordered_map<string,int> possible_answer;
    unordered_map<char,string> mapping;
public:
    Encrypter(vector<char>& keys, vector<string>& values, vector<string>& dictionary) {
        for(int i=0;i<keys.size();i++){
            mapping[keys[i]] = values[i];
        }
        for(auto& word:dictionary){
            string after_encrypt = encrypt(word);
            if(after_encrypt.size()<=0) continue;
            possible_answer[after_encrypt]++;
        }
    }
    
    string encrypt(string word1) {
        string res = "";
        for(auto& ch:word1){
            if(mapping.find(ch)!=mapping.end()) res += mapping[ch];
            else return "";
        }
        return res;
    }
    
    int decrypt(string word2) {
        if(possible_answer.find(word2)==possible_answer.end()) return 0;
        return possible_answer[word2];
    }
};

/**
 * Your Encrypter object will be instantiated and called as such:
 * Encrypter* obj = new Encrypter(keys, values, dictionary);
 * string param_1 = obj->encrypt(word1);
 * int param_2 = obj->decrypt(word2);
 */