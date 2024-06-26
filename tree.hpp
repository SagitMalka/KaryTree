#pragma once

#include <iostream>
#include <sstream>
#include <fstream>
#include <memory>
#include <string>
#include <map>
#include <vector>
#include <cmath>
//#include "Node.hpp"
using std::vector;
using std::ostream;
using std::invalid_argument;
using std::shared_ptr;
using std::make_shared;
using std::weak_ptr;
using std::unique_ptr;
using std::move;
using std::string;
using std::endl;
using std::out_of_range;
using std::array;

namespace ariel {
    template<typename T>
    class Node {
    public:
        T _val;
        vector<shared_ptr<Node>> _children;
        weak_ptr<Node> _parent;
        int _depth;
        int _children_count;
        shared_ptr<Node> _left_most;
        shared_ptr<Node> _right_most;

        explicit Node(T value)
                : _val(value), _depth(0), _children_count(0), _left_most(nullptr), _right_most(nullptr) {}

//        explicit Node(T &&value) noexcept: _val(value), _children({nullptr}), _depth(0), _children_count(0){
//            _parent = make_shared<Node<T>>();
////            _left_most = _children[0];
////            _right_most = _children[_children_count-1];
//        }

//        explicit Node(T value) : _val(value), _children({nullptr}), _depth(0),_children_count(0){
//            _parent = make_shared<Node<T>>();
//            _left_most = nullptr;
//            _right_most = nullptr;
//        }

        Node() = default;

        void addChild(shared_ptr<Node> child) {
            if (_children.size() < _children_count) {
                _children.push_back(child);
            } else {
                throw out_of_range("Exceeded max number of children");
            }
        }
    };

    template<typename T>
    class Tree {
    private:
        shared_ptr<Node<T>> _root;
        int _k;
        int _maxDepth = 0;
        int _treeSize = 0;


        enum Traversal {
            InOrder, PreOrder, PostOrder, DFS, BFS, Heap
        }; // traversal types

    public:
        class Iterator {
            Traversal _traversal = Traversal::InOrder;
            shared_ptr<Node<T>> _current;

        private:
            bool isRoot() const {
                auto parent = _current->_parent;
                return !parent.owner_before(weak_ptr<Node<T>>{}) && !weak_ptr<Node<T>>{}.owner_before(parent);
            }

            bool isLeftMost() const {
                return !isRoot() && (_current == _current->_parent.lock()->_left_most);
            }

            bool isRightMost() const {
                return !isRoot() && (_current == _current->_parent.lock()->_right_most);
            }

            bool isLeaf() const {
                return _current->_children[0] == nullptr;
            }

            bool hasLeft() {
                return _current->_left_most != nullptr;
            }

            bool hasRight() {
                return _current->_right_most != nullptr;
            }

            void goDownLeft() {
                while (hasLeft()) {
                    _current = _current->_left_most;
                }
            }

            void goDownLeftAndRight() {
                do {
                    goDownLeft();

                    if (hasRight()) {
                        oneRight();
                    }

                } while (hasLeft() || hasRight());
            }

            void oneRight() {
                _current = _current->_right_most;
            }

            void oneLeft() {
                _current = _current->_left_most;
            }

            void oneUp() {
                _current = _current->_parent.lock();
            }

            void inorder_Next() {

                if (hasRight()) {
                    _current = _current->_right_most;

                    goDownLeft();
                } else if (isLeftMost()) {
                    oneUp();
                } else if (isRightMost()) {
                    do {
                        oneUp();
                    } while (isRightMost());

                    oneUp();
                } else {
                    this->_current = nullptr;
                }
            }

            void preOrder_Next() {
                if (hasLeft()) {
                    oneLeft();
                } else if (hasRight()) {
                    oneRight();
                } else {
                    bool prevRight = false;

                    do {
                        prevRight = isRightMost();
                        oneUp();

                        if (_current == nullptr) { return; }

                    } while (prevRight || !hasRight());

                    oneRight();
                }
            }

