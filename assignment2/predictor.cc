#include "predictor.h"

/////////////////////////////////////////////////////////////
// 2bitsat
/////////////////////////////////////////////////////////////
//static int predictor_2bit;//2bit saturating counter predictor
static int prediction_buffer[4096];
void InitPredictor_2bitsat() {

//predictor_2bit=1;
	for (int i=0; i<4096; i++)
		prediction_buffer[i]=1;
}

bool GetPrediction_2bitsat(UINT32 PC) {
	unsigned int index= PC%4096;
	if(prediction_buffer[index]>1)
		return TAKEN;
	else if(prediction_buffer[index]<2)
		return NOT_TAKEN;
	return TAKEN;
}

void UpdatePredictor_2bitsat(UINT32 PC, bool resolveDir, bool predDir, UINT32 branchTarget) {
	unsigned int index= PC%4096;
	if(resolveDir)
		{
			if(prediction_buffer[index]==3)
				return;
			else prediction_buffer[index]++;
		}
	else 
		{
			if(prediction_buffer[index]==0)
				return;
			else
				prediction_buffer[index]--;
		}
}

/////////////////////////////////////////////////////////////
// 2level
/////////////////////////////////////////////////////////////

static u_int8_t BHT[512];
static int * PHT[8];
static int PHT1[64];
static int PHT2[64];
static int PHT3[64];
static int PHT4[64];
static int PHT5[64];
static int PHT6[64];
static int PHT7[64];
static int PHT8[64];

void InitPredictor_2level() {
	//int index1=PC%4096;
	//int index_BHT=index1/8;
	//int index_PHT=index1%8;
	for (int i=0;i<64;i++)
	{
		PHT1[i]=1;
		PHT2[i]=1;
		PHT3[i]=1;
		PHT4[i]=1;
		PHT5[i]=1;
		PHT6[i]=1;
		PHT7[i]=1;
		PHT8[i]=1;		
	}
	PHT[0]=PHT1;
	PHT[1]=PHT2;
	PHT[2]=PHT3;
	PHT[3]=PHT4;
	PHT[4]=PHT5;
	PHT[5]=PHT6;
	PHT[6]=PHT7;
	PHT[7]=PHT8;

}

bool GetPrediction_2level(UINT32 PC) {
	unsigned int index1=PC%4096;
	unsigned int index_BHT=index1/8;
	unsigned int index_PHT1=index1%8;
	unsigned int index_PHT2=BHT[index_BHT]%64;
	unsigned int prediction=PHT[index_PHT1][index_PHT2];
	if(prediction>1)
		return TAKEN;
	else if(prediction<2)
		return NOT_TAKEN;

}

void UpdatePredictor_2level(UINT32 PC, bool resolveDir, bool predDir, UINT32 branchTarget) {
	int index1=PC%4096;
	int index_BHT=index1/8;
	int index_PHT1=index1%8;
	int index_PHT2=BHT[index_BHT]%64;
	//int prediction=PHT[index_PHT1][index_PHT2];
	BHT[index_BHT]=BHT[index_BHT]<<1;
	if(resolveDir)
	{
		BHT[index_BHT]+=0x1;		
		//PHT[index_PHT1][index_PHT2];
		if(PHT[index_PHT1][index_PHT2]==3)
				return;
		else PHT[index_PHT1][index_PHT2]++;
	}
	else 
		{
			if(PHT[index_PHT1][index_PHT2]==0)
				return;
			else
				PHT[index_PHT1][index_PHT2]--;
		}

}

/////////////////////////////////////////////////////////////
// openend
/////////////////////////////////////////////////////////////

//TAGE predictor
int provider;
int cnt=0;//count number of branch instructions 
int base_predictor[4096];
int T1_predict[2048];
int T1_tag[2048];
int T1_u[2048];
int T2_predict[2048];
int T2_tag[2048];
int T2_u[2048];
int T3_predict[2048];
int T3_tag[2048];
int T3_u[2048];
int T4_predict[2048];
int T4_tag[2048];
int T4_u[2048]; 
unsigned int BT1;//global branch history register 32bits
unsigned int BT2;
unsigned int BT3;
unsigned int BT4;

//bitset<100>GHR;
#define WEEKLYNOTTAKEN 7
#define STRONGLYTAKEN 15
#define WEEKLYTAKEN 8

void InitPredictor_openend() {
for(int i=0;i<4096;i++)
{
base_predictor[i]=WEEKLYNOTTAKEN;
}

BT1=0;
BT2=0;
BT3=0;
BT4=0;

for(int i=0;i<2048;i++)
{
T1_predict[i]=WEEKLYNOTTAKEN;
T2_predict[i]=WEEKLYNOTTAKEN;
T3_predict[i]=WEEKLYNOTTAKEN;
T4_predict[i]=WEEKLYNOTTAKEN;
T1_u[i]=0;
T2_u[i]=0;
T3_u[i]=0;
T4_u[i]=0;
}

}

