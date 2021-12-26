#include <bits/stdc++.h>

using namespace std;

struct point{
    int x, y, label;
    double distance;
};

// Compare two points based on their distances
bool compareDistance(point a, point b){
    return (a.distance < b.distance);
};

// Classify a point as either belonging to class 1 or class 0
int KNearestNeighbourClass(point arr[], int len, int k, point p){

    // Calculate the distance from a given point and each point in the dataset
    for (int i = 0; i < len; i ++)
        arr[i].distance = sqrt((arr[i].x - p.x) * (arr[i].x - p.x) + (arr[i].y - p.y) * (arr[i].y - p.y));

    // Sort points array based on the distance
    sort(arr, arr+len, compareDistance);

    // Class frequencies
    int class1Freq = 0;
    int class2Freq = 0;

    // Calculate the class frequencies in neighbours
    for (int i = 0; i < k; i++){
        if (arr[i].label == 0){
            class1Freq++;
        }
        else if (arr[i].label == 1){
            class2Freq++;
        }
    }

    // Return the class value of highest frequency
    return (class1Freq > class2Freq ? 0 : 1);
}

int main()
{
    printf("The K-Nearest Neighbors classifier classifies a single input point to a random dataset.\nEnter an x value for point p...\n");
    int x, y;

    cin >> x;

    printf("Enter Enter an y value for point p...\n");

    cin >> y;

    srand(time(0));

    int len = 10;

    // Create a dataset with a specified size
    point data[len];

    // Set maximum value for each point in the dataset
    int maximum = 10;

    // Create a random dataset
    for (int i = 0; i < len; i++){
        point x = {rand()%maximum, rand()%maximum, rand()%2};
        data[i] = x;
    }

    // Create a point to classify
    point p = {x, y};

    printf("The class of new point: %d.\n", KNearestNeighbourClass(data, len, 3, p));
}
