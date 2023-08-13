/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; Copyright (c) 2020 STMicroelectronics.
  * All rights reserved.</center></h2>
  *
  * This software component is licensed by ST under Ultimate Liberty license
  * SLA0044, the "License"; You may not use this file except in compliance with
  * the License. You may obtain a copy of the License at:
  *                             www.st.com/SLA0044
  *
  ******************************************************************************
  */
/* USER CODE END Header */
/* Includes ------------------------------------------------------------------*/
#include "main.h"
#include "adc.h"
#include "dac.h"
#include "lwip.h"
#include "usart.h"
#include "gpio.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include "tcp.h"
#include "string.h"
#include "stdbool.h"


uint16_t k=0 ,i=0,j=0,j1=0;
bool _even;
bool flag_run_loop = false;
bool flag_exit_loop = false;
uint16_t xs = 0;
uint16_t xe = 0;
uint16_t ys = 0;
uint16_t ye = 0;
uint16_t sx = 0;
uint16_t sy = 0;
uint16_t dly = 0;
uint16_t loop = 0;


/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */

/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */
#define KEYDEBOUNCE  	20
#define MAXDATALEN 		10
#define LED1_ON  			'1'
#define LED2_ON				'2'
#define LED3_ON				'3'
#define LED4_ON				'4'
#define LED1_OFF			'5'
#define LED2_OFF			'6'
#define LED3_OFF			'7'
#define LED4_OFF			'8'
#define GET_PB1				'9'
#define  tcp_listen(pcb)
/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */
void server_init				(u16_t port);
void 	server_conn_err		(void *arg, err_t err);
//err_t server_recv(void *arg, struct tcp_pcb *pcb, struct pbuf *p, err_t err);
err_t server_tcp_recv_null(void *arg, struct tcp_pcb *pcb, struct pbuf *p, err_t err);
//err_t server_tcp_accept_null(void *arg, struct tcp_pcb *pcb, err_t err);
err_t server_tcp_accept	(void *arg, struct tcp_pcb *pcb, err_t err);
char 	get_key_state			(void);
extern __IO uint32_t uwTick;

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/

/* USER CODE BEGIN PV */

#ifdef __GNUC__
  #define PUTCHAR_PROTOTYPE int __io_putchar(int ch)
  #else
  #define PUTCHAR_PROTOTYPE int fputc(int ch,FILE *f)
  #endif

  PUTCHAR_PROTOTYPE
  {//                        "SALAM"       5 100
  HAL_UART_Transmit(&huart1,(uint8_t*)&ch,1,100);

    return ch;

  }


uint8_t Hi_byte(uint16_t i );
uint8_t Lo_byte(uint16_t i );





// O/P Voltage = (Reference Voltage / Resolution) x Digital Value
void set_voltage_on_dax_X (float milivoltage)
{

	uint16_t dig_val = (uint16_t)  (milivoltage / (Reference_Voltage / Resolution));

	HAL_DAC_SetValue(&hdac, DAC_CH_X, DAC_ALIGN_12B_R, dig_val);
	printf("milivoltage=%d,dig_val=%d",milivoltage,dig_val);

}
void set_voltage_on_dax_Y (float milivoltage)
{

	uint16_t dig_val = (uint16_t)  (milivoltage / (Reference_Voltage / Resolution));

	HAL_DAC_SetValue(&hdac, DAC_CH_Y, DAC_ALIGN_12B_R, dig_val);
	printf("milivoltage=%d,dig_val=%d",milivoltage,dig_val);

}
//milivolt = (dig_val * Reference_Voltage)/Resolution = >> { Reference_Voltage=3300 , Resolution(12bit)=4096 } => milivolt = dig_val * 0.80






