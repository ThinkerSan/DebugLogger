#include <Arduino.h>
#include "DebugLogger.h"

void setup() {
  Debug.begin(115200);

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
  Debug << "The value of 'i' is " << i << ". In hex it's 0x" << hex << i << "." << endl
        << endl;

  Debug << "--- Starting main loop ---" << endl;
}

void loop() {
}
