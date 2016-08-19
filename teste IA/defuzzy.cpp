#include <iostream>
#include <cmath>
#include <cstring>

#define mtoFrio 0
#define frio 15
#define bom 25
#define quente 35
#define mtoQuente 50
//definições básicas de temperaturas

#define Tmin 0
#define Tmax 50
//temperaturas máxima e minima de operação

int Smax=30;
int Smin=17;
//range do sistema de ar condicionado(o que ele pode mandar)

double dfuzzy[] = {10,5,0,-5,-10};
//regra para defuzzyficação define as ações de acordo com o conjunto fuzzy ao qual o ponto pertence
double var = 0;
//indica a variação do inserido para o padrão


using namespace std;

int get_temp(){
	int tmp;
	cin >> tmp;
	return tmp;
}//recebe valor de temperatura inserido pelo usuário

int generateOut(double fuzzyValues[5]){
	double partial = 0;
	int final;
	for(int i=0; i<5; i++){
		partial += dfuzzy[i]*fuzzyValues[i];
	}
	final = bom - var + partial;
	return final;
}//realiza a defuzzyficação dos valores gerando uma saida de temperatura

class CFuzzyFunction{
	protected :
		double dLeft, dRight;
		char   cType;
		char*  sName;

	public:
		CFuzzyFunction(){};
		
		virtual ~CFuzzyFunction(){
			delete [] sName;
			sName=NULL;
		}

		virtual void setInterval(double l,double r){
			dLeft=l; dRight=r;
		}

		virtual void setMiddle( double dL=0,double dR=0)=0;

		virtual void setType(char c){
			cType=c;
		}

		virtual void setName(const char* s){ 
		  sName = new char[strlen(s)+1];
		  strcpy(sName,s);
		}

		bool isDotInInterval(double t){
			if((t>=dLeft)&&(t<=dRight)) return true; else return false;
		}

		char getType(void)const{ return cType;}

		void getName() const{
			cout<<sName<<endl;
		}

		virtual double getValue(double t)=0;
};//classe de funções fuzzy generica

class CTriangle : public CFuzzyFunction{
	private: 
		double dMiddle;

	public:
		void setMiddle(double dL, double dR){
			dMiddle=dL;
		}

		double getValue(double t){
			if(t<=dLeft)
				return 0;
			else if(t<dMiddle)
				return (t-dLeft)/(dMiddle-dLeft);
			else if(t==dMiddle)
				return 1.0;
			else if(t<dRight)
				return (dRight-t)/(dRight-dMiddle);
			else
				return 0;
		}
};//classe derivada de funções fuzzy triangulares

class CTrapezoid : public CFuzzyFunction{
	private:
		double dLeftMiddle, dRightMiddle;

	public:
		void setMiddle(double dL, double dR){
			dLeftMiddle=dL;
			dRightMiddle=dR;
		}

		double getValue(double t){
			if(t<=dLeft)
				return 0;
			else if(t<dLeftMiddle)
				return (t-dLeft)/(dLeftMiddle-dLeft);
			else if(t<=dRightMiddle)
				return 1.0;
			else if(t<dRight)
				return (dRight-t)/(dRight-dRightMiddle);
			else 
				return 0;
		}   
};//classe derivada de funções fuzzy trapezoidais

void fuzzInit(CFuzzyFunction** FuzzySet){
	FuzzySet[0] = new CTriangle;
	FuzzySet[1] = new CTriangle;
	FuzzySet[2] = new CTriangle;
	FuzzySet[3] = new CTriangle;
	FuzzySet[4] = new CTriangle;

	FuzzySet[0]->setInterval(mtoFrio,frio);
	FuzzySet[0]->setMiddle(mtoFrio,mtoFrio);
	FuzzySet[0]->setType('t');
	FuzzySet[0]->setName("mtoFrio");

	FuzzySet[1]->setInterval(mtoFrio,bom);
	FuzzySet[1]->setMiddle(frio,frio);
	FuzzySet[1]->setType('t');
	FuzzySet[1]->setName("frio");

	FuzzySet[2]->setInterval(frio,quente);
	FuzzySet[2]->setMiddle(bom,bom);
	FuzzySet[2]->setType('t');
	FuzzySet[2]->setName("bom");

	FuzzySet[3]->setInterval(bom,mtoQuente);
	FuzzySet[3]->setMiddle(quente,quente);
	FuzzySet[3]->setType('t');
	FuzzySet[3]->setName("quente");

	FuzzySet[4]->setInterval(quente,mtoQuente);
	FuzzySet[4]->setMiddle(mtoQuente,mtoQuente);
	FuzzySet[4]->setType('t');
	FuzzySet[4]->setName("mtoQuente");
}//inicializa os conjuntos fuzzy com os valores predefinidos das temperaturas

void moveFuzz(CFuzzyFunction** FuzzySet){
	FuzzySet[0]->setMiddle(mtoFrio - var,mtoFrio - var);
	FuzzySet[1]->setMiddle(frio - var,frio - var);
	FuzzySet[2]->setMiddle(bom - var,bom - var);
	FuzzySet[3]->setMiddle(quente - var,quente - var);
	FuzzySet[4]->setMiddle(mtoQuente - var,mtoQuente - var);

	FuzzySet[0]->setInterval(mtoFrio-var,frio-var);
	FuzzySet[1]->setInterval(mtoFrio-var,bom-var);
	FuzzySet[2]->setInterval(frio-var,quente-var);
	FuzzySet[3]->setInterval(bom-var,mtoQuente-var);
	FuzzySet[4]->setInterval(quente-var,mtoQuente-var);
}//move os conjuntos fuzzy de acordo com a temperatura desejada

int main(){
	CFuzzyFunction *FuzzySet[5];
	fuzzInit(FuzzySet);
	//cria e inicializa os conjuntos fuzzy
	
	double tValue;
	//valor de temperatura a ser medido

	do{	
		char menu = 0;
		//variavel auxiliar para operar o menu
		double fuzzyValues[5];
		//variavel que registra os valores fuzzy para cada um dos conjuntos

		cout<<"\nInput the operation type:\n"<<"a - set center\n"<<"b - Input a value" << endl;
		cin >> menu;
		switch (menu){
			case 'a':
				cout<<"imput the center temperature: ";
				var = (bom - get_temp());
				moveFuzz(FuzzySet);
				continue;
				//move os conjuntos fuzzy para se adequar a uma nova temperatura ideal
			case 'b':
				cout<<"\nInput the value:" <<endl;
				tValue=get_temp();
				break;
				//registra uma temperatura a ser comparada
			default:
				continue;
				//se inseriu algo inválido refaz o loop
		}


		if(tValue < Tmin) continue;
		if(tValue > Tmax) continue;
		//checa se está na faixa de operação

		for(int i=0; i<5; i++){
			cout<<"In function:";
			FuzzySet[i]->getName();

			fuzzyValues[i]=FuzzySet[i]->getValue(tValue);

			cout<<"the membership is=";
			cout<<fuzzyValues[i]<<endl;
		}//mostra os valores fuzzy da temperatura inserida para cada um dos conjuntos

		cout<<"output temperature: "<<generateOut(fuzzyValues)<<endl;
		//printa o resultado de saida gerado pela defuzzyficaçãos
	}
	while(true);

	return 0;
}