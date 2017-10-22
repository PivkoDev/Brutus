#include "GameModels.h"

const auto VEC3SIZE = sizeof(glm::vec3);

GameModels::GameModels()
{
}

GameModels::~GameModels()
{
	for (auto& it : GameModelList)
	{
		// Delete VAO and VBOs (if many)
		unsigned int* p = &(it.second.vao);
		glDeleteVertexArrays(1, p);
		glDeleteBuffers(it.second.vbos.size(), &(it.second.vbos[0]));
		it.second.vbos.clear();
	}
	GameModelList.clear();
}

void
GameModels::CreateTriangleModel(const std::string& gameModelName)
{
	unsigned int vao;
	unsigned int vbo;

	glGenVertexArrays(1, &vao);
	glBindVertexArray(vao);

	std::vector<VertexFormat> vertices;
	vertices.push_back(
		VertexFormat(glm::vec3(0.25, -0.25, 0.0),
					 glm::vec4(1,0,0,1)));
	vertices.push_back(
		VertexFormat(glm::vec3(-0.25, -0.25, 0.0),
			         glm::vec4(0,1,0,1)));
	vertices.push_back(
		VertexFormat(glm::vec3(0.25, 0.25, 0.0),
			         glm::vec4(0,0,0,1)));

	glGenBuffers(1, &vbo);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBufferData(GL_ARRAY_BUFFER, sizeof(VertexFormat) * vertices.size(), &vertices[0], GL_STATIC_DRAW);

	// Layout qualifier (pipeline) : 0
	glEnableVertexAttribArray(0);
	// Interleaved attribute instead of separate buffers.
	// All parameters change probabilty is equal
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(VertexFormat), (void*)0);
	
	// Layout qualifier (pipeline) : 1
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, sizeof(VertexFormat), (void*)VEC3SIZE);


	Model myModel;
	myModel.vao = vao;
	myModel.vbos.push_back(vbo);
	GameModelList[gameModelName] = myModel;
}

void
GameModels::DeleteModel(const std::string& gameModelName)
{
	Model model = GameModelList[gameModelName];
	unsigned int p = model.vao;
	glDeleteVertexArrays(1, &p);
	glDeleteBuffers(model.vbos.size(), &model.vbos[0]);
	model.vbos.clear();
	GameModelList.erase(gameModelName);

}

unsigned int
GameModels::GetModel(const std::string& gameModelName)
{
	if (GameModelList.count(gameModelName) > 0)
	{
		return GameModelList[gameModelName].vao;
	}
	else
	{
		return 0;
	}
}