//-------------------------------------------------------------------------------------------
uint16_t get_adc_raw(int chanel)
{

	uint16_t digital_result=0;

	if(chanel==READ_ADC_CH_HV_PDUCL_PX)
	{

			hadc1.Init.NbrOfConversion=READ_ADC_CH_HV_PDUCL_PX;// READ PIN 31 // ADC1_IN6
			HAL_ADC_Init(&hadc1);
			HAL_ADC_Start(&hadc1);
			if(HAL_ADC_PollForConversion(&hadc1,500)== HAL_OK)
			{

			digital_result=HAL_ADC_GetValue(&hadc1);

			}
			HAL_ADC_Stop(&hadc1);


	}

	else if(chanel==READ_ADC_CH_HV_PDUCL_PY)// // READ PIN 31 // ADC1_IN7
	{

				hadc1.Init.NbrOfConversion=READ_ADC_CH_HV_PDUCL_PY;//
				HAL_ADC_Init(&hadc1);
				HAL_ADC_Start(&hadc1);
				if(HAL_ADC_PollForConversion(&hadc1,500)== HAL_OK)
				{

				digital_result=HAL_ADC_GetValue(&hadc1);

				}
				HAL_ADC_Stop(&hadc1);


	}
	else if(chanel==READ_ADC_SENS1)
	{

			hadc1.Init.NbrOfConversion=READ_ADC_SENS1;//ch2
			HAL_ADC_Init(&hadc1);
			HAL_ADC_Start(&hadc1);
			if(HAL_ADC_PollForConversion(&hadc1,500)== HAL_OK)
			{

			digital_result=HAL_ADC_GetValue(&hadc1);

			}
			HAL_ADC_Stop(&hadc1);


	}

	else  if(chanel== READ_ADC_SENS2)//
	{


			hadc1.Init.NbrOfConversion=READ_ADC_SENS2;
			HAL_ADC_Init(&hadc1);
			HAL_ADC_Start(&hadc1);
			if(HAL_ADC_PollForConversion(&hadc1,500)== HAL_OK)
			{

			digital_result=HAL_ADC_GetValue(&hadc1);

			}
			HAL_ADC_Stop(&hadc1);

	}

	else  if(chanel== READ_ADC_CH_HV_PDU_MX)// ADC1_IN14 //PIN 33 //
	{


			hadc1.Init.NbrOfConversion=READ_ADC_CH_HV_PDU_MX;
			HAL_ADC_Init(&hadc1);
			HAL_ADC_Start(&hadc1);
			if(HAL_ADC_PollForConversion(&hadc1,500)== HAL_OK)
			{

			digital_result=HAL_ADC_GetValue(&hadc1);

			}
			HAL_ADC_Stop(&hadc1);

	}
	else  if(chanel== READ_ADC_CH_HV_PDU_MY)//ADC1_IN15
	{


			hadc1.Init.NbrOfConversion=READ_ADC_CH_HV_PDU_MY;
			HAL_ADC_Init(&hadc1);
			HAL_ADC_Start(&hadc1);
			if(HAL_ADC_PollForConversion(&hadc1,500)== HAL_OK)
			{

			digital_result=HAL_ADC_GetValue(&hadc1);

			}
			HAL_ADC_Stop(&hadc1);

	}


	return digital_result;

}




/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
/* USER CODE BEGIN PFP */

/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */

/* USER CODE END 0 */

/**
  * @brief  The application entry point.
  * @retval int
  */
