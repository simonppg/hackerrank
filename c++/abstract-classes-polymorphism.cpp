#include <iostream>
#include <vector>
#include <map>
#include <string>
#include <algorithm>
#include <set>
#include <cassert>
using namespace std;

struct Node{
    Node* next;
    Node* prev;
    int value;
    int key;
    Node(Node* p, Node* n, int k, int val):prev(p),next(n),key(k),value(val) {
        //printf("Create node: %d, %d, prev: %d, next: %d\n", key, val, p ? p->key : -1, n ? n->key : -1);
    };
    Node(int k, int val):prev(NULL),next(NULL),key(k),value(val){
        //printf("Create node: %d, %d\n", key, val);
    };
};

class Cache{
    protected: 
        map<int,Node*> mp; //map the key to the node in the linked list
        int cp;  //capacity
        Node* tail; // double linked list tail pointer
        Node* head; // double linked list head pointer
        virtual void set(int, int) = 0; //set function
        virtual int get(int) = 0; //get function

};

class LRUCache : public Cache {
    private:
        int capacity;
        int size = 0;
    public:
        LRUCache(int& val) {
            head = tail = NULL;
            capacity = val;
        }
        bool is_empty_list() { return tail == NULL && head == NULL; }
        void print_mp() {
            cout << "Map:\n";
            for (auto itr = mp.begin(); itr != mp.end(); ++itr) { 
                cout << '\t' << itr->first 
                    << "\t[" << ((Node *)itr->second)->key << " "
                    << "\t" << ((Node *)itr->second)->value << "]\n"; 
            } 
        }
        void print_queue() {
            Node *n = head;
            cout << "Queue:\n";
            while(n != NULL) {
                printf("\t[%d, %d]", n->key, n->value); 
                n = n->next;
            }
            cout << endl;
        }
        void set(int key, int value) {
            //printf("set %d -> %d\n", key, value);
            auto it = mp.find(key);

            if(is_empty_list()) {
                Node *node = new Node(key, value);
                mp[key] = node;
                head = tail = node;
                size = 1;
            } else if(it != mp.end()) {
                // move it to the tail
                Node *p, *n, *node;
                node = it->second;
                node->value = value;
                p = node->prev;
                n = node->next;
                if(p)
                    p->next = n;
                if(n)
                    n->prev = p;
                    
                node->next = NULL;
                node->prev = NULL;
                tail->next = node;
                tail = node;
                mp[key] = node;
            } else if(size < capacity) {
                Node *node = new Node(tail, NULL, key, value);
                tail->next = node;
                tail = node;
                mp[key] = node;
                size++;
            } else {
                Node *node = new Node(tail, NULL, key, value);
                tail->next = node;
                tail = node;
                mp[key] = node;

                auto it = mp.find(head->key);
                if(it != mp.end()) {
                    Node *deleteme = head;
                    //printf("head: %d", (*it->second).key);
                    mp.erase(head->key);
                    head = head->next;
                    head->prev = NULL;
                    delete deleteme;
                }
            }

            //print_mp();
            //print_queue();
        }
        int get(int key) {
            auto it = mp.find(key);

            if(it != mp.end()) {
                return (it->second)->value;
            }

            return -1;
        }

};

int main() {
    int n, capacity,i;
    cin >> n >> capacity;
    LRUCache l(capacity);
    for(i=0;i<n;i++) {
        string command;
        cin >> command;
        if(command == "get") {
            int key;
            cin >> key;
            cout << l.get(key) << endl;
        } 
        else if(command == "set") {
            int key, value;
            cin >> key >> value;
            l.set(key,value);
        }
    }
    return 0;
}

