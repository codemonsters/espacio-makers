#include <Wire.h>

const int ledExternoPin = 3; // LED externo conectado al pin D3 (con su resistencia a GND)
bool estadoLed = false;      // Estado actual del LED (falso = apagado)

void setup() {
  pinMode(ledExternoPin, OUTPUT);
  digitalWrite(ledExternoPin, LOW); // Asegura que el LED empiece apagado

  Wire.begin(8);                 // Iniciar I2C como Slave usando la dirección 8
  Wire.onReceive(receiveEvent);  // Configura la función que reacciona a los datos del Master
}

void loop() {
  // El loop se queda libre. El cambio del LED se gestiona por interrupción en receiveEvent
  delay(1000);
}

// Esta función se ejecuta automáticamente en segundo plano cuando el Master envía datos
void receiveEvent(int howMany) {
  while (Wire.available()) {
    char dato = Wire.read(); // Lee el carácter enviado ('1')
    
    if (dato == '1') {
      estadoLed = !estadoLed; // Si está apagado lo enciende / Si está encendido lo apaga
      digitalWrite(ledExternoPin, estadoLed); // Aplica el cambio al pin físico
    }
  }
}
