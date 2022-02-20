#include "pch.h"
#include "Clouds.h"


Clouds::Clouds(Renderer& renderer): skybox(nullptr), meshData(DefaultMesh::PLANE, 50, 50, false), mesh(renderer, this->meshData),
shader(renderer), constantBuffer(renderer, sizeof(CloudsBuffer)),renderer(renderer),
perturbTexture(renderer, TextureFilter::BILINEAR, TextureFormat::R16G16B16A16_UNORM, TextureEdgeSampling::REPEAT),
cloudTexture(renderer, TextureFilter::BILINEAR, TextureFormat::R8G8B8A8_UNORM, TextureEdgeSampling::REPEAT) {
	
	//Load dds clouds textures
	this->cloudTexture.createFromFile("Resources/Textures/cloud001.dds");
	this->perturbTexture.createFromFile("Resources/Textures/perturb001.dds");
	cb.brightness = 0.5f;
	cb.scale = 0.3f;
	cb.padding = 0.0f;
	cb.translation = 0.0f;
}

Clouds::~Clouds(){}

void Clouds::draw() {
	cb.translation += 0.0001f;
	if (cb.translation > 1.0f)
	{
		cb.translation -= 1.0f;
	}
	this->constantBuffer.update(&this->cb);
	this->cloudTexture.setPS(0);
	this->perturbTexture.setPS(1);
	this->shader.update(renderer, this->skybox->getWorldMatrix());
	this->shader.set();
	this->mesh.draw();
}

void Clouds::setSkybox(Skybox& skybox) {
	this->skybox = &skybox;
}
