#include "Dijkstra.h"

using namespace std;

Path Dijkstra::findShortestPath(IncidentMatrix* incidentMatrix, size_t from, size_t to)
{
	//	Stworzenie potrzebnych zmiennych.
	Path result;
	CellType** matrix = incidentMatrix->getMatrix();
	size_t vertexNumber = incidentMatrix->getVertexNumber();
	size_t edgesNumer = incidentMatrix->getEdgeNumber();
	size_t* values = incidentMatrix->getValues();
	//	Stworzenie tablicy przechowującej informację czy wierzchołek został już odwiedzony.
	bool* visitedVertices = new bool[vertexNumber];
	for (size_t i = 0; i < vertexNumber; i++)
	{
		visitedVertices[i] = false;
	}
	//	Stworzenie początkowej wagi.
	size_t* travelCosts = new size_t[vertexNumber];
	for (size_t i = 0; i < vertexNumber; i++)
	{
		travelCosts[i] = SIZE_MAX;
	}

	//	Stworzenie tablicy przechowującej poprzednie wierzchołki.
	size_t* reachableFrom = new size_t[vertexNumber];

	for (size_t vertex = 0; vertex < vertexNumber; vertex++)
	{
		reachableFrom[vertex] = SIZE_MAX;
	}

	//	Stworzenie tablicy do przechowywania pojedyńczych wag.
	size_t* reachableFor = new size_t[vertexNumber];

	travelCosts[from] = 0;
	size_t currentVertex = from;
	size_t unvisitedVerticesNumber = vertexNumber;

	//	Znalezienie nowego wierzchołka.
	auto assignNewCurrentVertex = [&]()
	{
		visitedVertices[currentVertex] = true;
		unvisitedVerticesNumber--;
		size_t sortestPath = SIZE_MAX;
		for (size_t vertex = 0; vertex < vertexNumber; vertex++)
		{
			if (visitedVertices[vertex] == false && travelCosts[vertex] < sortestPath)
			{
				sortestPath = travelCosts[vertex];
				currentVertex = vertex;
			}
		}
	};

	//	Wykona się, jesli istnieją jakiekolwiek nieodwiedzone wierzchołki.
	while (unvisitedVerticesNumber > 0)
	{
		//	Iteracja przez wszystkie krawędzie.
		for (size_t edge = 0; edge < edgesNumer; edge++)
		{
			if (matrix[currentVertex][edge] != CellType::origin)
			{
				continue;
			}

			//	Iteracja przez wszystkie wierzchołki.
			for (size_t vertex = 0; vertex < vertexNumber; vertex++)
			{
				if (matrix[vertex][edge] != CellType::destination)
				{
					continue;
				}

				//	Sprawdzenie czy aktualna waga jest mniejsza niż stara.
				if (travelCosts[currentVertex] + values[edge] < travelCosts[vertex])
				{
					travelCosts[vertex] = travelCosts[currentVertex] + values[edge];
					reachableFrom[vertex] = currentVertex;
					reachableFor[vertex] = values[edge];
				}

				break;
			}
		}

		//	Przypisanie nowego wierzchołka.
		assignNewCurrentVertex();
	}

	currentVertex = to;

	//	Stworzenie najkrótszej drogi.
	while (currentVertex != from)
	{
		//	Sprawdzenie czy połączenie istnieje.
		if (currentVertex == SIZE_MAX)
		{
			return Path();
		}

		result.addEdge(PathEdge(reachableFor[currentVertex], reachableFrom[currentVertex], currentVertex));
		currentVertex = reachableFrom[currentVertex];
	}

	return result;
}

Path Dijkstra::findShortestPath(NeighborhoodList* neighborhoodList, size_t from, size_t to)
{
	//	Stworzenie potrzebnych zmiennych. 
	Path result;
	Edge** edges = neighborhoodList->getEdges();
	size_t vertexNumber = neighborhoodList->getVertexNumber();

	//	Stworzenie tablicy przechowującej informacje czy czy dany wierzchołek został już odwiedzony.
	bool* visitedVertices = new bool[vertexNumber];
	for (size_t i = 0; i < vertexNumber; i++)
	{
		visitedVertices[i] = false;
	}

	//	Stworzenie początkowych wag.
	size_t* travelCosts = new size_t[vertexNumber];
	for (size_t i = 0; i < vertexNumber; i++)
	{
		travelCosts[i] = SIZE_MAX;
	}

	//	Stworzenie tablicy do przechowywania poprzednich wierzchołków.
	size_t* reachableFrom = new size_t[vertexNumber];

	for (size_t vertex = 0; vertex < vertexNumber; vertex++)
	{
		reachableFrom[vertex] = SIZE_MAX;
	}


	//	Stworzenie tablicy do przechowywania poszczególnych wag.
	size_t* reachableFor = new size_t[vertexNumber];

	travelCosts[from] = 0;
	size_t currentVertex = from;
	size_t unvisitedVerticesNumber = vertexNumber;

	//	Znalezienie nowego wierzchołka.
	auto assignNewCurrentVertex = [&]()
	{
		visitedVertices[currentVertex] = true;
		unvisitedVerticesNumber--;
		size_t sortestPath = SIZE_MAX;
		for (size_t vertex = 0; vertex < vertexNumber; vertex++)
		{
			if (visitedVertices[vertex] == false && travelCosts[vertex] < sortestPath)
			{
				sortestPath = travelCosts[vertex];
				currentVertex = vertex;
			}
		}
	};

	//	Jeśli istnieją nieodwiedzone wierzchołki.
	while (unvisitedVerticesNumber > 0)
	{
		Edge* edge = edges[currentVertex];
		while (edge != nullptr)
		{
			//	Sprawdzenie czy aktualna waga jest mniejsza od poprzedniej.
			if (travelCosts[currentVertex] + edge->value < travelCosts[edge->destination])
			{
				travelCosts[edge->destination] = travelCosts[currentVertex] + edge->value;
				reachableFrom[edge->destination] = currentVertex;
				reachableFor[edge->destination] = edge->value;
			}

			edge = edge->next;
		}

		//	Przypisanie nowego wierzchołka.
		assignNewCurrentVertex();
	}

	currentVertex = to;

	//	Stworzenie najkrótszej drogi.
	while (currentVertex != from)
	{
		//	Sprawdzenie czy istnieje połączenie.
		if (currentVertex == SIZE_MAX)
		{
			return Path();
		}

		result.addEdge(PathEdge(reachableFor[currentVertex], reachableFrom[currentVertex], currentVertex));
		currentVertex = reachableFrom[currentVertex];
	}

	return result;
}