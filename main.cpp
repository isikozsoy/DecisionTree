/*
* Title: Algorithm Efficiency and Sorting
* Author: Isik Ozsoy
* ID: 21703160
* Section: 1
* Assignment: 1
* Description: description of your code
*/

#include <iostream>
#include <string>
#include "DecisionTree.h"
#include "DecisionTreeNode.h"

using namespace std;

int main() {

    bool** data = new bool*[8];
    int* label = new int[8];

    data[0] = new bool[3];
    data[1] = new bool[3];
    data[2] = new bool[3];
    data[3] = new bool[3];
    data[4] = new bool[3];
    data[5] = new bool[3];
    data[6] = new bool[3];
    data[7] = new bool[3];

    data[0][0] = true;
    data[1][0] = false;
    data[2][0] = true;
    data[3][0] = false;
    data[4][0] = true;
    data[5][0] = true;
    data[6][0] = false;
    data[7][0] = false;

    data[0][1] = false;
    data[1][1] = false;
    data[2][1] = false;
    data[3][1] = false;
    data[4][1] = true;
    data[5][1] = true;
    data[6][1] = true;
    data[7][1] = true;

    data[0][2] = false;
    data[1][2] = true;
    data[2][2] = true;
    data[3][2] = false;
    data[4][2] = false;
    data[5][2] = true;
    data[6][2] = false;
    data[7][2] = true;

    label[0] = 1;
    label[1] = 1;
    label[2] = 1;
    label[3] = 1;
    label[4] = 2;
    label[5] = 2;
    label[6] = 3;
    label[7] = 3;


    bool** data1 = new bool*[6];
    int* label1 = new int[6];

    data1[0] = new bool[2];
    data1[1] = new bool[2];
    data1[2] = new bool[2];
    data1[3] = new bool[2];
    data1[4] = new bool[2];
    data1[5] = new bool[2];

    data1[0][0] = true;
    data1[1][0] = false;
    data1[2][0] = false;
    data1[3][0] = false;
    data1[4][0] = true;
    data1[5][0] = true;

    data1[0][1] = true;
    data1[1][1] = false;
    data1[2][1] = false;
    data1[3][1] = true;
    data1[4][1] = true;
    data1[5][1] = true;

    label1[0] = 1;
    label1[1] = 2;
    label1[2] = 2;
    label1[3] = 2;
    label1[4] = 3;
    label1[5] = 3;

    bool** data2 = new bool*[2];
    data2[0] = new bool[21];
    data2[1] = new bool[21];
    //data2[2] = new bool[21];

    int* labels2 = new int[2];

    data2[0][0] = 0;
    data2[0][1] = 0;
    data2[0][2] = 0;
    data2[0][3] = 0;
    data2[0][4] = 0;
    data2[0][5] = 0;
    data2[0][6] = 0;
    data2[0][7] = 0;
    data2[0][8] = 0;
    data2[0][9] = 0;
    data2[0][10] = 1;
    data2[0][11] = 0;
    data2[0][12] = 0;
    data2[0][13] = 0;
    data2[0][14] = 0;
    data2[0][15] = 0;
    data2[0][16] = 0;
    data2[0][17] = 0;
    data2[0][18] = 0;
    data2[0][19] = 1;
    data2[0][20] = 1;

    data2[1][0] = 0;
    data2[1][1] = 0;
    data2[1][2] = 0;
    data2[1][3] = 0;
    data2[1][4] = 0;
    data2[1][5] = 0;
    data2[1][6] = 0;
    data2[1][7] = 0;
    data2[1][8] = 0;
    data2[1][9] = 0;
    data2[1][10] = 1;
    data2[1][11] = 0;
    data2[1][12] = 0;
    data2[1][13] = 0;
    data2[1][14] = 0;
    data2[1][15] = 0;
    data2[1][16] = 0;
    data2[1][17] = 0;
    data2[1][18] = 0;
    data2[1][19] = 1;
    data2[1][20] = 1;

    labels2[0] = 3;
    labels2[1] = 8;

    DecisionTree* tree = new DecisionTree();

  // tree->train("data_to_train.txt", 8, 3);

    tree->train("train_data.txt", 498, 21);

    //tree->train("train_data_ex.txt", 30, 10);

    //tree->train((const bool**)data, label, 8, 3);  // Works on dijkstra

    // tree->train((const bool**)data1, label1, 6, 2);   // Works on dijkstra

  // tree->train("train_data_feature.txt", 6, 2);

    tree->print();

    cout << tree->test((const bool**)data2, labels2, 2) << endl;

    cout << tree->test("test_data.txt", 473) << endl;

    for(int i = 0; i< 3; i++)
        delete [] data[i];
    delete [] data;
    delete label;

    for(int i = 0; i < 6; i++)
        delete [] data1[i];
    delete [] data1;
    delete label1;

    for(int i = 0; i < 2; i++)
        delete [] data2[i];
    delete [] data2;
    delete labels2;
    return 0;
}
