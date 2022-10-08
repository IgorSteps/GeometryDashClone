#include "Transform.h"
#include <Parser.h>
Transform::Transform(glm::vec2 position)
{
	this->position = position;
	this->scale = glm::vec2(1.0f, 1.0f);
	this->rotateion = 0.0f;
}

Transform::Transform(){}

Transform::Transform(Transform* trans)
{
	position = trans->position;
	scale = trans->scale;
	rotateion = trans->rotateion;
}


Transform* Transform::copy()
{
	Transform* tr = new Transform(this->position);
	
	tr->scale = this->scale;
	tr->rotateion = this->rotateion;

	return tr;
}

std::string Transform::serialise(int tabsize)
{
	std::string builder;
	builder.append(beginObjectProperty("Transform", tabsize));
	
	// Position
	builder.append(beginObjectProperty("Position", tabsize + 1));
	std::string builderPosition;
	builderPosition.append(addFloatProperty("x", position.x, tabsize + 2, true, true));
	builderPosition.append(addFloatProperty("y", position.y, tabsize + 2, true, false));
	builder.append(builderPosition);
	builder.append(closeObjectProperty(tabsize + 1));
	builder.append(addEnding(true, true));

	// Scale
	builder.append(beginObjectProperty("Scale", tabsize+1));
	std::string builderScale;
	builderScale.append(addFloatProperty("x", scale.x, tabsize + 2, true, true));
	builderScale.append(addFloatProperty("y", scale.y, tabsize + 2, true, false));
	builder.append(builderScale);
	builder.append(closeObjectProperty(tabsize + 1));
	builder.append(addEnding(true, true));

	// Rotation
	builder.append(addFloatProperty("rotation", rotateion, tabsize + 1, true, false));
	builder.append(closeObjectProperty(tabsize));

	return builder;
}

Transform* Transform::deserialise()
{
	Parser::consumeBeginObjectProperty("Transform");

	// Position
	Parser::consumeBeginObjectProperty("Position");
	float x = Parser::consumeFloatProperty("x");
	Parser::consume(','); // don't forget the comma between them
	float y = Parser::consumeFloatProperty("y");

	glm::vec2 pos = glm::vec2(x, y);
	Parser::consumeEndObjectProperty(); 
	Parser::consume(',');

	// Scale
	Parser::consumeBeginObjectProperty("Scale");
	 x = Parser::consumeFloatProperty("x");
	Parser::consume(','); // don't forget the comma between them
	 y = Parser::consumeFloatProperty("y");

	glm::vec2 sca = glm::vec2(x, y);
	Parser::consumeEndObjectProperty();
	Parser::consume(',');

	// Rotation
	float rotation = Parser::consumeFloatProperty("rotation");
	Parser::consumeEndObjectProperty();

	// Create Transform
	Transform* t = new Transform(pos);
	t->scale = sca;
	t->rotateion = rotation;

	return t;
}
