/* Copyright <c> Manoel Vilela 2017 HackerRank */
#include <iostream>
#include <vector>
#include <map>
#include <string>
#include <algorithm>
#include <set>
#include <cassert>
using namespace std;

// https://stackoverflow.com/questions/12222417/why-should-i-initialize-member-variables-in-the-order-theyre-declared-in
// a lista de inicialização deve serguir a ordem de criação dos membros;
struct Node{
    Node* prev;
    Node* next;
    int key;
    int value;
    Node(Node* p, Node* n, int k, int val):prev(p),next(n),key(k),value(val){};
    Node(int k, int val):prev(NULL),next(NULL),key(k),value(val){};
    ~Node(void);
};

Node::~Node(void) {
    delete &this->key;
    delete &this->value;
    delete this;
}

class Cache{

protected:
    map<int,Node*> mp; //map the key to the node in the linked list
    int cp;  //capacity
    Node* tail; // double linked list tail pointer
    Node* head; // double linked list head pointer
    virtual void set(int, int) = 0; //set function
    virtual int get(int) = 0; //get function
};

class LRUCache: public Cache {
private:
    int size;

    // método correto
    // E a desalocação? Acho que vai dar segfault
    void pop_node() {
        // cout << "POP TAIL" << endl;
        this->tail = this->tail->prev;
        this->tail->next = NULL;
        this->size -= 1;
    }

    // Essa definição é usada apenas
    // em hit_cache para deslocar o nó pra cabeça
    // então não é preciso desalocar memória
    void pop_node(Node *n) {
        // cout << "POP N" << endl;
        if (n->prev != NULL) {
            n->prev->next = n->next;
        }
        if (n->next != NULL) {
            n->next->prev = n->prev;
        }
        this->size -= 1;
    }

    // Aprentemente está correto
    void push_node(Node *head) {
        // cout << "PUSH!" << endl;
        if (this->size != 0) {
            // cout << "SIZE != 0" << endl;
            head->prev = NULL;
            head->next = this->head;
            this->head->prev = head;
            this->head = head;
        } else {
            // cout << "SIZE == 0" << endl;
            this->head = head;
            this->tail = head;
        }
        // if overflows the capacity of Cache
        this->size += 1;
        if (this->size > this->cp) {
            // cout << "FULL! POP TAIL" << endl;
            this->pop_node();
        }
    }

    // Se o nó não for a cabeça, move-o para a cabeça da lista.
    void hit_cache(Node *n) {
        if (n != this->head) {
            pop_node(n);
            push_node(n);
        }
    }


public:
    // não consegui usar lista de inicialização aqui
    // porque? diz que cp não é membro LRUCache
    LRUCache(int c) {
        this->cp = c;
        this->size = 0;
    }
    virtual void set(int key, int value) {
        // set já tiver a key, atualizar o valor do nó
        // e chamar hit_cache pra atualizar a posição
        if (this->mp.count(key) > 0) {
            this->mp[key]->value = value;
            this->hit_cache(this->mp[key]);
        } else {
            // do contrário criar um novo nó e fazer push na lista
            this->mp[key] = new Node(key, value);
            this->push_node(mp[key]);
        }
    }
    virtual int get(int key) {
        // cout << "SEARCHING..." << endl;
        // iterar os nós da cabeça até a cauda
        for (Node *n = this->head; n != NULL; n = n->next){
            // cout << "<" << n->key << "," << n->value << ">" << endl;
            if (n->key == key) {
                //cout << "FOUND!" << endl;
                this->hit_cache(n);
                return n->value;
            }
        }

        return -1;
    }

    // função usada apenas para debug
    void print_cache() {
        cout << "CACHE: ";
        for (Node *n = this->head; n != NULL; n = n->next) {
            cout << n->key << " ";
        }
        cout << endl;
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
        l.print_cache();
    }
    return 0;
}
