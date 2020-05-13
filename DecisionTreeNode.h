/*
* Title: Binary Trees
* Author: Isik Ozsoy
* ID: 21703160
* Section: 1
* Assignment: 2
* Description: header file of decisionTree
*/

#ifndef DecisionTreeNode_h
#define DecisionTreeNode_h

class DecisionTreeNode {
private:
    bool isLeaf;
    int featureId; // If it not a leaf node
    int className; // If it is a leaf node
    DecisionTreeNode *leftChild, *rightChild;
    bool* usedFeatures;
public:
    DecisionTreeNode();
    DecisionTreeNode(bool* usedFeatures, int numFeatures);
    void createUsedFeatures(int numFeatures);
    void setProperties(bool isLeaf, int info, int numFeatures);
    bool getIsLeaf();
    int getFeatureId();
    int getClassName();
    DecisionTreeNode* getRightChild();
    DecisionTreeNode* getLeftChild();
    bool* getUsedFeatures();
};

#endif
