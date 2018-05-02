#include "NSetCache.h"
#include "DumpLogManager.h"
#include <algorithm>

NSetCache::NSetCache(uint cacheSize, uint cacheBlockSize, uint nWay, uint* systemMemory, uint hitTime, uint missPenalty)
: _nWay(nWay), _systemMemory(systemMemory), _blockSize(cacheBlockSize), _hitCount(0), _missCount(0),_hitTime(hitTime), _missPenalty(missPenalty)
{
    auto log2 = [](double n)
    {
        return log(n) / log(2);
    };
    CacheLine line;
    line.offset = log2(_blockSize);
    
    uint cacheSetCount = (cacheSize / _blockSize) / nWay;
    line.index = log2(cacheSetCount);
    
    line.tag = 32 - (line.index + line.offset);
    
    _lineInfo = line;
    
    _cacheDatas = new CacheEntry*[line.index + 1];
    
    for (uint i = 0; i < line.index + 1; ++i)
    {
        _cacheDatas[i] = new CacheEntry[nWay];
        for(uint wayIdx = 0; wayIdx < nWay; ++wayIdx)
        {
            _cacheDatas[i][wayIdx].datas = new uint[_blockSize / 4];
            memset(_cacheDatas[i][wayIdx].datas, 0, _blockSize);
        }
    }
}

NSetCache::~NSetCache()
{
    
}

NSetCache::CacheLine NSetCache::MakeCacheLineCommand(uint address)
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

bool NSetCache::IsValid(const CacheLine& command, CacheEntry** outEntry)
{
    for (uint i = 0; i < _nWay; ++i)
    {
        CacheEntry& entry = _cacheDatas[command.index][i];
        if (entry.isEmpty == false)
        {
            if (outEntry)
                (*outEntry) = &entry;
            
            return (entry.isEmpty == false);
        }
    }
    
    return false;
}

bool NSetCache::IsTagMatch(const CacheLine& command, CacheEntry** outEntry)
{
    for (uint i = 0; i < _nWay; ++i)
    {
        CacheEntry& entry = _cacheDatas[command.index][i];
        
        if (entry.tag == command.tag)
        {
            if (outEntry)
                (*outEntry) = &entry;
            
            return (entry.isEmpty == false);
        }
    }
    
    return false;
}

bool NSetCache::LoadCache(uint address)
{
    CacheLine command = MakeCacheLineCommand(address);
    uint offset = (address / _blockSize) * _blockSize;
    
    bool success = false;
    for (uint wayIdx = 0; wayIdx < _nWay; ++wayIdx)
    {
        CacheEntry& entry = _cacheDatas[command.index][wayIdx];
        if (entry.isEmpty)
        {
            entry.tag = command.tag;
            entry.isEmpty = false;
            entry.dirty = false;
            entry.timeStamp = clock();
            
            memcpy(entry.datas, &_systemMemory[offset / 4], _blockSize);
            
            entry.memAddress = offset;
            success = true;
            
            break;
        }
    }
    
    return success;
}

bool NSetCache::Replace(uint address)
{
	// address를 캐시에서 사용할 tag, index, offset으로 분해한다.
    CacheLine command = MakeCacheLineCommand(address);

	uint	minTimeWayIndex = 0;
	clock_t	minTime			= _cacheDatas[command.index][minTimeWayIndex].timeStamp;
    for (uint wayIdx = 1; wayIdx < _nWay; ++wayIdx)	// 캐시 라인을 순회하며 가장 낮은 time 값을 가진 캐시라인 선택
	{
		clock_t time = _cacheDatas[command.index][wayIdx].timeStamp;
		if( minTime > time )
		{
			minTime			= time;
			minTimeWayIndex	= wayIdx;
		}
	}
	
	// time stamp 값이 높을수록 최근에 접근한 캐시 라인이므로, 가장 낮은 time stamp 값을 가진 캐시 라인을 선택
    CacheEntry& entry = _cacheDatas[command.index][minTimeWayIndex];
    {
        uint writeAddress = entry.memAddress;

		// Write Back 방식으로 memory에 write를 수행
        if(entry.dirty)
            memcpy(&_systemMemory[writeAddress / 4], entry.datas, _blockSize);
        
        entry.dirty			= false;
        entry.isEmpty		= true;
    }

	// 메모리에서 데이터를 가져와 캐시에 등록시키는 작업.
    return LoadCache(address);
}

uint NSetCache::FetchData(uint address)
{
    GlobalDumpLogManager->AddLog("Cache Fetch Data\n");
	// address를 분석하여 tag, index, offset으로 분해
	CacheLine command	= MakeCacheLineCommand(address);
	CacheEntry* entry	= nullptr;
	
	// Cache Hit 체크
	bool isHit = IsValid(command) && IsTagMatch(command, &entry);
    if (isHit == false)
    {
		GlobalDumpLogManager->AddLog("Cache Miss\t\t| Current Count = " + std::to_string(++_missCount), true);

		// OS Level
		// TLB 및 Page Table로 가서 데이터를 가져와 캐시에 데이터를 등록하는 절차를 단순화.
		if (LoadCache(address) == false)
			ASSERT_COND_MSG(Replace(address), "Error, where is your memory?");
		
		// 방금 등록한 Cache line 검색. 원래는 Replace에서 별도로 가져오면 좋으나
		for (uint i = 0; i < _nWay; ++i)
		{
			if (_cacheDatas[command.index][i].tag == command.tag)
			{
				entry = &_cacheDatas[command.index][i];
				break;
			}
		}
    }
	else
	{
		GlobalDumpLogManager->AddLog("Cache Hit\t\t| Current Count = " + std::to_string(++_hitCount), true);
	}
    HitAndAMATLog();
	

	// 1 word = 4 byte니, array index로 나타내려면 /4 해야함
    entry->timeStamp = clock();
    return entry->datas[command.offset / 4];
}

void NSetCache::InputData(uint address, uint data)
{
    CacheLine command = MakeCacheLineCommand(address);
    
    CacheEntry* entry = nullptr;
    bool isHit = IsValid(command) && IsTagMatch(command, &entry);
    
    if (isHit)
    {
        GlobalDumpLogManager->AddLog("Cache Hit\t\t| Current Count = " + std::to_string(++_hitCount), true);
    }
    else
    {
        GlobalDumpLogManager->AddLog("Cache Miss\t\t| Current Count = " + std::to_string(++_missCount), true);
        
        if (LoadCache(address) == false)
            ASSERT_COND_MSG(Replace(address), "Error, where is your memory?");
        
        isHit = IsValid(command) && IsTagMatch(command, &entry);
        ASSERT_COND_MSG(isHit, "Error, Invalid result value");
    }
    
    HitAndAMATLog();
    
    entry->datas[command.offset / 4] = data;
    entry->dirty = true;
    entry->timeStamp = clock();
}

void NSetCache::HitAndAMATLog(bool usePrintLog)
{
    float hitRate = (float)_hitCount / (float)(_hitCount + _missCount);
    std::string buff = "Current Hit Rate\t| " + std::to_string(hitRate);
    GlobalDumpLogManager->AddLog(buff, true);
    if(usePrintLog)
        printf("%s\n", buff.c_str());
    
    float missRate = (float)_missCount / (float)(_hitCount + _missCount);
    buff = "Current AMAT\t\t| " + std::to_string((hitRate * _hitTime) + (missRate * _missPenalty));
    GlobalDumpLogManager->AddLog(buff, true);
    if(usePrintLog)
        printf("%s\n", buff.c_str());
}
