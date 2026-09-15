#include <bits/stdc++.h>
using namespace std;

//Struct lưu 1 transaction
struct Transaction{
    string from;
    string to;
    int money;
    string time;
    string atm;
};

using Graph = map<string, vector<string>>;
using EdgeSet = set<pair<string, string>>;
//?number_transactions
int numberTransactions(const vector<Transaction> &trans){
    return trans.size();
}
//?total_money_transaction
long long totalMoneyTransaction(const vector<Transaction> &trans){
    long long sum = 0;
    for(const Transaction &t : trans){
        sum += t.money;
    }
    return sum;
}
//?list_sorted_accounts
string listSortedAccounts(const set<string> &accountSet){
    string result;
    bool first = true;
    for(const auto &acc : accountSet){
        if(!first) result += " ";
        result += acc;
        first = false;
    }
    return result;
}
//DFS + Backtracking
bool dfsCycle(const Graph &graph, const EdgeSet &edges, const string &start, const string &cur, int depth, int k, set<string> &visited){
    if(depth == k){
        return edges.count({cur, start}) > 0; //Kiểm tra cạnh quay về start
    }
    auto ptr = graph.find(cur);
    if(ptr == graph.end()) return false; //cur không gửi đi đâu cả
    for(const auto &next : ptr->second){
        if(visited.count(next)) continue;
        visited.insert(next);
        if(dfsCycle(graph, edges, start, next, depth + 1, k, visited)) return true;
        visited.erase(next);
    }
    return false;
}
//?inspect_cycle <account> k
int inspectCycle(const Graph &graph, const EdgeSet &edges, const string &acc, int k){
    if(k < 1) return 0;
    set<string> visited;
    visited.insert(acc);
    bool ok = dfsCycle(graph, edges, acc, acc, 1, k, visited);
    return ok ? 1 : 0;
}
int main(){
    vector <Transaction> trans;
    string line;
    //Đọc khối dữ liệu
    while(getline(cin, line)){
        if(line == "#") break;
        if(line.empty()) continue;
        stringstream ss(line);
        Transaction gd;
        ss >> gd.from >> gd.to >> gd.money >> gd.time >> gd.atm;
        trans.push_back(gd);
    }
    //Tiền xử lý
    set<string> accountSet;
    Graph graph;
    EdgeSet edges;
    map<string, long long> totalFrom;
    for(const auto &t : trans){
        accountSet.insert(t.from);
        accountSet.insert(t.to);
        graph[t.from].push_back(t.to);
        edges.insert({t.from, t.to});
        totalFrom[t.from] += t.money;
    }
    while(getline(cin, line)){
        if(line == "#") break;
        if(line.empty()) continue;
        stringstream ss(line);
        string cmd;
        ss >> cmd;
        if(cmd == "?number_transactions"){
            cout << numberTransactions(trans) << "\n";
        }else if(cmd == "?total_money_transaction"){
            cout << totalMoneyTransaction(trans) << "\n";
        }else if(cmd == "?list_sorted_accounts"){
            cout << listSortedAccounts(accountSet) << "\n";
        }else if(cmd == "?total_money_transaction_from"){
            string acc;
            ss >> acc;
            cout << totalFrom[acc] << "\n";
        }else if(cmd == "?inspect_cycle"){
            string acc;
            int k;
            ss >> acc >> k;
            cout << inspectCycle(graph, edges, acc, k) << "\n";
        }
    }
    return 0;
}