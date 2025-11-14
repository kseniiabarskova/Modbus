#ifndef MODBUS_LESSON_SRC_CONNECTION_MODBUS_CLIENT_H_
#define MODBUS_LESSON_SRC_CONNECTION_MODBUS_CLIENT_H_

#include <mutex>
#include <vector>

#include <boost/asio.hpp>
#include <boost/beast/core/tcp_stream.hpp>

#include "src/error_code.h"
#include "src/modbus_utils.h"

namespace modbus {
/**
 * Класс для осуществления работы с модбас устройством по протоколу Modbus RTU over TCP
 * Класс содержит только основные операции для использования, а т.е. чтение INPUT регистров
 * и чтение и запись HOLDING регистров.
 *
 * Так же, планируется предусмотреть обработку ошибок
 */
class ModbusClient{
    public:
    enum PackageType {
      RTU = 0x00,
          TCP = 0x01
    };

    public:
    virtual std::string getIP() const = 0;
    virtual uint16_t getPort() const = 0;

    virtual bool isConnected(uint16_t modbus_id = 1) = 0;

    /**
     * Метод для установки соединения с физическим устройством
     * @return true, если соединение установлено, false -- иначе
     */
    virtual bool connect() = 0;

    /**
     * Метод для разрыва соединеня с физическим устройством
     */
    virtual void disconnect() = 0;


    /**
     * Метод для чтения одного Input регистра. Рекомендуется использовать его, когда
     * необходимо за раз читать только один регистр по той принчине, что не создается бесполнезного
     * вектора
     * @param reg_num -- номер начального регистра
     * @param reg_count -- количество регистров, которое надо прочитать
     * @param result -- набор 16-битных значений, которые были прочитаны из регистров
     * @return true, если все прошло без ошибок, иначе -- false
     */
    virtual ModbusResult readInputRegister(uint16_t reg_num,
    uint16_t &result,
    uint8_t modbus_id = 1) = 0;

    /**
     * Метод для чтения Input регистров. Можно читать как один, так и несколько регистров
     * @param reg_num -- номер начального регистра
     * @param reg_count -- количество регистров, которое надо прочитать
     * @param result -- набор 16-битных значений, которые были прочитаны из регистров
     * @return true, если все прошло без ошибок, иначе -- false
     */
    virtual ModbusResult readInputRegisters(uint16_t reg_num,
    uint16_t reg_count,
    std::vector<uint16_t> &result,
    uint8_t modbus_id = 1) = 0;

    /**
      * Метод для чтения Holding регистра. Рекомендуется использовать его, когда
      * необходимо за раз читать только один регистр по той принчине, что не создается бесполнезного
      * вектора.
      * @param reg_count -- количество регистров, которое надо прочитать
      * @param result -- набор 16-битных значений, которые были прочитаны из регистров
      * @return true, если все прошло без ошибок, иначе -- false
      */
    virtual ModbusResult readHoldingRegister(uint16_t reg_num,
    uint16_t &result,
    uint8_t modbus_id = 1) = 0;

    /**
      * Метод для чтения Holding регистров. Можно читать как один, так и несколько регистров
      * @param reg_num -- номер начального регистра
      * @param reg_count -- количество регистров, которое надо прочитать
      * @param result -- набор 16-битных значений, которые были прочитаны из регистров
      * @return true, если все прошло без ошибок, иначе -- false
      */
    virtual ModbusResult readHoldingRegisters(uint16_t reg_num,
    uint16_t reg_count,
    std::vector<uint16_t> &result,
    uint8_t modbus_id = 1) = 0;

    /**
     * Метод для записи значения в Holding регистр
     * @param reg_num -- номер регистра
     * @param value -- значение для записи
     * @return true, если все прошло без ошибок, иначе -- false
     */
    virtual ModbusResult writeHoldingRegister(uint16_t reg_num,
    uint16_t value,
    uint8_t modbus_id = 1) = 0;

    /**
     * Метод для записи значенией в Holding регистры (последовательно). За несколько запросов
     * @param reg_num начальный номер регистра
     * @param values вектор значений (будут записаны последовательно в регистры под номерами начиная
     * с первого переданного
     * @return true если запись прошла успешно, false -- иначе
     */
    virtual ModbusResult writeHoldingRegisters(uint16_t reg_num,
    std::vector<uint16_t> values,
    uint8_t modbus_id = 1) = 0;


    virtual ModbusResult saveToEEPROM(uint8_t modbus_id = 1) = 0;
};
}

#endif //MODBUS_LESSON_SRC_CONNECTION_MODBUS_CLIENT_H_
