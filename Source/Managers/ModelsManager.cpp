#include "ModelsManager.h"

ModelsManager::ModelsManager()
{
	Triangle* triangle = new Triangle();
	triangle->SetProgram(ShaderManager::GetShader("ColorShader1"));
	triangle->Create();
	game_models_list["triangle"] = triangle;

	Quad* quad = new Quad();
	quad->SetProgram(ShaderManager::GetShader("ColorShader1"));
	quad->Create();
	game_models_list["quad"] = quad;
}

ModelsManager::~ModelsManager()
{
	for (auto model : game_models_list)
	{
		delete model.second;
	}
	game_models_list.clear();
}

void 
ModelsManager::DeleteModel(const std::string& game_model_name)
{
	IGameObject* model = game_models_list[game_model_name];
	model->Destroy();
	game_models_list.erase(game_model_name);
}

const IGameObject& 
ModelsManager::GetModel(const std::string& game_model_name) const
{
	return (*game_models_list.at(game_model_name));
}

void 
ModelsManager::Update()
{
	for (auto model : game_models_list)
	{
		model.second->Update();
	}
}

void 
ModelsManager::Draw()
{
	for (auto model : game_models_list)
	{
		model.second->Draw();
	}
}