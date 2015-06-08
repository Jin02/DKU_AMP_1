#pragma once

#include "Common.h"
#include <math.h>
#include <vector>
#include <time.h>
#include <memory.h>


class NSetCache
{
public:
	struct CacheLine
	{
		uint tag;
		uint index;
		uint offset;
	};

	struct CacheEntry
	{
		uint            tag;
		uint*           datas;
		bool            isEmpty;
		time_t          timeStamp;
		bool            isRequiredUpdate;
		uint            memAddress;

		CacheEntry() : tag(0), datas(0), isEmpty(true), timeStamp(0), isRequiredUpdate(false), memAddress(-1) {}
		~CacheEntry() {}
	};


private:
	CacheLine			_lineInfo;
	CacheEntry**		_cacheDatas;
	uint				_nWay;
	uint				_blockSize;
	uint				_cacheSetCount;
	uint				_hitCount;
	uint				_missCount;
	uint*       		_systemMemory;


public:
    NSetCache(uint cacheSize, uint cacheBlockSize, uint nWay, uint* systemMemory);
    ~NSetCache();

private:
    CacheLine MakeCacheLineCommand(uint address);
    bool IsValid(const CacheLine& command, CacheEntry** outEntry = nullptr);
    bool IsTagMatch(const CacheLine& command, CacheEntry** outEntry = nullptr);
    bool LoadCache(uint address);
    bool Replace(uint address);
    
public:
    uint FetchData(uint address);
    void InputData(uint address, uint data);
};
