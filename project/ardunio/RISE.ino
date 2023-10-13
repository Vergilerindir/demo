#include "sira.h"
#include "pins.h"
#include "max6675.h"
short int testt = 0;

typedef union{
	float value;
	long int value_int;
	unsigned char sekiz[4];
}temp_t;

void transferAdvanced(float _sicaklik,float _rezistansSicaklik,long int _state,long int _echo,long int _hedef){
	temp_t buffer;
	int i;
	buffer.value     = _sicaklik;           for(i = 0;i < 4;i++){Serial.write(buffer.sekiz[i]); delayMicroseconds(10);}
	buffer.value     = _rezistansSicaklik;  for(i = 0;i < 4;i++){Serial.write(buffer.sekiz[i]); delayMicroseconds(10);}
	buffer.value_int = _state;              for(i = 0;i < 4;i++){Serial.write(buffer.sekiz[i]); delayMicroseconds(10);}
	buffer.value_int = _echo;               for(i = 0;i < 4;i++){Serial.write(buffer.sekiz[i]); delayMicroseconds(10);}
	buffer.value_int = _hedef;              for(i = 0;i < 4;i++){Serial.write(buffer.sekiz[i]); delayMicroseconds(10);}
}

void RunHeater(float x){if(x > 0.0f) digitalWrite(RLY1HEAT_PIN,RLYHIGH);}
void StpHeater(float x){if(x < 1.0f) digitalWrite(RLY1HEAT_PIN,RLYLOW );}
void RunCooler(float x){if(x > 0.0f) digitalWrite(RLY2COOL_PIN,RLYHIGH);}
void StpCooler(float x){if(x < 1.0f) digitalWrite(RLY2COOL_PIN,RLYLOW );}


long int _echo =  99;
long int _hedef = 60;
char programStop = 0;

void OperateAndCommunicate(float runHeatCoefficent,float runCoolCoefficent,float centerT,float highT,long int _state){
	if(runHeatCoefficent > 1.0f || runHeatCoefficent < 0.0f || runCoolCoefficent > 1.0f || runCoolCoefficent < 0.0f){
		//ErrorLedCode(0);
	}
	else{
		float heatRunTime = runHeatCoefficent*WINDOW;
		float coolRunTime = runCoolCoefficent*WINDOW;
		transferAdvanced(centerT,highT,_state,_echo,_hedef);
		if(heatRunTime > coolRunTime){
			RunHeater(runHeatCoefficent);
			RunCooler(runCoolCoefficent);
			delay(coolRunTime);
			StpCooler(runCoolCoefficent);
			delay(heatRunTime-coolRunTime);
			StpHeater(runHeatCoefficent);
			delay(WINDOW-heatRunTime);
		}
		else if(coolRunTime > heatRunTime){
			RunHeater(runHeatCoefficent);
			RunCooler(runCoolCoefficent);
			delay(heatRunTime);
			StpHeater(runHeatCoefficent);
			delay(coolRunTime-heatRunTime);
			StpCooler(runCoolCoefficent);
			delay(WINDOW-coolRunTime);
		}
		else{
			RunHeater(runHeatCoefficent);
			RunCooler(runCoolCoefficent);
			delay(heatRunTime);
			StpHeater(runHeatCoefficent);
			StpCooler(runCoolCoefficent);
			delay(WINDOW - heatRunTime);
		}
	}

}



MAX6675 termoUp (SCK_PIN, CSHGH_PIN, SO_PIN);
MAX6675 termoMid(SCK_PIN, CSMID_PIN, SO_PIN);

/////////////////////////////////////////////////////
/////////////////////////////////////////////////////
/////////////////////////////////////////////////////







