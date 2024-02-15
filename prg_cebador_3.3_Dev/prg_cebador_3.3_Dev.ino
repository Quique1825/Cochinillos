/* El siguiente codigo esta realizado para que encienda un motor durante 5 segundos
   2 veces por dia durante la noche con un intervalo entre cada encndido de 2 hs. Se utiliza 
   para esta accion un micro conntrolador Attiny85.

   Diseño de PCB y programacion del Micro : Sabetta Enrique 
   Comienzo del Proyecto : 11/2022
*/
#define MS_INTERVALO_LED_TEST 300000  //Function LedTest()
#define MS_DESTELLO_LED_TEST 250
#define LED_TEST 13
#define CONFIG_LED_TEST pinMode(LED_TEST, OUTPUT)
#define ACTUALIZAR_LED_TEST(x) digitalWrite(LED_TEST, x)

#define PIN_MOTOR 11
#define CONFIG_PIN_MOTOR pinMode(PIN_MOTOR, OUTPUT)
#define ENCENDER_MOTOR analogWrite(PIN_MOTOR, 200)
#define APAGAR_MOTOR analogWrite(PIN_MOTOR, 0)

#define PIN_BTN_TEST 9
#define MS_INTERVALO_BTN 100
#define CONFIG_PIN_BTN_TEST pinMode(PIN_BTN_TEST, INPUT)
#define LEER_BTN_TEST digitalRead(PIN_BTN_TEST)

#define PIN_LDR A0
#define CONFIG_PIN_LDR pinMode(PIN_LDR, INPUT)
#define LEER_LDR analogRead(PIN_LDR)


#define TPO_ENCENDIDO 5   // tiempo de funcionamiento del motor en segundos.
#define TPO_APAGADO 7200  // tiempo en segundos del motor en estado apagado.
#define TPO_TEST 5        // tiempo de funcionamiento del motor en segundos.


//Variables Globales
int Tiempo_Motor = 0;
int tirada = 0;
unsigned long Millis_apagado_ant = millis();


void setup() {
  CONFIG_LED_TEST;
  CONFIG_PIN_MOTOR;
  CONFIG_PIN_LDR;
  CONFIG_PIN_BTN_TEST;

  ACTUALIZAR_LED_TEST(0);
  APAGAR_MOTOR;
}

void loop() {
  LedTest();
  Leer_LDR();
  Ctrl_Btn_Test();
  Ctrl_Motor();
}


void LedTest() {
  static int ledState = 0;
  static unsigned long antMillis = 0;
  static unsigned long ant_Millis_bl = 0;

  if (millis() - antMillis < MS_INTERVALO_LED_TEST) {
    ant_Millis_bl = millis();
    return;
  }
  ACTUALIZAR_LED_TEST(1);
  if (millis() - ant_Millis_bl < MS_DESTELLO_LED_TEST) return;
  antMillis = millis();
  ACTUALIZAR_LED_TEST(0);
}

void Leer_LDR() {
  static unsigned long millis_ant = 0,

                       if (millis() - millis_ant < 1000) return;
  millis_ant = millis();

  if (LEER_LDR > 600) {
    tirada = 0;
    return;
  }
  if (Tiempo_Motor) {
    Millis_apagado_ant = millis();
    return;
  }

  if (millis() - Millis_apagado_ant < TPO_APAGADO) return;

  if (tirada > 2) return;
  Tiempo_Motor = TPO_ENCENDIDO;
  tirada++;
}

/*void Ctrl_Btn_Test(){
    if(PIN_BTN_TEST) return;
     Tiempo_Motor = TPO_TEST;
 }*/

void Ctrl_Btn_Test() {
  static unsigned long ant_Millis_btn = 0;

  if (PIN_BTN_TEST) return;
  if (millis() - ant_Millis_btn < MS_INTERVALO_BTN) return;
  ant_Millis_btn = millis();
}

void Ctrl_Motor() {
  static unsigned long millis_ant = 0, Tiempo_Motor_ant = 0;

  if (millis() - millis_ant < 1000) return;
  millis_ant = millis();

  //EVENTO ENCENDER MOTOR
  if (Tiempo_Motor && !Tiempo_Motor_ant) ENCENDER_MOTOR;

  //EVENTO APAGAR MOTOR
  if (!Tiempo_Motor && Tiempo_Motor_ant) APAGAR_MOTOR;

  Tiempo_Motor_ant = Tiempo_Motor;

  if (Tiempo_Motor) Tiempo_Motor--;
}
