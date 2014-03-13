#ifndef OBJ_LOADER_H_INCLUDED
#define OBJ_LOADER_H_INCLUDED

#include "math3d.h"
#include <vector>
#include <string>

struct OBJIndex
{
    unsigned int vertexIndex;
    unsigned int uvIndex;
    unsigned int normalIndex;
    
    bool operator<(const OBJIndex& r) const { return vertexIndex < r.vertexIndex; }
};

class IndexedModel
{
public:
    std::vector<Vector3f> positions;
    std::vector<Vector2f> texCoords;
    std::vector<Vector3f> normals;
    std::vector<unsigned int> indices;
    
    void CalcNormals();
};

class OBJModel
{
public:
    std::vector<OBJIndex> OBJIndices;
    std::vector<Vector3f> vertices;
    std::vector<Vector2f> uvs;
    std::vector<Vector3f> normals;
    bool hasUVs;
    bool hasNormals;
    
    OBJModel(const std::string& fileName);
    
    IndexedModel ToIndexedModel();
private:
    unsigned int FindLastVertexIndex(const std::vector<OBJIndex*>& indexLookup, const OBJIndex* currentIndex, const IndexedModel& result) const;
    void CreateOBJFace(const std::string& line);
    
    //Vector2f ParseOBJVec2(const std::string& line);
    //Vector3f ParseOBJVec3(const std::string& line);
    //OBJIndex ParseOBJIndex(const std::string& token, bool* hasUVs, bool* hasNormals);
};

#endif // OBJ_LOADER_H_INCLUDED
