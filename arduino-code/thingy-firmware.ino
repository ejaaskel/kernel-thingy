#include <Wire.h>

#define STRCOUNT 8
#define MAXSTRLEN 16

char arr[STRCOUNT][MAXSTRLEN] = {"lorem", 
                   "ipsum", "dolor", "sit",
                   "amet", "consectetur",
                   "adipiscing", "elit"};
 
void I2C_TxHandler(void)
{
    char *str = arr[random(0, STRCOUNT)];
    Wire.write(str);
}
 
void setup() {
    randomSeed(analogRead(0));
    Wire.begin(0x55);
    Wire.onRequest(I2C_TxHandler);
}
 
void loop() {
    delay(100);
}
