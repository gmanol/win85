// SeikoEmul.h: interface for the CSeikoEmul class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_SEIKOEMUL_H__6174C003_9ECA_11D3_8906_BCAAC79D7612__INCLUDED_)
#define AFX_SEIKOEMUL_H__6174C003_9ECA_11D3_8906_BCAAC79D7612__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class CSeikoEmul  
{
public:
	CSeikoEmul();
	virtual ~CSeikoEmul();
private:

public:
	void Reset();
	BOOL m_update;
	int* m_pIRQPenting;

	BYTE m_cs_port;
	BYTE m_data_port;
	BYTE m_instr_port;

	BYTE Read(BYTE port);
	void Write(BYTE port,BYTE data);

BYTE SeikoRAM[128*8];
BYTE SeikoOFF[128*8];

BOOL Seiko_Display1;
BOOL Seiko_Display2;
BOOL Seiko_bug;

	// Seiko G1216B1N000 Variables
BYTE Seiko_CS;		// xxB
BYTE Seiko_X1;		// 0..7
BYTE Seiko_X2;		// 0..7
BYTE Seiko_Y1;		// 0..63
BYTE Seiko_Y2;		// 0..63
BYTE Seiko_Z1;		// 0..63
BYTE Seiko_Z2;		// 0..63

};

#endif // !defined(AFX_SEIKOEMUL_H__6174C003_9ECA_11D3_8906_BCAAC79D7612__INCLUDED_)
