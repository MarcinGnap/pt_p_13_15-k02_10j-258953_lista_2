#pragma once

#include "IncidentMatrix.h"
#include "NeighborhoodList.h"
#include "Edge.h"
#include "EdgeHeap.h"

class Prim
{
	static IncidentMatrix* generateMst(IncidentMatrix* incidentMatrix);
	static NeighborhoodList* generateMst(NeighborhoodList* neighborhoodList);
};