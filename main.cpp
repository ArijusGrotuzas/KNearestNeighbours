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
        //arr[i].distance = sqrt((arr[i].x - p.x) * (arr[i].x - p.x) + (arr[i].y - p.y) * (arr[i].y - p.y));

    // Sort points array based on the distance
    sort(arr.begin(), arr.end(), compareDistance);

    // Array for class freq
    int classFrequencies[classNum] = {};

    // Calculate the class frequencies in neighbors
    for (int i = 0; i < k; i++){
        if (arr[i].label == i){
            classFrequencies[i]+=1;
        }
    }

    int2 largest = largestInt(classFrequencies, classNum);

    // Return the class value of highest frequency
    return largest.y;
}

int main()
{
    // Specify the dataset file
    string filename = "Raisin_Dataset.csv";

    // Specify the filename, and optional argument of reading class values
    dataset frame(filename);

    int len = frame.getLenght();

    printf("Number of instances: %d \n", len);
    cout << endl;

    // Read the lines in the csv file
    frame.readDataset();

    // Print n number of entries in the dataset
    frame.printDataset(FEW);
    cout << endl;

    // Get the data
    vector<point> data = frame.getData();

    // A set of test features, the real class value is 1
    vector<double> t = {85609, 512.0817743, 215.2719758, 0.907345395, 89197, 0.632019963, 1272.862};

    // Classify the point to one of the two classes
    point test = {t};

    printf("New point's class value: %d", KNearestNeighbourClass(data, 2, 3, test));

    return 0;
}
