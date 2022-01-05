#include <bits/stdc++.h>
#include <dataset.h>
#include <math.h>

#define FEW 10
#define SOME 50
#define MANY 100

// Structure for returning largest integer and it's position in the array
struct int2{
    int x, y;
};

// Find the largest integer in the array
int2 largestInt (int arr[], int len){
    int largest = 0, pos = 0;

    for(int i = 0; i < len; i++){
        if (arr[i] > largest){
            largest = arr[i];
            pos = i;
        }
    }

    int2 result = {largest, pos};

    return result;
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
int KNearestNeighbourClass(vector<point> arr, int classNum, int k, point p){

    // Calculate the distance from a given point and each point in the dataset
    for (int i = 0; i < arr.size(); i ++)
        arr[i].distance = EuclideanDistance(arr[i].features, p.features);

    // Sort points array based on the distance
    sort(arr.begin(), arr.end(), compareDistance);

    // Array for class freq
    int classFrequencies[classNum] = {};

    // Calculate the class frequencies in neighbors
    for (int i = 0; i < k; i++){
        classFrequencies[arr[i].label] += 1;
    }

    int2 largest = largestInt(classFrequencies, classNum);

    return largest.y;
}

// Classify multiple instances
void classifyKNN(vector<point> train, vector<point> test, int neighbours){
    for (int i = 0; i < test.size(); i ++){
        cout << "New point's class value: " << KNearestNeighbourClass(train, 3, neighbours, test[i]) << endl;
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

    int len = train.getLenght();
    printf("Number of instances: %d \n", len);
    cout << endl;

    // Read the lines in the csv file
    train.readDataset();
    test.readDataset();

    // Print n number of entries in the dataset
    train.printDataset(FEW);
    cout << endl;

    // Get the data
    vector<point> trainData = train.getData();
    vector<point> testData = test.getData();

    classifyKNN(trainData, testData, 10);

    return 0;
}
