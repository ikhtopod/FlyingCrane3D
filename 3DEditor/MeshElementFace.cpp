#include "MeshElementFace.h"


const GLenum MeshElementFace::DEFAULT_MESH_TYPE = GL_LINE_LOOP;

MeshElementFace::MeshElementFace(Face& _face) :
	MeshElementFace(_face.first, _face.second, _face.third) {}

MeshElementFace::MeshElementFace(Vertex& first, Vertex& second, Vertex& third) :
	MeshElement(DEFAULT_MESH_TYPE) {

	this->vertices.insert(this->vertices.end(), { first, second, third });
	this->indices.insert(this->indices.end(), { 0, 1, 2 });

	glm::vec3 markCenter = (first.position + second.position + third.position) / 3.0f;
	float scale = 0.05f;

	this->markPoints.insert(
		this->markPoints.end(), {
			{ ((first.position - markCenter) * scale) + markCenter, 0 },
			{ ((second.position - markCenter) * scale) + markCenter, 1 },
			{ ((third.position - markCenter) * scale) + markCenter, 2 },
		}
	);
}


void MeshElementFace::initMark() {
	glGenVertexArrays(BUFFER_SIZE, &this->vaoMark);
	glGenBuffers(BUFFER_SIZE, &this->vboMark);

	glBindVertexArray(this->vaoMark);

	glBindBuffer(GL_ARRAY_BUFFER, this->vboMark);
	glBufferData(GL_ARRAY_BUFFER, this->markPoints.size() * sizeof(Vertex),
				 &(this->markPoints)[0], GL_STREAM_DRAW);

	// vertex positions
	glEnableVertexAttribArray(MeshBase::AttribIndex::POSITION);
	glVertexAttribPointer(MeshBase::AttribIndex::POSITION, 3,
						  GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)0);

	glBindVertexArray(0); // unbind
}

void MeshElementFace::drawMark() {
	glBindVertexArray(this->vaoMark);
	glLineWidth(2.5f);
	glDrawArrays(GL_LINE_LOOP, 0, 3);
	glLineWidth(1.0f);
	glBindVertexArray(0); // unbind
}

void MeshElementFace::freeMark() {
	glDeleteVertexArrays(BUFFER_SIZE, &this->vaoMark);
	glDeleteBuffers(BUFFER_SIZE, &this->vboMark);
}


void MeshElementFace::init() {
	MeshElement::init();
	this->initMark();
}

void MeshElementFace::draw() {
	MeshElement::draw();
	this->drawMark();
}

void MeshElementFace::free() {
	MeshElement::free();
	this->freeMark();
}
