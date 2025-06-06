#include <iostream>
#include <vector>
#include <limits>
#include <iomanip>
using namespace std;

typedef pair<int, double> Aresta; // (destino, peso)
typedef vector<vector<Aresta>> Lista;

void leituraGrafo(Lista &G, int m)
{
    int a, b;
    double peso;
    while (m--)
    {
        cin >> a >> b >> peso;
        G[a].push_back({b, peso}); // Direcionado
    }
}

void escritaGrafo(const Lista &G)
{
    int n = G.size();
    cout << "Lista de Adjacência:" << endl;
    for (int u = 0; u < n; u++)
    {
        cout << u << ": ";
        for (auto [v, w] : G[u])
        {
            cout << "(" << v << ", " << w << ") ";
        }
        cout << endl;
    }
}

void bellmanFord(const Lista &G, int origem)
{
    int n = G.size();
    vector<double> dist(n, numeric_limits<double>::infinity());
    dist[origem] = 0.0;

    for (int i = 1; i < n; ++i)
    {
        for (int u = 0; u < n; ++u)
        {
            for (auto [v, peso] : G[u])
            {
                if (dist[u] + peso < dist[v])
                {
                    dist[v] = dist[u] + peso;
                }
            }
        }
    }

    // Verificação de ciclos negativos
    for (int u = 0; u < n; ++u)
    {
        for (auto [v, peso] : G[u])
        {
            if (dist[u] + peso < dist[v])
            {
                cout << "Ciclo negativo detectado!" << endl;
                return;
            }
        }
    }

    cout << fixed << setprecision(2);
    cout << "Distâncias a partir do vértice " << origem << ":" << endl;
    for (int i = 0; i < n; ++i)
    {
        if (isinf(dist[i]))
            cout << i << ": INFINITO" << endl;
        else
            cout << i << ": " << dist[i] << endl;
    }
}

int main()
{
    int n, m;
    cin >> n >> m;
    Lista Grafo(n);
    leituraGrafo(Grafo, m);
    escritaGrafo(Grafo);
    cout << "Total Vértices: " << n << endl;
    cout << "Total Arestas: " << m << endl;

    int origem = 0;
    bellmanFord(Grafo, origem);
    return 0;
}
