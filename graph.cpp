//UMBC - CSEE - CMSC 341 - Fall 2021 - Proj1
#include "graph.h"
Graph::Graph() :m_head(nullptr), m_numNodes(0), m_dataFile("") {}

Graph::Graph(string dataFile):m_head(nullptr),m_numNodes(0),m_dataFile(dataFile) { loadData(); }

Graph::~Graph() {
    if (!m_head) {//empty graph
        return;
    }
    //Delete nodes one by one
    Node* curr_node = m_head;
    Node* temp = nullptr;
    while (curr_node->getNext() != nullptr) {
        temp = curr_node->getNext();
        delete curr_node;
        curr_node = temp;
    }
}

void Graph::loadData() {
    int numNodes;
    int node, n, e, s, w;
    ifstream dataFile;
    dataFile.open(m_dataFile);
    if (dataFile.is_open()) {
        dataFile >> numNodes;
        m_numNodes = numNodes;
        for (int i = 0; i < numNodes; i++) {
            dataFile >> node >> n >> e >> s >> w;
            insert(node, n, e, s, w);
        }
    }
    else
        //the following statement provides the reason if a file doesn't open
        //please note: not all platforms are providing the same message
        cerr << "Error: " << strerror(errno) << endl;
}

void Graph::insert(int node, int n, int e, int s, int w) {
    
    Node* new_node = findNode(node);//find if node exists
    Node* n_node = findNode(n);
    n != -1 && !n_node ? n_node = new Node(n) : n_node = nullptr;
    Node* e_node = findNode(e);
    e != -1 && !e_node ? e_node = new Node(e) : e_node = nullptr;
    Node* s_node = findNode(s);
    s != -1 && !s_node ? s_node = new Node(s) : s_node = nullptr;
    Node* w_node = findNode(w);
    w != -1 && !w_node ? w_node = new Node(w) : w_node = nullptr;
    if (new_node) {//if node exists set its pointers and return
        new_node->setNorth(n_node);
        new_node->setEast(e_node);
        new_node->setSouth(s_node);
        new_node->setWest(w_node);
    }
    else {//if not exists create a new node and add to graph
        new_node = new Node(node, n_node, e_node, s_node, w_node);
    }
    if (!m_head) {
        m_head = new_node;
        return;
    }

    //insertion at tail
    Node* curr_node = m_head;
    while (curr_node->getNext() != nullptr) {
        curr_node = curr_node->getNext();
    }
    curr_node->setNext(new_node);
}

void Graph::insertAtHead(Node* aNode) {
    aNode->setNext(m_head);
    m_head = aNode;
    m_numNodes++;
}

Node* Graph::findNode(int nodeValue) {
    if (nodeValue == -1 || !m_head) {//if val is -1 or graph is empty
        return nullptr;
    }
    //Traverse all nodes and there pointers and return the node if found.
    Node* curr_node = m_head;
    while (curr_node != nullptr) {
        if (curr_node->getValue() == nodeValue)
            return curr_node;
        if (curr_node->getNorth() != nullptr)
            if (curr_node->getNorth()->getValue() == nodeValue)
                return curr_node->getNorth();
        if (curr_node->getSouth() != nullptr)
            if (curr_node->getSouth()->getValue() == nodeValue)
                return curr_node->getSouth();
        if (curr_node->getWest() != nullptr)
            if (curr_node->getWest()->getValue() == nodeValue)
                return curr_node->getWest();
        if (curr_node->getEast() != nullptr)
            if (curr_node->getEast()->getValue() == nodeValue)
                return curr_node->getEast();
        curr_node = curr_node->getNext();
    }
}

bool Graph::findPath(int start, int end) {
    clearVisited();//clear all nodes visited status
    clearResult();//clear stack
    Node* start_node = findNode(start);//find if start node exist
    Node* end_node = findNode(end);//find if end node exist
    if (!start_node || !end_node || m_numNodes==0) {//in case start or end node doesn't exist return false
        return false;
    }
    if (findPath(start_node, end))//find and return path
        return true;
    return false;
}

bool Graph::findPath(Node* aNode, int end) {
    if (!aNode || aNode->getVisited())//if node is null or visited return (base case 1)
        return false;
    if (aNode->getValue() == end) {//if node is end return (base case 2)
        m_path.push(end);
        return true;
    }
    //Recursively traverse the node's pointers and find path
    aNode->setVisited(true);
    if (aNode->getNorth() && !aNode->getNorth()->getVisited()) {
        if (findPath(aNode->getNorth(), end)) {//if found add value to stack
            m_path.push(aNode->getValue());
            return true;
        }
    }
    if (aNode->getSouth() && !aNode->getSouth()->getVisited()) {
        if (findPath(aNode->getSouth(), end)) {//if found add value to stack
            m_path.push(aNode->getValue());
            return true;
        }
    }
    if (aNode->getWest() && !aNode->getWest()->getVisited()) {
        if (findPath(aNode->getWest(), end)) {//if found add value to stack
            m_path.push(aNode->getValue());
            return true;
        }
    }
    if (aNode->getEast() && !aNode->getEast()->getVisited()) {
        if (findPath(aNode->getEast(), end)) {//if found add value to stack
            m_path.push(aNode->getValue());
            return true;
        }
    }
    return false;
}

void Graph::dump() {
    //print stack data empty it
    while(!m_path.empty()) {
        cout << m_path.top() << "=>";
        m_path.pop();
    }
    cout << "END\n";
}

void Graph::clearResult() {
    //clear stack
    while (!m_path.empty()) {
        m_path.pop();
    }
}

void Graph::clearVisited() {
    //clear all node visited status
    if (!m_head)
        return;
    Node* curr_node = m_head;
    while (curr_node->getNext() != nullptr) {
        curr_node->setVisited(false);
        curr_node = curr_node->getNext();
    }
}

void Graph::buildGraph(string file) {
    //clear graph and rebuild it from the file
    clearGraph();
    m_dataFile = file;
    loadData();
}

void Graph::clearGraph() {
    //clear all data of the graph
    if (!m_head) {
        return;
    }
    clearResult();
    Node* curr_node = m_head;
    Node* temp = nullptr;
    while (curr_node->getNext() != nullptr) {
        temp = curr_node->getNext();
        delete curr_node;
        curr_node = temp;
    }
    m_numNodes = 0;
    m_head = nullptr;
}

const Graph& Graph::operator=(const Graph& rhs) {
    if (&rhs == this)
        return *this;
    
    clearGraph();
    m_numNodes = rhs.m_numNodes;
    m_dataFile = rhs.m_dataFile;
    loadData();
    return *this;
}

bool Graph::empty() const		// is the list empty?
{
    return m_head == nullptr;
}