void state0_000x1_050(float coreTemp,float highTemp,degisim_t dCore,degisim_t dHigh){OperateAndCommunicate(0.000f,1.000f,coreTemp,highTemp,218);}
void state1_050x1_025(float coreTemp,float highTemp,degisim_t dCore,degisim_t dHIGH){
	//////////////////////////////////////////////////////////////////////////////////////
	if(highTemp > 65.0f){
		OperateAndCommunicate(0.000f,1.000f,coreTemp,highTemp,218);
	}
	else{
		if(dCore == BUP  ){
			if     (dHIGH == BUP  ){OperateAndCommunicate(0.000f,1.000f,coreTemp,highTemp,217);}
			else if(dHIGH == MUP  ){OperateAndCommunicate(0.000f,1.000f,coreTemp,highTemp,216);}
			else if(dHIGH == SUP  ){OperateAndCommunicate(0.000f,1.000f,coreTemp,highTemp,215);}
			else if(dHIGH == SDOWN){OperateAndCommunicate(0.000f,1.000f,coreTemp,highTemp,214);}
			else if(dHIGH == MDOWN){OperateAndCommunicate(0.000f,1.000f,coreTemp,highTemp,213);}
			else if(dHIGH == BDOWN){OperateAndCommunicate(0.000f,1.000f,coreTemp,highTemp,212);}
			else                   {OperateAndCommunicate(0.000f,1.000f,coreTemp,highTemp,211);}
		}
		else if(dCore == MUP  ){
			if      (dHIGH == BUP ){OperateAndCommunicate(0.000f,1.000f,coreTemp,highTemp,210);}
			else if(dHIGH == MUP  ){OperateAndCommunicate(0.000f,1.000f,coreTemp,highTemp,209);}
			else if(dHIGH == SUP  ){OperateAndCommunicate(0.000f,1.000f,coreTemp,highTemp,208);}
			else if(dHIGH == SDOWN){OperateAndCommunicate(0.000f,1.000f,coreTemp,highTemp,207);}
			else if(dHIGH == MDOWN){OperateAndCommunicate(0.000f,1.000f,coreTemp,highTemp,206);}
			else if(dHIGH == BDOWN){OperateAndCommunicate(0.000f,1.000f,coreTemp,highTemp,205);}
			else                   {OperateAndCommunicate(0.000f,1.000f,coreTemp,highTemp,204);}
		}
		else if(dCore == SUP  ){
			if     (dHIGH == BUP  ){OperateAndCommunicate(0.000f,1.000f,coreTemp,highTemp,203);}
			else if(dHIGH == MUP  ){OperateAndCommunicate(0.000f,0.750f,coreTemp,highTemp,202);}
			else if(dHIGH == SUP  ){OperateAndCommunicate(0.000f,0.750f,coreTemp,highTemp,201);}
			else if(dHIGH == SDOWN){OperateAndCommunicate(0.000f,0.000f,coreTemp,highTemp,200);}
			else if(dHIGH == MDOWN){OperateAndCommunicate(0.000f,0.000f,coreTemp,highTemp,199);}
			else if(dHIGH == BDOWN){OperateAndCommunicate(0.000f,0.000f,coreTemp,highTemp,198);}
			else                   {OperateAndCommunicate(0.000f,1.000f,coreTemp,highTemp,197);}
		}
		else if(dCore == SDOWN){
			if     (dHIGH == BUP  ){OperateAndCommunicate(0.000f,0.750f,coreTemp,highTemp,196);}
			else if(dHIGH == MUP  ){OperateAndCommunicate(0.000f,0.750f,coreTemp,highTemp,195);}
			else if(dHIGH == SUP  ){OperateAndCommunicate(0.000f,0.750f,coreTemp,highTemp,194);}
			else if(dHIGH == SDOWN){OperateAndCommunicate(0.000f,0.000f,coreTemp,highTemp,193);}
			else if(dHIGH == MDOWN){OperateAndCommunicate(0.000f,0.000f,coreTemp,highTemp,192);}
			else if(dHIGH == BDOWN){OperateAndCommunicate(0.000f,0.000f,coreTemp,highTemp,191);}
			else                   {OperateAndCommunicate(0.000f,1.000f,coreTemp,highTemp,190);}
		}
		else if(dCore == MDOWN){
			if     (dHIGH == BUP  ){OperateAndCommunicate(0.000f,0.000f,coreTemp,highTemp,189);}
			else if(dHIGH == MUP  ){OperateAndCommunicate(0.000f,0.000f,coreTemp,highTemp,188);}
			else if(dHIGH == SUP  ){OperateAndCommunicate(0.000f,0.000f,coreTemp,highTemp,187);}
			else if(dHIGH == SDOWN){OperateAndCommunicate(0.000f,0.000f,coreTemp,highTemp,186);}
			else if(dHIGH == MDOWN){OperateAndCommunicate(0.000f,0.000f,coreTemp,highTemp,185);}
			else if(dHIGH == BDOWN){OperateAndCommunicate(0.000f,0.000f,coreTemp,highTemp,184);}
			else                   {OperateAndCommunicate(0.000f,1.000f,coreTemp,highTemp,183);}
		}
		else if(dCore == BDOWN){
			if     (dHIGH == BUP  ){OperateAndCommunicate(0.000f,0.000f,coreTemp,highTemp,182);}
			else if(dHIGH == MUP  ){OperateAndCommunicate(0.000f,0.000f,coreTemp,highTemp,181);}
			else if(dHIGH == SUP  ){OperateAndCommunicate(0.000f,0.000f,coreTemp,highTemp,180);}
			else if(dHIGH == SDOWN){OperateAndCommunicate(0.000f,0.000f,coreTemp,highTemp,179);}
			else if(dHIGH == MDOWN){OperateAndCommunicate(0.000f,0.000f,coreTemp,highTemp,178);}
			else if(dHIGH == BDOWN){OperateAndCommunicate(0.100f,0.000f,coreTemp,highTemp,177);}
			else                   {OperateAndCommunicate(0.000f,1.000f,coreTemp,highTemp,176);}
		}
		else                   {OperateAndCommunicate(0.000f,1.000f,coreTemp,highTemp,175);}

	}
	//////////////////////////////////////////////////////////////////////////////////////
}
void state1_025x1_000(float coreTemp,float highTemp,degisim_t dCore,degisim_t dHIGH){
	//////////////////////////////////////////////////////////////////////////////////////
	if(highTemp > 65.0f){
		OperateAndCommunicate(0.000f,1.000f,coreTemp,highTemp,217);
	}
	else{
		if(dCore == BUP  ){
			if     (dHIGH == BUP  ){OperateAndCommunicate(0.000f,0.750f,coreTemp,highTemp,174);}
			else if(dHIGH == MUP  ){OperateAndCommunicate(0.000f,0.750f,coreTemp,highTemp,173);}
			else if(dHIGH == SUP  ){OperateAndCommunicate(0.000f,0.750f,coreTemp,highTemp,172);}
			else if(dHIGH == SDOWN){OperateAndCommunicate(0.000f,0.750f,coreTemp,highTemp,171);}
			else if(dHIGH == MDOWN){OperateAndCommunicate(0.000f,0.750f,coreTemp,highTemp,170);}
			else if(dHIGH == BDOWN){OperateAndCommunicate(0.000f,0.750f,coreTemp,highTemp,169);}
			else                   {OperateAndCommunicate(0.000f,1.000f,coreTemp,highTemp,168);}
		}
		else if(dCore == MUP  ){
			if      (dHIGH == BUP ){OperateAndCommunicate(0.000f,0.750f,coreTemp,highTemp,167);}
			else if(dHIGH == MUP  ){OperateAndCommunicate(0.000f,0.750f,coreTemp,highTemp,166);}
			else if(dHIGH == SUP  ){OperateAndCommunicate(0.000f,0.750f,coreTemp,highTemp,165);}
			else if(dHIGH == SDOWN){OperateAndCommunicate(0.000f,0.750f,coreTemp,highTemp,164);}
			else if(dHIGH == MDOWN){OperateAndCommunicate(0.000f,0.750f,coreTemp,highTemp,163);}
			else if(dHIGH == BDOWN){OperateAndCommunicate(0.000f,0.750f,coreTemp,highTemp,162);}
			else                   {OperateAndCommunicate(0.000f,1.000f,coreTemp,highTemp,161);}
		}
		else if(dCore == SUP  ){
			if     (dHIGH == BUP  ){OperateAndCommunicate(0.000f,0.750f,coreTemp,highTemp,160);}
			else if(dHIGH == MUP  ){OperateAndCommunicate(0.000f,0.750f,coreTemp,highTemp,159);}
			else if(dHIGH == SUP  ){OperateAndCommunicate(0.000f,0.750f,coreTemp,highTemp,158);}
			else if(dHIGH == SDOWN){OperateAndCommunicate(0.000f,0.000f,coreTemp,highTemp,157);}
			else if(dHIGH == MDOWN){OperateAndCommunicate(0.000f,0.000f,coreTemp,highTemp,156);}
			else if(dHIGH == BDOWN){OperateAndCommunicate(0.000f,0.000f,coreTemp,highTemp,155);}
			else                   {OperateAndCommunicate(0.000f,1.000f,coreTemp,highTemp,154);}
		}
		else if(dCore == SDOWN){
			if     (dHIGH == BUP  ){OperateAndCommunicate(0.000f,0.750f,coreTemp,highTemp,153);}
			else if(dHIGH == MUP  ){OperateAndCommunicate(0.000f,0.750f,coreTemp,highTemp,152);}
			else if(dHIGH == SUP  ){OperateAndCommunicate(0.000f,0.000f,coreTemp,highTemp,151);}
			else if(dHIGH == SDOWN){OperateAndCommunicate(0.000f,0.000f,coreTemp,highTemp,150);}
			else if(dHIGH == MDOWN){OperateAndCommunicate(0.000f,0.000f,coreTemp,highTemp,149);}
			else if(dHIGH == BDOWN){OperateAndCommunicate(0.100f,0.000f,coreTemp,highTemp,148);}
			else                   {OperateAndCommunicate(0.000f,1.000f,coreTemp,highTemp,147);}
		}
		else if(dCore == MDOWN){
			if     (dHIGH == BUP  ){OperateAndCommunicate(0.000f,0.000f,coreTemp,highTemp,146);}
			else if(dHIGH == MUP  ){OperateAndCommunicate(0.000f,0.000f,coreTemp,highTemp,145);}
			else if(dHIGH == SUP  ){OperateAndCommunicate(0.000f,0.000f,coreTemp,highTemp,144);}
			else if(dHIGH == SDOWN){OperateAndCommunicate(0.000f,0.000f,coreTemp,highTemp,143);}
			else if(dHIGH == MDOWN){OperateAndCommunicate(0.100f,0.000f,coreTemp,highTemp,142);}
			else if(dHIGH == BDOWN){OperateAndCommunicate(0.100f,0.000f,coreTemp,highTemp,141);}
			else                   {OperateAndCommunicate(0.000f,1.000f,coreTemp,highTemp,140);}
		}
		else if(dCore == BDOWN){
			if     (dHIGH == BUP  ){OperateAndCommunicate(0.000f,0.000f,coreTemp,highTemp,139);}
			else if(dHIGH == MUP  ){OperateAndCommunicate(0.000f,0.000f,coreTemp,highTemp,138);}
			else if(dHIGH == SUP  ){OperateAndCommunicate(0.000f,0.000f,coreTemp,highTemp,137);}
			else if(dHIGH == SDOWN){OperateAndCommunicate(0.000f,0.000f,coreTemp,highTemp,136);}
			else if(dHIGH == MDOWN){OperateAndCommunicate(0.150f,0.000f,coreTemp,highTemp,135);}
			else if(dHIGH == BDOWN){OperateAndCommunicate(0.200f,0.000f,coreTemp,highTemp,134);}
			else                   {OperateAndCommunicate(0.000f,1.000f,coreTemp,highTemp,133);}
		}
		else                   {OperateAndCommunicate(0.000f,1.000f,coreTemp,highTemp,132);}
	}
	//////////////////////////////////////////////////////////////////////////////////////

}
void state1_000x0_975(float coreTemp,float highTemp,degisim_t dCore,degisim_t dHIGH){
	//////////////////////////////////////////////////////////////////////////////////////
	if(highTemp > 65.0f){
		OperateAndCommunicate(0.000f,1.000f,coreTemp,highTemp,217);
	}
	else{
		if(dCore == BUP  ){
			if     (dHIGH == BUP  ){OperateAndCommunicate(0.000f,0.750f,coreTemp,highTemp,131);}
			else if(dHIGH == MUP  ){OperateAndCommunicate(0.000f,0.750f,coreTemp,highTemp,130);}
			else if(dHIGH == SUP  ){OperateAndCommunicate(0.000f,0.750f,coreTemp,highTemp,129);}
			else if(dHIGH == SDOWN){OperateAndCommunicate(0.000f,0.750f,coreTemp,highTemp,128);}
			else if(dHIGH == MDOWN){OperateAndCommunicate(0.000f,0.000f,coreTemp,highTemp,127);}
			else if(dHIGH == BDOWN){OperateAndCommunicate(0.000f,0.000f,coreTemp,highTemp,126);}
			else                   {OperateAndCommunicate(0.000f,1.000f,coreTemp,highTemp,125);}
		}
		else if(dCore == MUP  ){
			if      (dHIGH == BUP ){OperateAndCommunicate(0.000f,0.750f,coreTemp,highTemp,124);}
			else if(dHIGH == MUP  ){OperateAndCommunicate(0.000f,0.750f,coreTemp,highTemp,123);}
			else if(dHIGH == SUP  ){OperateAndCommunicate(0.000f,0.750f,coreTemp,highTemp,122);}
			else if(dHIGH == SDOWN){OperateAndCommunicate(0.000f,0.000f,coreTemp,highTemp,121);}
			else if(dHIGH == MDOWN){OperateAndCommunicate(0.000f,0.000f,coreTemp,highTemp,120);}
			else if(dHIGH == BDOWN){OperateAndCommunicate(0.000f,0.000f,coreTemp,highTemp,119);}
			else                   {OperateAndCommunicate(0.000f,1.000f,coreTemp,highTemp,118);}
		}
		else if(dCore == SUP  ){
			if     (dHIGH == BUP  ){OperateAndCommunicate(0.000f,0.750f,coreTemp,highTemp,117);}
			else if(dHIGH == MUP  ){OperateAndCommunicate(0.000f,0.000f,coreTemp,highTemp,116);}
			else if(dHIGH == SUP  ){OperateAndCommunicate(0.000f,0.000f,coreTemp,highTemp,115);}
			else if(dHIGH == SDOWN){OperateAndCommunicate(0.000f,0.000f,coreTemp,highTemp,114);}
			else if(dHIGH == MDOWN){OperateAndCommunicate(0.100f,0.000f,coreTemp,highTemp,113);}
			else if(dHIGH == BDOWN){OperateAndCommunicate(0.150f,0.000f,coreTemp,highTemp,112);}
			else                   {OperateAndCommunicate(0.000f,1.000f,coreTemp,highTemp,111);}
		}
		else if(dCore == SDOWN){
			if     (dHIGH == BUP  ){OperateAndCommunicate(0.000f,0.000f,coreTemp,highTemp,110);}
			else if(dHIGH == MUP  ){OperateAndCommunicate(0.000f,0.000f,coreTemp,highTemp,109);}
			else if(dHIGH == SUP  ){OperateAndCommunicate(0.000f,0.000f,coreTemp,highTemp,108);}
			else if(dHIGH == SDOWN){OperateAndCommunicate(0.000f,0.000f,coreTemp,highTemp,107);}
			else if(dHIGH == MDOWN){OperateAndCommunicate(0.100f,0.000f,coreTemp,highTemp,106);}
			else if(dHIGH == BDOWN){OperateAndCommunicate(0.150f,0.000f,coreTemp,highTemp,105);}
			else                   {OperateAndCommunicate(0.000f,1.000f,coreTemp,highTemp,104);}
		}
		else if(dCore == MDOWN){
			if     (dHIGH == BUP  ){OperateAndCommunicate(0.000f,0.000f,coreTemp,highTemp,103);}
			else if(dHIGH == MUP  ){OperateAndCommunicate(0.000f,0.000f,coreTemp,highTemp,102);}
			else if(dHIGH == SUP  ){OperateAndCommunicate(0.000f,0.000f,coreTemp,highTemp,101);}
			else if(dHIGH == SDOWN){OperateAndCommunicate(0.100f,0.000f,coreTemp,highTemp,100);}
			else if(dHIGH == MDOWN){OperateAndCommunicate(0.150f,0.000f,coreTemp,highTemp,99);}
			else if(dHIGH == BDOWN){OperateAndCommunicate(0.150f,0.000f,coreTemp,highTemp,98);}
			else                   {OperateAndCommunicate(0.000f,1.000f,coreTemp,highTemp,97);}
		}
		else if(dCore == BDOWN){
			if     (dHIGH == BUP  ){OperateAndCommunicate(0.000f,0.000f,coreTemp,highTemp,96);}
			else if(dHIGH == MUP  ){OperateAndCommunicate(0.000f,0.000f,coreTemp,highTemp,95);}
			else if(dHIGH == SUP  ){OperateAndCommunicate(0.000f,0.000f,coreTemp,highTemp,94);}
			else if(dHIGH == SDOWN){OperateAndCommunicate(0.100f,0.000f,coreTemp,highTemp,93);}
			else if(dHIGH == MDOWN){OperateAndCommunicate(0.150f,0.000f,coreTemp,highTemp,92);}
			else if(dHIGH == BDOWN){OperateAndCommunicate(0.200f,0.000f,coreTemp,highTemp,91);}
			else                   {OperateAndCommunicate(0.000f,1.000f,coreTemp,highTemp,90);}
		}
		else                   {OperateAndCommunicate(0.000f,1.000f,coreTemp,highTemp,89);}
	}
	//////////////////////////////////////////////////////////////////////////////////////
}
void state0_975x0_950(float coreTemp,float highTemp,degisim_t dCore,degisim_t dHIGH){
	//////////////////////////////////////////////////////////////////////////////////////
	if(highTemp > 66.0f){
		OperateAndCommunicate(0.000f,1.000f,coreTemp,highTemp,219);
	}
	else{
		if(dCore == BUP  ){
			if     (dHIGH == BUP  ){OperateAndCommunicate(0.000f,0.750f,coreTemp,highTemp,88);}
			else if(dHIGH == MUP  ){OperateAndCommunicate(0.000f,0.750f,coreTemp,highTemp,87);}
			else if(dHIGH == SUP  ){OperateAndCommunicate(0.000f,0.750f,coreTemp,highTemp,86);}
			else if(dHIGH == SDOWN){OperateAndCommunicate(0.000f,0.750f,coreTemp,highTemp,85);}
			else if(dHIGH == MDOWN){OperateAndCommunicate(0.000f,0.000f,coreTemp,highTemp,84);}
			else if(dHIGH == BDOWN){OperateAndCommunicate(0.000f,0.000f,coreTemp,highTemp,83);}
			else                   {OperateAndCommunicate(0.000f,1.000f,coreTemp,highTemp,82);}
		}
		else if(dCore == MUP  ){
			if      (dHIGH == BUP ){OperateAndCommunicate(0.000f,0.750f,coreTemp,highTemp,81);}
			else if(dHIGH == MUP  ){OperateAndCommunicate(0.000f,0.750f,coreTemp,highTemp,80);}
			else if(dHIGH == SUP  ){OperateAndCommunicate(0.000f,0.750f,coreTemp,highTemp,79);}
			else if(dHIGH == SDOWN){OperateAndCommunicate(0.000f,0.000f,coreTemp,highTemp,78);}
			else if(dHIGH == MDOWN){OperateAndCommunicate(0.000f,0.000f,coreTemp,highTemp,77);}
			else if(dHIGH == BDOWN){OperateAndCommunicate(0.000f,0.000f,coreTemp,highTemp,76);}
			else                   {OperateAndCommunicate(0.000f,1.000f,coreTemp,highTemp,75);}
		}
		else if(dCore == SUP  ){
			if     (dHIGH == BUP  ){OperateAndCommunicate(0.000f,0.500f,coreTemp,highTemp,74);}
			else if(dHIGH == MUP  ){OperateAndCommunicate(0.000f,0.500f,coreTemp,highTemp,73);}
			else if(dHIGH == SUP  ){OperateAndCommunicate(0.000f,0.000f,coreTemp,highTemp,72);}
			else if(dHIGH == SDOWN){OperateAndCommunicate(0.000f,0.000f,coreTemp,highTemp,71);}
			else if(dHIGH == MDOWN){OperateAndCommunicate(0.100f,0.000f,coreTemp,highTemp,70);}
			else if(dHIGH == BDOWN){OperateAndCommunicate(0.150f,0.000f,coreTemp,highTemp,69);}
			else                   {OperateAndCommunicate(0.000f,1.000f,coreTemp,highTemp,68);}
		}
		else if(dCore == SDOWN){
			if     (dHIGH == BUP  ){OperateAndCommunicate(0.000f,0.500f,coreTemp,highTemp,67);}
			else if(dHIGH == MUP  ){OperateAndCommunicate(0.000f,0.500f,coreTemp,highTemp,66);}
			else if(dHIGH == SUP  ){OperateAndCommunicate(0.000f,0.000f,coreTemp,highTemp,65);}
			else if(dHIGH == SDOWN){OperateAndCommunicate(0.100f,0.000f,coreTemp,highTemp,64);}
			else if(dHIGH == MDOWN){OperateAndCommunicate(0.100f,0.000f,coreTemp,highTemp,63);}
			else if(dHIGH == BDOWN){OperateAndCommunicate(0.100f,0.000f,coreTemp,highTemp,62);}
			else                   {OperateAndCommunicate(0.000f,1.000f,coreTemp,highTemp,61);}
		}
		else if(dCore == MDOWN){
			if     (dHIGH == BUP  ){OperateAndCommunicate(0.000f,0.000f,coreTemp,highTemp,60);}
			else if(dHIGH == MUP  ){OperateAndCommunicate(0.000f,0.000f,coreTemp,highTemp,59);}
			else if(dHIGH == SUP  ){OperateAndCommunicate(0.000f,0.000f,coreTemp,highTemp,58);}
			else if(dHIGH == SDOWN){OperateAndCommunicate(0.150f,0.000f,coreTemp,highTemp,57);}
			else if(dHIGH == MDOWN){OperateAndCommunicate(0.150f,0.000f,coreTemp,highTemp,56);}
			else if(dHIGH == BDOWN){OperateAndCommunicate(0.150f,0.000f,coreTemp,highTemp,55);}
			else                   {OperateAndCommunicate(0.000f,1.000f,coreTemp,highTemp,54);}
		}
		else if(dCore == BDOWN){
			if     (dHIGH == BUP  ){OperateAndCommunicate(0.000f,0.000f,coreTemp,highTemp,53);}
			else if(dHIGH == MUP  ){OperateAndCommunicate(0.000f,0.000f,coreTemp,highTemp,52);}
			else if(dHIGH == SUP  ){OperateAndCommunicate(0.000f,0.000f,coreTemp,highTemp,51);}
			else if(dHIGH == SDOWN){OperateAndCommunicate(0.200f,0.000f,coreTemp,highTemp,50);}
			else if(dHIGH == MDOWN){OperateAndCommunicate(0.250f,0.000f,coreTemp,highTemp,49);}
			else if(dHIGH == BDOWN){OperateAndCommunicate(0.300f,0.000f,coreTemp,highTemp,48);}
			else                   {OperateAndCommunicate(0.000f,1.000f,coreTemp,highTemp,47);}
		}
		else                   {OperateAndCommunicate(0.000f,1.000f,coreTemp,highTemp,46);}
	}
	//////////////////////////////////////////////////////////////////////////////////////
}
void state0_950x0_800(float coreTemp,float highTemp,degisim_t dCore,degisim_t dHIGH){
	//////////////////////////////////////////////////////////////////////////////////////
	if(highTemp > 67.0f){
		OperateAndCommunicate(0.000f,1.000f,coreTemp,highTemp,220);
	}
	else{
		if(dCore == BUP  ){
			if     (dHIGH == BUP  ){OperateAndCommunicate(0.000f,0.750f,coreTemp,highTemp,45);}
			else if(dHIGH == MUP  ){OperateAndCommunicate(0.000f,0.750f,coreTemp,highTemp,44);}
			else if(dHIGH == SUP  ){OperateAndCommunicate(0.000f,0.000f,coreTemp,highTemp,43);}
			else if(dHIGH == SDOWN){OperateAndCommunicate(0.000f,0.000f,coreTemp,highTemp,42);}
			else if(dHIGH == MDOWN){OperateAndCommunicate(0.000f,0.000f,coreTemp,highTemp,41);}
			else if(dHIGH == BDOWN){OperateAndCommunicate(0.000f,0.000f,coreTemp,highTemp,40);}
			else                   {OperateAndCommunicate(0.000f,1.000f,coreTemp,highTemp,39);}
		}
		else if(dCore == MUP  ){
			if      (dHIGH == BUP ){OperateAndCommunicate(0.000f,0.750f,coreTemp,highTemp,38);}
			else if(dHIGH == MUP  ){OperateAndCommunicate(0.000f,0.750f,coreTemp,highTemp,37);}
			else if(dHIGH == SUP  ){OperateAndCommunicate(0.000f,0.000f,coreTemp,highTemp,36);}
			else if(dHIGH == SDOWN){OperateAndCommunicate(0.000f,0.000f,coreTemp,highTemp,35);}
			else if(dHIGH == MDOWN){OperateAndCommunicate(0.000f,0.000f,coreTemp,highTemp,34);}
			else if(dHIGH == BDOWN){OperateAndCommunicate(0.000f,0.000f,coreTemp,highTemp,33);}
			else                   {OperateAndCommunicate(0.000f,1.000f,coreTemp,highTemp,32);}
		}
		else if(dCore == SUP  ){
			if     (dHIGH == BUP  ){OperateAndCommunicate(0.000f,0.500f,coreTemp,highTemp,31);}
			else if(dHIGH == MUP  ){OperateAndCommunicate(0.000f,0.000f,coreTemp,highTemp,30);}
			else if(dHIGH == SUP  ){OperateAndCommunicate(0.000f,0.000f,coreTemp,highTemp,29);}
			else if(dHIGH == SDOWN){OperateAndCommunicate(0.100f,0.000f,coreTemp,highTemp,28);}
			else if(dHIGH == MDOWN){OperateAndCommunicate(0.150f,0.000f,coreTemp,highTemp,27);}
			else if(dHIGH == BDOWN){OperateAndCommunicate(0.200f,0.000f,coreTemp,highTemp,26);}
			else                   {OperateAndCommunicate(0.000f,1.000f,coreTemp,highTemp,25);}
		}
		else if(dCore == SDOWN){
			if     (dHIGH == BUP  ){OperateAndCommunicate(0.000f,0.000f,coreTemp,highTemp,24);}
			else if(dHIGH == MUP  ){OperateAndCommunicate(0.000f,0.000f,coreTemp,highTemp,23);}
			else if(dHIGH == SUP  ){OperateAndCommunicate(0.000f,0.000f,coreTemp,highTemp,22);}
			else if(dHIGH == SDOWN){OperateAndCommunicate(0.000f,0.000f,coreTemp,highTemp,21);}
			else if(dHIGH == MDOWN){OperateAndCommunicate(0.150f,0.000f,coreTemp,highTemp,20);}
			else if(dHIGH == BDOWN){OperateAndCommunicate(0.200f,0.000f,coreTemp,highTemp,19);}
			else                   {OperateAndCommunicate(0.000f,1.000f,coreTemp,highTemp,18);}
		}
		else if(dCore == MDOWN){
			if     (dHIGH == BUP  ){OperateAndCommunicate(0.000f,0.000f,coreTemp,highTemp,17);}
			else if(dHIGH == MUP  ){OperateAndCommunicate(0.000f,0.000f,coreTemp,highTemp,16);}
			else if(dHIGH == SUP  ){OperateAndCommunicate(0.000f,0.000f,coreTemp,highTemp,15);}
			else if(dHIGH == SDOWN){OperateAndCommunicate(0.200f,0.000f,coreTemp,highTemp,14);}
			else if(dHIGH == MDOWN){OperateAndCommunicate(0.250f,0.000f,coreTemp,highTemp,13);}
			else if(dHIGH == BDOWN){OperateAndCommunicate(0.300f,0.000f,coreTemp,highTemp,12);}
			else                   {OperateAndCommunicate(0.000f,1.000f,coreTemp,highTemp,11);}
		}
		else if(dCore == BDOWN){
			if     (dHIGH == BUP  ){OperateAndCommunicate(0.000f,0.000f,coreTemp,highTemp,11);}
			else if(dHIGH == MUP  ){OperateAndCommunicate(0.000f,0.000f,coreTemp,highTemp,10);}
			else if(dHIGH == SUP  ){OperateAndCommunicate(0.000f,0.000f,coreTemp,highTemp,9);}
			else if(dHIGH == SDOWN){OperateAndCommunicate(0.400f,0.000f,coreTemp,highTemp,8);}
			else if(dHIGH == MDOWN){OperateAndCommunicate(0.400f,0.000f,coreTemp,highTemp,7);}
			else if(dHIGH == BDOWN){OperateAndCommunicate(0.400f,0.000f,coreTemp,highTemp,6);}
			else                   {OperateAndCommunicate(0.000f,1.000f,coreTemp,highTemp,5);}
		}
		else                   {OperateAndCommunicate(0.000f,1.000f,coreTemp,highTemp,4);}

	}
	//////////////////////////////////////////////////////////////////////////////////////
}
void state0_800x0_700(float coreTemp,float highTemp,degisim_t dCore,degisim_t dHigh){
	if(highTemp > 68.0f){
		OperateAndCommunicate(0.000f,1.000f,coreTemp,highTemp,221);
	}
	else{	
		OperateAndCommunicate(0.400f,0.000f,coreTemp,highTemp,3);
	}
}
void state0_700x0_600(float coreTemp,float highTemp,degisim_t dCore,degisim_t dHigh){
	if(highTemp > 69.0f){
		OperateAndCommunicate(0.000f,1.000f,coreTemp,highTemp,222);
	}
	else{	
		OperateAndCommunicate(0.500f,0.000f,coreTemp,highTemp,2);
	}
}
void state0_600x0_500(float coreTemp,float highTemp,degisim_t dCore,degisim_t dHigh){
	if(highTemp > 70.0f){
		OperateAndCommunicate(0.000f,1.000f,coreTemp,highTemp,223);
	}
	else{	
	OperateAndCommunicate(0.750f,0.000f,coreTemp,highTemp,1);
	}

}
void state0_500x0_000(float coreTemp,float highTemp,degisim_t dCore,degisim_t dHigh){OperateAndCommunicate(1.000f,0.000f,coreTemp,highTemp,0);}
void state7_777x7_777(float coreTemp,float highTemp,degisim_t dCore,degisim_t dHigh){OperateAndCommunicate(0.000f,1.000f,coreTemp,highTemp,777);}








