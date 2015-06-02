#pragma once

#include "Common.h"
#include <math.h>
#include <vector>

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
		uint tag;
		uint data;
		bool isEmpty;

		CacheEntry() : tag(0), data(0), isEmpty(true) {}
		~CacheEntry() {}
	};

private:
	CacheLine                   _lineInfo;
	std::vector<CacheEntry>		_cacheDatas;
	uint						_nWay;
	uint						_cacheSetCount;
	uint						_hitCount;
	uint						_missCount;

public:
	NSetCache(uint cacheSize, uint cacheBlockSize, uint nWay) : _nWay(nWay)
	{
		CacheLine line;
		line.offset = log(cacheBlockSize);

		_cacheSetCount = (cacheSize / cacheBlockSize) / nWay;
		line.index = log(_cacheSetCount);

		line.tag = 32 - (line.index - line.offset);

		_lineInfo = line;

		_cacheDatas.reserve(_cacheSetCount * nWay);
	}

	~NSetCache()
	{

	}

public:
	void Init()
	{

	}

	inline const CacheEntry& GetCacheData(uint index, uint wayIdx)
	{
		return _cacheDatas[index * _cacheSetCount + wayIdx];
	}
	CacheLine MakeCacheLineCommand(uint address)
	{
		auto FillBit = [](unsigned int from, unsigned int to)
		{
			uint result = 0;

			for(uint i = from; i <= to; ++i)
				result |= (1 << i + from);
			result <<= from;
			return result;
		};     
   
		uint offset = 32 - _lineInfo.tag;

		CacheLine line;
		line.tag = (address & FillBit(_lineInfo.tag, offset)) >> offset;
		line.index = (address & FillBit(_lineInfo.index, _lineInfo.offset)) >> _lineInfo.offset;
		line.offset = (address & FillBit(_lineInfo.offset, 0));

		return line;
	}
	void Write(const CacheLine& command)
	{
		for(uint i=0;  i<_nWay; ++i)
		{
			CacheEntry& entry = _cacheDatas[command.index * _cacheSetCount + i];
			if(entry.isEmpty)
			{
				entry.tag = command.tag;
				// do.. something?
				entry.isEmpty = false;
			}
		}
	}

	bool IsValid(const CacheLine& command)
	{
		for(uint i=0; i<_nWay; ++i)
		{
			const CacheEntry& entry = GetCacheData(command.index, i);
			if(entry.isEmpty == false)
				return true;
		}

		return false;
	}
	bool IsTagMatch(const CacheLine& command)
	{
		for(uint i=0; i<_nWay; ++i)
		{
			const CacheEntry& entry = GetCacheData(command.index, i);
			if(entry.tag == command.tag)
				return true;
		}

		return false;
	}
	void Test_Check(uint address)
	{
		CacheLine command = MakeCacheLineCommand(address);

		bool isHit = IsValid(command) && IsTagMatch(command);
		if(isHit)
			_hitCount++;
		else
		{
			_missCount++;

		}
	}
};