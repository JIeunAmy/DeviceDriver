#include "gmock/gmock.h"
#include "flash_memory_device.h"

using namespace testing;
class FlashMock : public FlashMemoryDevice {

public:
	MOCK_METHOD(unsigned char, read, (long address), (override));
	MOCK_METHOD(void, write, (long address, unsigned char data), (override));
};