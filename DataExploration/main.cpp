#include <iostream>
#include <fstream>
#include <cstring>
#include <vector>
#include <algorithm>
#include <math.h>

using namespace std;

//Prototypes
void print_stats(vector<double> vec, string vectorname);
double vector_sum(vector<double> vec);
double vector_mean(vector<double> vec);
double vector_median(vector<double> vec);
double vector_range(vector<double> vec);
double covariance(vector<double> vecA, vector<double> vecB);
double correlation(vector<double> vecA, vector<double> vecB);

int main()
{

    //Prepare to read the file.
    ifstream in;

    cout << "Attempting to open file 'Boston.csv'," << endl;
    in.open("Boston.csv");
    if(in.is_open()){
        cout << "File opened successfully." << endl;
    }else{
        cout << "File could not be opened. Terminating program." << endl;
        return 1;
    }

    //Now that we have the file, we can actually read it.
    //We will need more variables.
    string line;
    const int MAXLEN = 1000;
    //rm and medv match the names of what is given in the file, so we will retain those names for ease of communication
    string rm_in, medv_in;
    vector<double> rm(MAXLEN);
    vector<double> medv(MAXLEN);
    int numOfObservations = 0;

    cout << "Reading heading: ";
    getline(in,line);
    cout << line << endl;
    //It shows us the column titles, 'rm' and 'medv', separated by a comma
    //From here, we can move on to actually reading in the data.

    while(in.peek()!= EOF){
        getline(in,rm_in,',');
        getline(in,medv_in);

        //put the values into our vectors
        rm.at(numOfObservations) = stof(rm_in);
        medv.at(numOfObservations) = stof(medv_in);

        numOfObservations++;
    }

    //make sure the vectors aren't taking up too much space
    rm.resize(numOfObservations);
    medv.resize(numOfObservations);

    cout << "Length is now " << rm.size() << endl;
    cout << "Now closing file 'Boston.csv'" << endl;

    //Always important to clean up.
    in.close();

    //Now, we utilize the data to compute information on it.
    cout << "\n\nNumber of records: " << numOfObservations << endl;
    cout << "Stats for rm- " << endl;
    print_stats(rm,"rm");
    cout << "Stats for medv- " << endl;
    print_stats(medv,"medv");
    cout << "Covariance: " << covariance(rm,medv) << endl;
    cout << "Correlation: " << correlation(rm,medv) << endl;

    cout << "End of program. Goodbye. " << endl;


    return 0;
}

//Print out various statistics about a vector with a given name.
void print_stats(vector<double> vec, string vectorname){

    cout << "   Sum of vector " << vectorname << ": " << vector_sum(vec) << endl;
    cout << "   Mean of vector " << vectorname << ": " << vector_mean(vec) << endl;
    cout << "   Median of vector " << vectorname << ": " << vector_median(vec) << endl;
    cout << "   Range of vector " << vectorname << ": " << vector_range(vec)  << endl;

    return;
}

//Sum up all elements of a vector.
double vector_sum(vector<double> vec){

    double sum = 0;

    vector<double>::iterator it;
    //Go through the vector and add each value to a summation variable.
    for(it = vec.begin(); it < vec.end(); it++ ){
        sum+= *it;
    }

    return sum;
}

//Average all elements of a vector.
double vector_mean(vector<double> vec){

    //Divide the sum by the size of the vector.
    return vector_sum(vec) / vec.size();
}

//Find the sorted middle of a vector.
double vector_median(vector<double> vec){

    double median = 0;

    //Sort the vector
    std::sort(vec.begin(),vec.end());
    //find the middle
    int middle = vec.size() / 2;
    //if its odd, average the items there
    if(vec.size() % 2 == 1){
        median = vec.at(middle) + vec.at(middle+1);
        median = median / 2;

    }else{
        median = vec.at(middle);
    }


    return median;
}

//Find the max difference between values in a given vector.
double vector_range(vector<double> vec){

    //we have already sorted the vector, but since it has to be generally applicable and should work in unit tests, we will sort it again.
    std::sort(vec.begin(),vec.end());

    //Now, the range is just the difference between largest and smallest value.
    double range = vec.at(vec.size()-1) - vec.at(0);
    return range;
}


//Calculate the covariance between two vectors.
double covariance(vector<double> vecA, vector<double> vecB){

    //we'll use this to slowly sum up the values we need to
    double covar = 0;

    //make sure these are compatible vectors
    if(vecA.size() == vecB.size()){

        double meanA = vector_mean(vecA);
        double meanB = vector_mean(vecB);

        vector<double>::iterator itA;
        vector<double>::iterator itB = vecB.begin();
        int i = 0;
        //Iterate through the vector and add each value to a summation variable.
        for(itA = vecA.begin(); itA < vecA.end(); i++){
            covar+= (*itA - meanA) * (*itB - meanB);

            itA++;
            itB++;
        }
        //Now we divide by the size minus one. Both vectors have the same size, so we are safe to use either.
        covar = covar/(vecA.size()-1);
    }else{
        cout << "Vector sizes are not compatible. Covariance cannot be calculated.";
    }

    return covar;
}

//Calculate the correlation between two vectors.
double correlation(vector<double> vecA, vector<double> vecB){

    double corr = 0;

    //make sure these are compatible vectors
    if(vecA.size() == vecB.size()){
        //correlation is the covariance divided by the multiplied standard deviation
        corr = covariance(vecA,vecB) / (sqrt(covariance(vecA,vecA)) * sqrt(covariance(vecB,vecB)));

    }else{
        cout << "Vector sizes are not compatible. Correlation cannot be calculated.";
    }

    return corr;
}







