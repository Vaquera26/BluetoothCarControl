#include <SoftwareSerial.h>

// CONEXIONES PARA EL BLUETOOTH
int bluetoothTx = 2;
int bluetoothRx = 3;

SoftwareSerial bluetooth(bluetoothTx, bluetoothRx);

// MOTOR DERECHO (Puente H)
int Motor1A = 5;
int Motor1B = 6;
int pwmP1 = 11;

// MOTOR IZQUIERDO (Puente H)
int Motor2A = 9;
int Motor2B = 10;
int pwmP2 = 12;

// Variables para almacenar la velocidad (0 a 255)
int velocidadI = 0; // Velocidad inicial izquierda
int velocidadD = 0; // Velocidad inicial derecha

void setup() {
  // Inicializar Bluetooth a 9600 baudios
  bluetooth.begin(9600);

  // Configurar pines de los motores como salida
  pinMode(Motor1A, OUTPUT);
  pinMode(Motor1B, OUTPUT);
  pinMode(Motor2A, OUTPUT);
  pinMode(Motor2B, OUTPUT);
  pinMode(pwmP1, OUTPUT);
  pinMode(pwmP2, OUTPUT);

  // Inicializar motores apagados
  detener();

  Serial.begin(9600);  // Para depuración
}

// Variables para los modos de dirección
int modoD, modoI;

void loop() {
  // Verificar si hay datos disponibles en el Bluetooth
  if (bluetooth.available()) {
    String values = bluetooth.readStringUntil('\n');
    sscanf(values.c_str(), "%d %d %d %d", &modoD, &velocidadD, &modoI, &velocidadI);
    Serial.println(values);
    Serial.println(modoI);

    // Control del motor derecho
    if (modoD == 1) {
      derechaSentido1();
    } else {
      derechaSentido2();
    }

    // Control del motor izquierdo
    if (modoI == 1) {
      izquierdaSentido1();
    } else {
      izquierdaSentido2();
    }
  }
}

void derechaSentido1() {
  digitalWrite(Motor1A, LOW);
  digitalWrite(Motor1B, HIGH);
  analogWrite(pwmP1, velocidadD);
}

void derechaSentido2() {
  digitalWrite(Motor1A, HIGH);
  digitalWrite(Motor1B, LOW);
  analogWrite(pwmP1, velocidadD);
}

void izquierdaSentido1() {
  digitalWrite(Motor2A, LOW);
  digitalWrite(Motor2B, HIGH);
  analogWrite(pwmP2, velocidadI);
}

void izquierdaSentido2() {
  digitalWrite(Motor2A, HIGH);
  digitalWrite(Motor2B, LOW);
  analogWrite(pwmP2, velocidadI);
}

void detener() {
  digitalWrite(Motor1A, LOW);
  digitalWrite(Motor1B, LOW);
  digitalWrite(Motor2A, LOW);
  digitalWrite(Motor2B, LOW);
  analogWrite(pwmP1, 0);
  analogWrite(pwmP2, 0);
}