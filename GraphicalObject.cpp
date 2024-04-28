#include"GraphicalObject.h"


// Graphical Object Class Functions -----------------------------------------------------------------------------------

GraphicalObj::~GraphicalObj()
{
	glDeleteVertexArrays(1, &this->VBO);
}

void GraphicalObj::BufferUpdate()
{
	glGenBuffers(1, &this->VBO);
	glGenVertexArrays(1, &this->VAO);
	glGenBuffers(1, &this->EBO);

	glBindBuffer(GL_ARRAY_BUFFER, this->VBO);
	glBufferData(GL_ARRAY_BUFFER, vertexBuffer.size() * sizeof(float), static_cast<const void*>(vertexBuffer.data()), GL_STATIC_DRAW);

	glBindVertexArray(this->VAO);

	if (!indexBuffer.empty())
	{
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, this->EBO);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, indexBuffer.size() * sizeof(int), static_cast<const void*>(indexBuffer.data()), GL_STATIC_DRAW);


		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
		glEnableVertexAttribArray(0);

		/*glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
		glEnableVertexAttribArray(1);*/

		glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));
		glEnableVertexAttribArray(1);
	}
	else 
	{
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
		glEnableVertexAttribArray(0);

		glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));
		glEnableVertexAttribArray(1);
	}
}

void GraphicalObj::SetShader(Shader* shader)
{
	Objshader = shader;
	BufferUpdate();
}

void GraphicalObj::VertexUpdate(vector<float>* vertices, vector<int>* indices)
{
	vertexBuffer.clear();

	for (float v : *vertices)
		vertexBuffer.push_back(v);

	if (indices != nullptr)
	{
		indexBuffer.clear();
		for (int i : *indices)
			indexBuffer.push_back(i);
	}
	else 
	{
		indexBuffer.clear();
	}

	this->BufferUpdate();
}

void GraphicalObj::DrawShape(glm::vec3 color)
{
	//this->BufferUpdate();
	this->Objshader->use();

	// Setting the Color
	this->Objshader->set3fv("myColor", color);
	transform();

	if(this->Objshader->HasTexture())
	{
		glBindTexture(GL_TEXTURE_2D, this->Objshader->texture);

		if (!indexBuffer.empty())
		{
			glBindVertexArray(this->VAO);
			glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, this->EBO);
			glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
			glBindTexture(GL_TEXTURE_2D, 0);
			glBindVertexArray(0);
		}
		else
		{
			glBindVertexArray(this->VAO);
			glDrawArrays(GL_TRIANGLES, 0, 36);
			glBindTexture(GL_TEXTURE_2D, 0);
			glBindVertexArray(0);
		}
	}
	else 
	{
		if (!indexBuffer.empty())
		{
			glBindVertexArray(this->VAO);
			glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, this->EBO);
			glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
			glBindVertexArray(0);
		}
		else
		{
			glBindVertexArray(this->VAO);
			glDrawArrays(GL_TRIANGLES, 0, 36);
			glBindVertexArray(0);
		}
	}
}


void GraphicalObj::transform(glm::vec3 scale, glm::vec3 translate, glm::float32 rotate)
{
	Shader* ThisObjectShader{ getShader() };
	ThisObjectShader->use();
	model = glm::mat4(1.0f);
	model = glm::scale(model, scale);
	model = glm::translate(model, translate);
	model = glm::rotate(model, (float)glfwGetTime() * glm::radians(50.0f), glm::vec3(0.5f, 1.0f, 0.0f));
	glm::mat4 view = glm::mat4(1.0f);
	view = glm::translate(view, glm::vec3(0.0f, 0.0f, -3.0f));
	glm::mat4 projection;
	projection = glm::perspective(glm::radians(45.0f), 1.0f, 0.1f, 100.0f);

	ThisObjectShader->set4mat("model", model);
	ThisObjectShader->set4mat("view", view);
	ThisObjectShader->set4mat("projection", projection);
}

Shader* GraphicalObj::getShader()
{
	return this->Objshader;
}