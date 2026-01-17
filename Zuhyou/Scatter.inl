//////////////////////////////////////////////////////////////////////////////
//
// Zuhyou (https://github.com/Hapaxia/Zuhyou)
//
// Copyright(c) 2023-2026 M.J.Silk
//
// This software is provided 'as-is', without any express or implied
// warranty. In no event will the authors be held liable for any damages
// arising from the use of this software.
//
// Permission is granted to anyone to use this software for any purpose,
// including commercial applications, and to alter it and redistribute it
// freely, subject to the following restrictions :
//
// 1. The origin of this software must not be misrepresented; you must not
// claim that you wrote the original software.If you use this software
// in a product, an acknowledgment in the product documentation would be
// appreciated but is not required.
//
// 2. Altered source versions must be plainly marked as such, and must not be
// misrepresented as being the original software.
//
// 3. This notice may not be removed or altered from any source distribution.
//
// M.J.Silk
// MJSilk2@gmail.com
//
//////////////////////////////////////////////////////////////////////////////

#pragma once

#include "Scatter.hpp"
namespace zuhyou
{

template <class T>
inline Scatter<T>::Scatter()
	: m_isUpdateRequired{ false }
	, m_vertices{}
	, m_axesVertices{}
	, m_points{}
	, m_minXValue{ static_cast<T>(0) }
	, m_maxXValue{ static_cast<T>(1) }
	, m_minYValue{ static_cast<T>(0) }
	, m_maxYValue{ static_cast<T>(1) }
	, m_xAxisValue{ static_cast<T>(0) }
	, m_yAxisValue{ static_cast<T>(0) }
	, m_size{}
	, m_color{ sf::Color::White }
	, m_axesColor{ sf::Color::White }
	, m_showAxes{ true }
	, m_pointShapeTemplate(48u) // default point shape template is an 'X' shape: 8 quads = 16 triangles = 48 vertices
	, m_pointShapeScale{ 5.f, 5.f } // this displays the default point shape template with a size of 10x10
{
	// default point shape template is an 'X' shape: 8 quads = 16 triangles = 48 vertices
	// the vertices range from (-1, -1) to (1, 1)
	for (std::size_t i{ 0u }; i < 48u; ++i)
	{
		constexpr float o{ 0.3f }; // offset from corners, this is effectively the control for the width of the lines
		std::size_t quadIndex{ i / 6u };
		const std::size_t vertexIndex{ i % 6u };
		sf::Vector2f v{ 0.f, 0.f };
		switch (vertexIndex)
		{
		default:
		case 0u:
		case 4u:
			break;
		case 1u:
			v = { 1.f, 1.f };
			break;
		case 2u:
		case 5u:
			v = { 1.f, 1.f - o };
			break;
		case 3u:
			v = { o, 0.f };
			break;
		}
		if (quadIndex > 3u)
		{
			quadIndex -= 4u;
			const float t{ v.x };
			v.x = v.y;
			v.y = -t;
		}
		switch (quadIndex)
		{
		default:
		case 0u:
			break;
		case 1u:
			v.x = -v.x;
			break;
		case 2u:
			v.y = -v.y;
			break;
		case 3u:
			v = -v;
			break;
		}
		m_pointShapeTemplate[i] = v;
	}
}

template<class T>
inline void Scatter<T>::clear()
{
	m_isUpdateRequired = true;
	m_points.clear();
}
template<class T>
inline void Scatter<T>::addPoint(const sf::Vector2<T> point)
{
	m_isUpdateRequired = true;
	m_points.push_back(point);
}
template<class T>
inline void Scatter<T>::addPoints(const std::vector<sf::Vector2<T>>& points)
{
	m_isUpdateRequired = true;
	m_points.insert(m_points.end(), points.begin(), points.end());
}
template<class T>
inline std::size_t Scatter<T>::getNumOfPoints() const
{
	return m_points.size();
}
template<class T>
inline void Scatter<T>::setPoint(const std::size_t pointIndex, const sf::Vector2<T> point)
{
	m_isUpdateRequired = true;
	m_points[pointIndex] = point;
}
template<class T>
inline void Scatter<T>::setMinXValue(const T& minXValue)
{
	m_isUpdateRequired = true;
	m_minXValue = minXValue;
}
template<class T>
inline void Scatter<T>::setMaxXValue(const T& maxXValue)
{
	m_isUpdateRequired = true;
	m_maxXValue = maxXValue;
}
template<class T>
inline void Scatter<T>::setMinYValue(const T& minYValue)
{
	m_isUpdateRequired = true;
	m_minYValue = minYValue;
}
template<class T>
inline void Scatter<T>::setMaxYValue(const T& maxYValue)
{
	m_isUpdateRequired = true;
	m_maxYValue = maxYValue;
}

template<class T>
inline void Scatter<T>::setLimitRect(const sf::Rect<T>& limitRect)
{
	setMinXValue(limitRect.position.x);
	setMinYValue(limitRect.position.y);
	setMaxXValue(limitRect.position.x + limitRect.size.x);
	setMaxYValue(limitRect.position.y + limitRect.size.y);
}

template<class T>
inline T Scatter<T>::getMinXValue() const
{
	return m_minXValue;
}
template<class T>
inline T Scatter<T>::getMaxXValue() const
{
	return m_maxXValue;
}
template<class T>
inline T Scatter<T>::getMinYValue() const
{
	return m_minYValue;
}
template<class T>
inline T Scatter<T>::getMaxYValue() const
{
	return m_maxYValue;
}

template<class T>
inline sf::Rect<T> Scatter<T>::getLimitRect() const
{
	const T minX{ getMinXValue() };
	const T minY{ getMinYValue() };
	const sf::Vector2<T> size{ getMaxXValue() - minX, getMaxYValue() - minY };
	return { { minX, minY }, size };
}

template<class T>
inline void Scatter<T>::setXAxisValue(const T& xAxisValue)
{
	m_isUpdateRequired = true;
	m_xAxisValue = xAxisValue;
}
template<class T>
inline void Scatter<T>::setYAxisValue(const T& yAxisValue)
{
	m_isUpdateRequired = true;
	m_yAxisValue = yAxisValue;
}
template<class T>
inline void Scatter<T>::setAxisPosition(const sf::Vector2<T>& axisPosition)
{
	setXAxisValue(axisPosition.x);
	setYAxisValue(axisPosition.y);
}
template<class T>
inline T Scatter<T>::getXAxisValue() const
{
	return m_xAxisValue;
}
template<class T>
inline T Scatter<T>::getYAxisValue() const
{
	return m_yAxisValue;
}

template<class T>
inline sf::Vector2<T> Scatter<T>::getAxisPosition() const
{
	return { getXAxisValue(), getYAxisValue() };
}



template<class T>
inline void Scatter<T>::setSize(const sf::Vector2f size)
{
	m_isUpdateRequired = true;
	m_size = size;
}
template<class T>
inline void Scatter<T>::setColor(const sf::Color color)
{
	m_isUpdateRequired = true;
	m_color = color;
}
template<class T>
inline void Scatter<T>::setAxesColor(sf::Color axesColor)
{
	m_isUpdateRequired = true;
	m_axesColor = axesColor;
}
template<class T>
inline void Scatter<T>::setShowAxes(bool showAxes)
{
	m_isUpdateRequired = true;
	m_showAxes = showAxes;
}

template<class T>
inline sf::Vector2f Scatter<T>::getSize() const
{
	return m_size;
}
template<class T>
inline sf::Color Scatter<T>::getColor() const
{
	return m_color;
}
template<class T>
inline sf::Color Scatter<T>::getAxesColor() const
{
	return m_axesColor;
}
template<class T>
inline bool Scatter<T>::getShowAxes() const
{
	return m_showAxes;
}

template<class T>
inline void Scatter<T>::setPointShapeTemplateVertices(const std::vector<sf::Vector2f>& pointShapeTemplateVertices)
{
	m_isUpdateRequired = true;
	m_pointShapeTemplate = pointShapeTemplateVertices;
}
template<class T>
inline void Scatter<T>::setPointShapeTemplateNumOfVertices(const std::size_t numOfPointShapeVertices)
{
	m_isUpdateRequired = true;
	m_pointShapeTemplate.resize(numOfPointShapeVertices);
}
template<class T>
inline void Scatter<T>::setPointShapeTemplateVertex(const std::size_t pointShapeVertexIndex, const sf::Vector2f pointShapeVertex)
{
	m_isUpdateRequired = true;
	m_pointShapeTemplate[pointShapeVertexIndex] = pointShapeVertex;
}
template<class T>
inline void Scatter<T>::setPointShapeTemplateScale(const sf::Vector2f pointShapeScale)
{
	m_isUpdateRequired = true;
	m_pointShapeScale = pointShapeScale;
}
template<class T>
inline void Scatter<T>::setPointShapeTemplateScale(const float pointShapeScale)
{
	setPointShapeTemplateScale({ pointShapeScale, pointShapeScale });
}








// PRIVATE
template <class T>
inline void Scatter<T>::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	states.transform *= getTransform();