bool GetPrediction_openend(UINT32 PC) {

cnt++;

u_int8_t tag_t1;
u_int8_t tag_t2;
u_int8_t tag_t3;
u_int8_t tag_t4;
int index_t1;
int index_t2;
int index_t3;
int index_t4;
u_int8_t pc_8;
u_int16_t pc_11;
int base_index;
int folded_bt1;
int folded_bt2;
int folded_bt3;


//folded fucntions
pc_8=(PC^(PC>>8)^(PC>>16)^(PC>>24))&((1<<8)-1);
folded_bt1=(BT1^(BT1>>8)^(BT1>>16)^(BT1>>24))&((1<<8)-1);
folded_bt2=(BT2^(BT2>>8)^(BT2>>16)^(BT2>>24))&((1<<8)-1);
folded_bt3=(BT3^(BT3>>8)^(BT3>>16)^(BT3>>24))&((1<<8)-1);
pc_11=(PC^(PC>>11)^(PC>>22))&((1<<11)-1);
//hash functions for tags and index
tag_t1=pc_8^(BT1&((1<<5)-1));
tag_t2=(pc_8^BT1^((BT1>>8)&((1<<6)-1)))&((1<<8)-1);
tag_t3=pc_8^folded_bt1^(BT2&((1<<5)-1));
tag_t4=pc_8^folded_bt1^folded_bt2^folded_bt3^(BT4&((1<<4)-1));
index_t1=(pc_11^(BT1&((1<<5)-1)))&((1<<11)-1);
index_t2=(pc_11^BT1^((BT1>>11)&((1<<6)-1)))&((1<<11)-1);
index_t3=(pc_11^BT1^(BT1>>11)^(BT1>>22)^((BT2<<10)&(1<<10))^((BT2>>1)&((1<<5)-1)))&((1<<11)-1);
index_t4=(pc_11^BT1^(BT1>>11)^(BT1>>22)^((BT2<<10)&(1<<10))^(BT2>>1)^(BT2>>12)^(BT2>>23)^((BT3<<9)&(3<<9))^(BT3>>2)^(BT3>>13)^(BT3>>24)^((BT4<<8)&(7<<8))^((BT4>>3)&((1<<4)-1)))&((1<<11)-1);

//get prediction
base_index=PC%4096;
if (T4_tag[index_t4]==tag_t4)
{
	provider=4;
	if(T4_predict[index_t4]>WEEKLYNOTTAKEN)
		return TAKEN;
	else return NOT_TAKEN;
}
else if (T3_tag[index_t3]==tag_t3)
{
	provider=3;
	if(T3_predict[index_t3]>WEEKLYNOTTAKEN)
		return TAKEN;
	else return NOT_TAKEN;
}
else if (T2_tag[index_t2]==tag_t2)
{	
	provider=2;
	if(T2_predict[index_t2]>WEEKLYNOTTAKEN)
		return TAKEN;
	else return NOT_TAKEN;
}
else if (T1_tag[index_t1]==tag_t1)
{
	provider=1;
	if(T1_predict[index_t1]>WEEKLYNOTTAKEN)
		return TAKEN;
	else return NOT_TAKEN;
}
else 
{
	provider=0;
	if(base_predictor[base_index]>WEEKLYNOTTAKEN)
		return TAKEN;
	else return NOT_TAKEN;
}
}



