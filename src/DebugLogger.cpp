/**
 * @file DebugLogger.cpp
 * @brief Реализация методов класса DebugLogger.
 * @details
 * Поддерживает удобный отладочный вывод с перегрузкой оператора <<.
 * Все вызовы обёрнуты в `#if DEBUG`, что позволяет полностью отключить вывод без
 * удаления кода.
 */

#include "DebugLogger.h"

/// @brief Глобальный экземпляр логгера.
DebugLogger Debug;

/// @brief Глобальный манипулятор: перевод строки.
LoggerManipulator endl = LoggerManipulator::_endl;
/// @brief Глобальный манипулятор: шестнадцатеричный формат.
LoggerManipulator hex = LoggerManipulator::_hex;
/// @brief Глобальный манипулятор: десятичный формат.
LoggerManipulator dec = LoggerManipulator::_dec;
/// @brief Глобальный манипулятор: восьмеричный формат.
LoggerManipulator oct = LoggerManipulator::_oct;
/// @brief Глобальный манипулятор: двоичный формат.
LoggerManipulator bin = LoggerManipulator::_bin;

//------------------------------------------------------------------------------
//                          Публичные методы
//------------------------------------------------------------------------------

/**
 * @brief Инициализация последовательного порта.
 * @param speed Скорость порта в бодах (например, 9600).
 */
void DebugLogger::begin(long speed) {
#if DEBUG
  SERIAL_PORT.begin(speed);
  #if defined(USBCON)
    // Эта проверка необходима для плат типа Leonardo, которые используют
    // USB-соединение, и порт не сразу готов к работе.
    while (!SERIAL_PORT) { ; }
  #endif
#endif
}

//------------------------------------------------------------------------------
//                          Перегрузка оператора <<
//------------------------------------------------------------------------------

/**
 * @brief Перегрузка для строковых литералов.
 */
DebugLogger& DebugLogger::operator<<(const char* value) {
#if DEBUG
  SERIAL_PORT.print(value);
#endif
  return *this;
}

/**
 * @brief Перегрузка для символов.
 */
DebugLogger& DebugLogger::operator<<(char value) {
#if DEBUG
  SERIAL_PORT.print(value);
#endif
  return *this;
}

/**
 * @brief Перегрузка для целых чисел.
 *
 * @details
 * После вывода числа, формат вывода сбрасывается к значению по умолчанию (десятичный),
 * чтобы следующее число не было выведено в том же формате (например, шестнадцатеричном).
 */
DebugLogger& DebugLogger::operator<<(int value) {
#if DEBUG
  SERIAL_PORT.print(value, _numberBase);
  _numberBase = DEC; // Сбрасываем формат к значению по умолчанию после вывода
#endif
  return *this;
}

/**
 * @brief Перегрузка для беззнаковых целых чисел.
 */
DebugLogger& DebugLogger::operator<<(unsigned int value) {
#if DEBUG
  SERIAL_PORT.print(value, _numberBase);
  _numberBase = DEC; // Сброс
#endif
  return *this;
}

/**
 * @brief Перегрузка для длинных целых чисел.
 */
DebugLogger& DebugLogger::operator<<(long value) {
#if DEBUG
  SERIAL_PORT.print(value, _numberBase);
  _numberBase = DEC; // Сброс
#endif
  return *this;
}

/**
 * @brief Перегрузка для беззнаковых длинных целых чисел.
 */
DebugLogger& DebugLogger::operator<<(unsigned long value) {
#if DEBUG
  SERIAL_PORT.print(value, _numberBase);
  _numberBase = DEC; // Сброс
#endif
  return *this;
}

/**
 * @brief Перегрузка для чисел с плавающей точкой.
 *
 * @details
 * Для чисел с плавающей точкой форматирование (`hex`, `bin`) не применяется,
 * так как `Serial.print` для `double` всегда выводит в десятичном формате.
 */
DebugLogger& DebugLogger::operator<<(double value) {
#if DEBUG
  SERIAL_PORT.print(value);
#endif
  return *this;
}

/**
 * @brief Перегрузка для объектов `String`.
 */
DebugLogger& DebugLogger::operator<<(const String& value) {
#if DEBUG
  SERIAL_PORT.print(value);
#endif
  return *this;
}

/**
 * @brief Перегрузка для строк, хранящихся во Flash-памяти (с использованием макроса F()).
 */
DebugLogger& DebugLogger::operator<<(const __FlashStringHelper* value) {
#if DEBUG
  SERIAL_PORT.print(value); // Serial.print() имеет перегрузку для __FlashStringHelper*
#endif
  return *this;
}

/**
 * @brief Перегрузка для манипуляторов.
 */
DebugLogger& DebugLogger::operator<<(LoggerManipulator manip) {
#if DEBUG
  switch (manip) {
      case LoggerManipulator::_endl:
        SERIAL_PORT.println();
        break;
      case LoggerManipulator::_hex:
        _numberBase = HEX;
        break;
      case LoggerManipulator::_dec:
        _numberBase = DEC;
        break;
      case LoggerManipulator::_oct:
        _numberBase = OCT;
        break;
      case LoggerManipulator::_bin:
        _numberBase = BIN;
        break;
    }
#endif
  return *this;
}