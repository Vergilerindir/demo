#include "sira.h"
#define SIZESIRA 20 
#include "stdio.h"
float rezistans[SIZESIRA];
float merkez[SIZESIRA];

void hazirlaSira(){
	int i = 0;
	for(i = 0;i<SIZESIRA;i++){
		rezistans[i] = 0;
		merkez   [i] = 0;
	}
}

static void assagiKay(float *p,int l) {
	float buffer[l];
	int i;
	for(i = 1;i < l;i++){
		buffer[i-1] = p[i];	
	}
	buffer[l-1] = 0;
	for(i = 0;i<l;i++){
		p[i] = buffer[i];
	}
}


void ekleRezistans(float x){
	static int k = 0;
	if(x < 0 && x > 300){x = 500;}
	assagiKay(rezistans,SIZESIRA);
	rezistans[SIZESIRA-1] = x;
	if(k == 0){
		int i = 0;
		for(i = 0;i<SIZESIRA-1;i++){
			rezistans[i] = x;
		}
		k = 1;
	}
}


void ekleMerkez(float x){

	static int k = 0;
	if(x < 0 && x > 300){x = 500;}
	assagiKay(merkez,SIZESIRA);
	merkez[SIZESIRA-1] = x;
	if(k == 0){
		int i = 0;
		for(i = 0;i<SIZESIRA-1;i++){
			merkez[i] = x;
		}
		k = 1;
	}
}


void gosterMerkez(){
	int i;
	for(i = 0;i < SIZESIRA;i++){
		printf("%5.2f ",merkez[i]);
	}
	printf("\n");
}


void gosterRezistans(){
	int i;
	for(i = 0;i < SIZESIRA;i++){
		printf("%5.2f ",rezistans[i]);
	}
	printf("\n");
}

static float ustOrtalama(float *p){
	int i;
	float sum = 0;
	for(i = SIZESIRA/2;i<SIZESIRA;i++){ sum += p[i];}
	return sum;
}


static float altOrtalama(float *p){
	int i;
	float sum = 0;
	for(i = 0;i<SIZESIRA/2;i++){ sum += p[i];}
	return sum;
}
/*
degisim_t degisimRezistans(){
	float ust =  rezistans[SIZESIRA-1]+rezistans[SIZESIRA-2];
	float alt =  rezistans[0] + rezistans[1];
	//printf("ust:%f alt:%f\n",ust,alt);
	if(ust >= alt){return UP ;}
	else {return DOWN;}
}


degisim_t degisimMerkez(){
	float ust = merkez[SIZESIRA-1]+merkez[SIZESIRA-2];
	float alt = merkez[0]+merkez[1];
	//printf("ust:%f alt:%f\n",ust,alt);
	if(ust >= alt){return UP ;}
	else {return DOWN;}
}
*/


degisim_t gelismisDegisimRezistans(){
    float t1 = rezistans[10];
    float t2 = rezistans[13];
    float t3 = rezistans[16];
    float t4 = rezistans[19];

         if(t4 > t3 > t2 > t1){return BUP;}
    else if(t4 > t3 > t2)     {return MUP;}
    else if(t4 >= t3)          {return SUP;}
    else if(t4 < t3 < t2 < t1){return BDOWN;}
    else if(t4 < t3 < t2)     {return MDOWN;}
    else if(t4 <= t3)          {return SDOWN;}
        else{return MIXED;}
}

degisim_t gelismisDegisimMerkez(){
    float t1 = rezistans[10];
    float t2 = rezistans[13];
    float t3 = rezistans[16];
    float t4 = rezistans[19];

         if(t4 > t3 > t2 > t1){return BUP;}
    else if(t4 > t3 > t2)     {return MUP;}
    else if(t4 >= t3)          {return SUP;}
    else if(t4 < t3 < t2 < t1){return BDOWN;}
    else if(t4 < t3 < t2)     {return MDOWN;}
    else if(t4 <= t3)          {return SDOWN;}
        else{return MIXED;}
}




