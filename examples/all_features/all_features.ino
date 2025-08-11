/************************************************************************** */
/* Этот пример демонстрирует все возможности логгера, включая использование */
/* манипуляторов, различных типов данных и функции printf.                 */
/************************************************************************** */

#include <Arduino.h>
#include "DebugLogger.h"

// Вызывается один раз при старте
void setup() {
  // Инициализируем логгер со скоростью 115200 бод
  Debug.begin(115200);

  // Переменные разных типов
  int i = 255;
  unsigned int ui = 65535;
  long l = 123456789L;
  unsigned long ul = 4294967295UL;
  double d = 3.14159;
  char c = 'A';
  String s = "Hello from String object!";

  // Пример 1: Простой вывод разных типов данных с помощью оператора <<
  // В примере также демонстрируется использование макроса F() для экономии RAM.
  Debug << F("--- 1. Basic types (operator<<) ---") << endl;
  Debug << "Integer:       " << i << endl;
  Debug << "Unsigned Int:  " << ui << endl;
  Debug << "Long:          " << l << endl;
  Debug << "Unsigned Long: " << ul << endl;
  Debug << "Double:        " << d << endl;
  Debug << "Char:          " << c << endl;
  Debug << "String:        " << s << endl
        << endl;

  // Пример 2: Использование манипуляторов
  Debug << "--- 2. Number formatting ---" << endl;
  Debug << "Dec (default): " << dec << i << endl;
  Debug << "Hex:           0x" << hex << i << endl;
  Debug << "Oct:           " << oct << i << endl;
  Debug << "Bin:           " << bin << i << endl;
  Debug << "Another Hex:   0x" << hex << ui << endl
        << endl;

  // Пример 3: Последовательный вывод
  Debug << "--- 3. Chained output ---" << endl;
  Debug << "The value of 'i' is " << dec << i << ". In hex it's 0x" << hex << i << "." << endl
        << endl;

  // Пример 4: Использование printf (на поддерживаемых платформах)
  // Этот код скомпилируется и будет работать только на платформах,
  // поддерживаемых printf, например, ESP32, ESP8266 или ядрах MCUdude.
  // На других платформах вызов будет просто проигнорирован
  Debug << "--- 4. Printf formatting (if supported) ---" << endl;
  // Вывод нескольких значений за один вызов. Так же показано использование макроса F()
  Debug.printf(F("A single call to print multiple values:\n"));
  Debug.printf("  - Integer:\t %d\n  - Hexadecimal: 0x%X\n  - String:\t %s\n", i, i, s.c_str());

// Можно проверить, есть ли поддержка printf через определения в библиотеке.
#if (!PRINTF_HAS_ESP) && (!PRINTF_HAS_MCUDUDE)
  Debug << "`Printf` is not supported on this platform." << endl
        << endl;
#endif

  Debug << "--- Starting main loop ---" << endl;
}

// Главный цикл
void loop() {
  static unsigned long loopcounter = 0;

// Используем printf для более компактного вывода в цикле
#if PRINTF_HAS_ESP || PRINTF_HAS_MCUDUDE
  Debug.printf("Loop counter: %lu\n", loopcounter++);
#else
  Debug << "Loop counter: " << loopcounter++ << endl;
#endif

  delay(1000);
}
