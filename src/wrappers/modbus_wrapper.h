#ifndef MODBUS_LESSON_MODBUS_WRAPPER_H
#define MODBUS_LESSON_MODBUS_WRAPPER_H

#include <vector>
#include <memory>

namespace modbus {
    class ModbusClient;
}

class ModbusWrapper
{
public:
    virtual ~ModbusWrapper() = default;
    virtual bool connect() = 0;
    virtual void disconnect() = 0;
    virtual bool ReadHR(uint16_t address, uint16_t &value, uint8_t modbus_id = 1) = 0;
    virtual bool ReadHRs(uint16_t address, uint16_t count, std::vector<uint16_t> &values, uint8_t modbus_id = 1) = 0;
    virtual bool ReadIR(uint16_t address, uint16_t &value, uint8_t modbus_id = 1) = 0;
    virtual bool ReadIRs(uint16_t address, uint16_t count, std::vector<uint16_t>& values, uint8_t modbus_id = 1) = 0;
    virtual bool WriteHR(uint16_t address, uint16_t value, uint8_t modbus_id = 1) = 0;
    virtual bool WriteHRs(uint16_t address, const std::vector<uint16_t> &values, uint8_t modbus_id = 1) = 0;
    virtual void Update() = 0;

protected:
    uint16_t holding_count = 0;
    uint16_t input_count = 0;
    std::shared_ptr<modbus::ModbusClient> _modbus_client;
};

#endif //MODBUS_LESSON_MODBUS_WRAPPER_H