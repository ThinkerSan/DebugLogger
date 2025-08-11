#include <Arduino.h>

void setup() {
  Serial.begin(115200);

  int i = 255;
  unsigned int ui = 65535;
  long l = 123456789L;
  unsigned long ul = 4294967295UL;
  double d = 3.14159;
  char c = 'A';
  String s = "Hello from String object!";

  // Пример 1: Простой вывод разных типов данных с помощью оператора <<
  // В примере также демонстрируется использование макроса F() для экономии RAM.
  Serial.println(F("--- 1. Basic types (operator<<) ---"));
  Serial.print("Integer:       ");
  Serial.println(i);
  Serial.print("Unsigned Int:  ");
  Serial.println(ui);
  Serial.print("Long:          ");
  Serial.println(l);
  Serial.print("Unsigned Long: ");
  Serial.println(ul);
  Serial.print("Double:        ");
  Serial.println(d);
  Serial.print("Char:          ");
  Serial.println(c);
  Serial.print("String:        ");
  Serial.println(s);
  Serial.println();

  // Пример 2: Использование манипуляторов
  Serial.println("--- 2. Number formatting ---");
  Serial.print("Dec (default): ");
  Serial.println(i);
  Serial.print("Hex:           0x");
  Serial.println(i, HEX);
  Serial.print("Oct:           ");
  Serial.println(i, OCT);
  Serial.print("Bin:           ");
  Serial.println(i, BIN);
  Serial.print("Another Hex:   0x");
  Serial.println(ui, HEX);
  Serial.println();

  // Пример 3: Последовательный вывод
  Serial.println("--- 3. Chained output ---");
  Serial.print("The value of 'i' is ");
  Serial.print(i);
  Serial.print(". In hex it's 0x");
  Serial.print(i, HEX);
  Serial.println(".");
  Serial.println();

  Serial.println("--- Starting main loop ---");
}

void loop() {
}
