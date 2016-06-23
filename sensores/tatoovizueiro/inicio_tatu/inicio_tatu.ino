#include <TimerOne.h>

int medir=0, periodos=2,val,contagem;

int pin_tatu = 24;
int pin_led = 22;
 
void setup()
{
  pinMode(pin_tatu,INPUT);//pino do sensor
  pinMode(pin_led,OUTPUT);//pino do led
  Timer1.initialize(30000000); //configura a interrupção para acontecer a cada 30 segundos
  Timer1.attachInterrupt( timerIsr );  //adiciona a interrupção do timer1
  Serial.begin(9600);
}

void loop()
{
  if(medir==1)
  {
    //VÊ a porta e pá
    Serial.print("OLAR \n");
    val=digitalRead(pin_tatu);
    if(val!=0)
    {
      contagem=0;
      digitalWrite(pin_led,HIGH);
    }
    else
    {
      contagem++;
    }
    if(contagem>=periodos)
    {
      //ação de desligar e pá
      digitalWrite(pin_led,LOW);
    }
    medir=0;
  }
}

void timerIsr()  //sub-rotina de interrupção do timer 1 para sinalizar que uma medida de temperatura e umidade deve ser feita
{
  medir=1;  //coloca o valor 1 na variavel medir, o que indica que deve ser feita uma medida de temperatura e umidade
}
