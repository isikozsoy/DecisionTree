
/*
* Title: Binary Trees
* Author: Isik Ozsoy
* ID: 21703160
* Section: 1
* Assignment: 2
* Description: cpp file of decisionTree
*/

#include "DecisionTree.h"
#include "DecisionTreeNode.h"
#include <iostream>
#include <fstream>
#include <string>
#include <string.h>

using namespace std;

DecisionTree :: DecisionTree()
{
    root = new DecisionTreeNode();
    trained = false;
    numFeatures = 0;
}

DecisionTreeNode* DecisionTree :: getRoot()
{
    return root;
}

void DecisionTree::train(const bool** data, const int* labels, const
                         int numSamples, const int numFeatures)
{
    this->numFeatures = numFeatures;
    trained = true;
    bool* usedSamples = new bool[numSamples];
    for(int i = 0; i < numSamples; i++)
        usedSamples[i] = true;
    root->createUsedFeatures(numFeatures);
    build(data, labels, numSamples, numFeatures, usedSamples, root);
}

void DecisionTree :: build(const bool** data, const int* labels, const
                           int numSamples, const int numFeatures, bool* usedSamples, DecisionTreeNode* node)
{
    // nodeInfo will be className or featureId
    int nodeInfo = -1;
    bool* usedSamplesR = new bool[numSamples];
    bool* usedSamplesL = new bool[numSamples];
    // First we check whether the usedSamples are leaf or not
    bool isLeaf = true;
    for(int i = 0; i < numSamples && isLeaf; i++)
    {
        for(int j = i + 1; j < numSamples && isLeaf; j++)
        {
            if(usedSamples[i] && usedSamples[j])
            {
                if(labels[i] != labels[j])
                    isLeaf = false;
            }
        }
    }
    // Here we calculate the number of classes and
    // number of samples of each classes
    int numClasses = 0;
    for(int i = 0; i < numSamples; i++)
    {
        if(labels[i] > numClasses)
            numClasses = labels[i];
    }

    int* classCounts = new int[numClasses];
    for(int i = 0; i < numClasses; i++)
        classCounts[i] = 0;

    for(int i = 0; i < numSamples; i++)
    {
        if(usedSamples[i])
            classCounts[labels[i] - 1]++;
    }
    // If the node is leaf we set nodeInfo to className
    if(isLeaf)
    {
        for(int i = 0; i < numClasses; i++)
        {
            if(classCounts[i] != 0)
            {
                nodeInfo = i+1;
                break;
            }
        }

    }
    else
    {
        // In else firstly we will check
        // there is any remaining feature or not
        bool featureLeft = false;
        bool* usedFeatures = node->getUsedFeatures();
        for(int i = 0; i < numFeatures && !featureLeft; i++)
        {
            if(!usedFeatures[i])
                featureLeft = true;
        }
        // If there is no feature left we set isLeaf to true
        // and nodeInfo to className
        if(!featureLeft)
        {
            isLeaf = true; // Since there is no feature left

            // Find the class with grater number of samples
            // repeatedClass will hold the index of repeated
            // class in classCounts
            int repeatedClass = 0;
            int current = classCounts[0];
            for(int i = 1; i < numClasses; i++)
            {
                if(current < classCounts[i])
                {
                    current = classCounts[i];
                    repeatedClass = i;
                }
            }                        // the most repeated class in labels
            nodeInfo = repeatedClass + 1;
        }
        // If the node is not leaf and there are features left
        // we will find the feature to split it
        else
        {
            // We set nodeInfo to featureId which is used to split
            // Here we find feature with the greatest informationGain
            double infoGain = -1;
            for(int i = 0; i < numFeatures; i++)
            {
                if(!usedFeatures[i])
                {
                    if(infoGain < calculateInformationGain(data, labels, numSamples, numFeatures, usedSamples, i))
                    {
                        infoGain = calculateInformationGain(data, labels, numSamples, numFeatures, usedSamples, i);
                        nodeInfo = i;
                    }
                }

            }
            // We determined the usedSamples of left and right children if the node is not leaf
            for(int i = 0; i < numSamples; i++)
            {
                usedSamplesL[i] = usedSamples[i];
                usedSamplesR[i]= usedSamples[i];
                if(usedSamples[i])
                {
                    if(data[i][nodeInfo])
                        usedSamplesL[i] = false;
                    else
                        usedSamplesR[i] = false;
                }
            }
        }
    }
    // We set properties of current node
    node->setProperties(isLeaf, nodeInfo, numFeatures);
    if(!isLeaf)
    {
        // If it is not leaf we split it and called build function for left and right
        DecisionTreeNode* rightChild = node->getRightChild();
        DecisionTreeNode* leftChild = node->getLeftChild();

        build(data, labels, numSamples, numFeatures, usedSamplesL, leftChild);
        build(data, labels, numSamples, numFeatures, usedSamplesR, rightChild);
    }
}

