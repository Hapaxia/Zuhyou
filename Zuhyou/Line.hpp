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

namespace zuhyou
{

template <class T>
class Line : public sf::Drawable, public sf::Transformable
{
public:
	Line();



	// data
	void setNumberOfValues(std::size_t numberOfValues);
	void setValues(const std::vector<T>& values);
	void setValues(const std::vector<T>&& values);
	void setValue(std::size_t index, const T& value);
	void setMinValue(const T& minValue);
	void setMaxValue(const T& maxValue);

	std::size_t getNumberOfValues() const;
	T getValue(std::size_t index) const;
	T getMinValue() const;
	T getMaxValue() const;



	// visual properties
	void setSize(sf::Vector2f size);
	void setLineColor(sf::Color lineColor);
	void setAreaColor(sf::Color areaColor);
	void setShowLine(bool showLine);
	void setShowArea(bool showArea);

	sf::Vector2f getSize() const;
	sf::Color getLineColor() const;
	sf::Color getAreaColor() const;
	bool getShowLine() const;
	bool getShowArea() const;







private:
	mutable bool m_isUpdateRequired;
	mutable std::vector<sf::Vertex> m_lineVertices;
	mutable std::vector<sf::Vertex> m_areaVertices;

	std::vector<T> m_values;
	T m_minValue;
	T m_maxValue;

	sf::Vector2f m_size;
	sf::Color m_lineColor;
	sf::Color m_areaColor;
	bool m_showLine;
	bool m_showArea;

	void draw(sf::RenderTarget& target, sf::RenderStates states) const override final;
	void priv_updateVertices() const;
};

} // namespace zuhyou
#include "Line.inl"
