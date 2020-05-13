
/*
* Title: Binary Trees
* Author: Isik Ozsoy
* ID: 21703160
* Section: 1
* Assignment: 2
* Description: header file of decisionTree
*/

#include "DecisionTreeNode.h"
#include <cmath>
#include <iostream>
#include <limits>

using namespace std;

class DecisionTree
{
private:
    DecisionTreeNode* root;
    bool trained;
    int numFeatures;

public:
    DecisionTree();
    void train(const bool**, const int*, const int, const
               int);
    void train(const string, const int, const int);
    int predict(const bool*);
    double test(const bool**, const int*, const int);
    double test(const string, const int);
    void print();
    void build(const bool** data, const int* labels, const
               int numSamples, const int numFeatures, bool* usedSamples, DecisionTreeNode* node);
    DecisionTreeNode* getRoot();
    void print(DecisionTreeNode* node, string str);
};

static double calculateEntropy(const int* classCounts, const int numClasses)
{
    double sum = 0;
    double result = 0;
    for(int i = 0; i < numClasses; ++i)
        sum += classCounts[i];
    if(sum == 0)
        return 0;
    for(int i = 0; i < numClasses; ++i)
    {
        if(classCounts[i] != 0)
            result += (double)classCounts[i] / (double)sum * (double)log2((double)classCounts[i] / (double)sum);
    }
    return (double)(-1) * result;
}

static double calculateInformationGain(const bool** data, const int* labels,
                                       const int numSamples, const int numFeatures, const bool* usedSamples,
                                       const int featureId)
{
    // We know that labels are from 1 to N so it gives us numClasses
   int numClasses = 0;
    for(int i = 0; i < numSamples; i++){
        if(labels[i] > numClasses)
            numClasses = labels[i];
    }

    int* classCounts = new int[numClasses];
    for(int i = 0; i < numClasses; i++)
        classCounts[i] = 0;

    for(int i = 0; i < numSamples; i++) {
        if(usedSamples[i])
            classCounts[labels[i] - 1]++;
    }
    double hP = calculateEntropy(classCounts, numClasses);
    delete [] classCounts;

    int numClassesR = 0;
    int numClassesL = 0;
    int* classCountsR = new int[numClasses];
    int* classCountsL = new int[numClasses];

    for(int i = 0; i < numClasses; i++){
        classCountsR[i] = 0;
        classCountsL[i] = 0;
    }
    for(int i = 0; i < numSamples; i++){
        if(usedSamples[i]) {
            if(data[i][featureId]) {
                numClassesR++;
                classCountsR[labels[i] - 1]++;
            }
            else {
                numClassesL++;
                classCountsL[labels[i] - 1]++;
            }
        }
    }
    double hR = calculateEntropy(classCountsR, numClasses);
    double hL = calculateEntropy(classCountsL, numClasses);

   delete [] classCountsL;
   delete [] classCountsR;

    double hS = hP - (double) numClassesR / (double)(numClassesL + numClassesR) * hR
    - (double) numClassesL / (double)(numClassesL + numClassesR) * hL;
return hS;
}


