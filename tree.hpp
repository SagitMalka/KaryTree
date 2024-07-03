#pragma once

#include <iostream>
#include <memory>
#include <string>
#include <vector>
#include <queue>

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
using std::queue;
using std::array;
//using std::array;

namespace ariel {
template<typename T, int k = 2>

class Tree {
public:
    class Node {
    public:
        T _val;
        array<shared_ptr<Node>, k> _children;
        weak_ptr<Node> _parent;
        int _depth;
        int _children_count;
        shared_ptr<Node> _left_most;
        shared_ptr<Node> _right_most;

        //Node(T val) : _val(val), _children(k, nullptr) {}
        explicit Node(T value)
            : _val(value), _depth(0), _children_count(0), _left_most(nullptr), _right_most(nullptr) {
            _children.fill(nullptr);
        }


        //        void addChild(shared_ptr<Node> child) {
        //            if (_children.size() < _children_count) {
        //                _children.push_back(child);
        //            } else {
        //                throw out_of_range("Exceeded max number of children");
        //            }
        //        }
    };

    //public:
    //using Node = Node<T, k>;
private:
    shared_ptr<Node> _root;
    //int _k;
    int _maxDepth = 0;
    int _treeSize = 0;


    enum Traversal {
        InOrder, PreOrder, PostOrder, DFS, BFS, Heap
    }; // traversal types

public:
    class Iterator {
        Traversal _traversal = Traversal::InOrder;
        shared_ptr<Node> _current;


    private:
        queue<shared_ptr<Node>> _queue;
        //
        //            void traverseLeft(std::shared_ptr<Node> node) {
        //                while (node) {
        //                    stack.push(node);
        //                    node = node->_left_most;
        //                }
        //                if (!stack.empty()) {
        //                    _current = stack.front();
        //                    stack.pop();
        //                } else {
        //                    _current = nullptr;
        //                }
        //            }

        bool isOnlyChild() const {
            return !isRoot() && _current->_parent.lock()->_children_count == 1;
            //return !isRoot() && isRightMost() && isLeftMost();
        }

        bool isRoot() const {
            auto parent = _current->_parent;
            return !parent.owner_before(weak_ptr<Node>{}) && !weak_ptr<Node>{}.owner_before(parent);
        }

        bool isLeftMost() const {
            return !isRoot() && (_current == _current->_parent.lock()->_left_most);
        }

        bool isRightMost() const {
            return !isRoot() && (_current == _current->_parent.lock()->_right_most);
        }

        bool papaIsRightMost() const {
            auto papa = _current->_parent.lock();
            return papa == papa->_parent.lock()->_right_most;
        }

        bool isLeaf() const {
            return _current->_left_most == nullptr;
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

            } while (_current && (hasLeft() || hasRight()));
        }

        void oneRight() {
            if (hasRight()) {
                _current = _current->_right_most;
            }
        }

        void oneLeft() {
            if (hasLeft()) {
                _current = _current->_left_most;
            } else {
                _current = nullptr;
            }
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
            if (_current == nullptr) {
                return;
            } else if (isRoot()) {
                oneUp();
            } else if (isOnlyChild()) {
                oneUp();
            } else {
                if (isLeaf() && isRightMost()) {
                    oneUp();
                } else if (isLeaf() && !isRightMost()) {
                    oneUp();
                    oneRight();
                    goDownLeft();
                } else {
                    if (isRightMost()) {
                        oneUp();
                    } else {
                        oneUp();
                        oneRight();
                        goDownLeft();
                    }
                }
            }
        }

