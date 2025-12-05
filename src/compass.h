//compass.h

//
// Created by dylan on 9/19/2025.
//

#ifndef TEST_AVL_H
#define TEST_AVL_H

#endif //TEST_AVL_H

#include <vector>
#include <unordered_map>
#include <set>
#include <iostream>
#include <queue>

using namespace std;

class Compass {
    vector<vector<vector<int>>> location_list;
    unordered_map<string, int> class_map;
    set<string> IDs;
    set<string> classes;
    unordered_map<string, string> student_names;
    unordered_map<string, int> student_residences;
    unordered_map<string, set<string>> student_classes;

    public:
        bool convertEdges (vector<vector<string>> edges) {
            if (edges.size() < 2) return false;
            int list_size = 0;
            for (int i = 1; i < edges.size(); i++) {
                if (stoi(edges[i][0]) > list_size) {
                    list_size = stoi(edges[i][0]);
                }
                if (stoi(edges[i][1]) > list_size) {
                    list_size = stoi(edges[i][1]);
                }
            }
            vector<vector<vector<int>>> v(list_size+1);
            for (int i = 1; i < edges.size(); i++) {
                v[stoi(edges[i][0])].push_back({stoi(edges[i][1]), stoi(edges[i][4]), 1});
                v[stoi(edges[i][1])].push_back({stoi(edges[i][0]), stoi(edges[i][4]), 1});
            }
            this->location_list = v;
            return true;
        }

        bool convertClasses (vector<vector<string>> class_list) {
            if (class_list.size() < 2) return false;
            for (int i = 1; i < class_list.size(); i++) {
                this->class_map[class_list[i][0]] = stoi(class_list[i][1]);
                this->classes.insert(class_list[i][0]);
            }
            return true;
        }

        bool insert(string name, string ID, string residence, string n, vector<string> class_codes) {
            if (ID.length() != 8) {
                cout << "unsuccessful" << endl;
                return false;
            }
            for (int i = 0; i < 8; i++) {
                if (!isdigit(ID[i])) {
                    cout << "unsuccessful" << endl;
                    return false;
                }
            }
            if (name.length() > 1 && name[0] == '"' && name[name.length()-1] == '"') {
                name = name.substr(1, name.length()-2);
            }
            for (int i = 0; i < name.length(); i++) {
                if (!isalpha(name[i]) && name[i] != ' ') {
                    cout << "unsuccessful" << endl;
                    return false;
                }
            }
            if (class_codes.size() != stoi(n)) {
                cout << "unsuccessful" << endl;
                return false;
            }
            if (this->IDs.count(ID)) {
                cout << "unsuccessful" << endl;
                return false;
            }
            set<string> code_set;
            for (int i = 0; i < class_codes.size(); i++) {
                if (this->classes.count(class_codes[i]) == 0) {
                    cout << "unsuccessful" << endl;
                    return false;
                }
                code_set.insert(class_codes[i]);
            }
            this->IDs.insert(ID);
            this->student_names[ID] = name;
            this->student_residences[ID] = stoi(residence);
            this->student_classes[ID] = code_set;
            cout << "successful" << endl;
            return true;
        }

        bool remove(string ID) {
            if (this->IDs.count(ID) == 0) {
                cout << "unsuccessful" << endl;
                return false;
            }
            this->IDs.erase(ID);
            cout << "successful" << endl;
            return true;
        }

        bool dropClass(string ID, string class_code) {
            if (this->IDs.count(ID) == 0) {
                cout << "unsuccessful" << endl;
                return false;
            }
            if (this->student_classes.at(ID).count(class_code)) {
                this->student_classes.at(ID).erase(class_code);
                if (this->student_classes.at(ID).empty()) {
                    this->IDs.erase(ID);
                }
                cout << "successful" << endl;
                return true;
            }
            cout << "unsuccessful" << endl;
            return false;
        }

        bool replaceClass(string ID, string class_code_1, string class_code_2) {
            if (this->IDs.count(ID) == 0) {
                cout << "unsuccessful" << endl;
                return false;
            }
            if (this->student_classes.at(ID).count(class_code_1) == 0) {
                cout << "unsuccessful" << endl;
                return false;
            }
            if (this->student_classes.at(ID).count(class_code_2)) {
                cout << "unsuccessful" << endl;
                return false;
            }
            if (this->classes.count(class_code_2) == 0) {
                cout << "unsuccessful" << endl;
                return false;
            }
            this->student_classes.at(ID).erase(class_code_1);
            this->student_classes.at(ID).insert(class_code_2);
            cout << "successful" << endl;
            return true;
        }
    int removeClass(string class_code) {
   		int students = 0;
   		for (auto ID: this->IDs) {
       		if (this->student_classes.at(ID).count(class_code)) {
           			this->student_classes.at(ID).erase(class_code);
           			if (this->student_classes.at(ID).empty()) {
               			this->IDs.erase(ID);
           			}
           			students++;
       		}
   		}
   		cout << students << endl;
   		return students;
    }

    bool toggleEdgesClosure(int N, vector<int> edges){
        for (int i = 0; i < N; i += 2){
            for (int j = 0; j < this->location_list[edges[i]].size(); j++){
                if (this->location_list[edges[i]][j][0] == edges[i+1]){
                    int temp = (this->location_list[edges[i]][j][2] + 1) % 2;
                    this->location_list[edges[i]][j][2] = temp;
                }
            }
            for (int j = 0; j < this->location_list[edges[i+1]].size(); j++){
                if (this->location_list[edges[i+1]][j][0] == edges[i]){
                    int temp = (this->location_list[edges[i+1]][j][2] + 1) % 2;
                    this->location_list[edges[i+1]][j][2] = temp;
                }
            }
        }
        cout << "successful" << endl;
        return true;
    }

    int checkEdgeStatus(int location_x, int location_y){
        for (int j = 0; j < this->location_list[location_x].size(); j++){
            if (this->location_list[location_x][j][0] == location_y){
                if(this->location_list[location_x][j][2]) {
                    cout << "open" << endl;
                    return 2;
                }
                cout << "closed" << endl;
                return 1;
            }
        }
        cout << "DNE" << endl;
        return 0;
    }

    bool isConnected(int location_x, int location_y){
        std::set<int> visited;
        std::queue<int> stk;
        visited.insert(location_x);
        stk.push(location_x);
        while(!stk.empty()){
            int u = stk.front();
            stk.pop();
            for (vector<int> v: this->location_list[u]){
                if (visited.count(v[0]) == 0 && v[2]){
                    if (v[0] == location_y){
                        cout << "successful" << endl;
                        return true;
                    }
                    stk.push(v[0]);
                    visited.insert(v[0]);
                }
            }
        }
        cout << "successful" << endl;
        return true;
    }

    vector<int> getZone(string ID) {
        priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq;
        vector<int> dist(this->location_list.size(), -1);
        pq.push({0, this->student_residences[ID]});
        dist[this->student_residences[ID]] = 0;
        while (!pq.empty()){
            pair<int, int> curr = pq.top();
            pq.pop();
            int u = curr.second;
            for (int i = 0; i < this->location_list[u].size(); i++){
                int v = this->location_list[u][i][0];
                int w = this->location_list[u][i][1];
                if (this->location_list[u][i][2]){
                    if (dist[v] < 0 || dist[v] > dist[u] + w){
                        dist[v] = dist[u] + w;
                        pq.push({dist[v], v});
                    }
                }
            }
        }
        return dist;
