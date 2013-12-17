// 17/12/2013
// This encoder implemented by David Castells-Rufas (david.castells@uab.cat)
// to do research in parallel implementation of the JPEG encoding algorithm
// The code is implemented in C++ and derived from a Java version, see previous
// author licences below
//
#ifndef MATRIX_H_INCLUDED_
#define MATRIX_H_INCLUDED_

#include "datatypes.h"

template<typename T>
class Matrix
{
	T* m_data;
	int m_w;
	int m_h;

public:
	Matrix(int h, int w )
	{
		m_w = w;
		m_h = h;
		m_data = new T[w*h];
	}
	
	T get(int y, int x)
	{
		return m_data[m_w*y+x];
	}
	
	void put(int y, int x, T v)
	{
		m_data[m_w*y+x] = v;
	}
};

#endif