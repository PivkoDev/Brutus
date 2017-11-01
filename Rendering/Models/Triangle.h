#pragma once

#include "Model.h"
#include "../VertexFormat.h"

class Triangle : public Model
{
public:
	Triangle();
	~Triangle();

	void Create();
	virtual void Update() override final;
	virtual void Draw() override final;
};
