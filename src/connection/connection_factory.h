#ifndef MODBUS_LESSON_SRC_CONNECTION_CONNECTION_FACTORY_H_
#define MODBUS_LESSON_SRC_CONNECTION_CONNECTION_FACTORY_H_

#include <memory>

#include "modbus_client.h"

class ModbusClientFactory{
  virtual std::shared_ptr<modbus::ModbusClient> createConnection() = 0;
};

#endif //MODBUS_LESSON_SRC_CONNECTION_CONNECTION_FACTORY_H_
