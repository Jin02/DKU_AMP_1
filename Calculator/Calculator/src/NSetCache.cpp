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
            _cacheDatas[i][wayIdx].datas = new uint[_blockSize];
            memset(_cacheDatas[i][wayIdx].datas, 0, sizeof(uint) * _blockSize);
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
            entry.isRequiredUpdate = false;
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
    //maybe.., i think that write lru algo.
    CacheLine command = MakeCacheLineCommand(address);
    
    //first valus is wayIdx
    std::vector<std::pair<uint, clock_t>> timeStamps;

    bool isAllReadCache = false;
    for (uint wayIdx = 0; wayIdx < _nWay; ++wayIdx)
    {
        timeStamps.push_back(std::make_pair(wayIdx, _cacheDatas[command.index][wayIdx].timeStamp));
        isAllReadCache = (_cacheDatas[command.index][wayIdx].isRequiredUpdate == false);
    }
    
    auto sortFunc = [](const std::pair<uint, clock_t>& left, const std::pair<uint, clock_t>& right)
    {
        return left.second < right.second;
    };
    
    std::sort(timeStamps.begin(), timeStamps.end(), sortFunc);
    const std::pair<uint, clock_t>& replaceTarget = timeStamps[0];
    
    //first value is way idx
    CacheEntry& entry = _cacheDatas[command.index][replaceTarget.first];
    {
        uint writeAddress = entry.memAddress;

        if(entry.isRequiredUpdate)
            memcpy(&_systemMemory[writeAddress / 4], entry.datas, _blockSize);
        
        entry.isRequiredUpdate = false;
        entry.isEmpty = true;
    }

    return LoadCache(address);
}

uint NSetCache::FetchData(uint address)
{
    GlobalDumpLogManager->AddLog("Cache Fetch Data\n");
    uint result = 0;
    CacheLine command = MakeCacheLineCommand(address);
    
    CacheEntry* entry = nullptr;
    bool isHit = IsValid(command) && IsTagMatch(command, &entry);
    if (isHit) //딱히 더 손볼건 없는듯
    {
        GlobalDumpLogManager->AddLog("Cache Hit\t\t| Current Count = " + std::to_string(++_hitCount), true);
        ASSERT_COND_MSG(entry, "Error, what the");
        result = entry->datas[command.offset / 4];
    }
    else
    {
        GlobalDumpLogManager->AddLog("Cache Miss\t\t| Current Count = " + std::to_string(++_missCount), true);
        
        if (LoadCache(address) == false)
            ASSERT_COND_MSG(Replace(address), "Error, where is your memory?");
        
        isHit = IsValid(command) && IsTagMatch(command, &entry);
        ASSERT_COND_MSG(isHit, "Error, Invalid result value");
        result = entry->datas[command.offset / 4];
    }
    
    HitAndAMATLog();
    
    entry->timeStamp = clock();
    return result;
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
    entry->isRequiredUpdate = true;
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