#include <iostream>
#include <unordered_map>
#include <utility>
#include <vector>
using namespace std;

// Custom hash function for pair<int, char>
struct pair_hash {
    template <class T1, class T2>
    size_t operator()(const pair<T1, T2> &pair) const {
        return hash<T1>()(pair.first) ^ hash<T2>()(pair.second);
    }
};

int main() {
    int no_input_symbol;
    cout << "Enter number of input symbols: ";
    cin >> no_input_symbol;

    vector<char> symbol(no_input_symbol);
    cout << "Enter input symbols: ";
    for (int i = 0; i < no_input_symbol; i++) {
        cin >> symbol[i];
    }

    int states;
    cout << "Enter number of states: ";
    cin >> states;

    int ini_state;
    cout << "Enter initial state: ";
    cin >> ini_state;

    int no_accepting_state;
    cout << "Enter number of accepting states: ";
    cin >> no_accepting_state;

    vector<int> accepting_state(no_accepting_state);
    cout << "Enter accepting states: ";
    for (int i = 0; i < no_accepting_state; i++) {
        cin >> accepting_state[i];
    }

    // Transition table
    unordered_map<pair<int, char>, int, pair_hash> transition_map;
    cout << "Enter transition table (format: current_state input_symbol next_state): \n";
    for (int i = 0; i < no_input_symbol * states; i++) {
        int curr;
        char sym;
        int next;
        cin >> curr >> sym >> next;
        transition_map[{curr, sym}] = next;
    }

    int size;
    cout << "Enter input string size: ";
    cin >> size;

    vector<char> input_string(size);
    cout << "Enter input string: ";
    for (int i = 0; i < size; i++) {
        cin >> input_string[i];
    }

    int cur_state = ini_state;
    for (int i = 0; i < size; i++) {
        if (transition_map.find({cur_state, input_string[i]}) == transition_map.end()) {
            cout << "Not accepted\n";
            return 0;
        }
        cur_state = transition_map[{cur_state, input_string[i]}];
    }

    bool is_accepted = false;
    for (int state : accepting_state) {
        if (cur_state == state) {
            is_accepted = true;
            break;
        }
    }

    if (is_accepted) {
        cout << "Accepted\n";
    } else {
        cout << "Not accepted\n";
    }

    return 0;
}
