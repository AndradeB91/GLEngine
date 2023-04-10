#include <stdlib.h>
#include <stdio.h>
#include <unordered_map>

#include <glm/glm.hpp>

#include "Model.h"

#include "../vendor/tecgraf/mshsurf3d.h"

class MshSurfDriver
{
public:
    MshSurfDriver();
    ~MshSurfDriver();

    void executeSupport();

    void setModel(Model *model);

    void setSupportMaxElementSize(GLfloat maxElementSize);

    void convertToBoundarySurf(int &nPts,
                               double *&pts,
                               int &nBoundEdges,
                               int &nInterEdges,
                               int *&edges,
                               std::unordered_map<int, Vertice> &map,
                               bool clockWise);

private:
    Model *_model;
    Surf3DMessFunc *_messageFunction;
    bool _supportComputeCurvature;
    double _supportMaxElementSize;

    void convertToMeshSurf(int &nPts, double *&pts, int &nElems, int *&elems,
                           int type, bool clockWise);

    Geometry *convertFromMeshSurf(int nPts, double *pts, int nElems, int *elems);
};
