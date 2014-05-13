#ifndef TRANSFORM_H_
#define TRANSFORM_H_

#include <glm/glm.hpp>

class Transform2D
{
private:
	float			m_rotation;
	glm::vec3		m_position;
	float			m_scale;

	glm::mat4		m_matrix;

public:
	Transform2D();
	virtual ~Transform2D();

	void 				Clone(const Transform2D& transform);

	Transform2D& 		SetRotation(float rotation);
	float 				GetRotation() const;

	Transform2D& 		SetPosition(const glm::vec3& position);
	const glm::vec3& 	GetPosition() const;

	Transform2D& 		SetScale(const float scale);
	const float 		GetScale() const;

	void 				ApplyForward(const glm::vec4& in, glm::vec4& out) const;
	void 				ApplyInverse(const glm::vec4& in, glm::vec4& out) const;

	void 				UpdateMatrix();

	const glm::mat4&	GetMatrix() const;
	void 				GetInverseMatrix(glm::mat4& out) const;
};

#endif /* TRANSFORM_H_ */
