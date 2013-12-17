// Version 1.0a
// Copyright (C) 1998, James R. Weeks and BioElectroMech.
// Visit BioElectroMech at www.obrador.com.  Email James@obrador.com.
//
#include "FileOutputStream.h"


FileOutputStream::FileOutputStream(char* filename)
{
	m_fp = fopen(filename, "wb");
}

FileOutputStream::~FileOutputStream()
{
    flush();
	fclose(m_fp);
}

	
void FileOutputStream::flush()
{
	fflush(m_fp);
}

void FileOutputStream::write(byte data[], int offset, int len)
{
    fwrite(&data[offset], 1, len, m_fp);
}

void FileOutputStream::write(int c)
{
    byte v = c;
	
    fwrite(&v, 1, 1, m_fp);
}

