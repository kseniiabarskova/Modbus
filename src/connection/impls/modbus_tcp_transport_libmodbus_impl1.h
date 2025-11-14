#ifndef MODBUS_LESSON_SRC_CONNECTION_IMPLS_MODBUS_TCP_TRANSPORT_LIBMODBUS_IMPL1_H_
#define MODBUS_LESSON_SRC_CONNECTION_IMPLS_MODBUS_TCP_TRANSPORT_LIBMODBUS_IMPL1_H_

#include <string>

#include "../modbus_client.h"


 class ModbusTCPTransportLibmodbusImpl1 : public modbus::ModbusClient {
 public:
  explicit ModbusTCPTransportLibmodbusImpl1(const std::string &ip, int port, PackageType package_type);

  virtual ~ModbusTCPTransportLibmodbusImpl1();
  void setTimeout(uint32_t timeout_sec, uint32_t timeout_usec);

  bool connect() override;
  void disconnect() override;
  bool isConnected(uint16_t modbus_id) override;

  modbus::ModbusResult readInputRegister(uint16_t reg_num, uint16_t &result, uint8_t modbus_id) override;
  modbus::ModbusResult readInputRegisters(uint16_t reg_num,
                                          uint16_t reg_count,
                                          std::vector<uint16_t> &result,
                                          uint8_t modbus_id) override;
  modbus::ModbusResult readHoldingRegister(uint16_t reg_num, uint16_t &result, uint8_t modbus_id) override;
  modbus::ModbusResult readHoldingRegisters(uint16_t reg_num,
                                            uint16_t reg_count,
                                            std::vector<uint16_t> &result,
                                            uint8_t modbus_id) override;
  modbus::ModbusResult writeHoldingRegister(uint16_t reg_num, uint16_t value, uint8_t modbus_id) override;
  modbus::ModbusResult writeHoldingRegisters(uint16_t reg_num,
                                             std::vector<uint16_t> values,
                                             uint8_t modbus_id) override;
  modbus::ModbusResult saveToEEPROM(uint8_t modbus_id) override;
   std::string getIP() const override;
   uint16_t getPort() const override;

  private:
   struct Impl;
   Impl *_impl = nullptr;
 };

#endif //MODBUS_LESSON_SRC_CONNECTION_IMPLS_MODBUS_TCP_TRANSPORT_LIBMODBUS_IMPL1_H_
