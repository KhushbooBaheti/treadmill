/*
ro=vo2
r1=met
r2=caloriesburnt
r3=distance

flag[0]=positive
flag[1]=negative
flag[2]=zero
flag[3]=overflow

CONTROL SIGNALS FOR ALU ARE :-
   00 -> Addition
   01 -> Decrement
   10 -> Multiplication
   11 -> Division 
*/

#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<math.h>

char ir[16];
int pc=-1;
int flag[4];
float registers[7];
int rGRD;
int rWGT;
int rTME;
int rSPD;
int rWGT;
float rOUT;
void setspeed(int x,int ind1);
void settime(int x,int ind1);
void setweight(int x,int ind1);
void setgrade(int x,int ind1);
void Caldist(int ind1,int ind2);
void Caloxygen(int ind1,int ind2);
void caloburnt(int ind1);
void calmet(int ind1);
void cspdinc(int ind1);
void cspddec(int ind1);
void set();
void print_reg();
int bintodec(char c[]);
int i,j,k,d1,d2,p;


int main(){
	FILE* fp;
	char filename[20],ch1,ch2,f4[5]={0,0,0,0},f8[9]={0,0,0,0,0,0,0,0},f4last[5]={0,0,0,0},f8first[9]={0,0,0,0,0,0,0,0},f4mid[5]={0,0,0,0},f12first[13]={0,0,0,0,0,0,0,0,0,0,0,0},f12last[13]={0,0,0,0,0,0,0,0,0,0,0,0};
	char* a;
	
	printf("enter the file name you want to execute\n");
	scanf("%s",filename);
	
	fp=fopen(filename,"r");
	ch1=fscanf(fp,"%s",ir);
	pc++;
	while(ch1!=EOF){
		
		for(i=0;i<4;i++){
			f4[i]=ir[i];
		}
		f4[i]='\0';

		for(j=0;j<12;j++){
			f12last[j]=ir[i];
			i++;
		}
		f12last[j]='\0';

		for(i=0,k=4;i<8;i++,k++){
			f8[i]=ir[k];
		}
		
		for(j=0;j<4;j++){
			f4last[j]=ir[k];
			k++;
		}
		f4last[5]='\0';
		
		
		for(i=0;i<8;i++){
			f8first[i]=ir[i];
		}
		f8first[i]='\0';

		for(j=0;j<4;j++){
			f4mid[j]=ir[i];
			i++;
		}
		f4mid[j]='\0';

		for(j=0;j<12;j++){
			f12first[j]=ir[j];
		}
		f12first[j]='\0';
				
			if(strcmp(f4,"0000")==0){//checking for setspeed opcode
				d1=bintodec(f8);
				d2=bintodec(f4last);
				printf("Instruction reg: setspeed %d rSPD\n",d1);
				setspeed(d1,d2);
				printf("status of all the registers: \n");
				print_reg();			
				
			}
			else if(strcmp(f4,"0001")==0){//checking for settime opcode
				d1=bintodec(f8);
				d2=bintodec(f4last);
				printf("Instruction reg: settime %d rTME\n",d1);
				settime(d1,d2);
				printf("status of all the registers: \n");
				print_reg();
				
			}
			else if(strcmp(f4,"0010")==0){//checking for setweight opcode
				d1=bintodec(f8);
				d2=bintodec(f4last);
				printf("Instruction reg: setweight %d rWGT\n",d1);
				setweight(d1,d2);
				printf("status of all the registers: \n");
				print_reg();
				
			}
			else if(strcmp(f4,"0011")==0){//checking for setgrade opcode
				d1=bintodec(f8);
				d2=bintodec(f4last);
				printf("Instruction reg: setgrade %d rGRD\n",d1);
				setgrade(d1,d2);
				printf("status of all the registers: \n");
				print_reg();
				
			}
			else if(strcmp(f4,"0100")==0){//checking for sjump opcode
				d1=bintodec(f12last);				
				rewind(fp);				
				printf("Instruction reg: sjump %d \n",d1);
				printf("status of all the registers: \n");
				print_reg();
				ch2=fseek(fp,((d1-1)*15+1),SEEK_SET);
				pc= d1-1;
				ch1=fscanf(fp,"%s",ir);
				
								
			}
			else if(strcmp(f8first,"01010000")==0){//checking for Caldist opcode
				d1=bintodec(f4mid);
				d2=bintodec(f4last);				
				printf("Instruction reg: Caldist rSPD rTME\n");
				Caldist(d1,d2);
				printf("status of all the registers: \n");
				print_reg();				
			}
			else if(strcmp(f8first,"01010001")==0){//checking for Caloxygen opcode
				d1=bintodec(f4mid);
				d2=bintodec(f4last);
				printf("status of all the registers: \n");
				printf("Instruction reg: Caloxygen rSPD rGRD\n");
				Caloxygen(d1,d2);
				
			}
			else if(strcmp(f12first,"010100100000")==0){//checking for caloburnt opcode
				d1=bintodec(f4last);
				printf("Instruction reg: caloburnt r%d\n",d1);
				Caloxygen(10,7);
				calmet(0);
				caloburnt(d1);
				printf("status of all the registers: \n");
				print_reg();
				
			}
			else if(strcmp(f12first,"010100100001")==0){//checking for calmet opcode
				d1=bintodec(f4last);				
				printf("Instruction reg: calmet r%d\n",d1);
				Caloxygen(10,7);
				calmet(d1);
				printf("status of all the registers: \n");
				print_reg();
				
			}
			else if(strcmp(f12first,"010100100010")==0){//checking for spdinc opcode
				d1=bintodec(f4last);				
				printf("Instruction reg: cspdinc rSPD\n");
				cspdinc(d1);
				printf("status of all the registers: \n");
				print_reg();
				
			}
			else if(strcmp(f12first,"010100100011")==0){//checking for spddec opcode
				d1=bintodec(f4last);				
				printf("Instruction reg: cspddec rSPD\n");
				cspddec(d1);
				printf("status of all the registers: \n");
				print_reg();
				
			}
			else if(strcmp(ir,"0101001001000000")==0){//checking for hlt opcode
				
				printf("Instruction reg: hlt\n");
				printf("status of all the registers: \n");
				print_reg();
				return 0;
			}

			
		pc++;
		ch1=fscanf(fp,"%s",ir);
		
	}
	fclose(fp);
	
	
	



}

