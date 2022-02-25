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
		resX = 50;
		resY = 50;
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

void MeshData::createSkyPlane(int skyPlaneResolution, float skyPlaneWidth, float skyPlaneTop, float skyPlaneBottom, int textureRepeat) {
	
	float quadSize, radius, constant, textureDelta;
	int i, j, index;
	float positionX, positionY, positionZ, tu, tv;

	// Determine the size of each quad on the sky plane.
	quadSize = skyPlaneWidth / (float)skyPlaneResolution;

	// Calculate the radius of the sky plane based on the width.
	radius = skyPlaneWidth / 2.0f;

	// Calculate the height constant to increment by.
	constant = (skyPlaneTop - skyPlaneBottom) / (radius * radius);

	// Calculate the texture coordinate increment value.
	textureDelta = (float)textureRepeat / (float)skyPlaneResolution;

	// Loop through the sky plane and build the coordinates based on the increment values given.
	for (j = 0; j <= skyPlaneResolution; j++)
	{
		for (i = 0; i <= skyPlaneResolution; i++)
		{
			// Calculate the vertex coordinates.
			positionX = (-0.5f * skyPlaneWidth) + ((float)i * quadSize);
			positionZ = (-0.5f * skyPlaneWidth) + ((float)j * quadSize);
			positionY = skyPlaneTop - (constant * ((positionX * positionX) + (positionZ * positionZ)));

			// Calculate the texture coordinates.
			tu = (float)i * textureDelta;
			tv = (float)j * textureDelta;

			this->vertices.push_back(this->createVert(positionX, positionY, positionZ, tu, tv));

			// Calculate the index into the sky plane array to add this coordinate.
			index = j * (skyPlaneResolution + 1) + i;

			this->indices.push_back(index);
		}
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
	else if (defaultMeshType == DefaultMesh::SKY_PLANE) {
		int skyPlaneResolution, textureRepeat;
		float skyPlaneWidth, skyPlaneTop, skyPlaneBottom;
		bool result;

		skyPlaneResolution = 50;
		skyPlaneWidth = 10.0f;
		skyPlaneTop = 0.5f;
		skyPlaneBottom = 0.0f;
		textureRepeat = 2;

		this->createSkyPlane(skyPlaneResolution, skyPlaneWidth, skyPlaneTop, skyPlaneBottom, textureRepeat);

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