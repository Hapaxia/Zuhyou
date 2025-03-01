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

#include "Common.hpp"

#include <functional>

namespace zuhyou
{

template <class T>
class Function : public sf::Drawable, public sf::Transformable
{
public:
	Function();



	// function
	void setFunction(const std::function<T(T)>& function);
	T getOutputValue(T input) const;



	// limits
	void setMinXValue(const T& minXValue);
	void setMaxXValue(const T& maxXValue);
	void setMinYValue(const T& minYValue);
	void setMaxYValue(const T& maxYValue);

	T getMinXValue() const;
	T getMaxXValue() const;
	T getMinYValue() const;
	T getMaxYValue() const;



	// axes
	void setXAxisValue(const T& xAxisValue);
	void setYAxisValue(const T& yAxisValue);

	T getXAxisValue() const;
	T getYAxisValue() const;



	// visual properties
	void setSize(sf::Vector2f size);
	void setColor(sf::Color color);
	void setNumberOfSteps(std::size_t numberOfSteps); // if numberOfSteps is zero (default), the width (size's x value) is used instead
	void setAxesColor(sf::Color axesColor);
	void setShowAxes(bool showAxes);

	sf::Vector2f getSize() const;
	sf::Color getColor() const;
	std::size_t getNumberOfSteps() const;
	sf::Color getAxesColor() const;
	bool getShowAxes() const;







private:
	mutable bool m_isUpdateRequired;
	mutable std::vector<sf::Vertex> m_vertices;
	mutable std::array<sf::Vertex, 4u> m_axesVertices;

	std::function<T(T)> m_function;

	T m_minXValue;
	T m_maxXValue;
	T m_minYValue;
	T m_maxYValue;

	T m_xAxisValue;
	T m_yAxisValue;

	sf::Vector2f m_size;
	sf::Color m_color;
	std::size_t m_numberOfSteps;
	sf::Color m_axesColor;
	bool m_showAxes;

	void draw(sf::RenderTarget& target, sf::RenderStates states) const override final;
	void priv_updateVertices() const;
};

} // namespace zuhyou
#include "Function.inl"
