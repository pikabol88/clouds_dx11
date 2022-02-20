#pragma once
#include "ShaderHandlers/SkyboxShader.h"
#include "ShaderHandlers/SkyPlaneShaderClass.h"
#include "Engine/Graphics/Texture.h"
#include "Examples/GameObjects/Skybox.h"


class Clouds {

	struct CloudsBuffer {
		float translation;
		float scale;
		float brightness;
		float padding;
	} cb{};

	Renderer& renderer;

	MeshData meshData;
	Mesh mesh;

	Skybox *skybox;

	SkyPlaneShaderClass shader;
	ConstantBuffer constantBuffer;
	Texture  perturbTexture;
	Texture cloudTexture;

public:

	Clouds(Renderer& renderer);
	~Clouds();

	void draw();

	void setSkybox(Skybox& skybox);
};