/////////////////////////////////////////////////////
/////////////////////////////////////////////////////
/////////////////////////////////////////////////////





void setup() {
	Serial.begin(9600);
	hazirlaSira();
	pinMode(RLY1HEAT_PIN,OUTPUT);
	pinMode(RLY2COOL_PIN,OUTPUT);
	digitalWrite(RLY1HEAT_PIN,RLYLOW);
	digitalWrite(RLY2COOL_PIN,LOW);
}

void loop() {
	float coreTemp = termoMid.readCelsius();
	float highTemp = termoUp.readCelsius();
	ekleRezistans(highTemp);
	ekleMerkez(coreTemp);
	degisim_t dCore = gelismisDegisimMerkez();
	degisim_t dHigh = gelismisDegisimRezistans();
	while(programStop){
		digitalWrite(RLY1HEAT_PIN,RLYLOW);
		digitalWrite(RLY2COOL_PIN,RLYLOW);
		transferAdvanced(coreTemp,highTemp,444,_echo,_hedef);
		delay(10000);    
	}



	///////////////////////////
	//////ANTI OVERHEAT////////
	///////////////////////////
	if     (coreTemp >  _hedef*1.050f){state0_000x1_050(coreTemp,highTemp,dCore,dHigh);}
	else if(coreTemp >  _hedef*1.025f){state1_050x1_025(coreTemp,highTemp,dCore,dHigh);}
	else if(coreTemp >  _hedef*1.000f){state1_025x1_000(coreTemp,highTemp,dCore,dHigh);}
	else if(coreTemp >  _hedef*0.975f){state1_000x0_975(coreTemp,highTemp,dCore,dHigh);}
	else if(coreTemp >  _hedef*0.950f){state0_975x0_950(coreTemp,highTemp,dCore,dHigh);}
	else if(coreTemp >  _hedef*0.800f){state0_950x0_800(coreTemp,highTemp,dCore,dHigh);}
	else if(coreTemp >  _hedef*0.700f){state0_800x0_700(coreTemp,highTemp,dCore,dHigh);}
	else if(coreTemp >  _hedef*0.600f){state0_700x0_600(coreTemp,highTemp,dCore,dHigh);}
	else if(coreTemp >  _hedef*0.500f){state0_600x0_500(coreTemp,highTemp,dCore,dHigh);}
	else if(coreTemp <= _hedef*0.500f){state0_500x0_000(coreTemp,highTemp,dCore,dHigh);}
	else                              {state7_777x7_777(coreTemp,highTemp,dCore,dHigh);}


	//////////////////////////i
	///////////////////////////
	///////////////////////////
}

void serialEvent(){
	while(Serial.available()){
		char i = Serial.read();
		switch(i){
			case 'a':
				_hedef = 60;
				break;
			case 'y':
				_hedef = 70;
				break;
			case 'd':
				programStop = 1;
				break;
			case 'e':
				if(_echo == 99) _echo = 100;
				else _echo = 99;
				break;
		}
	}
}
