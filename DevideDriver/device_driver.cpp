#include "device_driver.h"
#include <vector>

using std::vector;

class ReadException : public std::exception
{
public:
    char const* what() const override
    {
        return "ReadFailException";
    }
};
class WriteException : public std::exception
{
public:
    char const* what() const override
    {
        return "WriteFailException";
    }
};

DeviceDriver::DeviceDriver(FlashMemoryDevice* hardware) : m_hardware(hardware)
{
}

int DeviceDriver::read(long address)
{
    // TODO: implement this method properly
    int initial_result = (int)(m_hardware->read(address));

    for (int i = 1; i < DeviceDriver::READ_COUNT; i++)
    {
        if (initial_result != (int)(m_hardware->read(address))) {
            throw ReadException();
        }
    }

    return initial_result;
}

void DeviceDriver::write(long address, int data)
{
    // TODO: implement this method
    if (m_hardware->read(address) == 0xFF) {
        m_hardware->write(address, (unsigned char)data);
    }
    else
    {
        throw WriteException();
    }
}