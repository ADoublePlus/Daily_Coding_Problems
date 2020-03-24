#include <iostream>
#include <memory>
#include <optional>
#include <queue>

template <class C>
class Node
{
    private:
        C label;
        std::shared_ptr<Node<C>> left;
        std::shared_ptr<Node<C>> right;

    public:
        Node(const C& name, std::optional<Node<C>>&& leftChild = {},
                            std::optional<Node<C>>&& rightChild = {}) : label(name),
                                                                        left(leftChild ? std::make_shared<Node<C>>(*leftChild) : nullptr),
                                                                        right(rightChild ? std::make_shared<Node<C>>(*rightChild) : nullptr) {}

        inline auto getLabel() const -> C { return this->label; }
        inline auto getLeft() const -> std::shared_ptr<Node<C>> { return this->left; }
        inline auto getRight() const -> std::shared_ptr<Node<C>> { return this->right; }
        inline auto setLeft(std::shared_ptr<Node<C>> leftChild) { this->left = leftChild; }
        inline auto setRight(std::shared_ptr<Node<C>> rightChild) { this->right = rightChild; }

        auto serialize() const -> std::string;
        static auto deserialize(std::string) -> std::shared_ptr<Node<C>>;
        static auto _deserialize(std::queue<std::string>&) -> std::shared_ptr<Node<C>>;

        static auto univalSubtrees(const std::shared_ptr<Node<C>>&) -> int;
};

// Only works for data-types that support the equality-operator
template <class C>
int Node<C>::univalSubtrees(const std::shared_ptr<Node<C>>& root)
{
    if (!root)
        return 0;

    if (!root->getLeft() && !root->getRight())
        return 1;

    if (!root->getLeft() && (root->getLabel() == root->getRight()->getLabel()))
        return 1 + Node::univalSubtrees(root->getRight());

    if (!root->getRight() && (root->getLabel() == root->getLeft()->getLabel()))
        return 1 + Node::univalSubtrees(root->getLeft());

    if (root->getLabel() == root->getLeft()->getLabel() &&
        root->getLabel() == root->getRight()->getLabel())
        return 1 + Node::univalSubtrees(root->getLeft()) + Node::univalSubtrees(root->getRight());
    else 
        return Node::univalSubtrees(root->getLeft()) + Node::univalSubtrees(root->getRight());
}

// Recursively building up the tree again
template <class C>
std::shared_ptr<Node<C>> Node<C>::_deserialize(std::queue<std::string>&) {}

template <>
std::shared_ptr<Node<std::string>> Node<std::string>::_deserialize(std::queue<std::string>& tree)
{
    std::shared_ptr<Node<std::string>> newNode;

    if (!tree.empty())
    {
        std::string label(tree.front());
        tree.pop();

        if (label != "#")
        {
            newNode = std::make_shared<Node<std::string>>(label);
            newNode->setLeft(_deserialize(tree));
            newNode->setRight(_deserialize(tree));
        }
        else 
        {
            newNode = nullptr;
        }
    }

    return newNode;
}

// For a simplistic appraoch when rebuilding the tree
// add all labels and empty leaves into a queue
template <class C>
std::shared_ptr<Node<C>> Node<C>::deserialize(std::string) {}

template <>
std::shared_ptr<Node<std::string>> Node<std::string>::deserialize(std::string tree)
{
    std::string temp;
    std::queue<std::string> list;

    for (char& ch : tree)
    {
        if (ch == ' ')
        {
            list.push(temp);
            temp.clear();
        }
        else 
        {
            temp += ch;
        }
    }

    list.push(temp);
    return _deserialize(list);
}

// Storing the tree in a preordered manner
// String encodings:
//      ' ' - separates leaves
//      '#' - represents an empty leaf
template <class C>
std::string Node<C>::serialize() const
{
    std::cerr << "Cannot serialize tree - missing template specialization";
    return "";
}

template <>
std::string Node<std::string>::serialize() const
{
    // Mark current node as having no children
    if (!this->left && !this->right)
        return this->label + " # #";

    // Mark current node as only having a left child 
    if (this->left && !this->right)
        return this->label + ' ' + this->left->serialize() + " #";

    // Mark current node as only having a right child
    if (!this->left && this->right)
        return this->label + " # " + this->right->serialize();

    // Build the string recursively 
    return this->label + ' ' + this->left->serialize() + ' ' + this->right->serialize() + ' ';
}