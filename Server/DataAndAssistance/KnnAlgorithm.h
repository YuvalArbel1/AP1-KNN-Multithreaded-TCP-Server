#ifndef EX4_KNNALGORITHM_H
#define EX4_KNNALGORITHM_H

#include "Server/Distances/AbstractDistance.h"
#include "ClassifiedRelativeVector.h"

class KnnAlgorithm {
public:
    KnnAlgorithm(AbstractDistance *calculation, unsigned long kNum);

    ~KnnAlgorithm();

    void setKNeighbors(unsigned long kNum);

    void setCalc(AbstractDistance *calculation);

    unsigned long getKNeighbors();

    AbstractDistance *getCalc();

    void setCatalogVec(vector<ClassifiedRelativeVector *> catalogVectors);

    vector<ClassifiedRelativeVector *> getCataloged();

    string classifyVector(vector<double> unclassifiedVector);

    bool KnnAlgorithm::calculateDistances(vector<double> uVec);

    // Check validation of the vectors.
    bool sizeComparison(const vector<double> &v1, const vector<double> &v2);

    vector<string> calculateFiles(vector<RelativeVector *> UnclassifiedVectors,
                                  vector<ClassifiedRelativeVector *> classifiedVectors);


private:
    // The calculation for the distance.
    AbstractDistance *calc;
    // The K nearest neighbors.
    unsigned long kNeighbors;
    // The classified relative vectors.
    vector<ClassifiedRelativeVector *> catalogedVectors;
};

#endif //EX4_KNNALGORITHM_H
