// Convert.cpp: implementation of the CConvert class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "Win85.h"
#include "Convert.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CConvert::CConvert()
{

}

CConvert::~CConvert()
{

}

CString CConvert::Val2Hex(BYTE i)
{
	char txt[10];
	CString r;

	r=itoa(i,txt,16);if (i<0x10) r="0"+r;
	
	r.MakeUpper();

	return r;
}
