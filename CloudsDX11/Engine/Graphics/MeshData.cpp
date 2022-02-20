#include "MeshData.h"

void MeshData::createCube() {
	// Front
	this->vertices.push_back(this->createVert( 0.5f, -0.5f,  0.5f,	0.0f, 1.0f));
	this->vertices.push_back(this->createVert( 0.5f,  0.5f,  0.5f,	0.0f, 0.0f));
	this->vertices.push_back(this->createVert(-0.5f, -0.5f,  0.5f,	1.0f, 1.0f));
	this->vertices.push_back(this->createVert(-0.5f,  0.5f,  0.5f,	1.0f, 0.0f));

	// Back
	this->vertices.push_back(this->createVert( 0.5f, -0.5f, -0.5f,	1.0f, 1.0f));
	this->vertices.push_back(this->createVert(-0.5f, -0.5f, -0.5f,	0.0f, 1.0f));
	this->vertices.push_back(this->createVert( 0.5f,  0.5f, -0.5f,	1.0f, 0.0f));
	this->vertices.push_back(this->createVert(-0.5f,  0.5f, -0.5f,	0.0f, 0.0f));

	// Top
	this->vertices.push_back(this->createVert( 0.5f,  0.5f, -0.5f,	1.0f, 1.0f));
	this->vertices.push_back(this->createVert(-0.5f,  0.5f, -0.5f,	0.0f, 1.0f));
	this->vertices.push_back(this->createVert( 0.5f,  0.5f,  0.5f,	1.0f, 0.0f));
	this->vertices.push_back(this->createVert(-0.5f,  0.5f,  0.5f,	0.0f, 0.0f));

	// Bottom
	this->vertices.push_back(this->createVert( 0.5f, -0.5f, -0.5f,	0.0f, 1.0f));
	this->vertices.push_back(this->createVert( 0.5f, -0.5f,  0.5f,	0.0f, 0.0f));
	this->vertices.push_back(this->createVert(-0.5f, -0.5f, -0.5f,	1.0f, 1.0f));
	this->vertices.push_back(this->createVert(-0.5f, -0.5f,  0.5f,	1.0f, 0.0f));

	// Left
	this->vertices.push_back(this->createVert(0.5f,  0.5f,  -0.5f,	0.0f, 0.0f));
	this->vertices.push_back(this->createVert(0.5f,  0.5f,   0.5f,	1.0f, 0.0f));
	this->vertices.push_back(this->createVert(0.5f, -0.5f,  -0.5f,	0.0f, 1.0f));
	this->vertices.push_back(this->createVert(0.5f, -0.5f,   0.5f,	1.0f, 1.0f));
												  
	// Right
	this->vertices.push_back(this->createVert(-0.5f,  0.5f, -0.5f,	1.0f, 0.0f));
	this->vertices.push_back(this->createVert(-0.5f, -0.5f, -0.5f,	1.0f, 1.0f));
	this->vertices.push_back(this->createVert(-0.5f,  0.5f,  0.5f,	0.0f, 0.0f));
	this->vertices.push_back(this->createVert(-0.5f, -0.5f,  0.5f,	0.0f, 1.0f));

	// Indices
	for (int i = 0; i < 6; ++i)	{
		// Triangle 1
		this->indices.push_back(i * 4 + 0);
		this->indices.push_back(i * 4 + 1);
		this->indices.push_back(i * 4 + 2);

		// Triangle 2
		this->indices.push_back(i * 4 + 1);
		this->indices.push_back(i * 4 + 3);
		this->indices.push_back(i * 4 + 2);
	}
}

