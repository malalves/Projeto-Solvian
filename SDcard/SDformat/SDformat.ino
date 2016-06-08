#include <SD.h>
#include <SPI.h>
/*para o uno
  ** MOSI - pin 11
 ** MISO - pin 12
 ** CLK - pin 13
 */
int sd_cs = 10;

char* nomes[]={"dados/a","dados/b"};
int numArq = 2;

File root = SD.open("/");//abre o diretório raiz

void setup(){
	Serial.begin(9600);

	if (!SD.begin(sd_cs)) {
    		Serial.println("Card failed, or not present");
			return;
		}
	Serial.println("card initialized.");//inicialização do sd

	clearSD(root);

	root = SD.close();

	formatSD();
}

void clearSD(File dir){
	File entry = dir.openNextFile();
	string nome;
	while(entry){
		nome = entry.name();
		entry = dir.openNextFile();
		remove(nome);
	}
}//remove todos os arquivos; abre os diretórios a partir da raiz copia o nome e exclui depois de abrir outro

void formatSD(){
	for(int i = 0; i<numArq; i++){
		if(!SD.exist(nome[i])){
			SD.open(nome[i]);
			SD.close(nome[i]);
		}
	}
}//cria os arquivos necessários

void loop(){
	//não faz nada
}
