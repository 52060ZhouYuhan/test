#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "tool.h"

#define MAXMINE 100
#define ACCRURACY 4

char* division(char* m,char* n,int accruracy);

void main(){
	char m[MAXMINE];
	char n[MAXMINE];
	while(1){ 
		printf("a =  \n");
		scanf("%s",m);
		printf("b =  \n");
		scanf("%s",n);
	
		printf("subtraction = %s\n", subtraction(m,n));
		char* result = division(m,n,ACCRURACY);
		printf("result = %s \n", result);
		if(result == NULL)
			free(result);
	} 
	
}
// reserve 0.00 accruracy = 2 
char* division(char* a,char* b,int accruracy){ // add zero : accruracy + 1
	int a_length = strlen(a);
	int b_length = strlen(b);

	if(b[0] == '0'){
		printf("error input\n");
		return NULL;
	}
	if(a[0] == '0'){
		char* result_temp = malloc(2);
		result_temp[0] = '0';
		result_temp[1] = '\0';
		return result_temp; 	
	}

	char* first = (char*)malloc(a_length + 1);
	char* second = (char*)malloc(b_length + 1);
	
	int a_dot = 0 , b_dot = 0;
	int i = 0 , count_a = 0, count_b = 0;
	for(i = 0;i<a_length;i++){
		if(a[i] == '.'){
			a_dot = a_length - i - 1;
			continue;
		}
		if(count_a > 0){
			first[count_a] = a[i];
			count_a++;		
		}
		else{
			if(a[i] > '0'){
				first[count_a] = a[i];
				count_a++;
			}
		}		
	}
	first[count_a] = '\0';

	for(i = 0;i<b_length;i++){
		if(b[i] == '.'){
			b_dot = b_length - i - 1;
			continue;
		}
		if(count_b > 0){
			second[count_b] = b[i];
			count_b++;		
		}
		else{
			if(b[i] > '0'){
				second[count_b] = b[i];
				count_b++;
			}
		}			
	}
	second[count_b] = '\0';
	printf("first = %s , second = %s , a_dot = %d , b_dot = %d \n", first , second, a_dot, b_dot);

	// both integer process
	int add_0_to_a = 0 , add_0_to_b = 0;
	int option = b_dot - a_dot;
	if(option < 0){
		add_0_to_b = -option; // both integer , b add 0
		memset(second + count_b,'0',add_0_to_b);
		second[count_b+add_0_to_b] = '\0';	
	}else{
		add_0_to_a = option; // both integer, a add 0
		memset(first + count_a,'0',add_0_to_a);
		first[count_a+add_0_to_a] = '\0';
	}
	
	int inta_length = count_a + add_0_to_a;
	int intb_length = count_b + add_0_to_b;
	int diff_length = inta_length - intb_length;
	printf("inta_length = %d , intb_length = %d\n", inta_length , intb_length);	


	printf("Integer :: -- first = %s , second = %s \n", first , second);
	
// ------------------------------------------- equalent ---------------------------------- 

	// ---  abs(a) > abs(b)
	
	int count_0_a = 0;

	if(diff_length < 0){
		count_0_a = -diff_length + 1;
	}else{
		count_0_a = 0;
	}

	printf("count_0_a = %d\n",count_0_a);
	
	int calculate_length = inta_length + count_0_a + accruracy + 1 + 1;
	char* temp_first = (char*)malloc(calculate_length);
	char* temp_second = (char*)malloc(calculate_length);

	memset(temp_first,'0',calculate_length);
	memset(temp_second,'0',calculate_length);

	memcpy(temp_first,first,inta_length);
	temp_first[calculate_length - 1] = '\0';
	memcpy(temp_second,second,intb_length);
	temp_second[calculate_length - 2] = '\0';

	printf("temp_first = %s, temp_second = %s\n",temp_first,temp_second);


	//subtraction();
	int quotient = 0;
	int for_is_end = 0;

	char pQuotient[100];
	int  q_index = 0;
	int  numberbit_b_add = strlen(temp_second) - intb_length;
	int  more_zero_in_for_is_end = 0;
	char* temp_1 = temp_first;
	char* temp_2 = NULL;
	char* temp_swap = NULL;
	int j = 0;
	for(j = 0 ; j < numberbit_b_add + 1 ; j++){
		if(for_is_end == 1)
			break;
		temp_second[calculate_length - 2 - j] = '\0';
		for(i=0; ;i++){
			temp_2 = subtraction(temp_1,temp_second);

			//printf("i = %d , temp_1 = %s , temp_second = %s , temp_2 = %s \n", i, temp_1, temp_second,temp_2);
		
			if(temp_2[0] == '-'){
				quotient = i;
				int temp = i;
				while(temp > 9){
					pQuotient[q_index] = temp / 10 + '0';
					temp = temp - (temp/10) * 10;
					q_index++;
				}
				pQuotient[q_index] = temp + '0';
				q_index++;

				free(temp_2);
				break;
			}else if(temp_2[0] == '0'){
				//printf("temp_2[0] == '0' !!! \n");
				quotient = i + 1;
				int temp = i + 1;

				while(temp > 9){
					pQuotient[q_index] = temp / 10 + '0';
					temp = temp - (temp/10) * 10;
					q_index++;
				}
				pQuotient[q_index] = temp + '0';
				q_index++;

				free(temp_2);
				
				more_zero_in_for_is_end = strlen(temp_second) - strlen(second); // note that
				for_is_end = 1;
				break;
			}else{
				if(temp_swap != NULL){
					free(temp_swap);
					temp_swap = NULL;
				}
				temp_1 = temp_2;
				temp_swap = temp_2;
			}		
		}
		printf("quotient = %d \n" , quotient);
	}	
	pQuotient[q_index] = '\0';
	printf("pQuotient = %s\n",pQuotient);
	

	char* result = (char*)malloc(32);
	memset(result,'0',32);
	int length_pQuotient = strlen(pQuotient);
	int count_number = 0;
	int dot_number = accruracy + count_0_a + 1 - more_zero_in_for_is_end; // insert postion  
	q_index = 0; 
	printf("dot_number = %d , length_pQuotient= %d ,for_is_end = %d\n", dot_number, length_pQuotient, for_is_end);

	if(dot_number >= length_pQuotient){ //0.xxxxx
		int number_zero = dot_number - length_pQuotient ;

		if(number_zero > 4){
			printf("accruracy is not enough !\n");
			return NULL;
		}		


		result[0] = '0';
		result[1] = '.';
		memcpy(result + number_zero + 2, pQuotient, length_pQuotient + 1);
		if(number_zero + length_pQuotient > accruracy){
			if(result[1 + accruracy + 1] > '4'){
				result[1 + accruracy] = result[1 + accruracy] + 1;
			}
			result[2 + accruracy] = '\0';

		}

	}else if(dot_number < length_pQuotient && dot_number > 0){ //xxx.xx
		int dot_pos = length_pQuotient - dot_number;
		int counter_temp = 0;
		for(i = 0; i < length_pQuotient + 1; i++){
			if(i == dot_pos){
				result[i] = '.';
			}
			else{
				result[i] = pQuotient[counter_temp];
				counter_temp++;
			}
		}
		result[i] = '\0';

		if(dot_number > 4){
			if(result[dot_pos + 5] > '4')
				result[dot_pos + 4] = result[dot_pos + 4] + 1;
			result[dot_pos + 5] = '\0';
		}
		
	}else{                                            // xxx000
		memcpy(result,pQuotient,length_pQuotient);
		if(dot_number < 0)
			result[length_pQuotient - dot_number] = '\0';
		else
			result[length_pQuotient] = '\0';
	}


	//printf("\n result = %s \n", result);
		


	free(first);
	free(second);
	
	free(temp_first);
	free(temp_second);
	return result;

}








