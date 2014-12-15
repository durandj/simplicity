#include "types.hpp"

namespace simplicity
{
	Coordinate::Coordinate(uint16_t nCoordX, uint16_t nCoordY) :
		m_nCoordX(nCoordX),
		m_nCoordY(nCoordY)
	{
	}

	uint16_t Coordinate::get_x(void) const
	{
		return m_nCoordX;
	}

	void Coordinate::set_x(uint16_t nCoordX)
	{
		m_nCoordX = nCoordX;
	}

	uint16_t Coordinate::get_y(void) const
	{
		return m_nCoordY;
	}

	void Coordinate::set_y(uint16_t nCoordY)
	{
		m_nCoordY = nCoordY;
	}
}