            void PostOrder_Next() {

                if (isRoot() || isRightMost()) {
                    oneUp();
                } else if (isLeftMost()) {
                    oneUp();

                    if (hasRight()) {
                        oneRight();
                        goDownLeftAndRight();
                    }
                }
            }

            void DfsScan_Next() {
                if (isLeaf()) {
                    oneUp();
                    if (hasRight()) {
                        oneRight();
                    } else {
                        oneUp();
                        oneRight();
                    }
                } else {
                    oneUp();
                    goDownLeft();
                }
            }

            void Bfs_Next() {
                if (isRoot()) {
                    oneLeft();
                } else if (isRightMost()) {
                    oneUp();
                    oneLeft();
                    oneLeft();
                } else {
                    oneUp();
                    oneRight();
                }
            }

            Iterator &next() {
                switch (_traversal) {
                    case Traversal::InOrder:
                        inorder_Next();
                        break;
                    case Traversal::PreOrder :
                        preOrder_Next();
                        break;
                    case Traversal::PostOrder :
                        PostOrder_Next();
                        break;
                    case Traversal::DFS :
                        DfsScan_Next();
                        break;
                    case Traversal::BFS :
                        Bfs_Next();
                        break;
                }
                return *this;
            }

        public:
            explicit Iterator(shared_ptr<Node<T>> curr = nullptr, Traversal type = Traversal::InOrder) : _current(curr),
                                                                                                         _traversal(
                                                                                                                 type) {
                if (_current) {
                    switch (type) {
                        case Traversal::InOrder:
                            goDownLeft();
                            break;
                        case Traversal::PostOrder:
                            goDownLeftAndRight();
                            break;
                        case Traversal::PreOrder:
                            break;
                        case Traversal::DFS:
                            goDownLeftAndRight();
                            break;
                        case Traversal::BFS:
                            break;
                    }
                }
            }

            shared_ptr<Node<T>> &getCurr() {
                return _current;
            }

            //    OPERATOR OVERLOADING
            T &operator*() {
                return _current->_val;
            }

            T *operator->() const {
                return &_current->_val;
            }

            Iterator &operator++() {
                next();
                return *this;
            }


            Iterator operator++(int) {
                Iterator temp = *this;
                ++*this;
                return temp;
            }

            bool operator==(const Iterator &other) const {
                return _current == other._current;
            }

            bool operator!=(const Iterator &other) const {
                return !(*this == other);
            }

        };

        void copySubTreeOf(shared_ptr<Node<T>> node) {

            if (node->_left_most) {
                add_left(node->_val, node->_left_most->_val);
                copySubTreeOf(node->_left_most);
            }

            if (node->_right_most) {
                add_right(node->_val, node->_right_most->_val);
                copySubTreeOf(node->_right_most);
            }
        }

        explicit Tree() : _root(nullptr), _k(2) , _treeSize(0){}

        explicit Tree(T root_value, int kids) : _k(kids) {
            this->_root = make_shared<Node<T>>(root_value);
            _treeSize = 1;
        }

        explicit Tree(Tree<T> &other) {
            if (!other._root) {
                this->_root = nullptr;
            } else {
                _root = make_shared<Node<T>>(other._root->_val);
                copySubTreeOf(other._root);
            }
        }

        shared_ptr<Node<T>> getNode(T val) {

            for (auto itr = begin(); itr != end(); itr++) {
                if (*itr == val) {
                    return itr.getCurr();
                }
            }

            return nullptr;
        }

        void updateDepth(shared_ptr<Node<T>> node) {
            node->_depth = node->_parent.lock()->_depth + 1;
            _maxDepth = std::max(_maxDepth, node->_depth);
        }

        Tree<T> &add_root(const T &val) {
            if (!_root) {
                _root = make_shared<Node<T>>(val);
                _root->_depth = 0;
                _treeSize++;
            } else {
                _root->_val = val;
            }
            return *this;
        }

