#include "modbus_tcp_transport_libmodbus_impl1.h"

#include <iostream>

#include "src/libs/libmodbus/modbus-private.h"


struct ModbusTCPTransportLibmodbusImpl1::Impl {
  PackageType _package_type = RTU;

  std::string ip;
  int port;

  // TODO: TD: Потом убрать!
  int default_timeout_in_ms = 3000;

  _modbus *ctx = nullptr;

  std::mutex mutex;

  modbus::ModbusResult readInputRegister(uint16_t reg_num, uint16_t &result, uint8_t modbus_id);
  modbus::ModbusResult readInputRegisters(uint16_t reg_num,
                                          uint16_t reg_count,
                                          std::vector<uint16_t> &result,
                                          uint8_t modbus_id);
  modbus::ModbusResult readHoldingRegister(uint16_t reg_num, uint16_t &result, uint8_t modbus_id);
  modbus::ModbusResult readHoldingRegisters(uint16_t reg_num,
                                            uint16_t reg_count,
                                            std::vector<uint16_t> &result,
                                            uint8_t modbus_id);
  modbus::ModbusResult writeHoldingRegister(uint16_t reg_num, uint16_t value, uint8_t modbus_id);
  modbus::ModbusResult writeHoldingRegisters(uint16_t reg_num,
                                             std::vector<uint16_t> values,
                                             uint8_t modbus_id);
  modbus::ModbusResult saveToEEPROM(uint8_t modbus_id);

  modbus::ModbusResult fromErrnoToModbusResult(int err);
};


ModbusTCPTransportLibmodbusImpl1::ModbusTCPTransportLibmodbusImpl1(const std::string &ip, int port,
                                                                   PackageType package_type):
    _impl(new Impl) {

  _impl->ip = ip;
  _impl->port = port;
  _impl->_package_type = package_type;
  switch (_impl->_package_type) {
    case RTU:
      _impl->ctx = modbus_new_rtutcp_pi(ip.c_str(), std::to_string(port).c_str());
      break;
    case TCP:
      _impl->ctx = modbus_new_tcp_pi(ip.c_str(), std::to_string(port).c_str());
      break;
  }

  setTimeout(_impl->default_timeout_in_ms / 1000, _impl->default_timeout_in_ms % 1000);
}

ModbusTCPTransportLibmodbusImpl1::~ModbusTCPTransportLibmodbusImpl1() {
  delete _impl;
}

void ModbusTCPTransportLibmodbusImpl1::setTimeout(uint32_t timeout_sec, uint32_t timeout_usec) {
  std::lock_guard<std::mutex> lock(_impl->mutex);
  auto mb = _impl->ctx;
  if (mb != nullptr) {
    modbus_set_response_timeout(mb, timeout_sec, timeout_usec);
  }
}

std::string ModbusTCPTransportLibmodbusImpl1::getIP() const {
  return _impl->ip;
}

uint16_t ModbusTCPTransportLibmodbusImpl1::getPort() const {
  return _impl->port;
}

bool ModbusTCPTransportLibmodbusImpl1::connect() {
  std::lock_guard<std::mutex> lock(_impl->mutex);

  auto conn_status = modbus_connect(_impl->ctx);
  return conn_status == 0;
}

void ModbusTCPTransportLibmodbusImpl1::disconnect() {
  std::lock_guard<std::mutex> lock(_impl->mutex);
  modbus_close(_impl->ctx);
}



modbus::ModbusResult ModbusTCPTransportLibmodbusImpl1::readInputRegister(uint16_t reg_num,
                                                                         uint16_t &result,
                                                                         uint8_t modbus_id) {
  std::lock_guard<std::mutex> lock(_impl->mutex);
  auto error_code = _impl->readInputRegister(reg_num, result, modbus_id);
  return error_code;
}

modbus::ModbusResult ModbusTCPTransportLibmodbusImpl1::readInputRegisters(uint16_t reg_num,
                                                                          uint16_t reg_count,
                                                                          std::vector<uint16_t> &result,
                                                                          uint8_t modbus_id) {
  std::lock_guard<std::mutex> lock(_impl->mutex);
  auto error_code = _impl->readInputRegisters(reg_num, reg_count, result, modbus_id);
  return error_code;
}

