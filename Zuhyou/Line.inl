//////////////////////////////////////////////////////////////////////////////
//
// Zuhyou (https://github.com/Hapaxia/Zuhyou)
//
// Copyright(c) 2023-2024 M.J.Silk
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

#include "Line.hpp"
namespace zuhyou
{

template<class T>
inline Line<T>::Line()
	: m_isUpdateRequired{ false }
	, m_lineVertices{}
	, m_areaVertices{}
	, m_values{}
	, m_minValue{ static_cast<T>(0) }
	, m_maxValue{ static_cast<T>(1) }
	, m_size{}
	, m_lineColor{ sf::Color::White }
	, m_areaColor{ sf::Color(128u, 128u, 128u) }
	, m_showLine{ true }
	, m_showArea{ false }
{

}

template<class T>
inline void Line<T>::setNumberOfValues(std::size_t numberOfValues)
{
	m_isUpdateRequired = true;
	m_values.resize(numberOfValues);
}
template<class T>
inline void Line<T>::setValues(const std::vector<T>& values)
{
	m_values = values;
}
template<class T>
inline void Line<T>::setValues(const std::vector<T>&& values)
{
	m_values = std::move(values);
}
template<class T>
inline void Line<T>::setValue(std::size_t index, const T& value)
{
	if (index >= m_values.size())
		throw(Exception("Unable to set value; invalid index."));

	m_isUpdateRequired = true;
	m_values[index] = value;
}
template<class T>
inline void Line<T>::setMinValue(const T& minValue)
{
	m_isUpdateRequired = true;
	m_minValue = minValue;
}
template<class T>
inline void Line<T>::setMaxValue(const T& maxValue)
{
	m_isUpdateRequired = true;
	m_maxValue = maxValue;
}

template<class T>
inline std::size_t Line<T>::getNumberOfValues() const
{
	return m_values.size();
}
template<class T>
inline T Line<T>::getValue(std::size_t index) const
{
	if (index >= m_values.size())
		throw(Exception("Unable to get value; invalid index."));

	return m_values[index];
}
template<class T>
inline T Line<T>::getMinValue() const
{
	return m_minValue;
}
template<class T>
inline T Line<T>::getMaxValue() const
{
	return m_maxValue;
}

template<class T>
inline void Line<T>::setSize(sf::Vector2f size)
{
	m_isUpdateRequired = true;
	m_size = size;
}
template<class T>
inline void Line<T>::setLineColor(sf::Color lineColor)
{
	m_isUpdateRequired = true;
	m_lineColor = lineColor;
}
template<class T>
inline void Line<T>::setAreaColor(sf::Color areaColor)
{
	m_isUpdateRequired = true;
	m_areaColor = areaColor;
}
template<class T>
inline void Line<T>::setShowLine(bool showLine)
{
	m_isUpdateRequired = true;
	m_showLine = showLine;
}
template<class T>
inline void Line<T>::setShowArea(bool showArea)
{
	m_isUpdateRequired = true;
	m_showArea = showArea;
}

template<class T>
inline sf::Vector2f Line<T>::getSize() const
{
	return m_size;
}
template<class T>
inline sf::Color Line<T>::getLineColor() const
{
	return m_lineColor;
}
template<class T>
inline sf::Color Line<T>::getAreaColor() const
{
	return m_areaColor;
}
template<class T>
inline bool Line<T>::getShowLine() const
{
	return m_showLine;
}
template<class T>
inline bool Line<T>::getShowArea() const
{
	return m_showArea;
}







// PRIVATE
template<class T>
inline void Line<T>::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	states.transform *= getTransform();

	if (m_isUpdateRequired)
		priv_updateVertices();

	if (m_showArea)
		target.draw(m_areaVertices.data(), m_areaVertices.size(), sf::PrimitiveType::TrianglesStrip, states);
	if (m_showLine)
		target.draw(m_lineVertices.data(), m_lineVertices.size(), sf::PrimitiveType::LineStrip, states);
}
template<class T>
inline void Line<T>::priv_updateVertices() const
{
	m_isUpdateRequired = false;
	const std::size_t numberOfValues{ m_values.size() };
	if (numberOfValues < 2u)
	{
		m_lineVertices.clear();
		m_areaVertices.clear();
		return;
	}
	constexpr std::size_t numberOfAreaVerticesPerValue{ 2u };
	m_lineVertices.resize(numberOfValues);
	m_areaVertices.resize(numberOfValues * numberOfAreaVerticesPerValue);
	const std::size_t finalValueIndex{ numberOfValues - 1u };
	for (std::size_t i{ 0u }; i <= finalValueIndex; ++i)
	{
		float alphaValue{ static_cast<float>(static_cast<double>(m_values[i] - m_minValue) / (m_maxValue - m_minValue)) };
		const sf::Vector2f point{ i * m_size.x / finalValueIndex, (1.f - alphaValue) * m_size.y };
		m_lineVertices[i].position = point;
		m_lineVertices[i].color = m_lineColor;
		const std::size_t areaBaseVertexIndex{ i * numberOfAreaVerticesPerValue };
		m_areaVertices[areaBaseVertexIndex + 0u].position = point;
		m_areaVertices[areaBaseVertexIndex + 1u].position = { point.x, m_size.y };
		m_areaVertices[areaBaseVertexIndex + 0u].color = m_areaColor;
		m_areaVertices[areaBaseVertexIndex + 1u].color = m_areaColor;
	}
}

} // namespace zuhyou
