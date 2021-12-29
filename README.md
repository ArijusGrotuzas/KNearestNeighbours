# K-Nearest Neighbours classifier

K-Nearest Neighbours classifier that classifies only two classes.

```c++
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
```