modbus::ModbusResult ModbusTCPTransportLibmodbusImpl1::readHoldingRegister(uint16_t reg_num,
                                                                           uint16_t &result,
                                                                           uint8_t modbus_id) {
  std::lock_guard<std::mutex> lock(_impl->mutex);
  auto error_code = _impl->readHoldingRegister(reg_num, result, modbus_id);
  return error_code;

}

modbus::ModbusResult ModbusTCPTransportLibmodbusImpl1::readHoldingRegisters(uint16_t reg_num,
                                                                            uint16_t reg_count,
                                                                            std::vector<uint16_t> &result,
                                                                            uint8_t modbus_id) {
  std::lock_guard<std::mutex> lock(_impl->mutex);
  auto error_code = _impl->readHoldingRegisters(reg_num, reg_count, result, modbus_id);
  return error_code;
}

modbus::ModbusResult ModbusTCPTransportLibmodbusImpl1::writeHoldingRegister(uint16_t reg_num,
                                                                            uint16_t value,
                                                                            uint8_t modbus_id) {
  std::lock_guard<std::mutex> lock(_impl->mutex);
  auto error_code = _impl->writeHoldingRegister(reg_num, value, modbus_id);
  return error_code;
}

modbus::ModbusResult ModbusTCPTransportLibmodbusImpl1::writeHoldingRegisters(uint16_t reg_num,
                                                                             std::vector<uint16_t> values,
                                                                             uint8_t modbus_id) {
  std::lock_guard<std::mutex> lock(_impl->mutex);
  auto error_code = _impl->writeHoldingRegisters(reg_num, values, modbus_id);
  return error_code;
}

modbus::ModbusResult ModbusTCPTransportLibmodbusImpl1::saveToEEPROM(uint8_t modbus_id) {
  std::lock_guard<std::mutex> lock(_impl->mutex);
  auto error_code = _impl->saveToEEPROM(modbus_id);
  return error_code;
}

bool ModbusTCPTransportLibmodbusImpl1::isConnected(uint16_t modbus_id) {
  uint16_t value;
  return readInputRegister(0, value, (uint8_t)modbus_id) == modbus::NO_MODBUS_ERROR;
}

modbus::ModbusResult ModbusTCPTransportLibmodbusImpl1::Impl::readInputRegister(uint16_t reg_num,
                                                                               uint16_t &result,
                                                                               uint8_t modbus_id) {
  auto error_code = modbus::UNHANDLED_ERROR;

  int reg_count = 1;
  std::vector<uint16_t> values(reg_count);
  error_code = readInputRegisters(reg_num, reg_count, values, modbus_id);
  result = values[0];
  return error_code;
}

modbus::ModbusResult ModbusTCPTransportLibmodbusImpl1::Impl::readInputRegisters(uint16_t reg_num,
                                                                                uint16_t reg_count,
                                                                                std::vector<uint16_t> &result,
                                                                                uint8_t modbus_id) {
  auto error_code = modbus::UNHANDLED_ERROR;

  auto *mb = ctx;
  if (mb != nullptr) {
    auto set_slave_status = modbus_set_slave(mb, modbus_id);
    if (set_slave_status != 0) {
      error_code = modbus::INVALID_REQUEST;
      return error_code;
    }

    result.resize(reg_count);
    auto request = new uint8_t[MAX_MESSAGE_LENGTH];
    auto response = new uint8_t[MAX_MESSAGE_LENGTH];
    size_t request_size = 0;
    size_t response_size = 0;
    auto read_reg_status = modbus_read_input_registers(mb, reg_num, reg_count, result.data(),
                                                       &request, &request_size, &response, &response_size);
    delete[] request;
    delete[] response;
    std::cout << "read reg status: " << read_reg_status << "; reg_count " << reg_count << " " << __func__ << std::endl;
    if (read_reg_status == reg_count) {
      error_code = modbus::NO_MODBUS_ERROR;
    } else {
      error_code = fromErrnoToModbusResult(errno);
    }
  }

  return error_code;
}

