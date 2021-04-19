#pragma once

#include <QObject>

#include "cachesim.h"

namespace Ripes {

/**
 * @brief The CacheShim class
 * Provides a wrapper around the current processor models' data- and instruction memories, to be used in the cache
 * simulator interface.
 */
class L1CacheShim : public CacheInterface {
    Q_OBJECT
public:
    enum class CacheType { DataCache, InstrCache };
    L1CacheShim(CacheType type, QObject* parent);
    void access(uint32_t address, AccessType type) override;

    void setType(CacheType type);
    void reassociateMemory();

private:
    void processorReset();
    void processorWasClocked();
    void processorReversed();

    /**
     * @brief m_memory
     * The cache simulator may be attached to either a ROM or a Read/Write memory element. Accessing the underlying
     * VSRTL component signals are dependent on the given type of the memory.
     */
    CacheType m_type;
    union {
        RWMemory const* rw = nullptr;
        ROMMemory const* rom;

    } m_memory;
};

}  // namespace Ripes