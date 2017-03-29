/*
COA Project Part B
Conversion of assembly code to Binary code
GROUP Members
1 Khushboo Baheti 	15ucs168
2 Smriti Jha		15ucs142
3 Shreya Rajput		15ucs134
4 Sakshi Goyal		15ucs116 
*/
#include<stdio.h>
#include<string.h>

int binaryNumber[8];
int binaryline[12];
int file_open=0;

main(){ 
        FILE *fp0,*fp1,*fp2,*fp,*fp3,*fp4;
	int i,j,quotient,l,k,lineno,ch2,ch3,ch0,h;
	
        char filename[20],oneword[100],ch1,ch4,ch5,oneword2[100],onewordjmp[4],onewordlab[12],oneword3[50];
        printf("please enter the file name\n");
        scanf("%s",filename);  
	
        fp0=fopen(filename,"r");
	if(fp0==NULL){
		printf("\n..............invalid file.................\n");//incase an invalid file name is given
		exit(-1);
	}
       					       
	lineno=1;
	int p=0;
        ch2=fgetc(fp0);							       
	while(ch2!=EOF){
		
 	 	 if(ch2 == '\n')
  		{
    			lineno++;
 		 }

                if(ch2=='L'){	ch0=ch2;
				ch3=fgetc(fp0);
				ch2=fgetc(fp0);
				
				if(ch2==':'){
				
				if(file_open==0)//if symbol table file is not already open so opening in "write" mode
				{
					fp=fopen("symbol_table.txt","w");//Symbol table in which opcode and ILC value for label is stored.
					file_open=1;			 //format for symbol table is
				}					 //label 	ILC	
				else
					fp=fopen("symbol_table.txt","a");//if already opened then appending it.
				fprintf(fp,"%c",ch0);
				fprintf(fp,"%c",ch3);
				fprintf(fp,"%s","\t\t\t");
				lineno=lineno-1;
				fprintf(fp,"%d",lineno+1);
				fprintf(fp,"%s","\n");
				fclose(fp);}
				else continue;
			
			}
			
			ch2=fgetc(fp0);	
	        }
	        fclose(fp0);
        fp0=fopen(filename,"r");
	fp1=fopen("finaloutput.txt","w");
	ch1=fscanf(fp0,"%s",oneword);
	while(ch1!=EOF){
		fp2=fopen("register.txt","r");
		i=atoi(oneword); 
		ch4=fscanf(fp2,"%s",oneword2);
		
		if(strcmp(oneword,"0")==0) //if immediate const is 0 directly place 00000000 in output file
		{	
			
			fprintf(fp1,"%s","00000000");
			fclose(fp2);
		}
		else if(i>0 && i<256) //if immediate const lies between 0-256 . then convert it in binary
		{
			j=7;
			quotient = i;
			for(l=0;l<8;l++)
				binaryNumber[l]=0;
			while(quotient!=0)	//piece of code for converting immediate constant into binary.
			{
				binaryNumber[j]= quotient % 2;
				quotient = quotient / 2;
				j--;
			}
			k=0;
			//fprintf(fp1,"\n%s","");
			while(k!=8) //placing the binary equivalent of immediate constant in file
			{
				fprintf(fp1,"%d",binaryNumber[k]);
				k++;
			}	
			fclose(fp2);
						
		}
		else{	
			
			while(ch4!=EOF) 
			{	
				
				if(strcmp(oneword,oneword2)==0 ) //as soon as we found opcode in registers file. move pointer by one and place 									its equivalent binary
				{
					
					ch4=fscanf(fp2,"%s",oneword2);
					if(strlen(oneword2)>=4 && oneword[0]!='r' && strcmp(oneword2,"0100")!=0 && oneword[0]!='L')
					{
						fprintf(fp1,"\n%s",oneword2); 
						
						
					}
					if(strcmp(oneword2,"0100")==0){
						fprintf(fp1,"\n%s",oneword2); 
						ch1=fscanf(fp0,"%s",oneword);
					}
					if(oneword[2]==':' && oneword[0]=='L'){
						fp=fopen("symbol_table.txt","r");
						ch5=fscanf(fp,"%s",oneword3);
						while(ch5!=EOF){
							if(oneword[0]==oneword3[0] && oneword[1]==oneword3[1]){
								ch5=fscanf(fp,"%s",oneword3);
								 h=atoi(oneword3);
								j=11;
								quotient = h;
								for(l=0;l<12;l++)
									binaryline[l]=0;
								while(quotient!=0)
								{
									binaryline[j]= quotient % 2;
									quotient = quotient / 2;
									j--;
								}
								k=0;
								fprintf(fp1,"%s","\n");
								while(k!=12)
								{
									fprintf(fp1,"%d",binaryline[k]);
									k++;
								}
								fclose(fp);
							}
							else{
								ch5=fscanf(fp,"%s",oneword3);
								ch5=fscanf(fp,"%s",oneword3);
							}
						}
						
					}
					else if(oneword[0]=='r')
					{
						fprintf(fp1,"%s",oneword2); //else if r0 ,etc us found no need to put \n
					}
					if(oneword[0]=='L' && oneword[2]!=':'){
						fp=fopen("symbol_table.txt","r");
						ch5=fscanf(fp,"%s",oneword3);
						while(ch5!=EOF){
							if(oneword[0]==oneword3[0] && oneword[1]==oneword3[1]){
								ch5=fscanf(fp,"%s",oneword3);
								 h=atoi(oneword3);
								j=11;
								quotient = h;
								for(l=0;l<12;l++)
									binaryline[l]=0;
								while(quotient!=0)
								{
									binaryline[j]= quotient % 2;
									quotient = quotient / 2;
									j--;
								}
								k=0;
								
								while(k!=12)
								{
									fprintf(fp1,"%d",binaryline[k]);
									k++;
								}
								fclose(fp);
							}
							else{
								ch5=fscanf(fp,"%s",oneword3);
								ch5=fscanf(fp,"%s",oneword3);
							}
						}
					}
					
					fclose(fp2);
				}
				else
				{	
					
					ch4=fscanf(fp2,"%s",oneword2); //if the matching opcode is not found. increment the pointer by 2
					ch4=fscanf(fp2,"%s",oneword2);
					
				}
					
				
			}
					
	
		}
		
		
		ch1=fscanf(fp0,"%s",oneword);
	
	}	
		
}
