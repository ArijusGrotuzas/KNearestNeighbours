# K-Nearest Neighbors classifier

K-Nearest Neighbors classifier implemented in `C++`.

```c++
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
```
The project includes the famous [Iris Dataset](https://archive.ics.uci.edu/ml/datasets/Iris).
