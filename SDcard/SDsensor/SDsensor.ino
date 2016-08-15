#include <SPI.h>
#include <SD.h>
#include <Vector.h>

/*para o uno
  ** MOSI - pin 11
 ** MISO - pin 12
 ** CLK - pin 13
 */
const int sd_cs = 10;
bool err;
const int LM35 = 0;//pino analogico em que o sensor está ligado
int pin_tatu = 7;//pino do tatuvizueiro
int counter=0;//só pra verificar a ordem das gravações


class Recorder{
	private:
		const int numArq = 2;
		static char *nomes[];
		File dataWrite;
		File dataRead;
		Vector<int> archiveStatus;//marca qual arquivo está sendo usado(1-leitura,2-escrita)
		float data;
		int ADClido = 0;
		bool presence = 0;

		void dataTreat(){
			data = ADClido*0.1075268817204301;//converte a leitura analogica 0-255 em temperatura celcius
			if(presence){
				bool eror;
				err = setFileW(1);
				if(eror){
					closeR();
					setFileW(1);
				}
			}
			else{
				bool eror;
				err = setFileW(0);
				if(eror){
					closeR();
					setFileW(0);
				}
			}//seleciona o arquivo de escrita dependendo da presença ou não de pessoas
		}//trata os dados brutos obtidos dos sensores para obter os valores que serão guardados no cartão sd

	public: 
		void init(){
			if (!SD.begin(sd_cs)) {
	   			Serial.println("Card failed, or not present");
				return;
			}
			Serial.println("card initialized.");//inicialização do sd
			for(int i=0; i<numArq; i++){
				archiveStatus.push_back(0);
			}
		}//inicializador para ser chamado no setup cria e inicializa o Recorder
		
		void rawDataGet(){
			ADClido = analogRead(LM35);//lê a temperatura
			presence=digitalRead(pin_tatu);//verifica a presença de pessoas
			dataTreat();
		}//coleta os dados dos sensores
		
		void data_sd_record(){
			if(!dataWrite)Serial.println("cade o meu arquivo?");
			dataWrite.print(counter);
			dataWrite.print(" - ");
			dataWrite.println(data);
			Serial.println("recorded");
			Serial.print("Temperatura:");
        	Serial.print(data);
        	Serial.print("graus celsius\nPresenca:");
        	Serial.println(presence);
      		dataWrite.flush();
		}//grava os dados no arquivo selecionado

		void data_sd_read(){
			dataRead.seek(0);
      		String temp = dataRead.readString();
      		Serial.println("ok");
	      	while(temp != NULL){
       			Serial.println(temp);
  				temp = dataRead.readString();
        		Serial.println("read");
			}
			Serial.println("fim do arquivo");
		}//le os dados do arquivo selecionado

		void clearFile(int num){
			File aux;
			SD.remove(nomes[num]);//exclui o arquivo
			aux = SD.open(nomes[num]);//recria o arquivo, mas em branco
			aux.close();
		}//deleta o arquivo num
		
		void dataClear(){
			File aux;
			for(int i = 0; i<numArq; i++){
				SD.remove(nomes[i]);//exclui o arquivo
				aux = SD.open(nomes[i]);//recria o arquivo, mas em branco
				aux.close();
			}
		}//limpa os dados gravados no cartão sd
		
		bool setFileR(int num){
			if (archiveStatus[num]) return 1;

			dataRead.close();
			dataRead = SD.open(nomes[num],FILE_READ);
			for(int i=0;i<numArq;i++){
				if(archiveStatus[i] == 1)archiveStatus[i] = 0;
			}
			archiveStatus[num] = 1;
			return 0;
		}//seleciona o arquivo de leitura

		bool setFileW(int num){
			if (archiveStatus[num]) return 1;

			dataWrite.close();
			dataWrite = SD.open(nomes[num],FILE_WRITE);
			for(int i=0;i<numArq;i++){
				if(archiveStatus[i] == 2)archiveStatus[i] = 0;
			}
			archiveStatus[num] = 2;
			return 0;
		}//seleciona o arquivo de escrita

		void closeR(){
			dataRead.close();
			for(int i=0;i<numArq;i++){
				if(archiveStatus[i] == 1)archiveStatus[i] = 0;
			}
		}//fecha o arquivo de leitura

		void closeW(){
			dataWrite.close();
			for(int i=0;i<numArq;i++){
				if(archiveStatus[i] == 2)archiveStatus[i] = 0;
			}
		}//fecha o arquivo de escrita
};//classe que grava no SD

char* Recorder::nomes[]={"dados/taVazio.txt","dados/temGente.txt"};
Recorder rec;


/*
nesse teste vou coletar informações do sensor de temperatura e do sensor de presença
*/


void setup(){
	Serial.begin(9600);
	rec.init();
	analogReference(INTERNAL); //Se estiver usando Arduino Mega, use INTERNAL1V1
	//alteramos a tensão máxima que pode entrar nas portas analógicas do Arduino de 5V para 1,1V
}

void loop(){
	rec.rawDataGet();
	rec.data_sd_record();
	counter ++;
	delay(10000);
}
