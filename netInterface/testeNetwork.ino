#include <SoftwareSerial.h>

SoftwareSerial netSerial(2,3);

void setup()
{
  netSerial.begin(19200);
  Serial.begin(19200);
}

void loop()
{
  if (netSerial.available())
    Serial.write(netSerial.read());
  if (Serial.available())
    netSerial.write(Serial.read());
}

/*
sequencia para configurar um modem gprs
AT - => AT

<= AT * This should come back. SIM900 default is to echo back commands you enter *

<= OK * This string should tell you all is well*

=>AT+CPIN? *This is to check if SIM is unlocked. This sample assumes unlocked SIMs*

<= +CPIN: READY * If your response contains this, then it means SIM is unlocked and ready*

=>AT+CREG? *This checks if SIM is registered or not*

<=+CREG: 0,1 *This string in the response indicates SIM is registered*

=>AT+CGATT? *Check if GPRS is attached or not*

<=+CGATT: 1 *A response containing this string indicates GPRS is attached*

=>AT+CIPSHUT *Reset the IP session if any*

<=SHUT OK *This string in the response represents all IP sessions shutdown.*

=>AT+CIPSTATUS *Check if the IP stack is initialized*

<=STATE: IP INITIAL *This string in the response indicates IP stack is initialized*

=>AT+CIPMUX=0 *To keep things simple, I’m setting up a single connection mode*

<=OK *This string indicates single connection mode set successfully at SIM 900*

=>AT+CSTT= “APN”, “UNAME”, “PWD” *Start the task, based on the SIM card you are using, you need to know the APN, username and password for your service provider*

<= OK *This response indicates task started successfully*

=> AT+CIICR *Now bring up the wireless. Please note, the response to this might take some time*

<=OK *This text in response string indicates wireless is up*

=>AT+CIFSR *Get the local IP address. Some people say that this step is not required, but if I do not issue this, it was not working for my case. So I made this mandatory, no harm.*

<= xxx.xxx.xxx.xxx *If previous command is successful, you should see an IP address in the response*

=>AT+CIPSTART= “TCP” , “www.vishnusharma.com”, “80” *Start the connection, TCP, domain name, port*

<= CONNECT OK *This string in the response indicates TCP connection established*

=>AT+CIPSEND *Request initiation of data sending (the request)*

<= > *The response should be the string “>” to indicate, type your data to send*

=> xxxxxx *Just type anything for now*

=>#026 *Now type the sequence #026. This tells the terminal.exe to send the hex code 0x1a (which is Ctrl+Z) to indicate end of data sending*

<= xxxxxxxxxx *You should get some response back from the server…it would generally be a complain that the request string was not valid…but that is a different subject…you have established the connection*

*To close the connection*

=>AT+CIPSHUT *Request shutting down of the current connections*

<=SHUT OK *Indicates shutdown successful
*/