int main(void)
{
  /* USER CODE BEGIN 1 */

  /* USER CODE END 1 */

  /* MCU Configuration--------------------------------------------------------*/

  /* Reset of all peripherals, Initializes the Flash interface and the Systick. */
  HAL_Init();

  /* USER CODE BEGIN Init */

  /* USER CODE END Init */

  /* Configure the system clock */
  SystemClock_Config();

  /* USER CODE BEGIN SysInit */

  /* USER CODE END SysInit */

  /* Initialize all configured peripherals */
  MX_GPIO_Init();
  MX_LWIP_Init();
  MX_ADC1_Init();
  MX_DAC_Init();
  MX_USART1_UART_Init();
  /* USER CODE BEGIN 2 */

  SET_BUZZ(0)  ;
  HAL_Delay(300);
  SET_BUZZ(1)  ;
  HAL_Delay(300);



  server_init(1000);


  //RELAY_USER_INT(1) ;
  PDU_POWER(0)  ;
  //RELAY_USER_INT(1) ;
  printf("hiiii\nstarted\n");




    HAL_DAC_Start(&hdac, DAC_CH_X);
    HAL_DAC_Start(&hdac, DAC_CH_Y);

	HAL_DAC_SetValue(&hdac, DAC_CH_X, DAC_ALIGN_12B_R, 255);

	HAL_DAC_SetValue(&hdac, DAC_CH_Y, DAC_ALIGN_12B_R, 255);

	printf("dac=128\n");

	HAL_Delay(2000);

	//PDU_POWER(0)  ;
   // RELAY_USER_INT(0) ;


            printf(" PDUCL_PX=%4.2fV\n PDUCL_PY=%4.2fV\n SENS1=%4.2fV\n SENS2=%4.2fV\nPDU_MX=%4.2fV\n PDU_MY=%4.2fV\n \n\n",
             ((float)get_adc_raw( READ_ADC_CH_HV_PDUCL_PX  )*3.30)/4096.0     ,
			 ((float)get_adc_raw( READ_ADC_CH_HV_PDUCL_PY  )*3.30)/4096.0     ,
			 ((float)get_adc_raw( READ_ADC_SENS1        )*3.30)/4096.0     ,
			 ((float)get_adc_raw( READ_ADC_SENS2        )*3.30)/4096.0     ,
			 ((float)get_adc_raw( READ_ADC_CH_HV_PDU_MX    )*3.30)/4096.0     ,
			 ((float)get_adc_raw( READ_ADC_CH_HV_PDU_MY    )*3.30)/4096.0     );

            float cof=18.2;


  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
  while (1)
  {


	  LED_TOGG;
	  HAL_Delay(300);
printf(" PDUCL_PX=%4.2fV\n PDUCL_PY=%4.2fV\n SENS1=%4.2fV\n SENS2=%4.2fV\n PDU_MX=%4.2fV\n PDU_MY=%4.2fV\n----\n",
((float)get_adc_raw( READ_ADC_CH_HV_PDUCL_PX  )*3.30)/4096.0     ,
((float)get_adc_raw( READ_ADC_CH_HV_PDUCL_PY  )*3.30)/4096.0     ,
((float)get_adc_raw( READ_ADC_SENS1        )*3.30)/4096.0     ,
((float)get_adc_raw( READ_ADC_SENS2        )*3.30)/4096.0     ,
((float)get_adc_raw( READ_ADC_CH_HV_PDU_MX    )*3.30)/4096.0     ,
((float)get_adc_raw( READ_ADC_CH_HV_PDU_MY    )*3.30)/4096.0     );

/*

	  HAL_DAC_SetValue(&hdac, DAC_CH_X, DAC_ALIGN_12B_R, 0);
	  HAL_DAC_SetValue(&hdac, DAC_CH_Y, DAC_ALIGN_12B_R, 0);
	  printf(" PDUCL_PX=%4.2fV\n PDUCL_PY=%4.2fV\n S_CURRENT=%4.2fV\n PDU_MX=%4.2fV\n PDU_MY=%4.2fV\n \n\n",
	 	  	             ( ((float)get_adc_raw( READ_ADC_CH_HV_PDUCL_PX   )*3.30)/4096.0 )*cof     ,
	 	  	 			 ( ((float)get_adc_raw( READ_ADC_CH_HV_PDUCL_PY   )*3.30)/4096.0 )*cof     ,
	 	  	 			 ( ((float)get_adc_raw( READ_ADC_CH_S_CURRENT     )*3.30)/4096.0 )*cof     ,
	 	  	 			 ( ((float)get_adc_raw( READ_ADC_CH_HV_PDU_MX     )*3.30)/4096.0 )*cof     ,
	 	  	 			 ( ((float)get_adc_raw( READ_ADC_CH_HV_PDU_MY     )*3.30)/4096.0 )*cof     );
	  HAL_Delay(5000);





	  HAL_DAC_SetValue(&hdac, DAC_CH_X, DAC_ALIGN_12B_R, 4095  );
	  HAL_DAC_SetValue(&hdac, DAC_CH_Y, DAC_ALIGN_12B_R, 4095);
	  printf(" PDUCL_PX=%4.2fV\n PDUCL_PY=%4.2fV\n S_CURRENT=%4.2fV\n PDU_MX=%4.2fV\n PDU_MY=%4.2fV\n \n\n",
	  	             ( ((float)get_adc_raw( READ_ADC_CH_HV_PDUCL_PX   )*3.30)/4096.0 )*cof     ,
	  	 			 ( ((float)get_adc_raw( READ_ADC_CH_HV_PDUCL_PY   )*3.30)/4096.0 )*cof     ,
	  	 			 ( ((float)get_adc_raw( READ_ADC_CH_S_CURRENT     )*3.30)/4096.0 )*cof     ,
	  	 			 ( ((float)get_adc_raw( READ_ADC_CH_HV_PDU_MX     )*3.30)/4096.0 )*cof     ,
	  	 			 ( ((float)get_adc_raw( READ_ADC_CH_HV_PDU_MY     )*3.30)/4096.0 )*cof     );
	  HAL_Delay(5000);


	      HAL_DAC_SetValue(&hdac, DAC_CH_X, DAC_ALIGN_12B_R, 2048  );
	 	  HAL_DAC_SetValue(&hdac, DAC_CH_Y, DAC_ALIGN_12B_R, 2048);
	 	  printf(" PDUCL_PX=%4.2fV\n PDUCL_PY=%4.2fV\n S_CURRENT=%4.2fV\n PDU_MX=%4.2fV\n PDU_MY=%4.2fV\n \n\n",
	 	  	             ( ((float)get_adc_raw( READ_ADC_CH_HV_PDUCL_PX   )*3.30)/4096.0 )*cof     ,
	 	  	 			 ( ((float)get_adc_raw( READ_ADC_CH_HV_PDUCL_PY   )*3.30)/4096.0 )*cof     ,
	 	  	 			 ( ((float)get_adc_raw( READ_ADC_CH_S_CURRENT     )*3.30)/4096.0 )*cof     ,
	 	  	 			 ( ((float)get_adc_raw( READ_ADC_CH_HV_PDU_MX     )*3.30)/4096.0 )*cof     ,
	 	  	 			 ( ((float)get_adc_raw( READ_ADC_CH_HV_PDU_MY     )*3.30)/4096.0 )*cof     );
	 	  HAL_Delay(5000);

*/
//
//	  printf(" PDUCL_PX=%d\n PDUCL_PY=%d\n S_CURRENT=%d\n PDU_MX=%d\n PDU_MY=%d\n \n\n",
//	     		get_adc_raw( READ_ADC_CH_HV_PDUCL_PX ) ,
//	 			get_adc_raw( READ_ADC_CH_HV_PDUCL_PY ) ,
//	 			get_adc_raw( READ_ADC_CH_S_CURRENT ) ,
//	 			get_adc_raw( READ_ADC_CH_HV_PDU_MX),
//	 			get_adc_raw( READ_ADC_CH_HV_PDU_MY)   );










	  if(flag_run_loop)
	  {
		  flag_run_loop=false;


		  for(k=0 ; k <= loop ; k++ )
		  {
			  _even = true;
			   for (i = xs ; i <= xe ; i = i + sx)
			   {

				   _even = !_even;
				 for (j = ys ; j <= ye ; j = j + sy)
				 {
					   if (_even)
					   {
						 j1 = ye + ys - j;
					   }
					   else
					   {
						 j1 = j;
					   }


					    HAL_DAC_SetValue(&hdac, DAC_CH_X , DAC_ALIGN_12B_R ,  i);
					    HAL_DAC_SetValue(&hdac, DAC_CH_Y , DAC_ALIGN_12B_R ,  j1);

					   printf("\nx = %d  \ny = %d\n", i , j1 );


					   /*
					   Serial.print("x = ");
					   Serial.println(i);
					   Serial.print("y = ");
					   Serial.println(j1);
					   digitalWrite(7, HIGH);
					   dac.begin(0x60);
					   dac.setVoltage(i, false);
					   dac.begin(0x61);
					   dac.setVoltage(j1, false);
					   */
					   MX_LWIP_Process();

					   if(flag_exit_loop) break;

				       HAL_Delay(dly);

				   //--------
				 }

				 if(flag_exit_loop) break;

				 //--------
			   }


			   if(flag_exit_loop) break;
			 }//foor k loop


	  }  //if








    /* USER CODE END WHILE */

    /* USER CODE BEGIN 3 */
	  MX_LWIP_Process();
  }
  /* USER CODE END 3 */
}

