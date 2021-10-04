//UMBC - CSEE - CMSC 341 - Fall 2021 - Proj1
#include "graph.h"

class Tester { // Tester class to implement test functions
public:
    void test_constructor() {
        Graph aGraph("testdata.txt");
        if (aGraph.m_dataFile != "testdata.txt") {//test if filename is correct
            cout << "Constructor Test --> failed --> filename is not correct" << endl;
            return;
        }
        if (aGraph.m_head->getValue() != 0) {//test if root = 0
            cout << "Constructor Test --> failed --> root value is not correct" << endl;
            return;
        }
        if (aGraph.m_numNodes != 16) {//test if num of nodes is corect
            cout << "Constructor Test --> failed --> number of node is not correct" << endl;
            return;
        }
        cout << "Constructor Test --> passed" << endl;
    }
    void test_emptyGraph() {
        Graph aGraph;
        if (aGraph.m_numNodes != 0) {
            cout << "Empty Graph Test --> failed --> num of node is not correct" << endl;
            return;
        }
        if (aGraph.m_dataFile != "") {
            cout << "Empty Graph Test --> failed --> data file name is not correct" << endl;
            return;
        }
        if (aGraph.m_head != nullptr) {
            cout << "Empty Graph Test --> failed --> head pointer has garbage" << endl;
            return;
        }
        cout << "Empty Graph Test --> passed" << endl;
    }
    void test_buildGraph() {
        Graph aGraph;
        aGraph.buildGraph("testdata.txt");
        if (aGraph.m_dataFile != "testdata.txt") {//test if filename is correct
            cout << "Build Graph Test --> failed --> data file name is not correct" << endl;
            return;
        }
        if (aGraph.m_head->getValue() != 0) {//test if root = 0
            cout << "Build Graph Test --> failed --> head pointer value is not correct" << endl;
            return;
        }
        if (aGraph.m_numNodes != 16) {//test if num of nodes is corect
            cout << "Build Graph Test --> failed --> number of node is not correct" << endl;
            return;
        }
        cout << "Build Graph Test --> passed" << endl;
    }
    void test_find_non_exisiting_path() {
        Graph aGraph("testdata.txt");
        if (aGraph.findPath(1, 14)) {
            cout << "Find non-existing path Test --> failed --> stack is not empty" << endl;
            return;
        }
        cout << "Find non-existing path Test --> passed" << endl;
    }
    void test_find_existing_path() {
        Graph aGraph("testdata.txt");
        aGraph.findPath(1, 15);
        int arr[] = { 1,2,6,7,11,15 };
        int i = 0;
        if (aGraph.m_path.size() != 6) {
            cout << "Find existing path Test --> failed --> more node than there should be" << endl;
            return;
        }
        while (!aGraph.m_path.empty()) {
            if (aGraph.m_path.top() != arr[i]) {
                cout << "Find existing path Test --> failed --> invalid node in path" << endl;
            }
            aGraph.m_path.pop();
            i++;
        }
        cout << "Find existing path Test --> passed" << endl;
    }
    void test_find_path_from_node_to_itself() {
        Graph aGraph("testdata.txt");
        aGraph.findPath(2, 2);
        if (aGraph.m_path.size() != 1) {
            cout << "Find path from node to itself --> failed --> stack size is not correct" << endl;
            return;
        }
        if (aGraph.m_path.top() != 2) {
            cout << "Find path from node to itself --> failed --> path is not correct" << endl;
            return;
        }
        aGraph.m_path.pop();
        cout << "Find path from node to itself --> passed" << endl;
    }
    void test_find_path_from_non_existing_start_node() {
        Graph aGraph("testdata.txt");
        aGraph.findPath(16, 14);
        if (aGraph.m_path.size() != 0) {
            cout << "Find path from a non-existing start node --> failed --> stack is not empty" << endl;
            return;
        }
        cout << "Find path from a non-existing start node --> passed" << endl;
    }
    void test_find_path_from_non_existing_end_node() {
        Graph aGraph("testdata.txt");
        aGraph.findPath(1, 16);
        if (aGraph.m_path.size() != 0) {
            cout << "Find path from a non-existing end node --> failed --> stack is not empty" << endl;
            return;
        }
        cout << "Find path from a non-existing end node --> passed" << endl;
    }
    void test_assignment_operator() {
        Graph aGraph("testdata.txt");
        Graph bGraph;
        bGraph = aGraph;
        aGraph.clearGraph();
        if (bGraph.m_head == nullptr || bGraph.m_numNodes == 0) {
            cout << "Assignment operator Test --> failed" << endl;
            return;
        }
        cout << "Assignment operator Test --> passed" << endl;
    }
};

int main() {
    Tester tester;
    tester.test_constructor();
    tester.test_emptyGraph();
    tester.test_buildGraph();
    tester.test_find_non_exisiting_path();
    tester.test_find_existing_path();
    tester.test_find_path_from_node_to_itself();
    tester.test_find_path_from_non_existing_start_node();
    tester.test_find_path_from_non_existing_end_node();
    tester.test_assignment_operator();
}