        Tree<T> &add_sub_node(T parent_val, T child_val) {
            auto parent = getNode(parent_val);
            if (parent == nullptr) {
                throw invalid_argument("Parent not found");
            }
            int kids = parent->_children_count;
            if (kids == _k) {
                throw invalid_argument("max kids. cant");
            }
            //parent->_children[parent->number_of_children] = make_shared<Node>(child_val);
            weak_ptr<Node<T>> weakPtr = parent;
            parent->_children.push_back(make_shared<Node<T>>(child_val));
            //parent->_children[kids] = make_shared<Node<T>>(child_val);


            parent->_children[kids]->_parent = weakPtr;

            parent->_children_count++;

            updateDepth((parent->_children[kids]));
            parent->_children[kids]->_val = child_val;
            if(kids == 0){
                parent->_left_most = parent->_children[kids];
            } else if(kids == _k -1){
                parent->_right_most = parent->_children[kids];
            }
            _treeSize++;
            return *this;
        }

        Iterator begin_pre_order() const {
            auto itr = Iterator{_root, Traversal::PreOrder};
            return itr;
        }

        Iterator end_pre_order() const {
            return end();
        }

        Iterator begin_in_order() const {
            auto itr = Iterator{_root, Traversal::InOrder};
            return itr;
        }

        Iterator end_in_order() const {
            return end();
        }

        Iterator begin_post_order() const {
            auto itr = Iterator{_root, Traversal::PostOrder};
            return itr;
        }

        Iterator end_post_order() const {
            return end();
        }

        Iterator begin_bfs_scan() const {
            auto itr = Iterator{_root, Traversal::BFS};
            return itr;
        }

        Iterator end_bfs_scan() const {
            return end();
        }

        Iterator begin_dfs_scan() const {
            auto itr = Iterator{_root, Traversal::DFS};
            return itr;
        }

        Iterator end_dfs_scan() const {
            return end();
        }

        Iterator begin() const {
            auto itr = Iterator{_root, Traversal::InOrder};
            return itr;
        }

        Iterator end() const {
            return Iterator();
        }

        Tree<T> &operator=(const Tree<T> &other) {
            if (&other == this) { return *this; }

            add_root(other._root->_val);

            copySubTreeOf(other._root);

            return *this;
        }

        Tree &operator=(Tree<T> &&other) noexcept {
            *this = move(other);

            return *this;
        }

        static ostream &
        buildTreeStream(const std::string &prefix, shared_ptr<Node<T>> node, bool isLeft, ostream &treeStream) {
            if (node != nullptr) {
                treeStream << prefix;

                string yellowLeft = "\x1B[93m├──\033[0m";
                string blueRight = "\x1B[34m└──\033[0m";
                treeStream << (isLeft ? yellowLeft : blueRight);

                treeStream << "\033[3;43;30m(" << node->_val << ")\033[0m" << endl;

                string yellowBranch = "\x1B[93m│   \033[0m";
                string blueBranch = "\x1B[34m│   \033[0m";
                buildTreeStream(prefix + (isLeft ? yellowBranch : "    "), node->_left_most, true, treeStream);
                buildTreeStream(prefix + (isLeft ? blueBranch : "    "), node->_right_most, false, treeStream);
            }
            return treeStream;
        }

        static ostream &buildTreeStream(shared_ptr<Node<T>> node, ostream &treeStream) {
            return buildTreeStream("", node, false, treeStream) << endl;
        }

        friend ostream &operator<<(ostream &out, const Tree<T> &BT) {
            out << endl;

            buildTreeStream(BT._root, out);

            out << "                  ----BINARY TREE----" << endl << endl << "* Preorder  -> ";

            for (auto it = BT.begin_pre_order(); it != BT.end_pre_order(); ++it) {
                out << (*it) << " ";
            }
            out << endl << "* Inorder   -> ";
            for (auto it = BT.begin_in_order(); it != BT.end_in_order(); ++it) {
                out << (*it) << " ";
            }
            out << endl << "* Postorder -> ";
            for (auto it = BT.begin_post_order(); it != BT.end_post_order(); ++it) {
                out << (*it) << " ";
            }
            return out;
        }
    };

};