        void Bfs_Next() {
            //                if (_current == nullptr) {
            //                    return;
            //                }
            //                static bool first_iter = true;
            //                if (isRoot() && !first_iter) {
            //                    this->_current == nullptr;
            //                    //return;
            //                } else if (isRoot() && first_iter) {
            //                    oneLeft();
            //                    first_iter = false;
            //
            //                } else if (isRightMost()) {
            //                    if (isLeaf()) {
            //                        if (papaIsRightMost()) {
            //                            this->_current = nullptr;
            //                        } else {
            //                            oneUp();
            //                            oneUp();
            //                            oneRight();
            //                        }
            //                    } else {   /// isRightMost but not a Leaf
            //                        oneUp();
            //                        oneUp();
            //                        oneRight();
            //                        oneLeft();
            //                    }
            //
            //                    /// isLeftMost
            //                } else {
            //                    if (isLeaf() && isOnlyChild()) {
            //                        oneUp();
            //                        if (!isRoot()) {
            //                            oneUp();
            //                            goDownLeft();
            //                        } else {
            //                            this->_current == nullptr;
            //                        }
            //                    } else {
            //                        oneUp();
            //                        oneRight();
            //                    }
            //
            //                }
            if (_queue.empty()) {
                _current = nullptr;
                return;
            }

            _current = _queue.front();
            _queue.pop();

            for (const auto& child : this->_current->_children) {
                if (child) {
                    _queue.push(child);
                }
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
        explicit Iterator(shared_ptr<Node> curr = nullptr, Traversal type = Traversal::InOrder) : _current(curr),
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
                    goDownLeft();
                    break;
                case Traversal::BFS:
                    _queue.push(_current);
                    break;
                }
            }
        }


