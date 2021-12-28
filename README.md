# K-Nearest Neighbours classifier

K-Nearest Neighbours classifier that classifies only two classes.

```c++
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
```
