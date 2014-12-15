#pragma once

#include <string>

namespace simplicity
{
	typedef char                    CHAR;
	typedef std::basic_string<CHAR> string;

	class Coordinate
	{
	private:
		uint16_t m_nCoordX;
		uint16_t m_nCoordY;

	public:
		Coordinate(uint16_t nCoordX, uint16_t nCoordY);
		uint16_t get_x(void) const;
		void set_x(uint16_t nCoordX);
		uint16_t get_y(void) const;
		void set_y(uint16_t nCoordY);
	};
}

