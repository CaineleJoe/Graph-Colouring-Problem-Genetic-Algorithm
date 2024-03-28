
#include "GraphColoring.h"





int main(int, char const**)
{

    srand(time(NULL));



    relativePath = "C:/Users/Luca/OneDrive/Desktop/";
    string filename = "flat1000_76_0.col";




    /* Genetic Algorithm Variables */
    popSize = 200; // population size
    mutationRate = 100; //for each 2 new children, i select one randomly to mutate, but this process happens with a mutationRate possibility (0 - 100)
    maxIterations = 5000; // when you reach maxIterations, end training
    patienceTime = 70; // when generations saturate for patienceTime generations, the helper function gets called
    maxUselessShuffle = 2; // maximum number of times intervention is called without improving the chromosome





    try {
        colorGraph(filename);

    }
    catch (string err)
    {
        cout << err << endl;
    }


    cout << " END " << endl;
    return 0;
}
