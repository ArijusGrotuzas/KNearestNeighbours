#include <bits/stdc++.h>
#include <dataset.h>
#include <math.h>

#define FEW 10
#define SOME 50
#define MANY 100

// Find the largest integer in the array
int largestInt (int arr[], int len){
    int largest = 0, pos = 0;

    for(int i = 0; i < len; i++){
        if (arr[i] > largest){
            largest = arr[i];
            pos = i;
        }
    }

    return pos;
}

// Compare two points based on their distances
bool compareDistance(point a, point b){
    return (a.distance < b.distance);
};

// An n-dimensional euclidean distance
double EuclideanDistance(vector<double> a, vector<double> b){
    if (a.size() == b.size()){
        double squaredDist = 0.0;

        for(int i = 0; i < a.size(); i++){
            squaredDist += (a[i] - b[i]) * (a[i] - b[i]);
        }
        return sqrt(squaredDist);
    }
    else{
        return 0.0;
    }
}

// Classify a point as either belonging to class 1 or class 0
int KNearestNeighbourClass(vector<point>* arr, int classNum, int k, point test){

    // Calculate the distance from a given point and each point in the dataset
    for (vector<point>::iterator i = arr->begin(); i != arr->end(); ++i){
        point p = *i;
        p.distance = EuclideanDistance(p.features, test.features);
        *i = p;
    }

    // Sort points array based on the distance
    sort(arr->begin(), arr->end(), compareDistance);

    // Array for class freq
    int classFrequencies[classNum] = {};

    // Calculate the class frequencies in neighbors
    for (vector<point>::iterator i = arr->begin(); i != arr->begin() + k; i++){
        point p = *i;
        classFrequencies[p.label] += 1;
    }

    return largestInt(classFrequencies, classNum);
}

// Classify multiple instances
void classifyKNN(vector<point>* train, vector<point>* test, int neighbours, int classNum){
    for (vector<point>::iterator i = test->begin(); i != test->end(); ++i){
        point p = *i;
        cout << "New point's class value: " << KNearestNeighbourClass(train, classNum, neighbours, p) << endl;
    }
}

int main()
{
    // Specify the dataset file
    string trainFilename = "iris_train.csv";
    string testFilename = "iris_test.csv";

    // Specify the filename, and optional argument of reading class values
    dataset train(trainFilename);
    dataset test(testFilename, false);

    // Read the lines in the csv file
    train.readDataset();
    test.readDataset();

    // Print the number of instances in the training dataset
    printf("Number of instances: %d \n", train.getLenght());
    cout << endl;

    // Print n number of entries in the dataset
    train.printDataset(FEW);
    cout << endl;

    classifyKNN(train.getData(), test.getData(), 10, train.getClassNum());

    return 0;
}
