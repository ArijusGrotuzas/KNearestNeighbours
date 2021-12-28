#include <bits/stdc++.h>
#include <dataset.h>

// Compare two points based on their distances
bool compareDistance(point a, point b){
    return (a.distance < b.distance);
};


// Classify a point as either belonging to class 1 or class 0
int KNearestNeighbourClass(vector<point> arr, int len, int k, point p){

    // Calculate the distance from a given point and each point in the dataset
    for (int i = 0; i < len; i ++)
        arr[i].distance = sqrt((arr[i].x - p.x) * (arr[i].x - p.x) + (arr[i].y - p.y) * (arr[i].y - p.y));

    // Sort points array based on the distance
    sort(arr.begin(), arr.end(), compareDistance);

    // Class frequencies
    int class1Freq = 0;
    int class2Freq = 0;

    // Calculate the class frequencies in neighbors
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
    // Specify the dataset file
    string filename = "dataset2.csv";
    dataset d(filename);

    int len = d.getLenght();

    printf("Number of lines in the file: %d \n", len);

    // Read the lines in the csv file
    d.readDataset();

    // Print n number of entries in the dataset
    d.printDataset(5);

    // Get the data
    vector<point> data = d.getData();

    // Classify the point to one of the two classes
    point test = {4, 1};

    printf("New point's class value: %d", KNearestNeighbourClass(data, len, 3, test));
}
