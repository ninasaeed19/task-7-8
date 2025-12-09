#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

struct Item {
    string name;
    int price;
};


// Greedy: take cheapest items

vector<int> greedySolve(vector<Item> items, int budget) {
    vector<int> idx(items.size());
    for (int i = 0; i < items.size(); i++) idx[i] = i;

    sort(idx.begin(), idx.end(), [&](int a, int b){
        return items[a].price < items[b].price;
    });

    vector<int> chosen;
    int money = budget;

    for (int i : idx) {
        if (items[i].price <= money) {
            chosen.push_back(i);
            money -= items[i].price;
        }
    }
    return chosen;
}


// Dynamic Programming

vector<int> dpSolve(vector<Item> items, int budget) {
    int n = items.size();
    vector<vector<int>> dp(n+1, vector<int>(budget+1, 0));

    for (int i = 1; i <= n; i++) {
        for (int b = 0; b <= budget; b++) {
            dp[i][b] = dp[i-1][b];
            if (items[i-1].price <= b) {
                dp[i][b] = max(dp[i][b], dp[i-1][b - items[i-1].price] + 1);
            }
        }
    }

    vector<int> chosen;
    int b = budget;

    for (int i = n; i > 0; i--) {
        if (dp[i][b] != dp[i-1][b]) {
            chosen.push_back(i-1);
            b -= items[i-1].price;
        }
    }
    reverse(chosen.begin(), chosen.end());
    return chosen;
}


// Print chosen items

void printItems(const vector<Item>& items, const vector<int>& chosen) {
    if (chosen.empty()) {
        cout << "No items can be bought.\n";
        return;
    }
    int total = 0;
    for (int i : chosen) {
        cout << items[i].name << " - " << items[i].price << endl;
        total += items[i].price;
    }
    cout << "Total price = " << total << endl;
}

int main() {
    int budget, n;

    cout << "Enter your budget: ";
    cin >> budget;

    cout << "How many items do you want to enter? ";
    cin >> n;

    vector<Item> items(n);

    for (int i = 0; i < n; i++) {
        cout << "Item name: ";
        cin >> items[i].name;
        cout << "Item price: ";
        cin >> items[i].price;
    }

    cout << "\nChoose algorithm:\n";
    cout << "1 - Greedy\n";
    cout << "2 - Dynamic Programming\n";
    cout << "Your choice: ";

    int choice;
    cin >> choice;

    if (choice == 1) {
        auto ans = greedySolve(items, budget);
        cout << "\nGreedy Result:\n";
        printItems(items, ans);
    }
    else if (choice == 2) {
        auto ans = dpSolve(items, budget);
        cout << "\nDP Result:\n";
        printItems(items, ans);
    }
    else {
        cout << "Invalid choice.\n";
    }

    return 0;
}
