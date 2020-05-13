/*
* Title: Binary Trees
* Author: Isik Ozsoy
* ID: 21703160
* Section: 1
* Assignment: 2
* Description: header file of decisionTree
*/

#include "DecisionTreeNode.h"
#include <iostream>
#include "DecisionTree.h"

using namespace std;

DecisionTreeNode :: DecisionTreeNode() {
    usedFeatures = 0;
    isLeaf = true;
    featureId = -1;
    className = -1;
    leftChild = 0;
    rightChild = 0;
}

DecisionTreeNode :: DecisionTreeNode(bool* usedFeatures, int numFeatures)
{
    this->usedFeatures = new bool[numFeatures];
    for(int i = 0; i < numFeatures; i++)
        this->usedFeatures[i] = usedFeatures[i];
    isLeaf = true;
    featureId = -1;
    className = -1;
    leftChild = 0;
    rightChild = 0;
}

bool DecisionTreeNode :: getIsLeaf()
{
    return isLeaf;
}

int DecisionTreeNode :: getFeatureId()
{
    return featureId;
}

int DecisionTreeNode :: getClassName()
{
    return className;
}

DecisionTreeNode* DecisionTreeNode :: getRightChild()
{
    return rightChild;
}

DecisionTreeNode* DecisionTreeNode :: getLeftChild()
{
    return leftChild;
}

bool* DecisionTreeNode :: getUsedFeatures()
{
    return usedFeatures;
}

void DecisionTreeNode :: createUsedFeatures(int numFeatures) {
    usedFeatures = new bool[numFeatures];
    for(int i = 0; i < numFeatures; i++)
        usedFeatures[i] = false;
}

void DecisionTreeNode :: setProperties(bool isLeaf, int info, int numFeatures) {
    this->isLeaf = isLeaf;
    if(isLeaf)
        className = info;
    else {
        featureId = info;
        usedFeatures[featureId] = true;
        leftChild = new DecisionTreeNode(usedFeatures, numFeatures);
        rightChild = new DecisionTreeNode(usedFeatures, numFeatures);
    }
}
