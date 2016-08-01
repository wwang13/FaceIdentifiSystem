#pragma once

#include "Poco/Runnable.h"
#include "Poco/Thread.h"
#include "QMFileSqlite.h"

struct CompareResult
{
	CompareResult()
	{
		data = nullptr;
		size = 0;
	}

	~CompareResult()
	{
		if (nullptr != data)
		{
			delete[] data;
			data = nullptr;
			size = 0;
		}
	}

	CompareResult(const CompareResult& other)
	{
		size = other.size;
		data = nullptr;
		setPacketData(other.data, other.size);
	}

	CompareResult(const BYTE* data, const short len)
	{
		size = len;
		data = nullptr;
		setPacketData((BYTE*)data, len);
	}


	void setPacketData(BYTE* pData, int len)
	{
		if (nullptr != data)
		{
			delete[] data;
			data = nullptr;
			size = 0;
		}

		if (len > 0)
		{
			data = new BYTE[len];
			size = len;
			memcpy(data, pData, len);
		}
	}

	CompareResult& operator= (const CompareResult& other)
	{
		if (&other == this)
		{
			return *this;
		}
		size = other.size;
		setPacketData(other.data, other.size);
		return *this;
	}

	//
	BYTE* getData() const
	{
		return data;
	}
	long getDataSize() const
	{
		return size;
	}

	long 		num;            //注册表原编号
	float		fsimilarity;    //相似度
	__int64		time;			//照片的时间
	BYTE *		data;			//照片的数据
	long		size;			//照片的时间
};

class BitMapCompare : public Poco::Runnable
{
public:
	BitMapCompare(void *pthis);
	~BitMapCompare();
	void run();
private:
	void CompareBitmap(BYTE *pFirst, BYTE *pSecond, long nFirstWidth, long nSecondWidth, long nFirstHeight, long nSecondHeight, float& fRet);
	Mat LoadBmpFile1(std::string strFilePath);
	void getCamBuf();
	void writeDB();
	void onEvent(const void* pSender, bool& arg);
	void getUserInfo();

private:
	bool             _break;
	void *           _pWnd;
	vector<readUserInfo> _vUserInfo;
};