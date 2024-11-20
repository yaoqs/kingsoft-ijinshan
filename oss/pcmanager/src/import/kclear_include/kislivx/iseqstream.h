
#pragma once

#ifndef __UPLIVE_ISEQSTREAM_H__
#define __UPLIVE_ISEQSTREAM_H__

#include "uplive_common.h"

// ����
interface IBaseStream
{
	virtual ~IBaseStream(){};
};

// �������
interface IOutStream
	: public IBaseStream
{
	/* Returns: result - the number of actually written bytes.
	(result < uSize) means error */
	virtual HRESULT Write(IN const byte * pbyBuf, IN u_int uSize, OUT u_int * pWrittenSize) = 0;
};

// ��������
interface IInStream
	: public IBaseStream
{
	/* if (input(*size) != 0 && output(*size) == 0) means end_of_stream.
	(output(*size) < input(*size)) is allowed */
	virtual HRESULT Read(IN const byte * pbyBuf, IN u_int uSize, OUT u_int * pReadedSize) = 0;
};

interface ISeqStream
	: public IOutStream, 
	  public IInStream
{
	
};


#endif	//__UPLIVE_ISEQSTREAM_H__