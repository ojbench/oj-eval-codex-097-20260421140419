#include <bits/stdc++.h>
using namespace std;

static vector<long long> parse_ints_between(const string &s, size_t l, size_t r){
    vector<long long> vals; vals.reserve(32);
    long long sign=1, cur=0; bool in=false, have=false;
    for(size_t i=l;i<r;i++){
        unsigned char uc = static_cast<unsigned char>(s[i]);
        char c = static_cast<char>(uc);
        if(c=='-' && !in){ sign=-1; in=true; cur=0; }
        else if(isdigit(uc)){ cur=cur*10 + (c-'0'); in=true; have=true; }
        else{ if(have){ vals.push_back(sign*cur); } sign=1; cur=0; in=false; have=false; }
    }
    if(have) vals.push_back(sign*cur);
    return vals;
}

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    // Read entire stdin
    ostringstream oss; oss << cin.rdbuf();
    string s = oss.str();
    if(s.empty()) return 0;

    vector<long long> root;
    long long cnt = LLONG_MIN;

    // 1) Prefer bracketed array if present
    size_t lb = s.find('['), rb = string::npos;
    if(lb != string::npos) rb = s.find(']', lb+1);
    if(lb != string::npos && rb != string::npos && rb > lb){
        root = parse_ints_between(s, lb+1, rb);
    }

    // 2) Try explicit "cnt = X"
    if(cnt == LLONG_MIN){
        static const regex re_cnt(R"(cnt\s*=\s*(-?\d+))");
        smatch m;
        if(regex_search(s, m, re_cnt)){
            try{ cnt = stoll(m[1].str()); }catch(...){ cnt = LLONG_MIN; }
        }
    }

    // 3) If cnt still unknown and we had brackets, find first number after ']'
    if(cnt == LLONG_MIN && rb != string::npos){
        string after = s.substr(rb+1);
        static const regex re_num(R"(-?\d+)");
        smatch m;
        if(regex_search(after, m, re_num)){
            try{ cnt = stoll(m[0].str()); }catch(...){ cnt = LLONG_MIN; }
        }
    }

    // 4) Fallback: extract all ints; last is cnt; prior are root
    if(root.empty() || cnt == LLONG_MIN){
        vector<pair<long long,pair<size_t,size_t>>> nums; nums.reserve(64);
        for(size_t i=0;i<s.size();){
            unsigned char uc = static_cast<unsigned char>(s[i]);
            if(isspace(uc) || s[i]==',' || s[i]==';'){ ++i; continue; }
            size_t j=i; bool neg=false; if(s[j]=='-'){ neg=true; ++j; }
            if(j<s.size() && isdigit(static_cast<unsigned char>(s[j]))){
                long long val=0; size_t k=j; 
                while(k<s.size() && isdigit(static_cast<unsigned char>(s[k]))){ val = val*10 + (s[k]-'0'); ++k; }
                long long v = neg ? -val : val;
                nums.push_back({v,{i,k}});
                i = k;
            }else{ ++i; }
        }
        if(root.empty() && !nums.empty() && lb!=string::npos && rb!=string::npos && rb>lb){
            for(auto &t: nums){ size_t a=t.second.first, b=t.second.second; if(a>lb && b<rb) root.push_back(t.first); }
            if(cnt==LLONG_MIN){
                for(int idx=(int)nums.size()-1; idx>=0; --idx){ size_t a=nums[idx].second.first, b=nums[idx].second.second; if(!(a>lb && b<rb)){ cnt = nums[idx].first; break; } }
            }
        }
        if((root.empty() || cnt==LLONG_MIN) && !nums.empty()){
            if(cnt==LLONG_MIN) cnt = nums.back().first;
            root.clear(); root.reserve(nums.size() ? nums.size()-1 : 0);
            for(size_t i=0;i+1<nums.size();++i) root.push_back(nums[i].first);
        }
    }

    if(root.empty() || cnt==LLONG_MIN) return 0;

    sort(root.begin(), root.end(), greater<long long>());
    long long k = cnt;
    if(k < 1) k = 1;
    if(k > (long long)root.size()) k = (long long)root.size();
    cout << root[k-1] << '\n';
    return 0;
}