/**
  * @brief System Clock Configuration
  * @retval None
  */
void SystemClock_Config(void)
{
  RCC_OscInitTypeDef RCC_OscInitStruct = {0};
  RCC_ClkInitTypeDef RCC_ClkInitStruct = {0};
  RCC_PeriphCLKInitTypeDef PeriphClkInit = {0};

  /** Initializes the RCC Oscillators according to the specified parameters
  * in the RCC_OscInitTypeDef structure.
  */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSE;
  RCC_OscInitStruct.HSEState = RCC_HSE_ON;
  RCC_OscInitStruct.HSEPredivValue = RCC_HSE_PREDIV_DIV5;
  RCC_OscInitStruct.HSIState = RCC_HSI_ON;
  RCC_OscInitStruct.Prediv1Source = RCC_PREDIV1_SOURCE_PLL2;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSE;
  RCC_OscInitStruct.PLL.PLLMUL = RCC_PLL_MUL9;
  RCC_OscInitStruct.PLL2.PLL2State = RCC_PLL2_ON;
  RCC_OscInitStruct.PLL2.PLL2MUL = RCC_PLL2_MUL10;
  RCC_OscInitStruct.PLL2.HSEPrediv2Value = RCC_HSE_PREDIV2_DIV2;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    Error_Handler();
  }
  /** Initializes the CPU, AHB and APB buses clocks
  */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                              |RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV2;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_2) != HAL_OK)
  {
    Error_Handler();
  }
  PeriphClkInit.PeriphClockSelection = RCC_PERIPHCLK_ADC;
  PeriphClkInit.AdcClockSelection = RCC_ADCPCLK2_DIV6;
  if (HAL_RCCEx_PeriphCLKConfig(&PeriphClkInit) != HAL_OK)
  {
    Error_Handler();
  }
  /** Enables the Clock Security System
  */
  HAL_RCC_EnableCSS();
  /** Configure the Systick interrupt time
  */
  __HAL_RCC_PLLI2S_ENABLE();
}

