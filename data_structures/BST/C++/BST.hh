#pragma once

#include <iostream>
#include <memory>

template <typename T>
class BST
{
    struct Node
    {
        T data;
        Node* parent = nullptr;
        std::unique_ptr<Node> left;
        std::unique_ptr<Node> right;

        Node(T data) : data(data) {}
        Node(T data, Node* parent) : Node(data)
        {
            this->parent = parent;
        }
    };

    std::unique_ptr<Node> root;

public:
    BST(T data) : root(std::make_unique<Node>(data)) {}
    void show_postorder() const
    {
        _traversal(this->root.get());
    }
    bool search(T data) const
    {
        return _search(this->root.get(), data);
    }
    T get_successor(T data) const
    {
        return _get_successor(this->root.get(), data);
    }
    void insert(T data)
    {
        _insert(this->root, data, this->root.get());
    }
    void delete_node(T data)
    {
        this->root = _delete_node(this->root, data);
    }

private:
    T _get_min(Node* root) const
    {
        Node* temp = root;
        while (temp->left)
            temp = temp->left.get();
        return temp->data;
    }

    void _traversal(const Node* root) const
    {
        if (root)
        {
            _traversal(root->left.get());
            _traversal(root->right.get());
            std::cout << root->data << " ";
        }
    }

    void _insert(std::unique_ptr<Node>& node, T data, Node* parent)
    {
        if (!node)
        {
            node = std::make_unique<Node>(data, parent);
            return;
        }
        return (data >= node->data)
                ? _insert(node->right, data, node.get())
                : _insert(node->left, data, node.get());
    }

    T _get_successor(const Node* root, T data) const
    {
        if (!root) return -1;
        if (data == root->data)
        {
            Node* right = root->right.get();
            auto succ_lambda = [ cur = root, parent = root->parent ]() mutable
            {
                while (cur == parent->right.get())
                {
                    cur = parent;
                    parent = parent->parent;
                    if (!parent) return -1;
                }
                return parent->data;
            };
            return (right)
                    ? _get_min(right)
                    : succ_lambda();
        }
        return (data > root->data)
                ? _get_successor(root->right.get(), data)
                : _get_successor(root->left.get(), data);
    }

    std::unique_ptr<Node> _delete_node(std::unique_ptr<Node>& root, T data)
    {
        if (!root) return std::move(root);

        if (data == root->data)
        {
            if (!root->right)
            {
                root = std::move(root->left);
            }
            else if (!root->left)
            {
                root = std::move(root->right);
            }
            else
            {
                T replacer = _get_min(root->right.get());
                root->data = replacer;
                root->right = _delete_node(root->right, replacer);
            }
        }
        else if (data > root->data)
            root->right = _delete_node(root->right, data);
        else
            root->left = _delete_node(root->left, data);
        return std::move(root);
    }

    bool _search(const Node* root, T data) const
    {
        if (!root) return false;
        if (data == root->data) return true;
        return (data > root->data)
                ? _search(root->right.get(), data)
                : _search(root->left.get(), data);
    }
};