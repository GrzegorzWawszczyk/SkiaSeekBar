#include "Drawable.hpp"

#include <core/SkCanvas.h>

namespace ssb::core
{
	Drawable::Drawable(unsigned int width, unsigned int height, int x, int y, bool visible, float opacity)
		: m_x(x)
		, m_y(y)
		, m_width(width)
		, m_height(height)
		, m_visible(visible)
		, m_opacity(opacity)
	{
	}

	int Drawable::x()
	{
		return m_x;
	}

	void Drawable::setX(int x)
	{
		m_x = x;
	}

	int Drawable::y()
	{
		return m_y;
	}

	void Drawable::setY(int y)
	{
		m_y = y;
	}

	unsigned int Drawable::width()
	{
		return m_width;
	}

	void Drawable::setWidth(unsigned int width)
	{
		m_width = width;
	}

	unsigned int Drawable::height()
	{
		return m_height;
	}

	void Drawable::setHeight(unsigned int height)
	{
		m_height = height;
	}

	bool Drawable::visible()
	{
		return m_visible;
	}

	void Drawable::setVisible(bool visible)
	{
		m_visible = visible;
	}

	float Drawable::opacity()
	{
		return m_opacity;
	}

	void Drawable::setOpacity(float opacity)
	{
		m_opacity = opacity;
	}
}