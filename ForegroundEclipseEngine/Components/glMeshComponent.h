#pragma once

#include<string>

#include"../EngineSystem/glSystem/VAO.h"
#include"../EngineSystem/glSystem/EBO.h"
#include"glCameraComponent.h"
#include"../EngineSystem/glSystem/Texture.h"

#include<json/json.h>
#include"../EngineSystem/glSystem/Mesh.h"
#include "../GameElements/Behaviour.h"
#include "IMesh.h"

using json = nlohmann::json;

class GameObject;
class glMeshComponent : public Behaviour, public IMesh
{
public:
	glMeshComponent(const char* file);

	inline virtual void SetActive(bool isActive) override { enabled = isActive; }

	virtual void DrawMesh() override;
	void SetDrawInfo(Shader& shader, glCameraComponent& camera);

private:
	void Draw(Shader& shader, glCameraComponent& camera);
	// ���� �޽� �ε�
	void loadMesh(unsigned int indMesh);
	// ��� ��ȸ
	void traverseNode(unsigned int nextNode, glm::mat4 matrix = glm::mat4(1.0f));
	std::vector<unsigned char> getData();
	// ���̳ʸ� ������ �ؼ�
	std::vector<float> getFloats(json accessor);
	std::vector<GLuint> getIndices(json accessor);
	std::vector<Texture> getTextures();
	// ���ļ� ���� ������ �����
	std::vector<Vertex> assembleVertices
	(
		std::vector<glm::vec3> positions,
		std::vector<glm::vec3> normals,
		std::vector<glm::vec2> texUVs
	);
	std::vector<glm::vec2> groupFloatsVec2(std::vector<float> floatVec);
	std::vector<glm::vec3> groupFloatsVec3(std::vector<float> floatVec);
	std::vector<glm::vec4> groupFloatsVec4(std::vector<float> floatVec);

	Shader* targetShader;
	glCameraComponent* targetCamera;

	const char* file;
	std::vector<unsigned char> data;
	json JSON;

	std::vector<Mesh> meshes;
	std::vector<glm::vec3> translationsMeshes;
	std::vector<glm::quat> rotationsMeshes;
	std::vector<glm::vec3> scalesMeshes;
	std::vector<glm::mat4> matricesMeshes;

	std::vector<std::string> loadedTexName;
	std::vector<Texture> loadedTex;
};