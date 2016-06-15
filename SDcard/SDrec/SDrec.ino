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

class Recorder{
	private:
		const int numArq = 2;
		static char *nomes[];
		File dataWrite;
		File dataRead;
		Vector<int> archiveStatus;
		String data;//teste

		void dataTreat(){

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
		}//construtor para ser chamado no setup cria e inicializa o Recorder
		
		void rawDataGet(){
			Serial.println("digite um dado");
			while(!Serial.available()){
				;
			}
			data = Serial.readString();//teste
			//dataTreat(); no momento é desnecessauro
		}//coleta os dados dos sensores
		
		void data_sd_record(){
      int err;
			err = dataWrite.print(data);
        	Serial.println(data);
        	Serial.println("recorded");
          Serial.println(data);
     		String tNom = dataWrite.name();
      		dataWrite.flush();
		}//grava os dados no cartão sd

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
		}
		
		void dataClear(){
			File aux;
			for(int i = 0; i<numArq; i++){
				SD.remove(nomes[i]);
				aux = SD.open(nomes[i]);
				aux.close();
			}
		}//limpa os dados gravados no cartão sd
		
		bool setFileR(int num){
			if (archiveStatus[num]) return 1;

			dataRead.close();
			dataRead = SD.open(nomes[num],FILE_READ);
			return 0;
		}//seleciona o arquivo de leitura

		bool setFileW(int num){
			if (archiveStatus[num]) return 1;

			dataWrite.close();
			dataWrite = SD.open(nomes[num],FILE_WRITE);
			return 0;
		}//seleciona o arquivo de escrita

		void closeR(){
			dataRead.close();
		}

		void closeW(){
			dataWrite.close();
		}
};//classe que grava no SD

char* Recorder::nomes[]={"dados/a","dados/b"};
Recorder rec;

void setup(){
	Serial.begin(9600);
	rec.init();
	Serial.println("ok");
	err = rec.setFileW(0);
	if(err){
		rec.closeR();
		rec.setFileW(0);
	}
	rec.rawDataGet();
	rec.data_sd_record();
	rec.closeW();
}

void loop(){
	//rec.dataClear();
	/*err = rec.setFileR(0);
	if(err){
		rec.closeW();
		rec.setFileR(0);
	}
	rec.data_sd_read();*/
}
