void microwave_Init(void){
	
}
void Time_Display(char time[]){
	int i,j;
	while (1){
	for(i=60;i>=0;i--){ 
		LCD_Array(time);
		i--;
				Systick_Wait_ms(1000);
		if(time[4]==0x30){
			time[4]=0x39;
			time[3]--;
		}
		else {
			time[4]--;
		}
		  
		    LCD_Clear_Display();
			}
	if(time[0]==0x30&&time[1]==0x30){break;}
	if(time[1]==0x30){
			time[1]=0x39;
			time[2]--;
		}
		else {
			time[1]--;
		}
			
		
}}

void Cook_Time(){
	char time[]={'0','0',':','0','0'};
	int i ,j ;
	LCD_Clear_Display();
	for (i=4;i>=0;i++){
	if (i==2){
		continue ;
	}
	time[4]=KeyScan();
	LCD_Array(time);
	for(j=4-i;j>=0;j--){
		if (j==2){
		time[0]=time[1];}
		if (j==1){
			time[1]=time[3];
		}
		time[3-j]=time[4-j];
	}
	while(SW2_Input()==1);
	if((time[0]>3)||(time[1]==0)||(time[0]==3&&time[1]>0)){
		LCD_String("Invalid value, please enter a value between 1 and 30");
		Cook_Time();
	}
	Time_Display(time);
	
}


}