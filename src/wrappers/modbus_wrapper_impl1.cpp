#include "modbusWrapperImpl1.h"

// Исправленный конструктор
ModbusWrapperImpl1::ModbusWrapperImpl1(const std::string &ip, int port, uint32_t response_timeout_ms, uint16_t holding_count, uint16_t input_count)
        : _ip(ip), _port(port), _timeout_ms(response_timeout_ms)
{
    this->holding_count = holding_count;
    this->input_count = input_count;

    auto factory = std::make_shared<ModbusRTUOverTCPFactoryImpl1>(_ip, _port, _timeout_ms);
    _modbus_client = factory->createConnection();
}

bool ModbusWrapperImpl1::connect() {
    if (_modbus_client) {
        return _modbus_client->connect();
    }
    return false;
}

void ModbusWrapperImpl1::disconnect() {
    if (_modbus_client) {
        _modbus_client->disconnect();
    }
}

bool ModbusWrapperImpl1::ReadHR(uint16_t address, uint16_t &value, uint8_t modbus_id) {
    if (!_modbus_client || address >= holding_count) {
        return false;
    }
    auto result = _modbus_client->readHoldingRegister(address, value, modbus_id);
    return (result == modbus::NO_MODBUS_ERROR);
}

bool ModbusWrapperImpl1::ReadHRs(uint16_t address, uint16_t count, std::vector<uint16_t> &values, uint8_t modbus_id) {
    if (!_modbus_client || address + count > holding_count) {
        return false;
    }
    auto result = _modbus_client->readHoldingRegisters(address, count, values, modbus_id);
    return (result == modbus::NO_MODBUS_ERROR);
}

bool ModbusWrapperImpl1::ReadIR(uint16_t address, uint16_t &value, uint8_t modbus_id) {
    if (!_modbus_client || address >= input_count) {
        return false;
    }
    auto result = _modbus_client->readInputRegister(address, value, modbus_id);
    return (result == modbus::NO_MODBUS_ERROR);
}

bool ModbusWrapperImpl1::ReadIRs(uint16_t address, uint16_t count, std::vector<uint16_t> &values, uint8_t modbus_id) {
    if (!_modbus_client || address + count > input_count) {
        return false;
    }
    auto result = _modbus_client->readInputRegisters(address, count, values, modbus_id);
    return (result == modbus::NO_MODBUS_ERROR);
}

bool ModbusWrapperImpl1::WriteHR(uint16_t address, uint16_t value, uint8_t modbus_id) {
    if (!_modbus_client || address >= holding_count) {
        return false;
    }
    auto result = _modbus_client->writeHoldingRegister(address, value, modbus_id);
    return (result == modbus::NO_MODBUS_ERROR);
}

bool ModbusWrapperImpl1::WriteHRs(uint16_t address, const std::vector<uint16_t> &values, uint8_t modbus_id) {
    if (!_modbus_client || address + values.size() > holding_count) {
        return false;
    }
    auto result = _modbus_client->writeHoldingRegisters(address, values, modbus_id);
    return (result == modbus::NO_MODBUS_ERROR);
}

void ModbusWrapperImpl1::Update() {

}