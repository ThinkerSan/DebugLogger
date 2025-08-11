/**
 * @file DebugLogger.h
 * @brief Заголовочный файл отладочного логгера с использованием оператора `<<`
 * @details
 * Предоставляет класс DebugLogger, предназначенный для вывода отладочной
 * информации в последовательный порт в интуитивной форме с использованием
 * оператора `<<`. Поддерживаются манипуляторы для форматирования чисел.
 * Совместим с Arduino и платформами с ограниченными ресурсами.
 */

#ifndef DEBUG_LOGGER_H
#define DEBUG_LOGGER_H

#include <Arduino.h>

// ======================== ПОЛЬЗОВАТЕЛЬСКИЕ НАСТРОЙКИ ========================
// Включение(1)/Выключение(0) поддержки платы Leonardo в симуляторе Proteus.
// Используется Serial1 вместо Serial.
#define LEONARDO_IN_PROTEUS 0
// ============================================================================

/**
 * @def DEBUG
 * @brief Макрос для включения/выключения отладочного вывода.
 *
 * Если DEBUG равен 1, отладочный вывод будет компилироваться и работать.
 * Если DEBUG равен 0 (или не определен), весь код внутри #if DEBUG будет
 * проигнорирован компилятором, что позволяет полностью отключить вывод без
 * удаления кода. По умолчанию установлен в 0, если не определен.
 */
#ifndef DEBUG
  #define DEBUG 0
#endif

#if LEONARDO_IN_PROTEUS
  #define SERIAL_PORT Serial1
#else
  #define SERIAL_PORT Serial
#endif

// Макрос для определения поддержки printf
#if defined(ESP8266) || defined(ESP32)
  #define PRINTF_HAS_ESP 1 // Поддержка printf для платформы ESP8266/ESP32
#elif defined(MCUDUDE_MINICORE) || defined(MCUDUDE_MIGHTYCORE) || defined(MCUDUDE_MEGACORE) || defined(MCUDUDE_MEGACOREX) || defined(MCUDUDE_MAJORCORE)
  #define PRINTF_HAS_MCUDUDE 1 // Поддержка printf для ядер MCUdude
  #define Debug_printf(...)  SERIAL_PORT.printf(__VA_ARGS__)
#else
  #define PRINTF_HAS_ESP     0
  #define PRINTF_HAS_MCUDUDE 0
  #define Debug_printf(...)  ((void)0)
#endif

/******************************************************************************
 * @enum LoggerManipulator
 * @brief Манипуляторы форматирования для логгера.
 */
enum class LoggerManipulator
{
  _endl, ///< Перевод строки.
  _hex,  ///< Шестнадцатеричный формат.
  _dec,  ///< Десятичный формат (по умолчанию).
  _oct,  ///< Восьмеричный формат.
  _bin   ///< Двоичный формат.
};

/******************************************************************************
 * @class DebugLogger
 * @brief Класс отладочного логгера с перегрузкой оператора вывода.
 * @details
 * Позволяет использовать синтаксис вида: `Debug << "value: " << val << endl;`
 * Поддерживаются числовые и строковые типы, а также манипуляторы вывода.
 */
class DebugLogger
{
 public:
  /**
   * @brief Инициализация последовательного порта.
   * @param speed Скорость порта в бодах (например, 9600).
   * @note Эту функцию необходимо вызвать в `setup()`, если `DEBUG` включен.
   */
  void begin(long speed);

  // --- Перегрузка оператора << для различных типов данных ---

