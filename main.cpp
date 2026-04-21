#include <bits/stdc++.h>
using namespace std;

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    // Read all input into a string
    std::ostringstream oss; oss << cin.rdbuf();
    string s = oss.str();
    if(s.empty()) return 0;

    // Extract all integers from the input
    vector<long long> nums;
    long long sign = 1, cur = 0; bool in = false, have = false;
    for(size_t i=0;i<s.size();++i){
        char c = s[i];
        if(c=='-' && !in){ sign = -1; in = true; cur = 0; }
        else if(isdigit(static_cast<unsigned char>(c))){ cur = cur*10 + (c - '0'); in = true; have = true; }
        else {
            if(have){ nums.push_back(sign * cur); }
            sign = 1; cur = 0; in = false; have = false;
        }
    }
    if(have) nums.push_back(sign * cur);

    if(nums.empty()) return 0;

    // Assume last number is cnt, others are node values
    long long cnt = nums.back();
    nums.pop_back();

    if(nums.empty()) return 0;

    // Compute cnt-th largest among node values
    sort(nums.begin(), nums.end(), greater<long long>());
    if(cnt < 1) cnt = 1;
    if(cnt > (long long)nums.size()) cnt = nums.size();
    cout << nums[cnt - 1] << '\n';
    return 0;
}
