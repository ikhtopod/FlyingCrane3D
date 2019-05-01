#include "MeshElement.h"

const std::string MeshElement::ELEMENT_VERTEX_SHADER =
R"(..\resources\shaders\mesh-element-shader.vs)";

const std::string MeshElement::ELEMENT_FRAGMENT_SHADER =
R"(..\resources\shaders\mesh-element-shader.fs)";


MeshElement::MeshElement(GLenum _type) :
	MeshElement(_type,
				Shader {
					ELEMENT_VERTEX_SHADER,
					ELEMENT_FRAGMENT_SHADER
				}
	) {}


MeshElement::MeshElement(GLenum _type, Shader _shader) :
	MeshBase(_type, _shader) {}
