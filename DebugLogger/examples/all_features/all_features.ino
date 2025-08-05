/************************************************************************** */
/* Этот пример демонстрирует все возможности логгера, включая использование */
/* манипуляторов и различных типов данных.                                  */
/************************************************************************** */

#include <Arduino.h>
#include "DebugLogger.h"

// Включаем отладочный вывод
#define DEBUG 1

// Вызывается один раз при старте
void setup() {
  // Инициализируем логгер
  Debug.begin(115200);

  // Переменные разных типов
  int i = 255;
  unsigned int ui = 65535;
  long l = 123456789L;
  unsigned long ul = 4294967295UL;
  double d = 3.14159;
  char c = 'A';
  String s = "Hello from String object!";

  // Пример 1: Простой вывод разных типов данных
  Debug << "--- Basic types ---" << endl;
  Debug << "Integer: " << i << endl;
  Debug << "Unsigned Int: " << ui << endl;
  Debug << "Long: " << l << endl;
  Debug << "Unsigned Long: " << ul << endl;
  Debug << "Double: " << d << endl;
  Debug << "Char: " << c << endl;
  Debug << "String: " << s << endl;

  // Пример 2: Использование манипуляторов
  Debug << endl << "--- Number formatting ---" << endl;
  Debug << "Decimal (default): " << dec << i << endl;
  Debug << "Hexadecimal: " << hex << i << endl;
  Debug << "Octal: " << oct << i << endl;
  Debug << "Binary: " << bin << i << endl;
  Debug << "Another hex value: " << hex << ui << endl;

  // Последовательный вывод
  Debug << endl << "--- Chained output ---" << endl;
  Debug << "The value of 'i' is " << dec << i << ". In hex it's " << hex << i << "." << endl;

  // Использование в `loop()`
  // Можно вызывать Debug << ... в любом месте кода
}

// Главный цикл
void loop() {
  // Логгирование в цикле
  static unsigned long counter = 0;
  Debug << "Loop counter: " << counter++ << endl;
  delay(1000); // Задержка 1 секунда
}