/* USER CODE BEGIN 4 */
/**
  * @brief  Called when a data is received on the server connection
  * @param  arg	the user argument
  * @param  pcb	the tcp_pcb that has received the data
  * @param  p	the packet buffer
  * @param  err	the error value linked with the received data
  * @retval error value
  */
err_t server_recv(void *arg, struct tcp_pcb *pcb, struct pbuf *p, err_t err)
{


  char *c;
  int i;
	char data_read[200]={0,0,0,0};
	char data_send[200]={0,0,0,0};


/* We perform here any necessary processing on the pbuf */
if (p != NULL)
{
	/* We call this function to tell the LwIp that we have processed the data */
	/* This lets the stack advertise a larger window, so more data can be received*/
	tcp_recved(pcb, p->tot_len);

	c = p->payload;

	for( i = 0 ; i < p->len ; i++)
    {
	  data_read[i] = c[i];
	}

	 tcp_write(pcb , data_read , p->len , 1);
	 pbuf_free(p);

//	p->payload=0;
//	p->tot_len=0;

//HAL_Delay(100);
if(data_read[0] == 0x7E)
{

	        printf("get command,len data=%d\n",p->len);

			if(data_read[1] == 0xBC)  //READ COMMAND
			{
				  k=0 ; i=0 ; j=0 ; j1=0;



				  xs =  (data_read[2]<<8 ) | data_read[3] ;
				  xe =  (data_read[4]<<8 ) | data_read[5] ;

				  ys =  (data_read[6]<<8 ) | data_read[7] ;
				  ye =  (data_read[8]<<8 ) | data_read[9] ;

				  sx =  (data_read[6]<<8 ) | data_read[7] ;
				  sy =  (data_read[8]<<8 ) | data_read[9] ;

				  dly  = (data_read[10]<<8 ) | data_read[11] ;

				  loop = (data_read[12]<<8 ) | data_read[13] ;

			    printf("\nxs=%d,xe=%d,ys=%d,ye=%d,sx=%d,sy=%d,delay=%d,loop=%d\n",xs,xe,ys,ye,sx,sy,dly,loop);
			    flag_exit_loop=false;

			    flag_run_loop=true;


			}
			if(data_read[1] == 0xBB)  //stop loop COMMAND
			{
				flag_exit_loop=true;

			}
			if(data_read[1] == 0xBD)  //RUN loop COMMAND
			{
				flag_run_loop=true;
				flag_exit_loop=false;
			}

			if(data_read[1] == 0x0D)//READ COMMAND
			{

					if(data_read[2] == 0x1D)	//READ PDU X+ VAL  mv
					{
						uint16_t val = get_adc_raw(READ_ADC_CH_HV_PDUCL_PX) ;
						uint8_t res[7] = "___";
						res[0] = 0x7E;
						res[1] = 0X0D;
						res[2] = 0X1D;
						res[3] = Hi_byte(val);
						res[4] = Lo_byte(val);
						tcp_write(pcb , res , 5 , 1);
						printf("READ PDUCL->x+ =%d\n" , val);

					}
					else if(data_read[2] == 0x2D)	//READ PDU Y+ VAL mv
					{
						uint16_t val = get_adc_raw(READ_ADC_CH_HV_PDUCL_PY);
						uint8_t res[7] = "___";
						res[0] = 0x7E;
						res[1] = 0X0D;
						res[2] = 0X2D;
						res[3] = Hi_byte(val);
						res[4] = Lo_byte(val);
						tcp_write(pcb , res , 5 , 1);
						printf("READ PDUCL->y+ =%d\n",val);
					}
					if(data_read[2] == 0x3D)	//READ PDU X- VAL  mv
					{
						uint16_t val = get_adc_raw(READ_ADC_CH_HV_PDU_MX);
						uint8_t res[7] = "___";
						res[0] = 0x7E;
						res[1] = 0X0D;
						res[2] = 0X3D;
						res[3] = Hi_byte(val);
						res[4] = Lo_byte(val);
						tcp_write(pcb , res , 5 , 1);
						printf("READ PDU->x- =%d\n",val);

					}
					else if(data_read[2] == 0x4D)	//READ PDU Y- VAL mv
					{
						uint16_t val = get_adc_raw(READ_ADC_CH_HV_PDU_MY);
						uint8_t res[7] = "___";
						res[0] = 0x7E;
						res[1] = 0X0D;
						res[2] = 0X4D;
						res[3] = Hi_byte(val);
						res[4] = Lo_byte(val);
						tcp_write(pcb , res , 5 , 1);
						printf("READ PDU->y- =%d\n",val);
					}

					if(data_read[2] == 0x5D)	//READ PDU X- VAL  mv
					{
						uint16_t val = get_adc_raw(READ_ADC_SENS1);
						uint8_t res[7] = "___";
						res[0] = 0x7E;
						res[1] = 0X0D;
						res[2] = 0X3D;
						res[3] = Hi_byte(val);
						res[4] = Lo_byte(val);
						tcp_write(pcb , res , 5 , 1);
						printf("READ_ADC_SENS CL1->x- =%d\n",val);

					}
					else if(data_read[2] == 0x6D)	//READ PDU Y- VAL mv
					{
						uint16_t val = get_adc_raw(READ_ADC_SENS2);
						uint8_t res[7] = "___";
						res[0] = 0x7E;
						res[1] = 0X0D;
						res[2] = 0X4D;
						res[3] = Hi_byte(val);
						res[4] = Lo_byte(val);
						tcp_write(pcb , res , 5 , 1);
						printf("READ_ADC_SENS CL2->y- =%d\n",val);
					}

			}
			if(data_read[1]==0x0F)//SET x y value COMMAND
			{

					if(data_read[2]==0x1F)	//SET PDU X+ VAL  mv
					{
						uint16_t val =  (data_read[3]<<8 ) | data_read[4] ;
						HAL_DAC_SetValue(&hdac, DAC_CH_X , DAC_ALIGN_12B_R ,  val);
						uint8_t res[7] = "___";
						res[0] = 0x7E;
						res[1] = 0x0F;
						res[2] = 0x1F;
						res[3]=(uint8_t)val>>8;
						res[4]=(uint8_t)val;
						tcp_write(pcb , res , 5 , 1);
						printf("SET PDU-x val=%d\n",  val);
						//printf("repund=%X",);
					}
					else if(data_read[2]==0x2F)	//SET PDU Y+ VAL mv
					{
						uint16_t val =  (data_read[3]<<8 ) | data_read[4] ;
						HAL_DAC_SetValue(&hdac, DAC_CH_Y , DAC_ALIGN_12B_R , val);
						uint8_t res[7] = "___";
						res[0] = 0x7E;
						res[1] = 0x0F;
						res[2] = 0x2F;
						res[3]=(uint8_t)val>>8;
						res[4]=(uint8_t)val;
						tcp_write(pcb , res , 5 , 1);
						printf("SET PDU-y val=%d\n",  val);
					}

			}

			else if(data_read[1]==0xAA)//pdu power on off
			{

					if(data_read[2]==0x1A)//pdu power   off
					{
						PDU_POWER(1)  ;
						uint8_t res[7]={0x7E,0XAA,0X0A,0X00,0X00};
						tcp_write(pcb , res , 5 , 1);
						printf("relay  pdu off\n");
					}
					if(data_read[2]==0x0A)//pdu power on
					{
						PDU_POWER(0)  ;
						uint8_t res[7]={0x7E,0XAA,0X1A,0X00,0X00};
						tcp_write(pcb , res , 5 , 1);
						printf("relay pdu on \n");
					}

			}

			else if(data_read[1]==0xC0)
			{

					if(data_read[2]==0xC1)//pdu set internal
					{
						RELAY_USER_INT(0)  ;
						uint8_t res[7]={0x7E,0XC0,0XC1,0X00,0X00};
						tcp_write(pcb , res , 5 , 1);
						printf("relay set on internal on \n");
					}
					if(data_read[2]==0xC2)//pdu set user
					{
						RELAY_USER_INT(1)  ;
						uint8_t res[7]={0x7E,0XC0,0XC2,0X00,0X00};
						tcp_write(pcb , res , 5 , 1);
						printf("relay set on external on \n");
					}

			}



	}
	else
	{
		switch (data_read[0])
		{
		  case LED1_ON:
				HAL_GPIO_WritePin(buzz_GPIO_Port,buzz_Pin,1);

				tcp_write(pcb,"buzz1_onn\n",10,1);
				HAL_Delay(100);
				break;
			case LED2_ON:
				HAL_GPIO_WritePin(buzz_GPIO_Port,buzz_Pin,0);
				tcp_write(pcb,"buzz1_off\n",10,1);
				HAL_Delay(100);
				break;
			case LED3_ON:
				HAL_GPIO_WritePin(LED3_GPIO_Port,LED3_Pin,1);
				break;
			case LED4_ON:
				HAL_GPIO_WritePin(LED4_GPIO_Port,LED4_Pin,1);
				break;
			case LED1_OFF:
				HAL_GPIO_WritePin(LED_1_GPIO_Port,LED_1_Pin,0);
				break;
			case LED2_OFF:
				HAL_GPIO_WritePin(LED2_GPIO_Port,LED2_Pin,0);
				break;
			case LED3_OFF:
				HAL_GPIO_WritePin(LED3_GPIO_Port,LED3_Pin,0);
				break;
			case LED4_OFF:
				HAL_GPIO_WritePin(LED4_GPIO_Port,LED4_Pin,0);
				break;
			case GET_PB1:
				sprintf(data_send,"%d",get_key_state());
			  tcp_write(pcb,data_send,strlen(data_send),1);
				break;
		}

  }//else

	/* End of processing, we free the pbuf */
 //   pbuf_free(p);
  }
  else if (err == ERR_OK)
  {
    /* When the pbuf is NULL and the err is ERR_OK, the remote end is closing the connection. */
    /* We close the connection */
    return tcp_close(pcb);
  }
  return ERR_OK;


}