        shared_ptr<Node> &getCurr() {
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

    void copySubTreeOf(shared_ptr<Node> node) {

        if (node->_left_most) {
            add_left(node->_val, node->_left_most->_val);
            copySubTreeOf(node->_left_most);
        }

        if (node->_right_most) {
            add_right(node->_val, node->_right_most->_val);
            copySubTreeOf(node->_right_most);
        }
    }
    //explicit Tree() : _root(nullptr), _treeSize(0) {}

    Tree() : _root(nullptr) {}

    explicit Tree(T root_value, int kids) {
        this->_root = make_shared<Node>(root_value, kids);
        _treeSize = 1;
    }

    explicit Tree(Tree<T> &other) {
        if (!other._root) {
            this->_root = nullptr;
        } else {
            _root = make_shared<Node>(other._root->_val);
            copySubTreeOf(other._root);
        }
    }

    ~Tree() {
        clear();
    }

    void clear(shared_ptr<Node> node) {
        if (!node) return;
        for (auto &child: node->_children) {
            clear(child);
        }
    }

    void clear() {
        clear(_root);
        _root.reset();
    }

    shared_ptr<Node> getNode(T val) {
        for (auto itr = begin(); itr != end(); itr++) {
            if (*itr == val) {
                return itr.getCurr();
            }
        }
        return nullptr;
    }

    void updateDepth(shared_ptr<Node> node) {
        node->_depth = node->_parent.lock()->_depth + 1;
        _maxDepth = std::max(_maxDepth, node->_depth);
    }

    Tree<T, k> &add_root(const T &val) {
        if (!_root) {
            _root = make_shared<Node>(val);
            _root->_depth = 0;
            _treeSize++;
        } else {
            _root->_val = val;
        }
        return *this;
    }

    Tree<T, k> &add_sub_node(T parent_val, T child_val) {
        auto parent = getNode(parent_val);
        if (parent == nullptr) {
            throw invalid_argument("Parent not found");
        }
        int kids = parent->_children_count;
        if (kids == k) {
            throw invalid_argument("max kids. cant");
        }
        //parent->_children[parent->number_of_children] = make_shared<Node>(child_val);
        weak_ptr<Node> weakPtr = parent;
        auto new_node = make_shared<Node>(child_val);
        parent->_children[kids] = new_node;
        new_node->_parent = weakPtr;
        //parent->_children.push_back(make_shared<Node<T>>(child_val));
        //parent->_children[kids] = make_shared<Node<T>>(child_val);


        //parent->_children[kids]->_parent = weakPtr;

        parent->_children_count++;

        updateDepth((parent->_children[kids]));
        parent->_children[kids]->_val = child_val;
        if (kids == 0) {
            parent->_left_most = parent->_children[kids];
            //parent->_right_most = parent->_children[kids];
        } else if (kids == k - 1) {
            parent->_right_most = parent->_children[kids];
        }
        _treeSize++;
        return *this;
    }

    shared_ptr<Node> getRoot() const {
        return _root;
    }
    int getKSize() const {
        return k;
    }
    void myHeap() {
        std::vector<T> elements;
        inOrderTraversal(_root, elements);
        std::make_heap(elements.begin(), elements.end(), std::greater<T>());

        // Reconstruct the tree from heap-ordered elements
        rebuildFromHeap(_root, elements);
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

    Tree<T, k> &operator=(const Tree<T> &other) {
        if (&other == this) { return *this; }

        add_root(other._root->_val);

        copySubTreeOf(other._root);

        return *this;
    }

    Tree &operator=(Tree<T> &&other) noexcept {
        *this = move(other);

        return *this;
    }

    void inOrderTraversal(std::shared_ptr<Node> node, std::vector<T> &elements) {
        if (!node) return;
        inOrderTraversal(node->_left_most, elements);
        elements.push_back(node->_val);
        inOrderTraversal(node->_right_most, elements);
    }

    // Helper function to rebuild tree from heap-ordered elements
    void rebuildFromHeap(std::shared_ptr<Node> &node, std::vector<T> &elements) {
        if (!node) return;

        // Set current node value to the top of heap and pop_heap to remove it
        node->_val = elements.front();
        std::pop_heap(elements.begin(), elements.end(), std::greater<T>());
        elements.pop_back();

        // Recursively rebuild left and right subtrees
        rebuildFromHeap(node->_left_most, elements);
        rebuildFromHeap(node->_right_most, elements);
    }

    static ostream &buildTreeStream(const std::string &prefix, shared_ptr<Node> node, bool isLeft, ostream &treeStream) {
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

    static ostream &buildTreeStream(shared_ptr<Node> node, ostream &treeStream) {
        return buildTreeStream("", node, false, treeStream) << endl;
    }

    friend ostream &operator<<(ostream &out, const Tree<T, k> &BT) {
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
        out << endl << "* Bfs -> ";
        for (auto it = BT.begin_bfs_scan(); it != BT.end_bfs_scan(); ++it) {
            out << (*it) << " ";
        }
        out << endl << "* Dfs -> ";
        for (auto it = BT.begin_dfs_scan(); it != BT.end_dfs_scan(); ++it) {
            out << (*it) << " ";
        }
        return out;
    }

    //         friend std::ostream &operator<<(std::ostream &out, const Tree<T, k> &BT) {
    //             out << std::endl;
    //             buildTreeStream(BT._root, "", false, out);
    //             out << "                  ----BINARY TREE----" << std::endl;
    //             out << std::endl << "* Inorder   -> ";
    //             for (auto it = BT.begin_in_order(); it != BT.end_in_order(); ++it) {
    //                 out << (*it) << " ";
    //             }
    //             out << std::endl << "* dfs   -> ";
    //             for (auto it = BT.begin_dfs_scan(); it != BT.end_dfs_scan(); ++it) {
    //                 out << (*it) << " ";
    //             }
    //             out << std::endl;
    //             return out;
    //         }

    //         static std::ostream &buildTreeStream(std::shared_ptr<Node<T>> node, const std::string &prefix,
    //                                              bool isLeft, std::ostream &treeStream) {
    //             if (node != nullptr) {
    //                 treeStream << prefix;
    //                 if (isLeft) {
    //                     treeStream << "├──";
    //                 } else {
    //                     treeStream << "└──";
    //                 }
    //                 treeStream << "(" << node->_val << ")" << std::endl;
    //
    //                 buildTreeStream(node->_left_most, prefix + (isLeft ? "│   " : "    "), true, treeStream);
    //                 buildTreeStream(node->_right_most, prefix + (isLeft ? "│   " : "    "), false, treeStream);
    //             }
    //             return treeStream;
    //         }
};

};