modbus::ModbusResult ModbusTCPTransportLibmodbusImpl1::Impl::readHoldingRegister(uint16_t reg_num,
                                                                                 uint16_t &result,
                                                                                 uint8_t modbus_id) {
  auto error_code = modbus::UNHANDLED_ERROR;

  int reg_count = 1;
  std::vector<uint16_t> values(reg_count);
  error_code = readHoldingRegisters(reg_num, reg_count, values, modbus_id);
  result = values[0];
  return error_code;
}

modbus::ModbusResult ModbusTCPTransportLibmodbusImpl1::Impl::readHoldingRegisters(uint16_t reg_num,
                                                                                  uint16_t reg_count,
                                                                                  std::vector<uint16_t> &result,
                                                                                  uint8_t modbus_id) {
  auto error_code = modbus::UNHANDLED_ERROR;

  auto *mb = ctx;
  if (mb != nullptr) {
    auto set_slave_status = modbus_set_slave(mb, modbus_id);
    if (set_slave_status != 0) {
      error_code = modbus::INVALID_REQUEST;
      return error_code;
    }

    result.resize(reg_count);
    auto request = new uint8_t[MAX_MESSAGE_LENGTH];
    auto response = new uint8_t[MAX_MESSAGE_LENGTH];
    size_t request_size = 0;
    size_t response_size = 0;
    auto read_reg_status = modbus_read_registers(mb, reg_num, reg_count, result.data(),
                                                 &request, &request_size, &response, &response_size);
    delete[] request;
    delete[] response;
    if (read_reg_status == reg_count) {
      error_code = modbus::NO_MODBUS_ERROR;
    } else {
      error_code = fromErrnoToModbusResult(errno);
    }
  }

  return error_code;
}

modbus::ModbusResult ModbusTCPTransportLibmodbusImpl1::Impl::writeHoldingRegister(uint16_t reg_num,
                                                                                  uint16_t value,
                                                                                  uint8_t modbus_id) {
  auto error_code = modbus::UNHANDLED_ERROR;

  auto *mb = ctx;
  if (mb != nullptr) {

    auto set_slave_status = modbus_set_slave(mb, modbus_id);
    if (set_slave_status != 0) {
      error_code = modbus::INVALID_REQUEST;
      return error_code;
    }

    auto request = new uint8_t[MAX_MESSAGE_LENGTH];
    auto response = new uint8_t[MAX_MESSAGE_LENGTH];
    size_t request_size = 0;
    size_t response_size = 0;
    auto write_reg_status = modbus_write_register(mb, reg_num, value,
                                                  &request, &request_size,
                                                  &response, &response_size);

    delete[] request;
    delete[] response;

    if (write_reg_status == 1) {
      error_code = modbus::NO_MODBUS_ERROR;
    } else {
      error_code = fromErrnoToModbusResult(errno);
    }
  }

  return error_code;
}

modbus::ModbusResult ModbusTCPTransportLibmodbusImpl1::Impl::writeHoldingRegisters(uint16_t reg_num,
                                                                                   std::vector<uint16_t> values,
                                                                                   uint8_t modbus_id) {
  auto error_code = modbus::UNHANDLED_ERROR;

  auto *mb = ctx;
  if (mb != nullptr) {
    auto set_slave_status = modbus_set_slave(mb, modbus_id);
    if (set_slave_status != 0) {
      error_code = modbus::INVALID_REQUEST;
      return error_code;
    }

    int reg_count = values.size();
    auto reg_data = values.data();
    auto request = new uint8_t[MAX_MESSAGE_LENGTH];
    auto response = new uint8_t[MAX_MESSAGE_LENGTH];
    size_t request_size = 0;
    size_t response_size = 0;
    auto write_reg_status = modbus_write_registers(mb, reg_num, reg_count, reg_data,
                                                   &request, &request_size, &response, &response_size);
    delete[] request;
    delete[] response;

    if (write_reg_status == reg_count) {
      error_code = modbus::NO_MODBUS_ERROR;
    } else {
      error_code = fromErrnoToModbusResult(errno);
    }
  }

  return error_code;
}

