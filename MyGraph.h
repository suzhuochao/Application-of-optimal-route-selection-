#include <iostream>
#include <vector>
using namespace std;

struct Node {
    int adjvex;
    float weight;
    struct Node* next;
};

struct Vertex {
   int nodeName;
   Node* link;
};


class MyGraph {
private:
    Vertex* _graph;
    int _node_num;
    vector<int> _path;
    float _cost;


public:
    MyGraph(int nodeNum){
        _node_num = nodeNum;
        _graph = new Vertex[nodeNum];

        _cost = 10000;
        for (int i = 0; i < nodeNum; i++) {
            _graph[i].nodeName = i + 1; // v1
            _graph[i].link = nullptr;
        }
    };
    MyGraph(const MyGraph& g){
        _node_num = g._node_num;
        _graph = new Vertex[g._node_num];
        _cost = 10000;
        for(int i = 0; i < g._node_num; i++){
            _graph[i].nodeName = g._graph[i].nodeName;
            _graph[i].link = g._graph[i].link;
        }
    };

    ~MyGraph()= default;


    bool AddEdge(int start, int end, float w){
        addEdge(start, end, w);
        return addEdge(end, start, w);
    };

    void Output(std::ostream& os){
        os << "The number of vertices is: " <<_node_num << endl;
        for (int  i = 0; i < _node_num; i++) {
            struct Node* curr = _graph[i].link;

            while (curr != nullptr) {
                os << "edge: " << _graph[i].nodeName << " -> ";
                os << curr->adjvex << " , weight " << curr->weight << endl;
                curr = curr->next;
            }
        }
        os << endl;
    };

    pair<std::vector<int>, float> HW2Prog(int s, int t) {
        vector<int> link_list;
        link_list.push_back(s);
        float cost = 0;
        int flag = 1;
        struct Node* link = _graph[s-1].link;

        // recursion
        find_path(link_list, link, t, cost, flag);


        float tmp = _cost;
        _cost = 10000; // clear _cost after a target path has found
        vector<int> b;
        _path.swap(b); // clear the _path vector after a target path has found
    
        return pair<vector<int>, float>(b, tmp);

    };

private:
    void find_path(vector<int>& link_list, struct Node* curr, int t, float cost, int flag){
        if (flag >= _node_num) {
            return;
        }
        flag++;
        while (curr != nullptr) {
            if (curr->adjvex == t) {
                float pre = cost;
                if (cost < curr->weight) {
                    cost = curr->weight;
                }
                // store the solution if it's the best
                if(cost < _cost){
                    _cost = cost;
                } else {
                    break;
                }
                link_list.push_back(t);
                _path = link_list;
                link_list.pop_back();
                flag--;
                cost = pre;

            } else {
                if (valid(link_list, curr->adjvex) && cost < _cost) {
                    float pre = cost;
                    if (cost < curr->weight) {
                        cost = curr->weight;
                    }
                    link_list.push_back(curr->adjvex);
                    int index =  curr->adjvex - 1;
                    struct Node* link = _graph[index].link;
                    //recursion, put the new link every time
                    find_path(link_list, link, t, cost, flag);
                    link_list.pop_back();
                    flag--;
                    cost = pre;
                }
            }
            curr = curr->next;
        }
    };

    // check cyclet
    static bool valid(vector<int>& link_list, int t) {
        size_t all_num_size = link_list.size();
        for (int i = 0; i < all_num_size; i++) {
            if (link_list[i] == t) {
                return false;
            }
        }
        return true;
    };


    bool addEdge(int start, int end, float w) {
        struct Node* node = new struct Node();
        if (node == nullptr) {
            return false;
        }
        node->adjvex = end;
        node->weight = w;

        node->next = _graph[start - 1].link;
        _graph[start-1].link = node;

        return true;
    };

};