void set(){
	for(i=0;i<7;i++){
		registers[i]=0;
	}
	rGRD=0;
	rWGT=0;
	rTME=0;
	rSPD=0;
	rWGT=0;
 	rOUT=0;
}

void setspeed(int x,int ind1){
	if(ind1==10){	
		rSPD=x;
	}
	else{
		printf("please enter a valid binary-function arguement");
	}
}

void settime(int x,int ind1){
	if(ind1==9){	
		rTME=x;
	}
	else{
		printf("please enter a valid binary-function arguement");
	}
}

void setweight(int x,int ind1){
	if(ind1==8){	
		rWGT=x;
	}
	else{
		printf("please enter a valid binary-function arguement");
	}
}

void setgrade(int x,int ind1){
	if(ind1==7){	
		rGRD=x;
	}
	else{
		printf("please enter a valid binary-function arguement");
	}
}

void Caldist(int ind1,int ind2){
	if(ind1==10 && ind2==9){
		registers[3]=rTME;
		registers[5]=rSPD;
		registers[3]=registers[5]*registers[3];
		printf("Multiplication done by ALU: S0:0,S1:1 (10)\n");
		if(registers[3]==0)
			flag[2]=1;
		else
			flag[2]=0;
		if(registers[3]<0)
			flag[1]=1;
		else
			flag[1]=0;
		if(registers[3]>0)
			flag[0]=1;
		else
			flag[0]=0;
		rOUT=registers[3];
	}
	else
		printf("error\n");
}

