#include <iostream>


#include "src/connection/factories/modbus_rtu_over_tcp_factory_impl1.h"

int main() {


  std::cout << "Hello, World!" << std::endl;

  auto factory = std::make_shared<ModbusRTUOverTCPFactoryImpl1>("127.0.0.1", 4001, 3000);

  auto client = factory->createConnection();

  client->connect();

  uint16_t value = -1;

  client->readHoldingRegister(1, value, 1);

  std::cout << "Read Holding register: " << value << std::endl;

  client->disconnect();

  return 0;
}
