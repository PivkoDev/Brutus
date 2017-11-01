#pragma once

#include <map>
#include <string>
#include "ShaderManager.h"
#include "../Rendering/IGameObject.h"
#include "../Rendering/Models/Triangle.h"
#include "../Rendering/Models/Quad.h"


class ModelsManager
{
public:
	ModelsManager();
	~ModelsManager();

	void Draw();
	void Update();
	void DeleteModel(const std::string& game_model_name);
	const IGameObject& GetModel(const std::string& game_model_name) const;

private:
	std::map<std::string, IGameObject*> game_models_list;
};