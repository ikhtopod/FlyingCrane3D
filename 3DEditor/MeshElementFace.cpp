#include "MeshElementFace.h"


const GLenum MeshElementFace::DEFAULT_MESH_TYPE = GL_LINE_LOOP;

MeshElementFace::MeshElementFace(Face* _face) :
	MeshElement(DEFAULT_MESH_TYPE), face(_face) {

	this->vertices.insert(this->vertices.end(),
						  { *this->face->first, *this->face->second, *this->face->third });
	this->indices.insert(this->indices.end(), { 0, 1, 2 });

	this->updateMarkList();
}

void MeshElementFace::updateMarkList() {
	glm::vec3 pos1 = this->face->first->position;
	glm::vec3 pos2 = this->face->second->position;
	glm::vec3 pos3 = this->face->third->position;

	glm::vec3 markCenter = (pos1 + pos2 + pos3) / 3.0f;
	float scale = 0.05f;

	this->markPoints.insert(
		this->markPoints.end(), {
			{ ((pos1 - markCenter) * scale) + markCenter, 0 },
			{ ((pos2 - markCenter) * scale) + markCenter, 1 },
			{ ((pos3 - markCenter) * scale) + markCenter, 2 },
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
	glDrawArrays(DEFAULT_MESH_TYPE, 0, 3);
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
