//
// Created by carri on 8/12/2024.
//
#include <queue>
#include <vector>
#include <iostream>

int n;
std::vector<int> parent, status;
std::vector<std::vector<bool>> inNetwork;
std::vector<std::vector<int>> residualCapacity, residualNetwork;

#define infinity 100000

#define Discovered 1
#define Discovering 0
#define notDiscovered (-1)
#define noParent (-1)

#define source 0
#define sink ((2*n)+1)
#define iLayer(x) ((x > n && x != sink) ? (x-n) : (x))
#define jLayer(x) ((x < n+1 && x != source) ? (x+n) : (x))

void bfs (std::vector<std::vector<int>>& AdjacencyList, const int root) {
    status.assign(2*n+2,notDiscovered);
    parent.assign(2*n+2, noParent);
    /*
     * Empiezo a recorrer desde la raiz.
     */
    status[root] = Discovering;
    std::queue<int> Q;
    Q.push(root);

    bool breakWhile = false;
    while (!Q.empty()) {
        const int u = Q.front(); Q.pop();

        for (int v : AdjacencyList[u]) {
            if (status[v] == notDiscovered) {
                if (residualCapacity[u][v] > 0) {
                    /*
                     * Discrimino caminos sin capacidad.
                     */
                    status[v] = Discovering;
                    parent[v] = u;

                    if (v == sink) {
                        breakWhile = true;
                        break;

                    }
                    Q.push(v);

                }
            }
        }
        status[u] = Discovered;
        /*
         * Si ya encontre el camino al Sink freno el BFS.
         */
        if (breakWhile) break;

    }
}

void augmentPath () {
    int node = sink;
    int minCapacity = infinity;
    while (parent[node] != noParent) {
        /*
         * Busco mínimo del camino de aumento.
         */
        if (residualCapacity[parent[node]][node] < minCapacity) {
            minCapacity = residualCapacity[parent[node]][node];

        }
        node = parent[node];

    }
    /*
     * Actualizo red residual en el sumidero.
     */
    node = sink;
    residualCapacity[node][parent[node]] += minCapacity;
    residualCapacity[parent[node]][node] -= minCapacity;
    node = parent[node];

    while (parent[node] != noParent) {
        /*
         * Actualizo la red residual.
         */
        if (inNetwork[iLayer(parent[node])][iLayer(node)]) {
            residualCapacity[node][parent[node]] += minCapacity;
            residualCapacity[parent[node]][node] -= minCapacity;

        } else {
            residualCapacity[parent[node]][node] += minCapacity;
            residualCapacity[node][parent[node]] -= minCapacity;

        }
        node = parent[node];

    }
}

void FFEK (std::vector<std::vector<int>>& AdjacencyList) {
    int maxFlow = 0;
    while (true) {
        bfs(AdjacencyList, source);
        /*
         * Me fijo si hay camino de aumento.
         */
        if (parent[sink] == noParent) break;
        /*
         * Aumento el flujo
         */
        augmentPath();
    }
}

int main () {
    std::cin >> n;
    /*
     * Matrices inNetwork (binaria) y residualCapacity.
     */
    residualCapacity.assign(2*n+2, std::vector<int>(2*n+2, 0));
    inNetwork.assign(n+2, std::vector<bool>(n+2, false));
    /*
     * Lista de adyacencia de la red residual:
     *       Posición [0] es Source y [2n+1] es Sink.
     *       Posición [i], 1 <= i <= n corresponde primera Layer.
     *       Posición [j], n+1 <= j <= 2n corresponde a segunda Layer.
     */
    residualNetwork.assign(2*n+2, std::vector<int>());
    for (int i = 1; i <= n; i++) {
        /*
         * Aristas de Source a primera Layer
         */
        inNetwork[source][i] = true;
        residualCapacity[source][iLayer(i)] = 1;
        residualNetwork[iLayer(i)].push_back(source);
        residualNetwork[source].push_back(iLayer(i));
        for (int j = 1; j <= n; j++) {
            if (i != j) {
                /*
                 * Aristas de primera a segunda Layer
                 */
                inNetwork[i][j] = true;
                residualCapacity[iLayer(i)][jLayer(j)] = 1;
                residualNetwork[iLayer(i)].push_back(jLayer(j));
                residualNetwork[jLayer(j)].push_back(iLayer(i));

            }
        }
        /*
         * Aristas de segunda Layer a Sink
         */
        inNetwork[i][sink] = true;
        residualCapacity[jLayer(i)][sink] = 1;
        residualNetwork[jLayer(i)].push_back(sink);
        residualNetwork[sink].push_back(jLayer(i));

    }
    /*
     * Corro FFEK
     */
    FFEK (residualNetwork);
    /*
     * Imprimo resultado
     */
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= n; j++) {
            if (residualCapacity[jLayer(j)][iLayer(i)] == 1) {
                std::cout << j-1 << " ";

            }
        }
    }
    return 0;

}