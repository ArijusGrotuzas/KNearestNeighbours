#include <bits/stdc++.h>
#include <vector>
#include <string>
#include <sstream>

using namespace std;

struct point{
    int x, y, label;
    double distance;
};

struct dataset{
    point* data;
    int lenght;
};


// Compare two points based on their distances
bool compareDistance(point a, point b){
    return (a.distance < b.distance);
};

int getLineNum(char filename[]){
    fstream file;

    file.open(filename, ios::in);

    string temp;
    int num = -1;

    if(file.is_open()){

        while(getline(file, temp)){
            num++;
        }

        file.close();
    }

    return num;
}

dataset readDataset(char filename[])
{
    int len = getLineNum(filename);
    point arr[len];

    // File pointer
    fstream file;

    // Open an existing file
    file.open(filename, ios::in);

    // Check if the file is still open
    if (file.is_open())
    {
        vector<string> row;
        string line, word, temp;
        int num = 0;

        // Get each line of the csv file
        while(getline(file, line)){

            // Clear the vector to avoid pushing previous data ontop
            row.clear();

            stringstream s(line);

            // Go through the line and and delimit each word separated by comma
            while (getline(s, word, ',')) {

                // Append each word to the vector
                row.push_back(word);
            }

            point p;

            // Add columns to a point structure
            for(int i = 0; i < row.size(); i++){
                if (i == 0){
                    p.x = stoi(row[i]);
                }
                else if(i == 1){
                    p.y = stoi(row[i]);
                }
                else if (i == 2){
                    p.label = stoi(row[i]);
                    arr[num] = p;
                }
            }

            num++;
        }

        // Close the file
        file.close();
    }

    dataset d;
    d.lenght = len;
    d.data = arr;

    return d;
}


void printDataset(dataset d){
    if (d.data != nullptr) {
        cout << "Dataset: " << endl;

        point temp;

        for (int i = 0; i < d.lenght; i++)
        {
            temp = *(d.data + i);
            cout << temp.x << ", " << temp.y << ", "<< temp.label << "\n";
        }

        cout << "---------------------------------------------------------" << endl;
    }
    else{
        printf("Empty pointer...");
    }
}

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
    // Specify file type
    char filename[] = "dataset.csv";

    // Get the dataset from the file
    dataset d = readDataset(filename);

    // Print the dataset
    printDataset(d);

    // Turn the dataset to an array instead of a pointer
    point arr[d.lenght];
    point temp;

    for(int i = 0; i < d.lenght; i++){
        temp = *(d.data + i);
        arr[i] = temp;
    }

    // Delete the old unused pointer
    delete d.data;


    // Classify the point to one of the two classes
    point test = {4, 1};

    printf("New point's class value: %d", KNearestNeighbourClass(arr, d.lenght, 3, test));
}