/**
  * @brief  This function when the server connection is established
  * @param  arg  user supplied argument
  * @param  pcb	 the tcp_pcb which accepted the connection
  * @param  err	 error value
  * @retval ERR_OK
  */
err_t server_accept(void *arg, struct tcp_pcb *pcb, err_t err)
{
  /* Configure LwIP to use our call back functions. */
  tcp_err(pcb, server_conn_err);
  tcp_recv(pcb, server_recv);
  return ERR_OK;
}

/**
  * @brief  Initialize the server application
  * @param  None
  * @retval None
  */
void server_init(u16_t port)
{
  struct tcp_pcb *pcb;

  /* Create a new TCP control block  */
  pcb = tcp_new();

  /* Assign to the new pcb a local IP address and a port number */
  /* Using IP_ADDR_ANY allow the pcb to be used by any local interface */
  tcp_bind(pcb, IP_ADDR_ANY, port);


  /* Set the connection to the LISTEN state */
 // pcb = tcp_listen(pcb);
  pcb = tcp_listen_with_backlog(pcb);

  /* Specify the function to be called when a connection is established */
  tcp_accept(pcb, server_accept);

}

/**
  * @brief  This function is called when an error occurs on the connection
  * @param  arg
  * @parm   err
  * @retval None
  */
void server_conn_err(void *arg, err_t err)
{
  struct name *name;
  name = (struct name *)arg;

  mem_free(name);
}


