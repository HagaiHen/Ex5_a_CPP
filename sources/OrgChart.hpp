#include <string>
#include <vector>
#include <iostream>
#include <iterator>
#include <unordered_map>
#include <stack>

using namespace std;


namespace ariel {
    
    class Node {

        private:
            string data;
            Node* parent;
            vector<Node*> childs;

        public:
            Node(const string &d) : data(d) {}
            string get_data() { return this->data; };
            void set_data(const string &s) { this->data=s; };
            Node * get_parent() { return this->parent; };
            void set_parent(Node *n) { this->parent = n; };
            friend ostream &operator<<(ostream &stream, const Node &n) {
                stream << n.data;
                return stream;
            }

            vector<Node*> get_childs() { return this->childs; };

            void add_childs(Node * son) {
                this->childs.push_back(son);
            }

            

    };

    class LevelIter {
        private:
            Node * curr;
            vector<Node*> s;

        public:
            LevelIter() : curr(nullptr) {}
            LevelIter (Node* root) : curr(root) {
                stack<Node*> tmp;
                tmp.push(this->curr);
                this->s.push_back(this->curr);
                // cout << "1" << endl;
                for (int i = 0; i < 20; i++) {
                    if (tmp.size() > 0) {
                        this->curr = tmp.top();
                        tmp.pop();
                    } else {
                        for (size_t i = 0; i < curr->get_childs().size(); i++) {
                            s.push_back(this->curr->get_childs()[i]);
                            tmp.push(this->curr->get_childs()[i]);
                        }
                    }
                }
                cout << "end" << endl;
                // for (size_t i = 0; i <s.size(); i++) {
                //     cout << *s[i] << endl;
                // }
            }

            LevelIter& operator++() {
                cout << "2" << endl;
                if (this->s.size() == 0) {
                    this->curr = nullptr;
                    return *this;
                }
                this->s.pop_back();
                Node *n = this->s.front();
                this->curr = n;
                return *this;
            }

            LevelIter operator++(int) {
                cout << "3" << endl;
                LevelIter it = *this;
                ++(*this);
                return it;
            }

            LevelIter& operator--() {
                curr--;
                return *this;
            }

            LevelIter operator--(int) {
                LevelIter it = *this;
                --(*this);
                return it;
            }

            LevelIter& operator[](int index) {
                this->curr = this->curr + index;
                return *this;
            }

            LevelIter* operator->() {
                return this;
            }

            LevelIter& operator*() {
                return *this;
            }

            bool operator==(const LevelIter& other) const {
                return curr == other.curr;
            }

            bool operator!=(const LevelIter& other) const {
                return !(*this == other.curr);
            }

            friend ostream &operator<<(ostream &stream, const LevelIter &it) {
                stream << it.curr;
                return stream;
            }           


    };
    
    class OrgChart {

        private:
            Node * root;
            unordered_map<string, vector<Node*>> childs;

        
        public:

            OrgChart() : root (nullptr) {}

            OrgChart& add_root (const string &s) {
                if (!this->root) {
                    this->root = new Node(s);
                    this->root->set_data(s);
                } else {
                    this->root->set_data(s);
                }
                return *this;
            }

            OrgChart& add_sub (const string &s1, const string &s2) {
                Node * n = new Node(s2);
                n->set_parent(this->get_node(s1));
                this->get_node(s1)->add_childs(n);
                this->childs[s1].push_back(n);
                this->childs[s2];
                return *this;
            }

            vector<string>::iterator begin_level_order() {
                vector <string> vec;
                return vec.begin();
            }

            vector<string>::iterator begin_reverse_order(){
                vector <string> vec;
                return vec.begin();
            }

            vector<string>::iterator begin_preorder(){
                vector <string> vec;
                return vec.begin();
            }

            vector<string>::iterator end_level_order() {
                vector<string> vec;
                return vec.begin();
            }

            vector<string>::iterator reverse_order() {
                vector <string> vec;
                return vec.begin();
            }

            vector<string>::iterator end_preorder() {
                vector <string> vec;
                return vec.begin();
            }

            friend ostream &operator<<(ostream &stream, const OrgChart &tree) {return stream;}
            
            vector<string>::iterator begin() {
                vector <string> vec;
                return vec.begin();
            }
            
            vector<string>::iterator end() {
                vector <string> vec;
                return vec.begin();
            }

            unordered_map<string, vector<Node*>> * get_childs() { return &this->childs; }; 

            Node * get_root() { return this->root; };

            vector<Node*> get_sub(const string &s) {

                unordered_map<string, vector<Node*>>::iterator it = this->childs.begin();
                while(it != this->childs.end()) {
                    if (it->first == s) {
                        return this->childs[s];
                    }
                    it++;
                }
                throw invalid_argument("No such Node");

            }

            Node * get_node(const string &s) {
                if (this->root->get_data() == s) {
                    return this->root;
                } else {
                    for (const auto & [key, val] : this->childs) {
                        for (size_t i = 0; i < val.size(); i++) {
                            if (val[i]->get_data() == s) {
                                return val[i];
                            }
                        }
                    }
                }
                return nullptr;
            }

            
    };
}