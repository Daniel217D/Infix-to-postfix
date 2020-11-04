#pragma once

template<class T>
class BiNode {
private:
    T value;
    BiNode<T> *left = nullptr;
    BiNode<T> *right = nullptr;
public:
    explicit BiNode(T _value, BiNode<T> *_left = nullptr, BiNode<T> *_right = nullptr) : value(_value), left(_left), right(_right){};

    BiNode(BiNode<T> *node) {
        if (node != nullptr) {
            value = node->value;
            if (node->left != nullptr) {
                left = new BiNode<T>(node->left);
            }
            if (node->right != nullptr) {
                right = new BiNode<T>(node->right);
            }
        }
    }

    ~BiNode() {
        delete left;
        delete right;
    }

    T getValue(){
        return value;
    }

    BiNode<T> * getLeft(){
        return left;
    }

    BiNode<T> * getRight(){
        return right;
    }
};
