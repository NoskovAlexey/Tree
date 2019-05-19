#include <iostream>
#include <vector>

using namespace std;

class Container
{
public:
    virtual void insert(int value) = 0;
    virtual bool exists(int value) = 0;
    virtual void remove(int value) = 0;
    virtual void print() = 0;
};

template <typename TreeType>
class SimpleTree : public Container {
private:
    template <typename NodeType>
    struct Node {
        NodeType value;
        Node *left, *right, *parent;

        Node(NodeType _value = 0) {
            value = _value;
            left = NULL;
            right = NULL;
            parent = NULL;
        }

        NodeType get_value() {
            return value;
        }

    };
    Node<TreeType> *root;
    size_t count;
public:
    SimpleTree() {
        root = NULL;
        count = 0;
    }

    void insert(TreeType value) {
        Node<TreeType> *n = new Node<TreeType>(value);
        Node<TreeType> *ptr = NULL;
        Node<TreeType> *ptr1 = NULL;

        ptr = root;

        while (ptr != 0) {
            ptr1 = ptr;
            if (value < ptr->value)
                ptr = ptr->left;
            else
                ptr = ptr->right;
        }

        n->parent = ptr1;

        if (ptr1 == 0)
            root = n;
        else {
            if (value < ptr1->value)
                ptr1->left = n;
            else
                ptr1->right = n;
        }

        count++;
    }

    Node<TreeType>* find_min(Node<TreeType>* x)
    {
        while(x->left != 0)
            x = x->left;
        return x;
    }

    Node<TreeType>* find_node(Node<TreeType> *n, const TreeType &value) {
        if (n == 0 || value == n->value)
            return n;

        if (value > n->value)
            return find_node(n->right, value);
        else
            return find_node(n->left, value);
    }

    Node<TreeType>* find_succsessor(const TreeType &value) {
        Node<TreeType>* x = find_node(root, value);
        Node<TreeType>* y;

        if (x == 0)
            return 0;

        if (x->right != 0)
            return find_min(x->right);

        y = x->parent;

        while(y != 0 && x == y->right) {
            x = y;
            y = y->parent;
        }
        return y;
    }

    void delete_node (Node<TreeType> *value) {
        Node<TreeType> *y;
        Node<TreeType> *x;
        if(value->left == 0 || value->right == 0)
            y = value;
        else
            y = find_succsessor(value->value);
        if(y->left != 0)
            x = y->left;
        else
            x = y->right;
        if (x !=0)
            x->parent = y->parent;
        if (y->parent == 0)
            root = x;
        else
        {
            if (y== (y->parent)->left)
                (y->parent)->left=x;
            else
                (y->parent)->right=x;
        }
        if (y != value)
            value->value = y->value;
        delete y;
    }

    void walk_through(Node<TreeType> *n) {
        if (n != 0) {
            walk_through(n->left);
            cout << n->value << endl;
            walk_through(n->right);
        }
    }

    void print() {
        walk_through(root);
    }

    Node<TreeType>* get_root() {
        return root;
    }

    bool exists(TreeType value) {
        Node<TreeType> *ptr;
        ptr = this->find_node(root, value);
        if (ptr == NULL)
            return false;
        else
            return true;
    }

    void remove(int value) {
        if (this->exists(value)) {
            this->delete_node(this->find_node(root, value));
        }
    }

    size_t get_count() {
        return count;
    }

};



int main()
{

    return 0;
}
