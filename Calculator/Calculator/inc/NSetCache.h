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
    uint*                       _systemMemory;
    

public:
	NSetCache(uint cacheSize, uint cacheBlockSize, uint nWay, uint* systemMemory) : _nWay(nWay), _systemMemory(systemMemory)
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
	inline const CacheEntry& GetEntry(uint index, uint wayIdx)
	{
		return _cacheDatas[index * _cacheSetCount + wayIdx];
	}
	CacheLine MakeCacheLineCommand(uint address)
	{
		auto FillBit = [](unsigned int from, unsigned int to)
		{
			uint result = 0;

			for(uint i = from; i <= to; ++i)
				result |= (1 << (i + from));
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

	bool IsValid(const CacheLine& command, const CacheEntry* outEntry = nullptr)
	{
		for(uint i=0; i<_nWay; ++i)
		{
			const CacheEntry& entry = GetEntry(command.index, i);
			if(entry.isEmpty == false)
            {
                outEntry = &entry;
				return true;
            }
		}

		return false;
	}
	bool IsTagMatch(const CacheLine& command, const CacheEntry* outEntry = nullptr)
	{
		for(uint i=0; i<_nWay; ++i)
		{
			const CacheEntry& entry = GetEntry(command.index, i);
			if(entry.tag == command.tag)
            {
                outEntry = &entry;
				return true;
            }
		}

		return false;
	}
	uint FetchData(uint address)
	{
        uint result = 0;
		CacheLine command = MakeCacheLineCommand(address);

        CacheEntry* entry = nullptr;
		bool isHit = IsValid(command) && IsTagMatch(command, entry);
		if(isHit) //딱히 더 손볼건 없는듯
        {
			_hitCount++;
            ASSERT_COND_MSG(entry, "Error, what the");
            result = entry->data;
        }
		else
		{
			_missCount++;
            ASSERT_MSG("not woooooorkkkkkkinnnnggg yeeeeeet");
            
            ASSERT_COND_MSG((address % 4) != 0, "Error, invalid memory address");
            uint memData = _systemMemory[address / 4];
            
            //가져올때 주변 얘들 다 긁어야하지 않나?
            //Locality 있잖아.
            
            for(uint i=0;  i<_nWay; ++i)
            {
                CacheEntry& entry = _cacheDatas[command.index * _cacheSetCount + i];
                if(entry.isEmpty)
                {
                    entry.tag = command.tag;
                    entry.isEmpty = false;
                    entry.data = memData;
                    break;
                }
            }
    
            result = memData;
		}
        
        return result;
	}
};