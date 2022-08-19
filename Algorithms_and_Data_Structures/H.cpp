#include <iostream>
#include <algorithm>
#include <queue>
#include <string>
bool used[100002];
int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(0);
    std::priority_queue <std::pair<int, int> > mn;
    std::priority_queue <std::pair<int, int> > mx;
    int call;
    std::cin >> call;
    int insert_number = 1;
    for (int i = 1; i <= call; i++) {
        std::string command;
        std::cin >> command;
        if (command[0] == 'I') {
            int val = 0;
            int j = 7;
            while (command[j] != ')') {
                val *= 10;
                val += (command[j] - '0');
                j++;
            }
            mx.push({val, insert_number});
            mn.push({-val, insert_number});
            insert_number++;
        }
        else if (command == "GetMin") {
            while (used[mn.top().second] == true) {
                mn.pop();
            }
            std::cout << -mn.top().first << '\n';
            used[mn.top().second] = true;
        }
        else {
            while (used[mx.top().second] == true) {
                mx.pop();
            }
            std::cout << mx.top().first << '\n';
            used[mx.top().second] = true;
        }
    }
    return 0;
}
