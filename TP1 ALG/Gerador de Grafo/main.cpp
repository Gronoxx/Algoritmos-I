#include <iostream>
#include <fstream>
#include <random>
#define N 100
using namespace std;

void GenerateRandomGraphs(int e) {
    int i, j, edge[e][2], count;
    int degree[N] = {0}; // Initialize degrees to zero for all vertices

    i = 0;
    // Generate a connection between two random numbers, for //sample a small case, limit the number of vertices to 10.
    while (i < e) {
        edge[i][0] = rand() % N + 1;
        edge[i][1] = rand() % N + 1;

        // Update degrees for both vertices
        degree[edge[i][0] - 1]++;
        degree[edge[i][1] - 1]++;

        i++;
    }

    double minX = -1040.0, maxX = 1040.0;
    double minY = -1040.0, maxY = 1040.0;
    std::random_device rd;
    std::mt19937 gen(rd());

    // Define distributions for x and y coordinates
    std::uniform_real_distribution<double> distX(minX, maxX);
    std::uniform_real_distribution<double> distY(minY, maxY);

    // Open a file for writing
    ofstream outputFile("random_graph.txt");
    if (!outputFile.is_open()) {
        cout << "Error opening the output file." << endl;
        return;
    }

    // Write all the connections of each vertex, along with their degrees, to the file
    for (i = 0; i < N; i++) {
        double x = distX(gen);
        double y = distY(gen);
        count = 0;
        outputFile << x << " " << y << " " << degree[i] << " ";
        for (j = 0; j < e; j++) {
            if (edge[j][0] == i + 1) {
                outputFile << edge[j][1] << " ";
                count++;
            } else if (edge[j][1] == i + 1) {
                outputFile << edge[j][0] << " ";
                count++;
            }
            // Print “Isolated vertex” for the vertex having zero degree.
            else if (j == e - 1 && count == 0)
                outputFile << "0";
        }
        outputFile << "\n";
    }

    // Close the output file
    outputFile.close();
}

int main() {
    int n, i, e;
    cout << "Enter the number of edges for the random graph: ";
    cin >> e;
    GenerateRandomGraphs(e);
}
