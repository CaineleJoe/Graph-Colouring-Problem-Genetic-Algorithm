
#ifndef Neural_Assignment_4_Chromosome_h
#define Neural_Assignment_4_Chromosome_h


#include <vector>
#include <cstdio>
#include <cctype>
#include <ctime>
#include <stdio.h>
#include <ctime>
#include <cmath>
#include <cctype>
#include <set>
#include <fstream>
#include <iostream>
#include <iomanip>
#include<algorithm>
#include<string>
using namespace std;


class Chromosome;

typedef void (*mutationFunctionPtr)(Chromosome*);
typedef double (*fitnessFunctionPtr)(Chromosome*);


class Chromosome
{
public:


    Chromosome(mutationFunctionPtr, fitnessFunctionPtr);
    Chromosome() {};
    void addGene(double);
    void setGene(int, int);
    void popGene();
    int size();
    void mutate();
    vector<double> getGenes();
    double getGeneAt(int);
    void updateFitness();
    double getFitness();
    mutationFunctionPtr getMutationFunctionPtr();
    fitnessFunctionPtr getFitnessFunctionPtr();
    bool operator < (const Chromosome&) const;

private:


    int chromosomeSize;
    vector<double> genes;
    mutationFunctionPtr mutationFun;
    fitnessFunctionPtr fitnessFun;
    double fitness;
    double randDouble(double fMin, double fMax);


};

#endif






