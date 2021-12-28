#ifndef DATASET_H
#define DATASET_H

using namespace std;

struct point{
    vector<double> features;
    int label;
    double distance;
};

int getLineNum(string filename){
    fstream file;

    file.open(filename, ios::in);

    string temp;
    int num = 0;

    if(file.is_open()){

        while(getline(file, temp)){
            num++;
        }

        file.close();
    }

    return num;
}

class dataset
{
    private:
        string filename;
        int lenght;
        vector<point> data;

    public:
        dataset(string filenamem);

        inline void readDataset();

        inline void printDataset(int rows);

        inline int getLenght();

        inline vector<point> getData();
};

dataset::dataset(string filename){
    this->filename = filename;
    lenght = getLineNum(filename);
}

inline void dataset::readDataset()
{
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

                p.features.push_back(stod(row[i]));

                if (i == row.size() - 1){
                    p.label = stoi(row[i]);
                }
                /*
                switch(i){
                case 0:
                    p.x = stod(row[i]);
                    break;
                case 1:
                    p.y = stod(row[i]);
                    break;
                case 2:
                    p.label = stod(row[i]);
                    break;
                }*/
            }

            data.push_back(p);
            num++;
        }

        // Close the file
        file.close();
    }
}

inline void dataset::printDataset(int rows){

    if(rows > lenght){
        rows = lenght;
    }

    for (int i = 0; i < rows; i++){
        vector<double> temp = data[i].features;

        for(int j = 0; j < temp.size(); j++){
            cout << temp[j] << ", ";
        }

        cout << endl;
    }

    cout << endl;
}

inline int dataset::getLenght(){
    return lenght;
};

inline vector<point> dataset::getData(){

    return data;
};

#endif // DATASET_H
