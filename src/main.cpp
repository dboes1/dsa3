//
// Created by dylan on 9/29/2025.
//

#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include "compass.h"
using namespace std;

vector<string> parseCSVRow(const string& row) {
    vector<string> fields;
    string field;
    bool inQuotes = false;

    for (char c : row) {
        if (!inQuotes && c == ',') {
            fields.push_back(field);
            field.clear();
        } else if (c == '"') {
            inQuotes = !inQuotes;
        } else {
            field += c;
        }
    }
    fields.push_back(field);

    return fields;
}

vector<vector<string>> readCSV(const string& filename) {
    vector<vector<string>> data;
    ifstream file(filename);

    if (!file.is_open()) {
        cerr << "Failed to open file: " << filename << endl;
        return data;
    }

    string line;
    while (getline(file, line)) {
        data.push_back(parseCSVRow(line));
    }

    file.close();
    return data;
}
// TIP To <b>Run</b> code, press <shortcut actionId="Run"/> or click the <icon src="AllIcons.Actions.Execute"/> icon in the gutter.
int main() {
    vector<vector<string>> edges = readCSV("../data/edges.csv");
    vector<vector<string>> classes = readCSV("../data/classes.csv");
    int commands = 0;
    cin >> commands;
    Compass campus;
    campus.convertEdges(edges);
    campus.convertClasses(classes);
    for (int i = 0; i < commands; i++) {
        string command;
        cin >> command;
        if (command == "insert") {
            string name;
            cin >> name;
            while (name[name.length()-1] != '"') {
                string add_name;
                cin >> add_name;
                name += add_name;
            }
            string ID;
            cin >> ID;
            string residence;
            cin >> residence;
            string N;
            cin >> N;
            vector<string> class_vector;
            for (int j = 0; j < stoi(N); j++) {
                string class_name;
                cin >> class_name;
                class_vector.push_back(class_name);
            }
            campus.insert(name, ID, residence, N, class_vector);
        }
        else if (command == "remove") {
            string ID;
            cin >> ID;
            campus.remove(ID);
        }
        else if (command == "dropClass") {
            string ID;
            cin >> ID;
            string class_name;
            cin >> class_name;
            campus.dropClass(ID, class_name);
        }
        else if (command == "replaceClass") {
            string ID;
            cin >> ID;
            string class_name_1;
            cin >> class_name_1;
            string class_name_2;
            cin >> class_name_2;
            campus.replaceClass(ID, class_name_1, class_name_2);
        }
        else if (command == "removeClass") {
            string class_code;
            cin >> class_code;
            campus.removeClass(class_code);
        }
        else if (command == "toggleEdgesClosure") {
            string N;
            cin >> N;
            vector<int> edge_vector;
            for (int j = 0; j < 2*stoi(N); j++) {
                string vertex;
                cin >> vertex;
                edge_vector.push_back(stoi(vertex));
            }
            campus.toggleEdgesClosure(stoi(N), edge_vector);
        }
        else if (command == "checkEdgeStatus") {
            string vertex_1;
            cin >> vertex_1;
            string vertex_2;
            cin >> vertex_2;
            campus.checkEdgeStatus(stoi(vertex_1), stoi(vertex_2));
        }
        else if (command == "isConnected") {
            string vertex_1;
            cin >> vertex_1;
            string vertex_2;
            cin >> vertex_2;
            campus.isConnected(stoi(vertex_1), stoi(vertex_2));
        }
        else if (command == "printShortestEdges") {
            string ID;
            cin >> ID;
            campus.printShortestEdges(ID);
        }
        else if (command == "printStudentZone") {
            string ID;
            cin >> ID;
            campus.printStudentZone(ID);
        }
        else {
            cout << "unsuccessful" << endl;
        }
    }
    return 0;
}
