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

class Grid : public sf::Drawable, public sf::Transformable
{
public:
	Grid();

	void setRound(bool round);
	bool getRound() const;

	void setAutoOffset(bool autoOffset);
	bool getAutoOffset() const;

	void setIncludeEdges(bool includeEdges);
	bool getIncludeEdges() const;

	void setSize(sf::Vector2f size);
	sf::Vector2f getSize() const;

	void setNumberOfSeparators(sf::Vector2u numberOfSeparators);
	sf::Vector2u getNumberOfSeparators() const;

	void setHorizColor(sf::Color horizColor);
	sf::Color getHorizColor() const;

	void setVertColor(sf::Color vertColor);
	sf::Color getVertColor() const;

	void setColor(sf::Color color);

private:
	mutable bool m_isUpdateRequired;
	mutable std::vector<sf::Vertex> m_vertices;

	bool m_doRound;
	bool m_doAutoOffset;
	bool m_includeEdges;
	sf::Vector2f m_size;
	sf::Vector2<std::size_t> m_numberOfSeparators; // a separator is a line that is not part of the edge i.e. inbetween the edges

	sf::Color m_horizColor;
	sf::Color m_vertColor;

	void draw(sf::RenderTarget& target, sf::RenderStates states) const override final;
	void priv_updateVertices() const;
};

} // namespace zuhyou
#include "Grid.inl"