modbus::ModbusResult ModbusTCPTransportLibmodbusImpl1::Impl::saveToEEPROM(uint8_t modbus_id) {
  auto error_code = modbus::UNHANDLED_ERROR;

  auto *mb = ctx;
  if (mb != nullptr) {
//    uint8_t raw_req[] = { modbus_id, 0x65, 0x00, 0x00, 0x00, 0x00 };
//    int req_length;
//    uint8_t rsp[MODBUS_TCP_MAX_ADU_LENGTH];

    auto request = new uint8_t[MAX_MESSAGE_LENGTH] { modbus_id, 0x65, 0x00, 0x00, 0x00, 0x00 };
    auto response = new uint8_t[MAX_MESSAGE_LENGTH];
    size_t request_size = 0;
    size_t response_size = 0;
    request_size = modbus_send_raw_request(mb, &request, 6 * sizeof(uint8_t));
    auto response_status = modbus_receive_confirmation(mb, response);

    bool is_ok = true;
    for (int i = 0; i < 6; i++) {
      is_ok &= request[i] == response[i];
    }

    if (request_size == -1) {
      error_code = modbus::TCP_TIMEOUT_ERROR;
    } else if (!is_ok) {
      error_code = modbus::INVALID_RESPONSE;
    } else {
      error_code = fromErrnoToModbusResult(errno);
    }

    delete[] request;
    delete[] response;
  }

  return error_code;
}

modbus::ModbusResult ModbusTCPTransportLibmodbusImpl1::Impl::fromErrnoToModbusResult(int err) {
  switch (err) {
    case EMBXILFUN:
      std::cerr << "Illegal function" << std::endl;
      return modbus::ILLEGAL_FUNCTION;
    case EMBXILADD:
      std::cerr << "Illegal data address" << std::endl;
      return modbus::ILLEGAL_DATA_ADDRESS;
    case EMBXILVAL:
      std::cerr << "Illegal data value" << std::endl;
      return modbus::ILLEGAL_DATA_VALUE;
    case EMBXSFAIL:
      std::cerr << "Slave device or server failure" << std::endl;
      return modbus::SERVER_DEVICE_FAILURE;
    case EMBXACK:
      std::cerr << "Acknowledge" << std::endl;
      return modbus::ACKNOWLEDGE;
    case EMBXSBUSY:
      std::cerr << "Slave device or server is busy" << std::endl;
      return modbus::SERVER_DEVICE_BUSY;
    case EMBXNACK:
      std::cerr << "Negative acknowledge" << std::endl;
      return modbus::NEGATIVE_ACKNOWLEDGE;
    case EMBXMEMPAR:
      std::cerr << "Memory parity error" << std::endl;
      return modbus::MEMORY_PARITY_ERROR;
    case EMBXGPATH:
      std::cerr << "Gateway path unavailable" << std::endl;
      return modbus::GATEWAY_PATH_UNAVAILABLE;
    case EMBXGTAR:
      std::cerr << "Target device failed to respond" << std::endl;
      return modbus::GATEWAY_TARGET_DEVICE_FAILED_TO_RESPOND;
    case EMBBADCRC:
      std::cerr << "Invalid CRC" << std::endl;
      return modbus::CRC_ERROR;
    case EMBBADDATA:
      std::cerr << "Invalid data" << std::endl;
      return modbus::INVALID_RESPONSE;
    case EMBBADEXC:
      std::cerr << "Invalid exception code" << std::endl;
      return modbus::INVALID_RESPONSE;
    case EMBMDATA:
      std::cerr << "Too many data" << std::endl;
      return modbus::INVALID_REQUEST;
    case EMBBADSLAVE:
      std::cerr << "Response not from requested slave" << std::endl;
      return modbus::INVALID_RESPONSE;
    case EMBSOCKERR:
      std::cerr << "Socket error" << std::endl;
      return modbus::NO_SOCKET_CONNECTION;
    case EMBTIMEOUTERR:
      std::cerr << "TCP Timeout error" << std::endl;
      return modbus::TCP_TIMEOUT_ERROR;
    default:
      std::cerr << strerror(err);
      return modbus::UNHANDLED_ERROR;
  }
}


