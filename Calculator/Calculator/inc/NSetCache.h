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
	NSetCache(uint cacheSize, uint cacheBlockSize, uint nWay, uint* systemMemory) : _nWay(nWay), _systemMemory(systemMemory), _blockSize(cacheBlockSize), _hitCount(0), _missCount(0)
	{
		auto log2 = [](double n)
		{
			return log(n) / log(2);
		};
		CacheLine line;
		line.offset = log2(_blockSize);

		_cacheSetCount = (cacheSize / _blockSize) / nWay;
		line.index = log2(_cacheSetCount);

		line.tag = 32 - (line.index + line.offset);

		_lineInfo = line;

		_cacheDatas = new CacheEntry*[_cacheSetCount + 1];

		for (uint i = 0; i < _cacheSetCount + 1; ++i)
		{
			_cacheDatas[i] = new CacheEntry[nWay];
            for(uint wayIdx = 0; wayIdx < nWay; ++wayIdx)
            {
                _cacheDatas[i][wayIdx].datas = new uint[_blockSize];
                memset(_cacheDatas[i][wayIdx].datas, 0, sizeof(uint) * _blockSize);
            }
		}
	}

	~NSetCache()
	{
	}

public:
	CacheLine MakeCacheLineCommand(uint address)
	{
		auto FillBit = [](unsigned int offset, unsigned int length)
		{
			uint result = 1;

			for (uint i = 0; i < length; ++i)
				result |= (1 << i);
			
            result <<= offset;
            return result;
		};

		ASSERT_COND_MSG((address % 4) == 0, "Error, Invalid address");
		uint offset = 32 - _lineInfo.tag;

		CacheLine line;
        uint mask = FillBit(offset, _lineInfo.tag);
		line.tag = (address & mask) >> offset;
        
        mask = FillBit(_lineInfo.offset, _lineInfo.index);
		line.index = (address & mask) >> _lineInfo.offset;

        mask = FillBit(0, _lineInfo.offset);
        line.offset = (address & mask);

		return line;
	}

	bool IsValid(const CacheLine& command, CacheEntry** outEntry = nullptr)
	{
		for (uint i = 0; i < _nWay; ++i)
		{
			CacheEntry& entry = _cacheDatas[command.index][i];
			if (entry.isEmpty == false)
			{
				if (outEntry)
					(*outEntry) = &entry;

				return true;
			}
		}

		return false;
	}

	bool IsTagMatch(const CacheLine& command, CacheEntry** outEntry = nullptr)
	{
		for (uint i = 0; i < _nWay; ++i)
		{
			CacheEntry& entry = _cacheDatas[command.index][i];

			if (entry.tag == command.tag)
			{
				if (outEntry)
					(*outEntry) = &entry;

				return true;
			}
		}

		return false;
	}

	bool LoadCache(uint address)
	{
		CacheLine command = MakeCacheLineCommand(address);
		ASSERT_COND_MSG((address % 4) == 0, "Error, invalid memory address");
		uint offset = (address / _blockSize) * _blockSize;

		bool success = false;
		for (uint wayIdx = 0; wayIdx < _nWay; ++wayIdx)
		{
			CacheEntry& entry = _cacheDatas[command.index][wayIdx];
			if (entry.isEmpty)
			{
				entry.tag = command.tag;
				entry.isEmpty = false;
				entry.isRequiredUpdate = false;
				entry.timeStamp = time(nullptr);

				uint offset = (address / _blockSize) * _blockSize;
				memcpy(entry.datas, &_systemMemory[offset / 4], sizeof(uint) * _blockSize);

				entry.memAddress = offset;
				success = true;

				break;
			}
		}

		return success;
	}

	bool Replace(uint address)
	{
		//maybe.., i think that write lru algo.
		CacheLine command = MakeCacheLineCommand(address);

		//first valus is wayIdx
		std::vector<std::pair<uint, time_t>> timeStamps;

		for (uint wayIdx = 0; wayIdx < _nWay; ++wayIdx)
			timeStamps.push_back(std::make_pair(wayIdx, _cacheDatas[command.index][wayIdx].timeStamp));

		auto sortFunc = [](const std::pair<uint, time_t>& left, std::pair<uint, time_t>& right)
		{
			return left.second < right.second;
		};

		std::sort(timeStamps.begin(), timeStamps.end(), sortFunc);

		const std::pair<uint, time_t>& replaceTarget = timeStamps[0];

		//first value is way idx
		CacheEntry& entry = _cacheDatas[command.index][replaceTarget.first];

		if (entry.isRequiredUpdate)
		{
			uint writeAddress = entry.memAddress;
			memcpy(&_systemMemory[writeAddress / 4], entry.datas, sizeof(uint) * _blockSize);
			
			entry.isRequiredUpdate = false;
			entry.isEmpty = true;
		}
		
		return LoadCache(address);
	}

	uint FetchData(uint address)
	{
		uint result = 0;
		CacheLine command = MakeCacheLineCommand(address);

		CacheEntry* entry = nullptr;
		bool isHit = IsValid(command) && IsTagMatch(command, &entry);
		if (isHit) //딱히 더 손볼건 없는듯
		{
			_hitCount++;
			ASSERT_COND_MSG(entry, "Error, what the");
			result = entry->datas[command.offset / 4];
		}
		else
		{
			_missCount++;

			if (LoadCache(address) == false)
				ASSERT_COND_MSG(Replace(address), "Error, yeah");

			isHit = IsValid(command) && IsTagMatch(command, &entry);
			ASSERT_COND_MSG(isHit, "Error, what the hell");
			result = entry->datas[command.offset / 4];
		}

		entry->timeStamp = time(nullptr);
		return result;
	}

	void InputData(uint address, uint data)
	{
		CacheLine command = MakeCacheLineCommand(address);

		CacheEntry* entry = nullptr;
		bool isHit = IsValid(command) && IsTagMatch(command, &entry);

		if (isHit)
		{
			_hitCount++;
		}
		else
		{
			_missCount++;
			
			if (LoadCache(address) == false)
				ASSERT_COND_MSG(Replace(address), "Error, yeah");

			isHit = IsValid(command) && IsTagMatch(command, &entry);
			ASSERT_COND_MSG(isHit, "Error, what the hell");
		}

		entry->datas[command.offset / 4] = data;
		entry->isRequiredUpdate = true;
		entry->timeStamp = time(nullptr);
	}
};
