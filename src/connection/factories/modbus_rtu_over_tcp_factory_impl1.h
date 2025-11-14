#ifndef MODBUS_LESSON_SRC_CONNECTION_FACTORIES_MODBUS_RTU_OVER_TCP_FACTORY_IMPL1_H_
#define MODBUS_LESSON_SRC_CONNECTION_FACTORIES_MODBUS_RTU_OVER_TCP_FACTORY_IMPL1_H_

#include <string>
#include <memory>
#include "../connection_factory.h"

class ModbusRTUOverTCPFactoryImpl1 : public ModbusClientFactory{
 public:
  explicit ModbusRTUOverTCPFactoryImpl1(const std::string &ip, int port, uint32_t response_timeout_ms);

  std::shared_ptr<modbus::ModbusClient> createConnection() override;

 private:
  std::string _ip;
  int _port = 0;
  uint32_t _timeout = 0;
};

#endif //MODBUS_LESSON_SRC_CONNECTION_FACTORIES_MODBUS_RTU_OVER_TCP_FACTORY_IMPL1_H_
