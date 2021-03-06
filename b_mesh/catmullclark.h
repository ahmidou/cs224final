#ifndef CATMULLCLARK_H
#define CATMULLCLARK_H

#include <QVector>
#include <QMap>
#include <QPair>
#include <QHash>
#include "mesh.h"

/**
  A library for Catmull-Clark subdivision.
  To subdivide a mesh, call CatmullMesh::subdivide(inputMesh, outputMesh);
  **/

// a face in a CatmullMesh
struct CatmullFace {
    CatmullFace(int numSides);

    int n;
    // these are filled to the correct size in the constructor, so they can be treated like arrays after construction
    QVector<const CatmullFace *> neighbors;
    QVector<int> points; // point indices
    QVector<QPair<int, int> > edges; // edge indices
    int facePoint;
};

// an edge in a CatmullMesh
struct CatmullEdge {
    CatmullEdge() { faces[0] = faces[1] = NULL; }

    Vector3 pos; // position of this edge's edgePoint
    QHash<int, float> jointWeights; // weighted joints for animation
    CatmullFace *faces[2];
};

// a vertex in a CatmullMesh
struct CatmullVertex {
    Vector3 pos;

    QHash<int, float> jointWeights; // weighted joints for animation
    QVector<Vertex *> facePoints; // face points for faces including this vertex
    QVector<CatmullEdge *> edges; // edges including this vertex

};

// a mesh holding additional data used for Catmull-Clark subdivision
class CatmullMesh {
public:
    // create the mesh Catmull mesh from a regular mesh
    CatmullMesh(const Mesh &m);

    bool convertToMesh(Mesh &m);
    static bool subdivide(const Mesh &in, Mesh &out);
    static bool subdivide(Mesh &mesh) { return subdivide(mesh, mesh); }

private:
    QList<CatmullVertex> vertices;
    QMap<QPair<int, int>, CatmullEdge> edges;
    QList<Vertex> facePoints;
    QList<CatmullFace> faces;
    bool valid;

    bool moveVertices();
};

#endif // CATMULLCLARK_H
