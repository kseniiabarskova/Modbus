#ifndef MODBUS_LESSON_MODBUSWRAPPERIMPL1_H
#define MODBUS_LESSON_MODBUSWRAPPERIMPL1_H

#include "modbus_wrapper.h"
#include "../connection/factories/modbus_rtu_over_tcp_factory_impl1.h"
#include <string>

class ModbusWrapperImpl1 : public ModbusWrapper {
public:
    ModbusWrapperImpl1(const std::string& ip, int port, uint32_t response_timeout_ms, uint16_t holding_count = 100, uint16_t input_count = 100);

    bool connect() override;
    void disconnect() override;
    bool ReadHR(uint16_t address, uint16_t &value, uint8_t modbus_id = 1) override;
    bool ReadHRs(uint16_t address, uint16_t count, std::vector<uint16_t> &values, uint8_t modbus_id = 1) override;
    bool ReadIR(uint16_t address, uint16_t &value, uint8_t modbus_id = 1) override;
    bool ReadIRs(uint16_t address, uint16_t count, std::vector<uint16_t>& values, uint8_t modbus_id = 1) override;
    bool WriteHR(uint16_t address, uint16_t value, uint8_t modbus_id = 1) override;
    bool WriteHRs(uint16_t address, const std::vector<uint16_t> &values, uint8_t modbus_id = 1) override;
    void Update() override;

private:
    std::string _ip;
    int _port;
    uint32_t _timeout_ms;
};

#endif //MODBUS_LESSON_MODBUSWRAPPERIMPL1_H