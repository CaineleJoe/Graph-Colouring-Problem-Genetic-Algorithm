#include <iostream>
#include <vector>
#include <cmath>
#include <cstdlib>
#include <ctime>
#include <string>
#include <cstring>
#include <set>
#include <fstream>
using namespace std;

int N; // Number of nodes
vector<vector<int>> graph; // Adjacency matrix representation of the graph
int numberOfColors;

// Function to calculate the number of conflicting edges
int calculateCost(const vector<int>& colors) {
    int conflicts = 0;
    std::set<int> uniqueColors;

    for (int i = 0; i < N; ++i) {
        uniqueColors.insert(colors[i]);
        for (int j = i + 1; j < N; ++j) {
            if (graph[i][j] && colors[i] == colors[j]) {
                conflicts++;
            }
        }
    }

    int number_of_colors_used = uniqueColors.size();
    int bad_edges = conflicts;
    int number_of_nodes = N;

    return (50 * number_of_colors_used + 1000 * bad_edges) / number_of_nodes;
}

// Function to generate a random initial solution
vector<int> generateInitialSolution() {
    vector<int> colors(N);
    for (int i = 0; i < N; ++i) {
        colors[i] = rand() % numberOfColors;
    }
    return colors;
}

// Function to modify the solution slightly
vector<int> modifySolution(const vector<int>& currentSolution) {
    vector<int> newSolution = currentSolution;
    int randomNode = rand() % N;
    int newColor;
    do {
        newColor = rand() % numberOfColors;
    } while (newColor == currentSolution[randomNode]);

    newSolution[randomNode] = newColor;
    return newSolution;
}

// Simulated Annealing algorithm
vector<int> simulatedAnnealing(double initialTemp, double coolingRate, int maxIterations) {
    vector<int> currentSolution = generateInitialSolution();
    vector<int> bestSolution = currentSolution;
    int currentCost = calculateCost(currentSolution);
    int bestCost = currentCost;

    double temp = initialTemp;

    for (int i = 0; i < maxIterations; ++i) {
        vector<int> newSolution = modifySolution(currentSolution);
        int newCost = calculateCost(newSolution);
        std::cout << "GENERATIA: " << i << std::endl;
        int delta = newCost - currentCost;

        if (delta < 0 || (exp(-delta / temp) > ((double)rand() / RAND_MAX))) {
            currentSolution = newSolution;
            currentCost = newCost;

            if (newCost < bestCost) {
                bestSolution = newSolution;
                bestCost = newCost;
            }
        }

        // Cooling down
        temp *= coolingRate;
    }

    return bestSolution;
}
void buildGraphFromDIMACS(const std::string& filePath) {
    std::ifstream IN(filePath);
    if (IN.fail()) {
        throw std::runtime_error("CAN'T OPEN " + filePath);
    }

    std::string inp;
    IN >> inp;
    while (!IN.eof() && inp != "p") {
        IN >> inp;  // Skip lines until we find the "p" line
    }

    std::string edge;
    IN >> edge >> N;  // Read "edge" and number of vertices

    // Initialize the adjacency matrix
    graph = std::vector<std::vector<int>>(N, std::vector<int>(N, 0));

    int u, v;
    while (IN >> u >> v) {
        // Adjusting for 1-based indexing in DIMACS format
        graph[u - 1][v - 1] = 1;
        graph[v - 1][u - 1] = 1;
    }
    IN.close();
}
int main() {
    srand(time(NULL));

    std::string filePath = "C:/Users/Luca/OneDrive/Desktop/anna.col";  // Replace with your actual file path

    try {
        buildGraphFromDIMACS(filePath);
    }
    catch (const std::runtime_error& e) {
        std::cerr << e.what() << std::endl;
        return 1;
    }

    numberOfColors = N; // Set the number of colors equal to the number of nodes
    double initialTemp = 10000;
    double coolingRate = 0.96;
    int maxIterations = 50000;

    vector<int> solution = simulatedAnnealing(initialTemp, coolingRate, maxIterations);
    int finalCost = calculateCost(solution);

    // Determine the number of unique colors used
    std::set<int> uniqueColors;
    for (int color : solution) {
        uniqueColors.insert(color);
    }

    cout << "Final Solution Cost (Number of Bad Edges): " << finalCost << endl;
    cout << "Total Number of Unique Colors Used: " << uniqueColors.size() << endl;

    // Print the solution
    cout << "Solution (Node Color):" << endl;
    for (int i = 0; i < solution.size(); i++) {
        cout << "Node " << (i + 1) << ": Color " << solution[i] << endl;
    }

    return 0;
}