void UpdatePredictor_openend(UINT32 PC, bool resolveDir, bool predDir, UINT32 branchTarget) {
u_int8_t tag_t1;
u_int8_t tag_t2;
u_int8_t tag_t3;
u_int8_t tag_t4;
int index_t1;
int index_t2;
int index_t3;
int index_t4;
u_int8_t pc_8;
u_int16_t pc_11;
int base_index;
int folded_bt1;
int folded_bt2;
int folded_bt3;


//folded fucntions
//pc_8=PC&((1<<8)-1);
pc_8=(PC^(PC>>8)^(PC>>16)^(PC>>24))&((1<<8)-1);
folded_bt1=(BT1^(BT1>>8)^(BT1>>16)^(BT1>>24))&((1<<8)-1);
folded_bt2=(BT2^(BT2>>8)^(BT2>>16)^(BT2>>24))&((1<<8)-1);
folded_bt3=(BT3^(BT3>>8)^(BT3>>16)^(BT3>>24))&((1<<8)-1);
pc_11=(PC^(PC>>11)^(PC>>22))&((1<<11)-1);
//pc_11=PC&((1<<11)-1);

//tags
tag_t1=pc_8^(BT1&((1<<5)-1));
tag_t2=(pc_8^BT1^((BT1>>8)&((1<<6)-1)))&((1<<8)-1);
tag_t3=pc_8^folded_bt1^(BT2&((1<<5)-1));
tag_t4=pc_8^folded_bt1^folded_bt2^folded_bt3^(BT4&((1<<4)-1));
index_t1=(pc_11^(BT1&((1<<5)-1)))&((1<<11)-1);
index_t2=(pc_11^BT1^((BT1>>11)&((1<<6)-1)))&((1<<11)-1);
index_t3=(pc_11^BT1^(BT1>>11)^(BT1>>22)^((BT2<<10)&(1<<10))^((BT2>>1)&((1<<5)-1)))&((1<<11)-1);
index_t4=(pc_11^BT1^(BT1>>11)^(BT1>>22)^((BT2<<10)&(1<<10))^(BT2>>1)^(BT2>>12)^(BT2>>23)^((BT3<<9)&(3<<9))^(BT3>>2)^(BT3>>13)^(BT3>>24)^((BT4<<8)&(7<<8))^((BT4>>3)&((1<<4)-1)))&((1<<11)-1);

base_index=PC%4096;


//update branch history register

BT4=BT4<<1;
BT4=BT4+(BT3>>31);
BT3=BT3<<1;
BT3=BT3+(BT2>>31);
BT2=BT2<<1;
BT2=BT2+(BT1>>31);
BT1=BT1<<1;
BT1=BT1+resolveDir;

int * tagTable[5];
tagTable[1]=T1_tag;
tagTable[2]=T2_tag;
tagTable[3]=T3_tag;
tagTable[4]=T4_tag;
int altpred;

int * prediction[5];
prediction[0]=base_predictor;
prediction[1]=T1_predict;
prediction[2]=T2_predict;
prediction[3]=T3_predict;
prediction[4]=T4_predict;

int index[5];
index[0]=base_index;
index[1]=index_t1;
index[2]=index_t2;
index[3]=index_t3;
index[4]=index_t4;

int tag[5];
tag[1]=tag_t1;
tag[2]=tag_t2;
tag[3]=tag_t3;
tag[4]=tag_t4;

int *u[5];
u[1]=T1_u;
u[2]=T2_u;
u[3]=T3_u;
u[4]=T4_u;

//update u bits
altpred=0;
if(provider>0)
	{
		for (int i=provider-1;i>0;i--)
		{
			if (tagTable[i][index[i]]==tag[i])
				{
					altpred=i;
					break;
				}
	
		}
		bool altprediction;
		if(prediction[altpred][index[altpred]]>WEEKLYNOTTAKEN)
			altprediction= TAKEN;
		else altprediction= NOT_TAKEN;
	
		/*if (cnt==256000)
		{
			for (int i=0;i<2048;i++)
			{
				if(T1_u[i]>1)
				T1_u[i]=T1_u[i]-2;	
				if(T2_u[i]>1)
				T2_u[i]=T2_u[i]-2;	
				if(T3_u[i]>1)
				T3_u[i]=T3_u[i]-2;	
				if(T4_u[i]>1)
				T4_u[i]=T4_u[i]-2;			
			}
			cnt=0;
		}*/
		if(predDir!=altprediction)
			{
				if(resolveDir==predDir)
				{
					if(u[provider][index[provider]]<3)
						u[provider][index[provider]]++;
				}				
				else
				{
					if(u[provider][index[provider]]>0)
						u[provider][index[provider]]--;
				}			
			}
	

	}
//update predictor if prediction is correct
if(resolveDir==predDir)
{
	if(resolveDir)
                {
                        if(prediction[provider][index[provider]]<STRONGLYTAKEN)
                                prediction[provider][index[provider]]++;
                }
    else
                {
                        if(prediction[provider][index[provider]]>0)
                               prediction[provider][index[provider]]--;
                }
		
}
//if prediction is wrong, update predictor and try to add new entries
else
{
	if(resolveDir)
	   {
                        if(prediction[provider][index[provider]]<STRONGLYTAKEN)
                                prediction[provider][index[provider]]++;
       }
   	else
       {
                        if(prediction[provider][index[provider]]>0)
                               prediction[provider][index[provider]]--;
       }
	int allocated=0;
	if (provider<4)
	{
		for (int i=provider+1;i<5;i++)
			{
				if(u[i][index[i]]==0)
					{
						tagTable[i][index[i]]=tag[i];
						//if(resolveDir)
						prediction[i][index[i]]=WEEKLYNOTTAKEN;
						//else
						//prediction[i][index[i]]=WEEKLYNOTTAKEN;
						//u[i][index[i]]=1;
						allocated=1;
						break;
					}			
			}
		if (allocated==0)
			{
				for (int i=provider+1;i<5;i++)
				{
					u[i][index[i]]--;
				}
			}
	}
	
}
}