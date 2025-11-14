#include <iostream>
#include "modbus_rtu_over_tcp_factory_impl1.h"

#include "../impls/modbus_tcp_transport_libmodbus_impl1.h"

ModbusRTUOverTCPFactoryImpl1::ModbusRTUOverTCPFactoryImpl1(const std::string &ip,
                                                           int port,
                                                           uint32_t response_timeout_ms)
    : _ip(ip), _port(port), _timeout(response_timeout_ms) {

}

std::shared_ptr<modbus::ModbusClient> ModbusRTUOverTCPFactoryImpl1::createConnection() {
  auto result = std::make_shared<ModbusTCPTransportLibmodbusImpl1>(_ip, _port, ModbusTCPTransportLibmodbusImpl1::RTU);

  uint32_t sec_timeout = _timeout / 1000;
  uint32_t usec_timeout = (_timeout % 1000) * 1000;

  std::cout << "SecTimeout: " << sec_timeout << "; " << "USecTimeout " << usec_timeout << " " << __func__ << std::endl;
  result->setTimeout(sec_timeout, usec_timeout);

  return result;
}
