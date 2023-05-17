#ifndef ASD_LABS_2021_AVLNODEIMPLEMENTATION_H
#define ASD_LABS_2021_AVLNODEIMPLEMENTATION_H

#include "avlNode.h"

namespace avl {

    template<typename Key>
    void checkNullRoot(Node<Key> *n) {
        if (n == nullptr)
            throw std::invalid_argument("Root doesn't exist");
    }

    template<typename Key>
    unsigned char getNodeHeight(Node<Key> *const &n) {
        if (n == nullptr) {
            return 0;
        }
        return n->nodeHeight;
    }

    template<typename Key>
    void calculateHeight(Node<Key> *const &n) {
        if (n != nullptr) {
            unsigned char heightRight = getNodeHeight(n->right());
            unsigned char heightLeft = getNodeHeight(n->left());
            if (heightRight > heightLeft) {
                n->nodeHeight = 1 + heightRight;
            } else {
                n->nodeHeight = 1 + heightLeft;
            }
        }
    }

    template<typename Key>
    void rotate(Node<Key> *&n, Side s) {
        Node<Key> *temp;
        temp = n->children[!s];
        n->children[!s] = temp->children[s];
        temp->children[s] = n;
        n = temp;
        calculateHeight(n->children[s]);
        calculateHeight(n);
    }

    template<typename Key>
    int balanceValue(Node<Key> *const &n) {
        if (n == nullptr) {
            return 0;
        }
        return (int) (getNodeHeight(n->left()) - getNodeHeight(n->right()));
    }

    template<typename Key>
    void restoreBalance(Node<Key> *&n) {
        if (n == nullptr) {
            return;
        }
        if (balanceValue(n) < -1) {
            if (balanceValue(n->right()) > 0) {
                rotate(n->right(), RIGHT);
            }
            rotate(n, LEFT);
        } else if (balanceValue(n) > 1) {
            if (balanceValue(n->left()) < 0) {
                rotate(n->left(), LEFT);
            }
            rotate(n, RIGHT);
        } else {
            calculateHeight(n);
        }
    }

    template<typename Key>
    void insertSubtreeAndBalance(Node<Key> *&n, Key const &k) {
        if (n == nullptr) {
            n = new Node<Key>{k, Node<Key>::NO_CHILD, 1};
        } else if (k == n->key) {
            return;
        } else {
            Side s = k < n->key ? LEFT : RIGHT;
            insertSubtreeAndBalance(n->children[s], k);
            restoreBalance(n);
        }
    }

    template<typename Key>
    void copy(Node<Key> *&n1, Node<Key> *const &n2) {
        if (n2 == nullptr) { return; }
        n1 = new Node<Key>{n2->key, Node<Key>::NO_CHILD, 1};
        copy(n1->left(), n2->left());
        copy(n1->right(), n2->right());
    }

    template<typename Key>
    bool exist(Node<Key> *const &n, const Key &k) noexcept {
        if (n == nullptr) {
            return false;
        } else if (k == n->key) {
            return true;
        } else if (k < n->key) {
            return exist(n->left(), k);
        }
        return exist(n->right(), k);
    }

    template<typename Key>
    std::ostream &showIndented(Node<Key> *n, std::ostream &out, std::string before,
                               bool isright) {
        out << before;
        if (not n) {
            out << ".\n";
        } else {
            if (not before.empty()) {
                before[before.size() - 2] = ' ';
                if (isright) {
                    before[before.size() - 3] = ' ';
                }
            }
            out << n->key << std::endl;
            if (n->children != Node<Key>::NO_CHILD) {
                for (Side s: {LEFT, RIGHT}) {
                    showIndented(n->children[s], out, before + "|_ ", s);
                }
            }
        }
        return out;
    }

    //Min : Side = LEFT
    //Max : Side = RIGHT
    template<typename Key>
    Key const &minMax(Node<Key> *n, Side s) {
        checkNullRoot(n);
        if (n->children[s] != nullptr) {
            return minMax(n->children[s], s);
        }
        return n->key;
    }

    //DeleteMin : Side = LEFT
    //DeleteMax : Side = RIGHT
    template<typename Key>
    void deleteNode(Node<Key> *&n, Side s) {
        checkNullRoot(n);
        if (n->children[s] != nullptr) {
            deleteNode(n->children[s], s);
            restoreBalance(n);
        } else { // n is the minimum
            Node<Key> *tmp = n->children[!s];
            delete n;
            n = tmp;
        }
    }

    template<typename Key>
    void destructor(Node<Key> *&node) {
        if (node != nullptr) {
            if (node->right() != nullptr) {
                destructor(node->right());
            }
            if (node->left() != nullptr) {
                destructor(node->left());
            }
        }
        delete node;
    }

    template<typename Key>
    std::ostream &display(Node<Key> const *n, std::ostream &os) {
        if (n) {
            os << n->key << '(';
            display(n->children[LEFT], os);
            os << ',';
            display(n->children[RIGHT], os);
            os << ')';
        } else {
            os << '.';
        }
        return os;
    }

    template<typename Key>
    Node<Key> *extractMin(Node<Key> *&n) {
        if (n->left() != nullptr) {
            return extractMin(n->left());
        }
        Node<Key> *tmp = n;
        n = n->right();
        return tmp;
    }

    template<typename Key>
    void deleteKey(Node<Key> *&n, Key k) {
        checkNullRoot(n);
        if (k < n->key) {
            deleteKey(n->left(), k);
        } else if (k > n->key) {
            deleteKey(n->right(), k);
        } else {
            Node<Key> *tmp = n;
            if (n->left() == nullptr) {
                n = n->right();
            } else if (n->right() == nullptr) {
                n = n->left();
            } else {
                Node<Key> *m = extractMin(n->right());
                m->right() = n->right();
                m->left() = n->left();
                n = m;
            }
            delete tmp;
        }
        restoreBalance(n);
    }
}

#endif //ASD_LABS_2021_AVLNODEIMPLEMENTATION_H
