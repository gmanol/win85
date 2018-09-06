// DeviceEmul.cpp: implementation of the CDeviceEmul class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "Keyboard.h"
#include "DeviceEmul.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CDeviceEmul::CDeviceEmul()
{
}

CDeviceEmul::~CDeviceEmul()
{

}


void CDeviceEmul::Write(BYTE port, BYTE data)
{
	if (port==m_sample_port)
	{
	}
}

BYTE CDeviceEmul::Read(BYTE port)
{
	if (port==m_sample_port)
	{
	return(m_buffer);
	}
return(-1);
}

void CDeviceEmul::Reset()
{
}
