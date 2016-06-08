#include <SPI.h>
#include <SD.h>

/*para o uno
  ** MOSI - pin 11
 ** MISO - pin 12
 ** CLK - pin 13
 */
const int sd_cs = 10;

const int numArq = 2;
const char *nomes[] = {"dados/a","dados/b"};

class recorder{
	private:
    File dataWrite;
		File dataRead;
 		String data;//teste

		void dataTreat(){

		}//trata os dados brutos obtidos dos sensores para obter os valores que serão guardados no cartão sd

	public:
		recorder(){
			if (!SD.begin(sd_cs)) {
    			Serial.println("Card failed, or not present");
				return;
			}
			Serial.println("card initialized.");//inicialização do sd
		}//construtor para ser chamado no setup cria e inicializa o recorder

		void rawDataGet(){
			while(!Serial.available()){
				;
			}
			data = Serial.readString();//teste
			//dataTreat(); no momento é desnecessauro
		}//coleta os dados dos sensores

		void data_sd_record(){
			dataWrite.print(data);
		}//grava os dados no cartão sd

		void data_sd_read(){
			dataRead.seek(0);
			String temp = dataRead.readString();
			Serial.print(temp);
			Serial.println("fim do arquivo");
		}

		void dataClear(){
			File aux;
			for(int i = 0; i<numArq; i++){
				SD.remove(nomes[i]);
				aux = SD.open(nomes[i]);
				aux.close();
			}
		}//limpa os dados gravados no cartão sd

		void setFileR(int num){
			dataRead.close();
			dataRead = SD.open(nomes[num],FILE_READ);
		}//seleciona o arquivo de leitura

		void setFileW(int num){
			dataWrite.close();
			dataWrite = SD.open(nomes[num],FILE_WRITE);
		}//seleciona o arquivo de escrita

};//classe que grava no SD

recorder rec;

void setup(){
	Serial.begin(9600);
}

void loop(){
  rec.dataClear();
	rec.setFileW(0);
	rec.setFileR(0);
	Serial.println("digite um dado");
	rec.rawDataGet();
	rec.data_sd_record();
	rec.data_sd_read();
	rec.setFileW(1);
	rec.setFileR(1);
	Serial.println("digite um dado");
	rec.rawDataGet();
	rec.data_sd_record();
	Serial.println("digite um dado");
	rec.rawDataGet();
	rec.data_sd_record();
	rec.data_sd_read();
	rec.data_sd_read();
	rec.dataClear();
	rec.data_sd_read();
}
