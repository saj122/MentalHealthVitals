//
// Created by stephen on 9/26/21.
//

#ifndef OBJECTBUILDER_H
#define OBJECTBUILDER_H

class ObjectBuilder
{

    public:
        ObjectBuilder() = delete;
        ~ObjectBuilder()
        {
            delete _vertexData;
        }
        void setVertexDataSize(int sizeInVertices)
        {
            _vertexData = new float[sizeInVertices * FLOATS_PER_VERTEX];
        }

    private:
        const int FLOATS_PER_VERTEX = 3;
        const float* _vertexData;
        int _offset = 0;
};

#endif // OBJECTBUILDER_H
