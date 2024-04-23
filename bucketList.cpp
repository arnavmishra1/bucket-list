// Author: Arnav Mishra
// CECS 325-02 Prog 5
// Due 04/23/2024

// I certify that this program is my own original work.
// I did not copy any part of this program from any other source.
// I further certify that I typed each and every line of code in this program.

#include <iostream>
#include <vector>
#include <time.h>
#include <fstream>

using namespace std;

int globalSwapCount = 0;

class Bucket{
    private:
        vector<int> v;
    public:
        Bucket();
        void generate(int size, int min, int max) {
            for (int i = 0; i < size; i++) {
                v.push_back(rand() % (max-min+1) + min);
            }
        }

        void sort() { // Use the bubble sort from Prog3 and Prog4
            for (int i = 0; i < size() - 1; i++) {
                for (int j = 0; j < size() - i - 1; j++) {
                    if (v[j] > v[j+1]) {
                        swap(v[j], v[j+1]);
                        globalSwapCount++;
                    }
                }
            }
        }

        int size() {
            return v.size();
        }

        int atIndex(int i) {
            return v[i];
        }

        int merge(Bucket b) { // merge b into this
            vector<int> bucket2;
            for(int i = 0; i < b.size(); i++) {
                bucket2.push_back(b.atIndex(i));
            }

            vector<int> temp;
            int i = 0, j = 0;
            while(i < size() && j < bucket2.size()) {
                if (v[i] <= bucket2[j]) {
                    temp.push_back(v[i]);
                    i++;
                } else {
                    temp.push_back(bucket2[j]);
                    j++;
                }
            }

            while(i < size()) {
                temp.push_back(v[i]);
                i++;
            }

            while(j < b.size()) {
                temp.push_back(bucket2[j]);
                j++;
            }

            v = temp;
        }
};

// usage: $ bucketList 100 100 1000000 9000000
//          bucketList bucketCount bucketSize min max
int main(int argc, char *argv[])
{
    srand(time(0));

    int bucketCount = stoi(argv[1]);
    int bucketSize = stoi(argv[2]);
    int bucketMin = stoi(argv[3]);
    int bucketMax = stoi(argv[4]);
    cout << "Bucket Count:"<<bucketCount<<endl;
    cout << "Bucket Size:"<<bucketSize<<endl;
    cout << "Bucket Min Value:"<<bucketMin<<endl;
    cout << "Bucket Max value:"<<bucketMax<<endl;

    vector<Bucket> list; // create empty Bucket vector

    Bucket *bptr;

    for(int i=0; i<bucketCount; i++) // creating bucketCount Buckets
    {
        bptr = new Bucket; // allocating new Bucket
        bptr->generate(bucketSize, bucketMin, bucketMax);
        //Bucket::generate(int,int,int,int)
        list.push_back(*bptr); // pushing Bucket onto list
    }

    for (auto it = list.begin(); it != list.end(); it++)
    {
        it->sort(); // Bucket::sort
    }

    Bucket endGame; // create empty Bucket to merge ALL buckets

    while (list.size() > 0) // vector<Bucket>::size()
    {
        endGame.merge(list[0]); // merge first bucket in list into endGame
        list.erase(list.begin()); // erase the first bucket in the list
    }

    // write all the numbers in endGame bucket to a file
    fstream out("bucketList.out", ios::out);
    for(int i=0; i<endGame.size(); i++) // Bucket::size()
        out << endGame.atIndex(i) << endl; // Bucket::atIndex(int)

    cout << "Global Swap Count:" << globalSwapCount << endl;
    cout << "\nbucketList.out has " << bucketCount * bucketSize << " sorted numbers\n";

    return 0;
}