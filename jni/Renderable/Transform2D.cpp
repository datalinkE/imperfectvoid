#include "Transform2D.h"
#include <glm/gtc/matrix_transform.hpp>

Transform2D::Transform2D()
	:	m_rotation(0)
	,	m_position(0.0f, 0.0f, 0.0f)
	,	m_scale(1.0f)
	,	m_matrix(1.0f)
{
}

Transform2D::~Transform2D()
{
}

void Transform2D::Clone(const Transform2D& transform)
{
	m_rotation = transform.m_rotation;
	m_position = transform.m_position;
	m_scale = transform.m_scale;

	UpdateMatrix();
}

Transform2D& Transform2D::SetRotation(float rotation)
{
	m_rotation = rotation;
	UpdateMatrix();
	return *this;
}

float Transform2D::GetRotation() const
{
	return m_rotation;
}

Transform2D& Transform2D::SetPosition(const glm::vec3& position)
{
	m_position = position;
	UpdateMatrix();
	return *this;
}

const glm::vec3& Transform2D::GetPosition() const
{
	return m_position;
}

Transform2D& Transform2D::SetScale(const float scale)
{
	m_scale = scale;
	UpdateMatrix();
	return *this;
}

const float Transform2D::GetScale() const
{
	return m_scale;
}

void Transform2D::ApplyForward(const glm::vec4& in, glm::vec4& out) const
{
	out = in;
	out *= m_scale;
	if(m_rotation)
	{
		out = glm::rotate(glm::mat4(1), m_rotation, glm::vec3(0.0f, 0.0f, 1.0f)) * out;
	}
	out += glm::vec4(m_position, 0.f);
}

void Transform2D::ApplyInverse(const glm::vec4& in, glm::vec4& out) const
{
	out = in;
	out -= glm::vec4(m_position, 0.f);
	if(m_rotation)
	{
		out = glm::rotate(glm::mat4(1.f), -m_rotation, glm::vec3(0.0f, 0.0f, 1.0f)) * out;
	}
	out /= m_scale;
}

void Transform2D::UpdateMatrix()
{
	m_matrix = glm::mat4(1.f);
	m_matrix = glm::scale(m_matrix, glm::vec3(m_scale));
	m_matrix = glm::rotate(m_matrix, m_rotation, glm::vec3(0.0f, 0.0f, 1.0f));
	m_matrix = glm::translate(glm::mat4(1.f), m_position) * m_matrix;
}

const glm::mat4& Transform2D::GetMatrix() const
{
	return m_matrix;
}

void Transform2D::GetInverseMatrix(glm::mat4& out) const
{
	out = glm::inverse(m_matrix);
}
