#include <iostream>
#include <string>
#include <vector>
#include <numeric>
 
using namespace std;
 
int calcM(string inp) {
    vector<int> args;
    vector<char> ops;
    for(int i = 0; i < inp.size(); i++)
        if(i % 2 == 0) args.push_back(inp[i] - '0');
        else ops.push_back(inp[i]);
 
    while(true) {
        int ind = -1;
        for(int i = 0; i < ops.size(); i++) if(ops[i] == '*') { ind = i; break; }
        if(ind == -1) break;
 
        vector<int> nargs;
        vector<char> nops;
        for(int i = 0; i < ind; i++) {
            nargs.push_back(args[i]);
            nops.push_back(ops[i]);
        }
        nargs.push_back(args[ind] * args[ind + 1]);
        for(int i = ind + 2; i < args.size(); i++) nargs.push_back(args[i]);
        for(int i = ind + 1; i < ops.size(); i++) nops.push_back(ops[i]);
        args = nargs, ops = nops;
    }
 
    return accumulate(args.begin(), args.end(), 0);
}
 
int calcL(string inp) {
    vector<int> args;
    vector<char> ops;
    for(int i = 0; i < inp.size(); i++)
        if(i % 2 == 0) args.push_back(inp[i] - '0');
        else ops.push_back(inp[i]);
 
    int res = args[0];
    for(int i = 1; i < args.size(); i++)
        if(ops[i - 1] == '+') res += args[i];
        else res *= args[i];
 
    return res;
}
 
int main(void) {
    string inp;
    int tar;
 
    cin >> inp >> tar;
 
    int mres = calcM(inp);
    int lres = calcL(inp);
 
    if(tar == mres and tar == lres) cout << "U\n";
    else if(tar == mres) cout << "M\n";
    else if(tar == lres) cout << "L\n";
    else cout << "I\n";
 
    return 0;
}