char get_key_state(void)
{
 if(!HAL_GPIO_ReadPin(PB1_GPIO_Port,PB1_Pin))
	{
		HAL_Delay(KEYDEBOUNCE);
		if(!HAL_GPIO_ReadPin(PB1_GPIO_Port,PB1_Pin))
		{
		 while(!HAL_GPIO_ReadPin(PB1_GPIO_Port,PB1_Pin));

		 return 1;
		}
	}

  if(!HAL_GPIO_ReadPin(PB2_GPIO_Port,PB2_Pin))
	{
		HAL_Delay(KEYDEBOUNCE);
		if(!HAL_GPIO_ReadPin(PB2_GPIO_Port,PB2_Pin))
		{
		 while(!HAL_GPIO_ReadPin(PB2_GPIO_Port,PB2_Pin));
		 return 2;
		}
	}

  if(!HAL_GPIO_ReadPin(PB3_GPIO_Port,PB3_Pin))
	{
		HAL_Delay(KEYDEBOUNCE);
		if(!HAL_GPIO_ReadPin(PB3_GPIO_Port,PB3_Pin))
		{
		 while(!HAL_GPIO_ReadPin(PB3_GPIO_Port,PB3_Pin));
		 return 3;
		}
	}

  if(!HAL_GPIO_ReadPin(PB4_GPIO_Port,PB4_Pin))
	{
		HAL_Delay(KEYDEBOUNCE);
		if(!HAL_GPIO_ReadPin(PB4_GPIO_Port,PB4_Pin))
		{
		 while(!HAL_GPIO_ReadPin(PB4_GPIO_Port,PB4_Pin));
		 return 4;
		}
	}

  return 0;
}



uint8_t Hi_byte(uint16_t i )
{
	 uint8_t u81=0,u82=0;
	 u81 = i;
	 i>>=8;
	 u82 = i;
	 return u82;
 }


 uint8_t Lo_byte(uint16_t i )
 {
 	uint8_t u81=0,u82=0;
 	u81 = i;
 	i>>=8;
 	u82 = i;
 	return u81;
 }



/* USER CODE END 4 */

/**
  * @brief  This function is executed in case of error occurrence.
  * @retval None
  */
void Error_Handler(void)
{
  /* USER CODE BEGIN Error_Handler_Debug */
  /* User can add his own implementation to report the HAL error return state */

  /* USER CODE END Error_Handler_Debug */
}

#ifdef  USE_FULL_ASSERT
/**
  * @brief  Reports the name of the source file and the source line number
  *         where the assert_param error has occurred.
  * @param  file: pointer to the source file name
  * @param  line: assert_param error line source number
  * @retval None
  */
void assert_failed(uint8_t *file, uint32_t line)
{
  /* USER CODE BEGIN 6 */
  /* User can add his own implementation to report the file name and line number,
     tex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */
  /* USER CODE END 6 */
}
#endif /* USE_FULL_ASSERT */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
