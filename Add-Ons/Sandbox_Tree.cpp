#include "Binary_Tree.h"

#include <cassert>
#include <memory>
#include <string>

int main()
{
    using sNode = Node<std::string>;
    auto exampleStringTree = std::make_unique<sNode>("root", sNode("left", sNode("left.left")), sNode("right"));
    assert(sNode::deserialize(exampleStringTree->serialize())->getLeft()->getLeft()->getLabel() == "left.left");

    using iNode = Node<int>;
    auto exampleIntTree = std::make_shared<iNode>(0, iNode(1), iNode(0, iNode(1, iNode(1), iNode(1)), iNode(0)));
    assert(iNode::univalSubtrees(exampleIntTree) == 5);
}