	if (m_isUpdateRequired)
		priv_updateVertices();

	target.draw(m_vertices.data(), m_vertices.size(), sf::PrimitiveType::Triangles, states);
}

template <class T>
inline void Scatter<T>::priv_updateVertices() const
{
	m_isUpdateRequired = false;

	sf::Vector2f scaledSize{ m_size.x / (m_maxXValue - m_minXValue), m_size.y / (m_maxYValue - m_minYValue) };

	const std::size_t numOfVerticesPerPoint{ m_pointShapeTemplate.size() };
	const std::size_t numOfPoints{ m_points.size() };
	const std::size_t numOfVertices{ numOfPoints * numOfVerticesPerPoint };
	m_vertices.resize(numOfVertices);

	for (std::size_t p{ 0u }; p < numOfPoints; ++p)
	{
		const std::size_t startVertexIndex{ p * numOfVerticesPerPoint };
		const sf::Vector2f position{ m_points[p] };
		for (std::size_t v{ 0u }; v < numOfVerticesPerPoint; ++v)
		{
			const std::size_t vertexIndex{ startVertexIndex + v };
			m_vertices[vertexIndex].color = m_color;
			m_vertices[vertexIndex].position = scaledSize.componentWiseMul(position) + (m_pointShapeTemplate[v].componentWiseMul(m_pointShapeScale));
		}
	}
}

} // namespace zuhyou
