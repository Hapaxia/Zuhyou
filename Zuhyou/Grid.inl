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

#include "Grid.hpp"

#include <cmath>

namespace zuhyou
{

inline Grid::Grid()
	: m_isUpdateRequired { false }
	, m_vertices{}
	, m_doRound{ true }
	, m_doAutoOffset{ true }
	, m_includeEdges{ true }
	, m_size{}
	, m_numberOfSeparators{}
	, m_horizColor{ sf::Color::White }
	, m_vertColor{ sf::Color::White }
{

}

inline void Grid::setRound(const bool round)
{
	m_doRound = round;
	m_isUpdateRequired = true;
}

inline bool Grid::getRound() const
{
	return m_doRound;
}

inline void Grid::setAutoOffset(bool autoOffset)
{
	m_doAutoOffset = autoOffset;
	m_isUpdateRequired = true;
}

inline bool Grid::getAutoOffset() const
{
	return m_doAutoOffset;
}

inline void Grid::setIncludeEdges(const bool includeEdges)
{
	m_includeEdges = includeEdges;
	m_isUpdateRequired = true;
}

inline bool Grid::getIncludeEdges() const
{
	return m_includeEdges;
}

inline void Grid::setSize(const sf::Vector2f size)
{
	m_size = size;
	m_isUpdateRequired = true;
}

inline sf::Vector2f Grid::getSize() const
{
	return m_size;
}

inline void Grid::setNumberOfSeparators(const sf::Vector2u numberOfSeparators)
{
	m_numberOfSeparators = sf::Vector2<std::size_t>(numberOfSeparators);
	m_isUpdateRequired = true;
}

inline sf::Vector2u Grid::getNumberOfSeparators() const
{
	return sf::Vector2u(m_numberOfSeparators);
}

inline void Grid::setHorizColor(const sf::Color horizColor)
{
	m_horizColor = horizColor;
	m_isUpdateRequired = true;
}

inline sf::Color Grid::getHorizColor() const
{
	return m_horizColor;
}

inline void Grid::setVertColor(const sf::Color vertColor)
{
	m_vertColor = vertColor;
	m_isUpdateRequired = true;
}

inline sf::Color Grid::getVertColor() const
{
	return m_vertColor;
}

inline void Grid::setColor(const sf::Color color)
{
	setHorizColor(color);
	setVertColor(color);
}







// PRIVATE
inline void Grid::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	states.transform *= getTransform();
	states.texture = nullptr;

	if (m_isUpdateRequired)
		priv_updateVertices();

	target.draw(m_vertices.data(), m_vertices.size(), sf::PrimitiveType::Lines, states);
}

inline void Grid::priv_updateVertices() const
{
	m_isUpdateRequired = false;

	const std::size_t numberOfLines{ (m_includeEdges ? 4u : 0u) + m_numberOfSeparators.x + m_numberOfSeparators.y };
	m_vertices.resize(numberOfLines * 2u);
	if (m_vertices.empty())
		return;

	sf::Vector2f size{ m_size };
	if (m_doRound)
	{
		size.x = std::round(size.x);
		size.y = std::round(size.y);
	}

	std::size_t currentVertexBase{ 0u };

	// vertical lines first
	for (std::size_t x{ 0u }; x < m_numberOfSeparators.x; ++x)
	{
		float xPos{ static_cast<float>(size.x * (x + 1u)) / (m_numberOfSeparators.x + 1u) };
		if (m_doRound)
			xPos = std::round(xPos);
		
		m_vertices[currentVertexBase + 0u].position = { xPos, 0.f };
		m_vertices[currentVertexBase + 1u].position = { xPos, size.y };
		m_vertices[currentVertexBase + 0u].color = m_vertColor;
		m_vertices[currentVertexBase + 1u].color = m_vertColor;

		currentVertexBase += 2u;
	}

	// horizontal lines second
	for (std::size_t y{ 0u }; y < m_numberOfSeparators.y; ++y)
	{
		float yPos{ static_cast<float>(size.y * (y + 1u)) / (m_numberOfSeparators.y + 1u) };
		if (m_doRound)
			yPos = std::round(yPos);

		m_vertices[currentVertexBase + 0u].position = { 0.f, yPos };
		m_vertices[currentVertexBase + 1u].position = { size.x, yPos };
		m_vertices[currentVertexBase + 0u].color = m_horizColor;
		m_vertices[currentVertexBase + 1u].color = m_horizColor;

		currentVertexBase += 2u;
	}

	// edges last
	if (m_includeEdges)
	{
		m_vertices[currentVertexBase + 0u].position = { 0.f, 0.f };
		m_vertices[currentVertexBase + 1u].position = { 0.f, size.y };
		m_vertices[currentVertexBase + 2u].position = { size.x, 0.f };
		m_vertices[currentVertexBase + 3u].position = { size.x, size.y };
		m_vertices[currentVertexBase + 4u].position = { 0.f, 0.f };
		m_vertices[currentVertexBase + 5u].position = { size.x, 0.f };
		m_vertices[currentVertexBase + 6u].position = { 0.f, size.y };
		m_vertices[currentVertexBase + 7u].position = { size.x, size.y };
		for (std::size_t v{ 0u }; v < 4u; ++v)
		{
			m_vertices[currentVertexBase + 0u + v].color = m_vertColor;
			m_vertices[currentVertexBase + 4u + v].color = m_horizColor;
		}
	}
}

} // namespace zuhyou
