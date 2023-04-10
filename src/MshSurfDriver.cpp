#include "MshSurfDriver.h"
#include <iostream>

MshSurfDriver::MshSurfDriver()
{
    this->_model = NULL;
    this->_messageFunction = NULL;
    this->_supportMaxElementSize = 0.03;
    this->_supportComputeCurvature = true;
}

MshSurfDriver::~MshSurfDriver()
{
}

void MshSurfDriver::setModel(Model *model)
{
    this->_model = model;
}

void MshSurfDriver::setSupportMaxElementSize(GLfloat maxElementSize)
{
    this->_supportMaxElementSize = maxElementSize;
}

void MshSurfDriver::convertToMeshSurf(int &nPts, double *&pts, int &nElems, int *&elems,
                                      int type, bool clockWise)
{
    Geometry *modelGeometry = this->_model->getSelectedMeshGeometry();

    nPts = static_cast<int>(modelGeometry->vertices.size());
    nElems = static_cast<int>(modelGeometry->faces.size());

    pts = new double[3 * nPts];
    elems = new int[(type + 1) * nElems];

    std::unordered_map<int, int> vMap;

    for (int i = 0; i < nPts; i++)
    {
        pts[3 * i + 0] = modelGeometry->vertices[i].coords.x;
        pts[3 * i + 1] = modelGeometry->vertices[i].coords.y;
        pts[3 * i + 2] = modelGeometry->vertices[i].coords.z;

        vMap[modelGeometry->vertices[i].id] = i;
    }

    for (int i = 0; i < nElems; i++)
    {
        elems[(type + 1) * i + 0] = type;

        Face f = modelGeometry->faces[i];

        for (int j = 0; j < type; j++)
        {
            int jj = clockWise ? (type - j) % type : j;
            elems[(type + 1) * i + j + 1] = vMap[modelGeometry->vertices[f.getIndex(jj)].id];
        }
    }
}

Geometry *MshSurfDriver::convertFromMeshSurf(int nPts, double *pts, int nElems, int *elems)
{
    Geometry *geometry = new Geometry();

    for (int i = 0; i < nPts; i++)
    {
        GLfloat x = pts[3 * i + 0];
        GLfloat y = pts[3 * i + 1];
        GLfloat z = pts[3 * i + 2];

        geometry->addVertice(x, y, z);
    }

    for (int i = 0; i < nElems; i++)
    {
        GLint indV0 = elems[4 * i + 1];
        GLint indV1 = elems[4 * i + 2];
        GLint indV2 = elems[4 * i + 3];

        geometry->addFace(indV0, indV1, indV2);

        Vertice *v0 = &geometry->vertices[indV0];
        Vertice *v1 = &geometry->vertices[indV1];
        Vertice *v2 = &geometry->vertices[indV2];

        Vertice v01, v02, v01v02;
        v01.coords = v1->coords - v0->coords;
        v02.coords = v2->coords - v0->coords;
        v01v02 = v01 % v02;

        geometry->addNormal(v01v02.coords.x, v01v02.coords.y, v01v02.coords.z);
    }

    return geometry;
}

void MshSurfDriver::convertToBoundarySurf(int &nPts,
                                          double *&pts,
                                          int &nBoundEdges,
                                          int &nInterEdges,
                                          int *&edges,
                                          std::unordered_map<int, Vertice> &map,
                                          bool clockWise)
{
    Geometry *geometry = this->_model->getSelectedMeshGeometry();
    std::vector<std::pair<GLint, GLint> > boundary = geometry->getBoundary();

    nPts = static_cast<int>(boundary.size());
    nBoundEdges = static_cast<int>(boundary.size());
    nInterEdges = 0;
    pts = new double[3 * nPts];
    edges = new int[2 * nBoundEdges];

    std::unordered_map<int, int> vMap;

    map.reserve(nPts);

    for (int i = 0; i < nPts; i++)
    {
        GLint ind0 = boundary[i].first;
        Vertice v0 = geometry->vertices[ind0];

        pts[3 * i + 0] = v0.coords.x;
        pts[3 * i + 1] = v0.coords.y;
        pts[3 * i + 2] = v0.coords.z;

        vMap[v0.id] = i;
    }

    for (int i = 0; i < nBoundEdges; i++)
    {
        GLint ind0 = clockWise ? boundary[i].second : boundary[i].first;
        GLint ind1 = clockWise ? boundary[i].first : boundary[i].second;

        Vertice v0 = geometry->vertices[ind0];
        Vertice v1 = geometry->vertices[ind1];

        edges[2 * i + 0] = vMap[v0.id];
        edges[2 * i + 1] = vMap[v1.id];
    }
}

void MshSurfDriver::executeSupport()
{
    int nSupPts = 0;
    double *supPts = NULL;
    int nSupElems = 0;
    int *supElems = NULL;

    this->convertToMeshSurf(nSupPts, supPts, nSupElems, supElems, 3, true);

    int nPts = 0;
    double *pts = NULL;
    int nBoundEdges = 0;
    int nInterEdges = 0;
    int *edges = NULL;
    std::unordered_map<int, Vertice> map;

    this->convertToBoundarySurf(nPts, pts, nBoundEdges, nInterEdges, edges, map, true);

    MshSurfSetSupportMesh(NULL, nSupPts, supPts, nSupElems, supElems);

    int nGenPts = 0;
    double *genPts = NULL;
    int nGenElems = 0;
    int *genElems = NULL;

    MshSurf3D(nPts, pts, nBoundEdges, nInterEdges, edges,
              this->_supportMaxElementSize, this->_supportComputeCurvature ? 1 : 0,
              this->_messageFunction,
              &nGenPts, &genPts, &nGenElems, &genElems);

    Geometry *generatedGeometry = this->convertFromMeshSurf(nGenPts, genPts, nGenElems, genElems);
    generatedGeometry->updateGeometryByModelMatrix(glm::inverse(this->_model->getModelMatrix()));
    Loader loader = Loader();
    Mesh *mesh = loader.geometryToMesh(generatedGeometry);
    this->_model->setSelectedMesh(mesh);

    delete[] supPts;
    delete[] supElems;
    delete[] pts;
    delete[] edges;
    free(genPts);
    free(genElems);
}