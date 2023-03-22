#include <stdio.h>
#include <stdlib.h>
#include <string.h>
struct machine_info
{
	int memory_num; //内存大小
	int data_bytes;	//数据段大小，从0开始
	char start_address[20];	//第一条指令的地址
	char instruct_file_name[20];//指令文件名称
};
extern struct machine_info *pmi;
extern char * memory;//内存
extern char R0,R1,R2,R3;//寄存器
extern unsigned int PC;
void ExecuteAdd(char source[],char dest[],int *result)
{
	char op;
	if(0==strcmp(source,"R0"))
		op=R0;
	else if(0==strcmp(source,"R1"))
		op=R1;
	else if(0==strcmp(source,"R2"))
		op=R2;
	else if(0==strcmp(source,"R3"))
		op=R3;
	else 
		*result=-1;
	if(0==strcmp(dest,"R0\n"))
		R0+=op;
	else if(0==strcmp(dest,"R1\n"))
		R1+=op;
	else if(0==strcmp(dest,"R2\n"))
		R2+=op;
	else if(0==strcmp(dest,"R3\n"))
		R3+=op;
	else 
		*result=-1;
	
}
void ExecuteSub(char source[],char dest[],int *result)
{
	char op;
	if(0==strcmp(source,"R0"))
		op=R0;
	else if(0==strcmp(source,"R1"))
		op=R1;
	else if(0==strcmp(source,"R2"))
		op=R2;
	else 
		*result=-1;
	if(0==strcmp(dest,"R0\n"))
	{
		R0-=op;
		if(R0>0) R3=1;
		else if(R0<0) R3=-1;
		else R3=0;
	}
	else if(0==strcmp(dest,"R1\n"))
	{
		R1-=op;
		if(R1>0) R3=1;
		else if(R1<0) R3=-1;
		else R3=0;
	}
	else if(0==strcmp(dest,"R2\n"))
	{
		R2-=op;
		if(R2>0) R3=1;
		else if(R2<0) R3=-1;
		else R3=0;
	}
	else 
		*result=-1;
	
	
}
void ExecuteMov(char source[],char dest[],int *result)
{
	char op;
	op=atoi(source);
	if(0==strcmp(dest,"R0\n"))
		R0=op;
	else if(0==strcmp(dest,"R1\n"))
		R1=op;
	else if(0==strcmp(dest,"R2\n"))
		R2=op;
	else if(0==strcmp(dest,"R3\n"))
		R3=op;
	else 
		*result=-1;
	
	
}
void ExecuteCopy(char source[],char dest[],int *result)
{
	char op;
	char buf[9];
	int loop;
	int i;
	if(0==strcmp(source,"R0"))
		op=R0;
	else if(0==strcmp(source,"R1"))
		op=R1;
	else if(0==strcmp(source,"R2"))
		op=R2;
	else if(0==strcmp(source,"R3"))
		op=R3;
	else
	{
		i=BCharsToInt(pmi->memory_num,source); 
//		printf("%d\n",i);
		strncpy(buf,memory+(i-1)*20,8);
		buf[8]='\0';
		op=BCharsToInt(8,buf);
//		printf("%s,%s,%s,%d\n",source,memory-20,buf,op);
	}
//	printf("%d\n",op);
	
	if(0==strcmp(dest,"R0\n"))
		R0=op;
	else if(0==strcmp(dest,"R1\n"))
		R1=op;
	else if(0==strcmp(dest,"R2\n"))
		R2=op;
	else if(0==strcmp(dest,"R3\n"))
		R3=op;
	else 
	{
		IntToBchars(op,8,buf);
		i=BCharsToInt(pmi->memory_num,dest);
		for(loop=0;loop<8;loop++)
			memory[(i-1)*20+loop]=buf[loop];
		memory[(i-1)*20+8]='\n';
		memory[(i-1)*20+9]='\0';
	}
		
}
void ExecuteOutput(char source[],int *result)
{
	char op;
	*result=0;
	if(0==strcmp(source,"R0\n"))
		op=R0;
	else if(0==strcmp(source,"R1\n"))
		op=R1;
	else if(0==strcmp(source,"R2\n"))
		op=R2;
	else if(0==strcmp(source,"R3\n"))
		op=R3;
	else 
		*result=-1;	
	if(*result!=-1)
		printf("%d\n",op);

}
void ExecuteInstruction(int * result)
{
	//取值
	char instruction_buffer[20];
	char *revbuf[8] = {0};
	int num;
	int op1,op2,op3;
	int i;
	strncpy(instruction_buffer,memory+(PC-1)*20,20);
//	printf("%s\n",instruction_buffer);
	switch(instruction_buffer[0])
	{
		case '0':
			*result=0;
			PC++;
			break;		//停机
		case '1':
			scanf("%d",&i);
			R0=(unsigned char)i;
			safe_flush(stdin);
			*result=1;
			PC++;
			break;
		case '2':		//加法
			split(instruction_buffer," ",revbuf,&num);
			if(3>num)
				*result=-1;	//出错
			else
				ExecuteAdd(revbuf[1],revbuf[2],result);
			if(*result!=-1) *result=2;
			PC++;
			break;
		case '3':		//减法
			split(instruction_buffer," ",revbuf,&num);
			if(3>num)
				*result=-1;	//出错
			else
				ExecuteSub(revbuf[1],revbuf[2],result);
			if(*result!=-1) *result=3;			
			PC++;
			break;	
		case '4':		//赋值
			split(instruction_buffer," ",revbuf,&num);
			if(3>num)
				*result=-1;	//出错
			else
				ExecuteMov(revbuf[1],revbuf[2],result);
			if(*result!=-1) *result=4;			
			PC++;
			break;
		case '5':		//拷贝
			split(instruction_buffer," ",revbuf,&num);
//			printf("%d\n",num);
			if(3>num)
				*result=-1;	//出错
			else
				ExecuteCopy(revbuf[1],revbuf[2],result);
			if(*result!=-1) *result=5;			
			PC++;
			break;
		case '6':		//判断跳转
			split(instruction_buffer," ",revbuf,&num);
			if(2!=num)
				*result=-1;	//出错
			else
			{
				i=atoi(revbuf[1]);
				if(R3==1) PC+=i;
				else PC++;
			};
			if(*result!=-1) *result=6;			
//			PC++;
			break;
		case '7':		//直接跳转
			split(instruction_buffer," ",revbuf,&num);
			if(2>num)
				*result=-1;	//出错
			else
			{
				i=atoi(revbuf[1]);
				PC+=i;
			};
			if(*result!=-1) *result=6;			
//			PC++;
			break;
		case '8':
			split(instruction_buffer," ",revbuf,&num);
			if(2>num)
				*result=-1;	//出错	
			else
				ExecuteOutput(revbuf[1],result);
			if(*result!=-1) *result=8;
//			safe_flush(stdin);
			PC++;	
			break;		
		default:
			*result=-1;	//出错
			break;
			
	}
	
}
