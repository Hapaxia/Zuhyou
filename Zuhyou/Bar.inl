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

#include "Bar.hpp"
namespace zuhyou
{

template<class T>
inline Bar<T>::Bar()
	: m_isUpdateRequired{ false }
	, m_vertices{}
	, m_values{}
	, m_minValue{ static_cast<T>(0) }
	, m_maxValue{ static_cast<T>(1) }
	, m_size{}
	, m_color{ sf::Color::White }
	, m_minBarWidth{ 1.f }
	, m_separationWidth{ 10.f }
{

}

template<class T>
inline void Bar<T>::setNumberOfValues(const std::size_t numberOfValues)
{
	m_isUpdateRequired = true;
	m_values.resize(numberOfValues);
}
template<class T>
inline void Bar<T>::setValues(const std::vector<T>& values)
{
	m_values = values;
}
template<class T>
inline void Bar<T>::setValues(const std::vector<T>&& values)
{
	m_values = std::move(values);
}
template<class T>
inline void Bar<T>::setValue(std::size_t index, const T& value)
{
	if (index >= m_values.size())
		throw(Exception("Unable to set value; invalid index."));

	m_isUpdateRequired = true;
	m_values[index] = value;
}
template<class T>
inline void Bar<T>::setMinValue(const T& minValue)
{
	m_isUpdateRequired = true;
	m_minValue = minValue;
}
template<class T>
inline void Bar<T>::setMaxValue(const T& maxValue)
{
	m_isUpdateRequired = true;
	m_maxValue = maxValue;
}

template<class T>
inline std::size_t Bar<T>::getNumberOfValues() const
{
	return m_values.size();
}
template<class T>
inline T Bar<T>::getValue(const std::size_t index) const
{
	if (index >= m_values.size())
		throw(Exception("Unable to get value; invalid index."));

	return m_values[index];
}
template<class T>
inline T Bar<T>::getMinValue() const
{
	return m_minValue;
}
template<class T>
inline T Bar<T>::getMaxValue() const
{
	return m_maxValue;
}

template<class T>
inline void Bar<T>::setSize(const sf::Vector2f size)
{
	m_isUpdateRequired = true;
	m_size = size;
}
template<class T>
inline void Bar<T>::setColor(const sf::Color color)
{
	m_isUpdateRequired = true;
	m_color = color;
}

template<class T>
inline void Bar<T>::setMinBarWidth(const float minBarWidth)
{
	m_minBarWidth = minBarWidth;
}

template<class T>
inline void Bar<T>::setSeparationWidth(const float separationWidth)
{
	m_isUpdateRequired = true;
	m_separationWidth = separationWidth;
}

template<class T>
inline sf::Vector2f Bar<T>::getSize() const
{
	return m_size;
}
template<class T>
inline sf::Color Bar<T>::getColor() const
{
	return m_color;
}

template<class T>
inline float Bar<T>::getMinBarWidth() const
{
	return m_minBarWidth;
}

template<class T>
inline float Bar<T>::getSeparationWidth() const
{
	return m_separationWidth;
}







// PRIVATE
template<class T>
inline void Bar<T>::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	states.transform *= getTransform();

	if (m_isUpdateRequired)
		priv_updateVertices();

	target.draw(m_vertices.data(), m_vertices.size(), sf::PrimitiveType::Triangles, states);
}

template<class T>
inline void Bar<T>::priv_updateVertices() const
{
	m_isUpdateRequired = false;
	const std::size_t numberOfValues{ m_values.size() };
	if (numberOfValues < 2u)
	{
		m_vertices.clear();
		return;
	}
	constexpr std::size_t numberOfVerticesPerValue{ 6u };
	m_vertices.resize(numberOfValues * numberOfVerticesPerValue);

	float separationWidth{ m_separationWidth };
	float separationTotal{ separationWidth * (numberOfValues - 1u) };
	if (separationTotal > (m_size.x - (numberOfValues * m_minBarWidth)))
	{
		separationTotal = m_size.x - (numberOfValues * m_minBarWidth);
		separationWidth = separationTotal / (numberOfValues - 1u);
	}
	const float actualBarsTotalWidth{ m_size.x - separationTotal };
	const float barWidth{ actualBarsTotalWidth / numberOfValues };

	for (std::size_t i{ 0u }; i < numberOfValues; ++i)
	{
		const float alphaValue{ static_cast<float>(static_cast<double>(m_values[i] - m_minValue) / (m_maxValue - m_minValue)) };
		const sf::Vector2f topLeft{ i * (barWidth + separationWidth), (1.f - alphaValue) * m_size.y };
		const sf::Vector2f bottomRight{ topLeft.x + barWidth, m_size.y };
		const std::size_t baseVertexIndex{ i * numberOfVerticesPerValue };
		m_vertices[baseVertexIndex + 0u].position = topLeft;
		m_vertices[baseVertexIndex + 1u].position = { topLeft.x, bottomRight.y };
		m_vertices[baseVertexIndex + 2u].position = bottomRight;
		m_vertices[baseVertexIndex + 5u].position = { bottomRight.x, topLeft.y };
		m_vertices[baseVertexIndex + 0u].color = m_color;
		m_vertices[baseVertexIndex + 1u].color = m_color;
		m_vertices[baseVertexIndex + 2u].color = m_color;
		m_vertices[baseVertexIndex + 5u].color = m_color;
		m_vertices[baseVertexIndex + 3u] = m_vertices[baseVertexIndex + 0u];
		m_vertices[baseVertexIndex + 4u] = m_vertices[baseVertexIndex + 2u];
	}
}

} // namespace zuhyou
