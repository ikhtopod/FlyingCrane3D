#pragma once

#include "MeshBase.h"
#include "Shader.h"
#include "PolymeshRepresentation.h"


class Mesh final : public MeshBase {
private:
	static const GLenum DEFAULT_MESH_TYPE;

private:
	PolymeshRepresentation polymesh;

public:
	Mesh() = delete;
	Mesh(PolymeshRepresentation _polymesh);
	Mesh(PolymeshRepresentation _polymesh, GLenum _type);
	Mesh(PolymeshRepresentation _polymesh, GLenum _type, Shader _shader);
	~Mesh() = default;

	PolymeshRepresentation& getPolymesh();

	virtual void init() override;
	virtual void draw() override;
	virtual void free() override;
};