void MeshData::createSquare() {
	this->vertices.push_back(this->createVert(0.5f, -0.5f, 0.5f, 0.0f, 1.0f));
	this->vertices.push_back(this->createVert(0.5f, 0.5f, 0.5f, 0.0f, 0.0f));
	this->vertices.push_back(this->createVert(-0.5f, -0.5f, 0.5f, 1.0f, 1.0f));
	this->vertices.push_back(this->createVert(-0.5f, 0.5f, 0.5f, 1.0f, 0.0f));

	for (int i = 0; i < 1; ++i) {
		// Triangle 1
		this->indices.push_back(i * 4 + 0);
		this->indices.push_back(i * 4 + 1);
		this->indices.push_back(i * 4 + 2);

		// Triangle 2
		this->indices.push_back(i * 4 + 1);
		this->indices.push_back(i * 4 + 3);
		this->indices.push_back(i * 4 + 2);
	}
}

void MeshData::createPlane(int resX, int resY)
{
	// Default resolution
	if (resX <= 1 || resY <= 1)
	{
		resX = 10;
		resY = 10;
	}

	// Vertices
	for (int y = 0; y < resY; ++y)
	{
		for (int x = 0; x < resX; ++x)
		{
			this->vertices.push_back(
				this->createVert(
					((float)x / (resX - 1)) - 0.5f,
					0,
					((float)-y / (resY - 1)) + 0.5f,

					(float)x / (resX - 1),
					(float)y / (resY - 1)
				)
			);
		}
	}

	// Indices
	for (int i = 0; i < (resX - 1) * (resY - 1); ++i)
	{
		int squareX = i % (resX - 1);
		int squareY = i / (resX - 1);

		this->indices.push_back(squareY * resX + squareX + 0);
		this->indices.push_back(squareY * resX + squareX + resX + 1);
		this->indices.push_back(squareY * resX + squareX + resX);

		this->indices.push_back(squareY * resX + squareX + 0);
		this->indices.push_back(squareY * resX + squareX + 1);
		this->indices.push_back(squareY * resX + squareX + resX + 1);
	}
}



Vertex MeshData::createVert(float _x, float _y, float _z, float _u, float _v) {
	return { _x, _y, _z, _u, _v };
}

void MeshData::transformVertices(const XMMATRIX& meshTransform) {
	for (int i = 0; i < this->vertices.size(); ++i) {
		// Convert to XMVECTOR and transform
		Vertex tempVert = this->vertices[i];
		XMVECTOR vertexPos = XMVectorSet(tempVert.x, tempVert.y, tempVert.z, 1.0f);
		vertexPos = XMVector4Transform(vertexPos, meshTransform);

		// Convert to XMFLOAT3 and apply
		XMFLOAT3 convertedVertexPos;
		XMStoreFloat3(&convertedVertexPos, vertexPos);

		this->vertices[i].x = convertedVertexPos.x;
		this->vertices[i].y = convertedVertexPos.y;
		this->vertices[i].z = convertedVertexPos.z;
	}
}

MeshData::MeshData(DefaultMesh defaultMeshType, int resolutionX, int resolutionY, bool shouldInvertFaces, const XMMATRIX meshTransform) {

	this->createDefault(defaultMeshType, resolutionX, resolutionY);

	if(shouldInvertFaces)
		this->invertFaces();

	//this->transformVertices(meshTransform);
}

void MeshData::createDefault(DefaultMesh defaultMeshType, int resolutionX, int resolutionY) {
	
	// Remove old data
	this->vertices.resize(0);
	this->indices.resize(0);

	if (defaultMeshType == DefaultMesh::CUBE) {
		this->createCube();
	}
	else if (defaultMeshType == DefaultMesh::SQUARE) {
		this->createSquare();
	}
	else if (defaultMeshType == DefaultMesh::PLANE) {
		this->createPlane(resolutionX, resolutionY);
	}
}

void MeshData::invertFaces() {
	// Swap 2 indices in each triangle
	for (size_t i = 0; i < this->indices.size(); i += 3) {
		int temp = this->indices[i];
		this->indices[i] = this->indices[i + 1];
		this->indices[i + 1] = temp;
	}
}

std::vector<Vertex>& MeshData::getVertices() {
	return this->vertices;
}

std::vector<int>& MeshData::getIndices() {
	return this->indices;
}