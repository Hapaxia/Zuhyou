//////////////////////////////////////////////////////////////////////////////
//
// Zuhyou (https://github.com/Hapaxia/Zuhyou)
//
// Copyright(c) 2023-2025 M.J.Silk
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

#include "Function.hpp"
namespace zuhyou
{

template <class T>
inline Function<T>::Function()
	: m_isUpdateRequired{ false }
	, m_vertices{}
	, m_axesVertices{}
	, m_function{}
	, m_minXValue{ static_cast<T>(0) }
	, m_maxXValue{ static_cast<T>(1) }
	, m_minYValue{ static_cast<T>(0) }
	, m_maxYValue{ static_cast<T>(1) }
	, m_xAxisValue{ static_cast<T>(0) }
	, m_yAxisValue{ static_cast<T>(0) }
	, m_size{}
	, m_color{ sf::Color::White }
	, m_numberOfSteps{ 0u }
	, m_axesColor{ sf::Color::White }
	, m_showAxes{ true }
{

}


template<class T>
inline void Function<T>::setFunction(const std::function<T(T)>& function)
{
	m_isUpdateRequired = true;
	m_function = function;
}
template<class T>
inline T Function<T>::getOutputValue(T input) const
{
	return m_function(input);
}

template<class T>
inline void Function<T>::setMinXValue(const T& minXValue)
{
	m_isUpdateRequired = true;
	m_minXValue = minXValue;
}
template<class T>
inline void Function<T>::setMaxXValue(const T& maxXValue)
{
	m_isUpdateRequired = true;
	m_maxXValue = maxXValue;
}
template<class T>
inline void Function<T>::setMinYValue(const T& minYValue)
{
	m_isUpdateRequired = true;
	m_minYValue = minYValue;
}
template<class T>
inline void Function<T>::setMaxYValue(const T& maxYValue)
{
	m_isUpdateRequired = true;
	m_maxYValue = maxYValue;
}

template<class T>
inline T Function<T>::getMinXValue() const
{
	return m_minXValue;
}
template<class T>
inline T Function<T>::getMaxXValue() const
{
	return m_maxXValue;
}
template<class T>
inline T Function<T>::getMinYValue() const
{
	return m_minYValue;
}
template<class T>
inline T Function<T>::getMaxYValue() const
{
	return m_maxYValue;
}

template<class T>
inline void Function<T>::setXAxisValue(const T& xAxisValue)
{
	m_isUpdateRequired = true;
	m_xAxisValue = xAxisValue;
}
template<class T>
inline void Function<T>::setYAxisValue(const T& yAxisValue)
{
	m_isUpdateRequired = true;
	m_yAxisValue = yAxisValue;
}
template<class T>
inline T Function<T>::getXAxisValue() const
{
	return m_xAxisValue;
}
template<class T>
inline T Function<T>::getYAxisValue() const
{
	return m_yAxisValue;
}

template<class T>
inline void Function<T>::setSize(const sf::Vector2f size)
{
	m_isUpdateRequired = true;
	m_size = size;
}
template<class T>
inline void Function<T>::setColor(const sf::Color color)
{
	m_isUpdateRequired = true;
	m_color = color;
}
template<class T>
inline void Function<T>::setNumberOfSteps(const std::size_t numberOfSteps)
{
	m_isUpdateRequired = true;
	m_numberOfSteps = numberOfSteps;
}
template<class T>
inline void Function<T>::setAxesColor(sf::Color axesColor)
{
	m_isUpdateRequired = true;
	m_axesColor = axesColor;
}
template<class T>
inline void Function<T>::setShowAxes(bool showAxes)
{
	m_isUpdateRequired = true;
	m_showAxes = showAxes;
}

template<class T>
inline sf::Vector2f Function<T>::getSize() const
{
	return m_size;
}
template<class T>
inline sf::Color Function<T>::getColor() const
{
	return m_color;
}
template<class T>
inline std::size_t Function<T>::getNumberOfSteps() const
{
	return m_numberOfSteps;
}
template<class T>
inline sf::Color Function<T>::getAxesColor() const
{
	return m_axesColor;
}
template<class T>
inline bool Function<T>::getShowAxes() const
{
	return m_showAxes;
}







// PRIVATE
template<class T>
inline void Function<T>::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	states.transform *= getTransform();

	if (m_isUpdateRequired)
		priv_updateVertices();

	if (m_showAxes)
		target.draw(m_axesVertices.data(), 4u, sf::PrimitiveType::Lines, states);
	target.draw(m_vertices.data(), m_vertices.size(), sf::PrimitiveType::LineStrip, states);
}

template<class T>
inline void Function<T>::priv_updateVertices() const
{
	m_isUpdateRequired = false;

	const float axisY{ ((m_yAxisValue - m_minYValue) / (m_maxYValue - m_minYValue)) * m_size.y };
	const float axisX{ ((m_xAxisValue - m_minXValue) / (m_maxXValue - m_minXValue)) * m_size.x };

	m_axesVertices[0u].position = { axisX, 0.f };
	m_axesVertices[1u].position = { axisX, m_size.y };
	m_axesVertices[2u].position = { 0.f, axisY };
	m_axesVertices[3u].position = { m_size.x, axisY };
	for (auto& v : m_axesVertices)
		v.color = m_axesColor;

	const std::size_t numberOfSteps{ (m_numberOfSteps == 0u) ? static_cast<std::size_t>(std::lround(m_size.x)) : m_numberOfSteps };

	if (numberOfSteps < 2u)
	{
		m_vertices.clear();
		return;
	}

	m_vertices.resize(numberOfSteps);

	const std::size_t finalStep{ numberOfSteps - 1u };

	for (std::size_t i{ 0u }; i <= finalStep; ++i)
	{
		const float xAlpha{ static_cast<float>(i) / finalStep };

		const float xValue{ (m_maxXValue * xAlpha) + (m_minXValue * (1.f - xAlpha)) };
		const float yValue{ getOutputValue(xValue) };

		const bool yOutOfRange{ (yValue < m_minYValue) || (yValue > m_maxYValue) };

		const float x{ xAlpha * m_size.x };

		const float y{ (1.f - ((yValue - m_minYValue) / (m_maxYValue - m_minYValue))) * m_size.y };

		m_vertices[i].position = { x, y };
		m_vertices[i].color = yOutOfRange ? sf::Color::Transparent : m_color;
	}
}

} // namespace zuhyou
