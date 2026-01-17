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

#include "Common.hpp"

namespace zuhyou
{

template <class T>
class Scatter : public sf::Drawable, public sf::Transformable
{
public:
	Scatter();



	// points
	void clear();
	void addPoint(sf::Vector2<T> point);
	void addPoints(const std::vector<sf::Vector2<T>>& points);
	std::size_t getNumOfPoints() const;
	void setPoint(std::size_t pointIndex, sf::Vector2<T> point);



	// limits
	void setMinXValue(const T& minXValue);
	void setMaxXValue(const T& maxXValue);
	void setMinYValue(const T& minYValue);
	void setMaxYValue(const T& maxYValue);
	void setLimitRect(const sf::Rect<T>& limitRect);

	T getMinXValue() const;
	T getMaxXValue() const;
	T getMinYValue() const;
	T getMaxYValue() const;
	sf::Rect<T> getLimitRect() const;



	// axes
	void setXAxisValue(const T& xAxisValue);
	void setYAxisValue(const T& yAxisValue);
	void setAxisPosition(const sf::Vector2<T>& axisPosition);

	T getXAxisValue() const;
	T getYAxisValue() const;
	sf::Vector2<T> getAxisPosition() const;



	// visual properties
	void setSize(sf::Vector2f size);
	void setColor(sf::Color color);
	void setAxesColor(sf::Color axesColor);
	void setShowAxes(bool showAxes);

	sf::Vector2f getSize() const;
	sf::Color getColor() const;
	sf::Color getAxesColor() const;
	bool getShowAxes() const;



	// point shape template
	void setPointShapeTemplateVertices(const std::vector<sf::Vector2f>& pointShapeTemplateVertices);
	void setPointShapeTemplateNumOfVertices(std::size_t numOfPointShapeVertices);
	void setPointShapeTemplateVertex(std::size_t pointShapeVertexIndex, sf::Vector2f pointShapeVertex);
	void setPointShapeTemplateScale(sf::Vector2f pointShapeScale);
	void setPointShapeTemplateScale(float pointShapeScale);



private:
	mutable bool m_isUpdateRequired;
	mutable std::vector<sf::Vertex> m_vertices;
	mutable std::array<sf::Vertex, 4u> m_axesVertices;

	std::vector<sf::Vector2<T>> m_points;

	T m_minXValue;
	T m_maxXValue;
	T m_minYValue;
	T m_maxYValue;

	T m_xAxisValue;
	T m_yAxisValue;

	sf::Vector2f m_size;
	sf::Color m_color;
	sf::Color m_axesColor;
	bool m_showAxes;

	std::vector<sf::Vector2f> m_pointShapeTemplate;
	sf::Vector2f m_pointShapeScale;

	void draw(sf::RenderTarget& target, sf::RenderStates states) const override final;
	void priv_updateVertices() const;
};

} // namespace zuhyou
#include "Scatter.inl"