void Caloxygen(int ind1,int ind2){
	if(ind1==10 && ind2==7){
		registers[0]=rSPD;
		registers[5]=rGRD;
		registers[0]=(0.2*registers[0]);
		printf("Multiplication done by ALU: S0:0,S1:1 (10)\n");
		registers[5]=(0.9*registers[5]);
		printf("Multiplication done by ALU: S0:0,S1:1 (10)\n");
		registers[5]=rSPD*registers[5];
		printf("Multiplication done by ALU: S0:0,S1:1 (10)\n");
		registers[0]=registers[5]+registers[0];
		printf("Addition done by ALU: S0:0,S1:0 (00)\n");
		registers[0]=3.5+registers[0];
		printf("Addition done by ALU: S0:0,S1:0 (00)\n");
				
		if(registers[0]==0)
			flag[2]=1;
		else
			flag[2]=0;
		if(registers[0]<0)
			flag[1]=1;
		else
			flag[1]=0;
		if(registers[0]>0)
			flag[0]=1;
		else
			flag[0]=0;
		rOUT=registers[0];
	}
	
}

void calmet(int ind1){
	if(ind1==0){
		registers[1]=registers[ind1];
		registers[1]=registers[1]/3.5;
		
		printf("Division done by ALU: S0:1,S1:1 (11)\n");
		if(registers[1]==0)
			flag[2]=1;
		else
			flag[2]=0;
		if(registers[1]<0)
			flag[1]=1;
		else
			flag[1]=0;
		if(registers[1]>0)
			flag[0]=1;
		else
			flag[0]=0;
		rOUT=registers[1];
	
	}
	else
		printf("error\n");	

}

void caloburnt(int ind1){
	if(ind1==1){
		registers[2]=registers[ind1];
		registers[2]=registers[2]*rWGT;
		printf("Multiplication done by ALU: S0:0,S1:1 (10)\n");
		registers[2]=registers[2]*3.5;
		printf("Multiplication done by ALU: S0:0,S1:1 (10)\n");
		registers[2]=registers[2]*rTME;
		printf("Multiplication done by ALU: S0:0,S1:1 (10)\n");
		registers[2]=registers[2]/200;
		printf("Division done by ALU: S0:1,S1:1 (11)\n");
		
		if(registers[2]==0)
			flag[2]=1;
		else
			flag[2]=0;
		if(registers[2]<0)
			flag[1]=1;
		else
			flag[1]=0;
		if(registers[2]>0)
			flag[0]=1;
		else
			flag[0]=0;
		rOUT=registers[2];
	}
	else
		printf("error\n");
}

void cspdinc(int ind1){
	if(ind1==10){
		rSPD=rSPD+1;
		printf("Addition done by ALU: S0:0,S1:0 (00)\n");
		if(rSPD<0){
			flag[1]=1;
			printf("spped in negative error\n");
		}
		else
			flag[1]=0;
		if(rSPD==0)
			flag[2]=1;
		else
			flag[2]=0;
		if(rSPD>0)
			flag[0]=1;
		else
			flag[0]=0;
		
	}
	else
		printf("error\n");

}

void cspddec(int ind1){
	if(ind1==10){
		rSPD=rSPD-1;
		printf("Subtraction done by ALU: S0:1,S1:0 (00)\n");
		if(rSPD<0){
			flag[1]=1;
			printf("spped in negative error\n");
		}
		else
			flag[1]=0;
		if(rSPD==0)
			flag[2]=1;
		else
			flag[2]=0;
		if(rSPD>0)
			flag[0]=1;
		else
			flag[0]=0;
		
	}
	else
		printf("error\n");

}

int bintodec(char c[])
{
	
	 int val = 0;
     
    while (*c != '\0')
        val = 2 * val + (*c++ - '0');
    return val;
}

void print_reg(){
		printf("rOUT: %.2f\n",rOUT);
		printf("rSPD: %d\n",rSPD);
		printf("rTME: %d\n",rTME);
		printf("rWGT: %d\n",rWGT);
		printf("rGRD: %d\n",rGRD);		
		printf("program counter: %d\n",pc+1);
		printf("overflow flag: %d\n",flag[3]);
		printf("negative flag: %d\n",flag[1]);
		printf("positive flag: %d\n",flag[0]);
		printf("zero flag: %d\n",flag[2]);
		for(i=0;i<7;i++){
			printf("r%d:  %0.2f\n",i,registers[i]);
		}
		printf("\n");	
}



