
#ifndef Graph_Coloring_GraphColoring_h
#define Graph_Coloring_GraphColoring_h


#include "Evolution.h"


int N;
int mat[10000][10000];
int popSize;
double maxFitness;
int maxIterations;
double mutationRate;
int maxUselessShuffle;
int patienceTime;
int numOfColoredUsed;
set<int> finalColors;
Chromosome target;
vector<Chromosome> simulationResults;
string relativePath;
string outputPath;

double fitnessFunction(Chromosome* ch);
double checkError();
void mutationFunction(Chromosome* ch);
void buildGraphFromDIMACS(const string&);
void colorGraph(const string&);



#endif



void init()
{
    simulationResults.clear();
    numOfColoredUsed = 0;
    finalColors.clear();

    outputPath = "";
    outputPath += relativePath;
    outputPath += "results/";



}


void buildGraphFromDIMACS(const string& filename)
{
    string filePath = "";
    filePath += relativePath;
    filePath += filename;


    outputPath += filename;
    outputPath += ".txt";

    ifstream IN(filePath);

    if (IN.fail()) throw ("CAN'T OPEN " + filePath);

    string inp;
    IN >> inp;
    while (!IN.eof() && inp != "edge") {
        IN >> inp;
    }

    IN >> N;
    IN >> inp;

    char e;
    int u, v;
    memset(mat, 0, sizeof mat);
    IN >> e;

    while (!IN.eof())
    {
        IN >> u >> v;
        mat[u][v] = 1;
        IN >> e;
    }
    IN.close();
}


void colorGraph(const string& filename)
{

    init();

    buildGraphFromDIMACS(filename);

    ofstream OUT(outputPath);
    if (OUT.fail()) throw "FAILED TO OPEN " + outputPath;

    Evolution evolution(maxIterations, mutationRate, patienceTime, maxUselessShuffle);


    for (int i = 0; i < popSize; i++)
    {
        Chromosome ch(mutationFunction, fitnessFunction);
        for (int j = 0; j < N; j++)
        {
            ch.addGene(1);
        }
        evolution.addChromosome(ch);
    }


    target = evolution.train(&OUT);
    simulationResults = evolution.getResults();


    OUT << endl << endl << "END " << "------------------------" << endl;
    OUT << "ERROR: " << checkError() << endl;
    OUT << "NUM OF COLORS USED = " << numOfColoredUsed << endl;
    OUT.close();
}





double fitnessFunction(Chromosome* ch)
{

    double ret = 0;
    set<int> colorsUsed;
    for (int u = 0; u < N; u++)
    {
        int uClr = ch->getGeneAt(u);
        colorsUsed.insert(uClr);
        for (int v = 0; v < N; v++)
        {
            if (mat[u][v])
                if (ch->getGeneAt(v) == uClr)
                    ret++;
        }
    }

    return -(50 * (colorsUsed.size()) + 1000 * ret) / N;
}


double checkError()
{
    double err = 0;
    int edges = 0;
    for (int i = 0; i < N; i++)
    {
        finalColors.insert((int)target.getGeneAt(i));
        for (int j = 0; j < N; j++)
        {
            if (mat[i][j])
            {
                edges++;
                if ((int)target.getGeneAt(i) == (int)target.getGeneAt(j)) {

                    err++;
                }
            }
        }
    }
    numOfColoredUsed = finalColors.size();


    if (edges == 0) return err;
    else return (err / edges);
}


void mutationFunction(Chromosome* ch) {

    for (int u = 0; u < N; u++) {
        int uClr = ch->getGeneAt(u);
        for (int v = 0; v < N; v++)
        {
            int colors = rand() % N;
            if (ch->getGeneAt(v) == uClr) {
                ch->setGene(u, colors);

            }
        }
    }

}



















