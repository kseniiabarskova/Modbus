#include <iostream>

#include "fstream"
#include "src/connection/factories/modbus_rtu_over_tcp_factory_impl1.h"

void readModbusToFile()
{
    auto factory = std::make_shared<ModbusRTUOverTCPFactoryImpl1>("127.0.0.1", 4001, 3000);
    auto client = factory->createConnection();
    client->connect();
    std::ofstream file("modbus_data.txt");
    file << "Address | value" << std::endl;
    for (int address = 0; address < 10; address++) {
        uint16_t value = 0;
        client->readHoldingRegister(address, value, 1);
        file << address << " | " << value << std::endl;

    }
    file.close();
    client->disconnect();
    std::string command = "notepad modbus_data.txt";
    system(command.c_str());

}


int main() {
    std::cout << "Hello, World!" << std::endl;
    readModbusToFile();


    return 0;
}