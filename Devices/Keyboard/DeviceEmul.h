// DeviceEmul.h: interface for the CDeviceEmul class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_DEVICEEMUL_H__A49D2C4F_CF7A_11D3_9FBB_84A70E15680A__INCLUDED_)
#define AFX_DEVICEEMUL_H__A49D2C4F_CF7A_11D3_9FBB_84A70E15680A__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class CDeviceEmul  
{
public:
	void Reset();
	BYTE m_buffer;
	int* m_pIRQPenting;
	BYTE m_sample_port;

	BYTE Read(BYTE port);
	void Write(BYTE port,BYTE data);

	CDeviceEmul();
	virtual ~CDeviceEmul();


private:
};

#endif // !defined(AFX_DEVICEEMUL_H__A49D2C4F_CF7A_11D3_9FBB_84A70E15680A__INCLUDED_)