  /**
   * @brief Перегрузка для строковых литералов.
   * @param value Указатель на строку в стиле C.
   * @return Ссылка на текущий объект для цепочки вызовов.
   */
  DebugLogger& operator<<(const char* value);
  /**
   * @brief Перегрузка для символов.
   * @param value Символ.
   * @return Ссылка на текущий объект.
   */
  DebugLogger& operator<<(char value);
  /**
   * @brief Перегрузка для целых чисел.
   * @param value Целое число.
   * @return Ссылка на текущий объект.
   */
  DebugLogger& operator<<(int value);
  /**
   * @brief Перегрузка для беззнаковых целых чисел.
   * @param value Беззнаковое целое число.
   * @return Ссылка на текущий объект.
   */
  DebugLogger& operator<<(unsigned int value);
  /**
   * @brief Перегрузка для длинных целых чисел.
   * @param value Длинное целое число.
   * @return Ссылка на текущий объект.
   */
  DebugLogger& operator<<(long value);
  /**
   * @brief Перегрузка для беззнаковых длинных целых чисел.
   * @param value Беззнаковое длинное целое число.
   * @return Ссылка на текущий объект.
   */
  DebugLogger& operator<<(unsigned long value);
  /**
   * @brief Перегрузка для чисел с плавающей точкой.
   * @param value Число `double`.
   * @return Ссылка на текущий объект.
   * @note Форматирование (`hex`, `bin` и т.д.) не применяется к числам с плавающей точкой.
   */
  DebugLogger& operator<<(double value);
  /**
   * @brief Перегрузка для объектов класса `String`.
   * @param value Объект `String`.
   * @return Ссылка на текущий объект.
   */
  DebugLogger& operator<<(const String& value);

  /**
   * @brief Перегрузка для строк, хранящихся во Flash-памяти (с использованием макроса F()).
   * @param value Указатель на строку во Flash-памяти.
   * @return Ссылка на текущий объект.
   */
  DebugLogger& operator<<(const __FlashStringHelper* value);

  /**
   * @brief Перегрузка для приема манипуляторов.
   * @param manip Объект-манипулятор из `LoggerManipulator`.
   * @return Ссылка на текущий объект.
   */
  DebugLogger& operator<<(LoggerManipulator manip);

// РЕАЛИЗАЦИЯ PRINTF
#if PRINTF_HAS_ESP
  /**
   * @brief Форматированный вывод в стиле printf. Является легковесной "обёрткой"
   * над нативной функцией Serial.printf().
   * @details Использует шаблоны C++ для прямой передачи аргументов без
   * промежуточных буферов и лишних затрат памяти.
   * @tparam Args Типы передаваемых аргументов.
   * @param format Форматная строка (в RAM или Flash).
   * @param args Аргументы для форматирования.
   */
  template <typename... Args>
  void printf(const char* format, Args... args)
  {
  #if DEBUG
    SERIAL_PORT.printf(format, args...);
  #endif
  }

  template <typename... Args>
  void printf(const __FlashStringHelper* format, Args... args)
  {
  #if DEBUG
    SERIAL_PORT.printf_P((PGM_P)format, args...);
  #endif
  }
#elif PRINTF_HAS_MCUDUDE
  template <typename... Args>
  void printf(const char* format, Args... args)
  {
  #if DEBUG
    Debug_printf(format, args...);
  #endif
  }
  template <typename... Args>
  void printf(const __FlashStringHelper* format, Args... args)
  {
  #if DEBUG
    Debug_printf(format, args...);
  #endif
  }
#else
  // ЗАГЛУШКА для НЕПОДДЕРЖИВАЕМЫХ платформ
  /**
   * @brief Заглушка для printf на неподдерживаемых платформах.
   * @details Эта функция ничего не делает и существует для того, чтобы код,
   * использующий Debug.printf(), компилировался без ошибок.
   * Компилятор полностью удалит этот вызов при оптимизации.
   */
  template <typename... Args>
  void printf(const char* format, Args... args)
  {
    // Подавляем предупреждения компилятора о неиспользуемых переменных.
    (void)format;
    (void)sizeof...(args);
  }

  template <typename... Args>
  void printf(const __FlashStringHelper* format, Args... args)
  {
    (void)format;
    (void)sizeof...(args);
  }
#endif

 private:
  // Внутренняя переменная для хранения формата числа (DEC, HEX и т.д.).
  // По умолчанию используется десятичный формат.
  int _numberBase = DEC;
};

// --- Объявление глобальных объектов-манипуляторов ---
// Они делают синтаксис использования очень удобным.
// Например, вместо Debug.operator<<(LoggerManipulator::_endl)
// мы можем писать просто Debug << endl;

extern LoggerManipulator endl;
extern LoggerManipulator hex;
extern LoggerManipulator dec;
extern LoggerManipulator oct;
extern LoggerManipulator bin;

// Глобальный экземпляр логгера, доступный во всем проекте.
extern DebugLogger Debug;

#endif // DEBUG_LOGGER_H