void DecisionTree::train (const string fileName, const int numSamples, const int numFeatures)
{
    // We set trained to true
    trained = true;
    string str;		// str contains lines in file
    ifstream file;
    file.open(fileName);	// We open file

    int* labels = new int[numSamples];  // We create labels

    bool** data = new bool*[numSamples];	// We create data
    for (int i = 0; i < numSamples; i++)
    {
        data[i] = new bool[numFeatures];
    }
    // The loop is executed until there is no new line
    for (int i = 0; getline(file, str); i++)
    {
        int cur = str.find(" "); // We find the first index containing space
        int j = 0;
        while (cur != std::string::npos)
        {
            string dataInfo = str.substr(0, cur);
            if( std::stoi(dataInfo) == 1) // we assign values to data
                data[i][j] = true;
            else
                data[i][j] = false;
            str.erase(0, cur + 1);
            j++;
            cur = str.find(" ");
        }
        if(i != numSamples)
            labels[i] = std::stoi(str); // we assign label
    }

    file.close(); // we close file
    // After initializing data and labels we call train function to build tree
    train((const bool**)data, labels, numSamples, numFeatures);
    delete[] labels;
    for (int i = 0; i < numSamples; i++)
    {
        //delete[] data[i];
        delete[] data[i];
    }
    delete[] data;
}

int DecisionTree :: predict(const bool* data)
{
    if(trained)
    {
        DecisionTreeNode* node = root;
        while(!node -> getIsLeaf())
        {
            if(data[node -> getFeatureId()])
                node = node -> getRightChild();
            else
                node = node -> getLeftChild();
        }
        return node -> getClassName();
    }
    return -1;
}

double DecisionTree :: test(const bool** data, const int* labels, const int numSamples)
{
    double correctPred = 0;
    if(trained)
    {
        for(int i = 0; i < numSamples; i++)
        {
            if(labels[i] == predict((const bool*)data[i]))
                correctPred++;
        }
        return correctPred / (double) numSamples;
    }
    return -1;
}

double DecisionTree :: test(const string fileName, const int numSamples)
{
    if(trained)
    {
        // I copied reading file part from train function
        string str;		// str contains lines in file
        ifstream file;
        file.open(fileName);	// we open file

        int* labels = new int[numSamples];  // initialize label

        bool** data = new bool*[numSamples];	// initialize datas
        for (int i = 0; i < numSamples; i++)
        {
            data[i] = new bool[numFeatures];
        }

        for (int i = 0; getline(file, str); i++)		// until there is no new line in file
        {
            int cur = str.find(" "); // we find the first index containing space
            int j = 0;
            while (cur != std::string::npos)
            {
                string dataInfo = str.substr(0, cur);
                if( std::stoi(dataInfo) == 1) // we assign values to data
                    data[i][j] = true;
                else
                    data[i][j] = false;
                str.erase(0, cur + 1);
                j++;
                cur = str.find(" ");
            }
            if(i != numSamples)
                labels[i] = std::stoi(str); // we assign label
        }

        file.close(); // we close file
        return test((const bool**)data, labels, numSamples);
    }
    return -1;
}

void DecisionTree :: print()
{
    {
        if(trained)
        {
            string str = "";
            print(root, str);

        }
        else
            cout << "Your tree is not trained yet." << endl;
    }
}

void DecisionTree :: print(DecisionTreeNode* node, string str)
{
    if(node->getIsLeaf())
    {
        if(node->getClassName()== -1)
            cout << str << "no sample" << endl;
        else
            cout << str << "class = " << node->getClassName() << endl;
        str += "\t";
        return;
    }
    cout << str + "F" << node->getFeatureId() << endl;
    str += "\t";
    print(node->getLeftChild(), str);
    print(node->getRightChild(), str);
}
