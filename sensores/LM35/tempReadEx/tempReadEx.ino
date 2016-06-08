/***************************************\
** ROBOCORE ARDUINO KIT INICIANTE **
* *
** Módulo 3 **
\***************************************/
const int LM35 = 0;
float temperatura = 0;
int ADClido = 0;

void setup(){
	Serial.begin(9600);
	analogReference(INTERNAL); //Se estiver usando Arduino Mega, use INTERNAL1V1
	//alteramos a tensão máxima que pode entrar nas portas analógicas do Arduino de 5V para 1,1V
}

void loop(){
	ADClido = analogRead(LM35);
	temperatura = ADClido * 0.1075268817204301;
	Serial.print("Temperatura = ");
	Serial.print(temperatura);
	Serial.println(" *C");
	delay(1000);
}