#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include "src/connection/factories/modbus_rtu_over_tcp_factory_impl1.h"

void readModbusToFile() {
    std::cout << "Reading from Modbus to file..." << std::endl;
    auto factory = std::make_shared<ModbusRTUOverTCPFactoryImpl1>("127.0.0.1", 4001, 3000);
    auto client = factory->createConnection();
    client->connect();

    std::ofstream file("modbus_data.txt");
    file << "Address | value" << std::endl;

    for (int address = 0; address < 10; address++) {
        uint16_t value = 0;
        client->readHoldingRegister(address, value, 1);
        file << address << " | " << value << std::endl;
        std::cout << "Read address " << address << " = " << value << std::endl;
    }

    file.close();
    client->disconnect();

    system("notepad modbus_data.txt");
}

void writeFileToModbus() {
    std::cout << "Writing from file to Modbus..." << std::endl;
    auto factory = std::make_shared<ModbusRTUOverTCPFactoryImpl1>("127.0.0.1", 4001, 3000);
    auto client = factory->createConnection();
    client->connect();

    std::ifstream file("modbus_data.txt");
    std::string line;
    std::vector<std::pair<int, uint16_t>> registers;

    std::getline(file, line); // skip header
    std::cout << "Reading from file:" << std::endl;

    while (std::getline(file, line)) {
        size_t pos = line.find(" | ");
        if (pos != std::string::npos) {
            int address = std::stoi(line.substr(0, pos));
            uint16_t value = std::stoi(line.substr(pos + 3));
            registers.push_back({address, value});
            std::cout << "  Address " << address << " = " << value << std::endl;
        }
    }
    file.close();

    for (const auto& reg : registers) {
        client->writeHoldingRegister(reg.first, reg.second, 1);
    }

    client->disconnect();
}

int main() {
    int choice;
    while (true) {
        std::cout << "1. Read Modbus to file\n2. Write file to Modbus\n ";
        std::cin >> choice;

        switch (choice) {
            case 1:
                readModbusToFile();
                break;
            case 2:
                writeFileToModbus();
                break;
        }

        std::cout << std::endl;
    }

    return 0;
}