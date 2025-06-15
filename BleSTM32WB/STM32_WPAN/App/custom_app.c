/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file    App/custom_app.c
  * @author  MCD Application Team
  * @brief   Custom Example Application (Server)
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2025 STMicroelectronics.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
  *
  ******************************************************************************
  */
/* USER CODE END Header */

/* Includes ------------------------------------------------------------------*/
#include "main.h"
#include "app_common.h"
#include "dbg_trace.h"
#include "ble.h"
#include "custom_app.h"
#include "custom_stm.h"
#include "stm32_seq.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include "encrypt.h"
/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
typedef struct
{
  /* My_P2P_Server */
  uint8_t               Switch_c_Notification_Status;
  uint8_t               Data_out_c_Notification_Status;
  uint8_t               Data_out_t_c_Notification_Status;
  /* USER CODE BEGIN CUSTOM_APP_Context_t */
  uint8_t               SW1_Status;
  /* USER CODE END CUSTOM_APP_Context_t */

  uint16_t              ConnectionHandle;
} Custom_App_Context_t;

/* USER CODE BEGIN PTD */
#define M_CHA_CHA		   0x01
#define M_CHA_POLY         0x02
#define CMD_AES_GCM        0x03

extern RNG_HandleTypeDef hrng;
/*
#define MAX_PLAIN_SIZE 500
static const uint8_t plain[MAX_PLAIN_SIZE] = {"Hello STM! Pokus o delsi zpravu, cekam kde se to zalomi a kde bude ten problem, pokud na nej nekde narazime, nebo taky ne u vidime. Pokracujici zprava, uvidime jak muze byt dlouha. Ale jeste uvidime co vsechno se posle. Chtel bych, aby to bylo 250B. Hello STM! Pokus o delsi zpravu, cekam kde se to zalomi a kde bude ten problem, pokud na nej nekde narazime, nebo taky ne u vidime. Pokracujici zprava, uvidime jak muze byt dlouha. Ale jeste uvidime co vsechno se posle. Chtel bych, aby to bylo 500B."};
*/
/*
#define MAX_PLAIN_SIZE 1000
static const uint8_t plain[MAX_PLAIN_SIZE] = {"Hello STM! Pokus o delsi zpravu, cekam kde se to zalomi a kde bude ten problem, pokud na nej nekde narazime, nebo taky ne u vidime. Pokracujici zprava, uvidime jak muze byt dlouha. Ale jeste uvidime co vsechno se posle. Chtel bych, aby to bylo 250B. Hello STM! Pokus o delsi zpravu, cekam kde se to zalomi a kde bude ten problem, pokud na nej nekde narazime, nebo taky ne u vidime. Pokracujici zprava, uvidime jak muze byt dlouha. Ale jeste uvidime co vsechno se posle. Chtel bych, aby to bylo 500B. Hello STM! Pokus o delsi zpravu, cekam kde se to zalomi a kde bude ten problem, pokud na nej nekde narazime, nebo taky ne u vidime. Pokracujici zprava, uvidime jak muze byt dlouha. Ale jeste uvidime co vsechno se posle. Chtel bych, aby to bylo 250B. Hello STM! Pokus o delsi zpravu, cekam kde se to zalomi a kde bude ten problem, pokud na nej nekde narazime, nebo taky ne u vidime. Pokracujici zprava, uvidime jak muze byt dlouha. Ale jeste uvidime co vsechno se posle. Chtel bych, aby to bylo 1000B."};
*/

//static const uint8_t plain[MAX_PLAIN_SIZE] = {"Hello STM! Pokus o delsi zpravu, cekam kde se to zalomi a kde bude ten problem, pokud na nej nekde narazime, nebo taky ne u vidime. Pokracujici zprava, uvidime jak muze byt dlouha. Ale jeste uvidime co vsechno se posle. Chtel bych, aby to bylo 250B. Hello STM! Pokus o delsi zpravu, cekam kde se to zalomi a kde bude ten problem, pokud na nej nekde narazime, nebo taky ne u vidime. Pokracujici zprava, uvidime jak muze byt dlouha. Ale jeste uvidime co vsechno se posle. Chtel bych, aby to bylo 500B. Hello STM! Pokus o delsi zpravu, cekam kde se to zalomi a kde bude ten problem, pokud na nej nekde narazime, nebo taky ne u vidime. Pokracujici zprava, uvidime jak muze byt dlouha. Ale jeste uvidime co vsechno se posle. Chtel bych, aby to bylo 750B. Hello STM! Pokus o delsi zpravu, cekam kde se to zalomi a kde bude ten problem, pokud na nej nekde narazime, nebo taky ne u vidime. Pokracujici zprava, uvidime jak muze byt dlouha. Ale jeste uvidime co vsechno se posle. Chtel bych, aby to bylo 1000B.Hello STM! Pokus o delsi zpravu, cekam kde se to zalomi a kde bude ten problem, pokud na nej nekde narazime, nebo taky ne u vidime. Pokracujici zprava, uvidime jak muze byt dlouha. Ale jeste uvidime co vsechno se posle. Chtel bych, aby to bylo 1250B.Hello STM! Pokus o delsi zpravu, cekam kde se to zalomi a kde bude ten problem, pokud na nej nekde narazime, nebo taky ne u vidime. Pokracujici zprava, uvidime jak muze byt dlouha. Ale jeste uvidime co vsechno se posle. Chtel bych, aby to bylo 1500B.Hello STM! Pokus o delsi zpravu, cekam kde se to zalomi a kde bude ten problem, pokud na nej nekde narazime, nebo taky ne u vidime. Pokracujici zprava, uvidime jak muze byt dlouha. Ale jeste uvidime co vsechno se posle. Chtel bych, aby to bylo 1750B. Hello STM! Pokus o delsi zpravu, cekam kde se to zalomi a kde bude ten problem, pokud na nej nekde narazime, nebo taky ne u vidime. Pokracujici zprava, uvidime jak muze byt dlouha. Ale jeste uvidime co vsechno se posle. Chtel bych, aby to bylo 2000B.Hello STM! Pokus o delsi zpravu, cekam kde se to zalomi a kde bude ten problem, pokud na nej nekde narazime, nebo taky ne u vidime. Pokracujici zprava, uvidime jak muze byt dlouha. Ale jeste uvidime co vsechno se posle. Chtel bych, aby to bylo 2250B.Hello STM! Pokus o delsi zpravu, cekam kde se to zalomi a kde bude ten problem, pokud na nej nekde narazime, nebo taky ne u vidime. Pokracujici zprava, uvidime jak muze byt dlouha. Ale jeste uvidime co vsechno se posle. Chtel bych, aby to bylo 500B. Hello STM! Pokus o delsi zpravu, cekam kde se to zalomi a kde bude ten problem, pokud na nej nekde narazime, nebo taky ne u vidime. Pokracujici zprava, uvidime jak muze byt dlouha. Ale jeste uvidime co vsechno se posle. Chtel bych, aby to bylo 2500B.Hello STM! Pokus o delsi zpravu, cekam kde se to zalomi a kde bude ten problem, pokud na nej nekde narazime, nebo taky ne u vidime. Pokracujici zprava, uvidime jak muze byt dlouha. Ale jeste uvidime co vsechno se posle. Chtel bych, aby to bylo 1000B. Hello STM! Pokus o delsi zpravu, cekam kde se to zalomi a kde bude ten problem, pokud na nej nekde narazime, nebo taky ne u vidime. Pokracujici zprava, uvidime jak muze byt dlouha. Ale jeste uvidime co vsechno se posle. Chtel bych, aby to bylo 2750B.Hello STM! Pokus o delsi zpravu, cekam kde se to zalomi a kde bude ten problem, pokud na nej nekde narazime, nebo taky ne u vidime. Pokracujici zprava, uvidime jak muze byt dlouha. Ale jeste uvidime co vsechno se posle. Chtel bych, aby to bylo 500B. Hello STM! Pokus o delsi zpravu, cekam kde se to zalomi a kde bude ten problem, pokud na nej nekde narazime, nebo taky ne u vidime. Pokracujici zprava, uvidime jak muze byt dlouha. Ale jeste uvidime co vsechno se posle. Chtel bych, aby to bylo 3000B.Hello STM! Pokus o delsi zpravu, cekam kde se to zalomi a kde bude ten problem, pokud na nej nekde narazime, nebo taky ne u vidime. Pokracujici zprava, uvidime jak muze byt dlouha. Ale jeste uvidime co vsechno se posle. Chtel bych, aby to bylo 4000B."};

/* USER CODE END PTD */

/* Private defines ------------------------------------------------------------*/
/* USER CODE BEGIN PD */

/* USER CODE END PD */

/* Private macros -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/
/**
 * START of Section BLE_APP_CONTEXT
 */

static Custom_App_Context_t Custom_App_Context;

/**
 * END of Section BLE_APP_CONTEXT
 */

uint8_t UpdateCharData[512];
uint8_t NotifyCharData[512];
uint16_t Connection_Handle;
/* USER CODE BEGIN PV */
#define MAX_CHUNK_SIZE_PC 153
#define TAG_SIZE 16
#define MAX_PLAIN_SIZE 50000
#define DELAY 5

uint8_t plain[MAX_PLAIN_SIZE];
const bool useGenData = true;
bool genNewData = true;
/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
/* My_P2P_Server */
static void Custom_Switch_c_Update_Char(void);
static void Custom_Switch_c_Send_Notification(void);
static void Custom_Data_out_c_Update_Char(void);
static void Custom_Data_out_c_Send_Notification(void);
static void Custom_Data_out_t_c_Update_Char(void);
static void Custom_Data_out_t_c_Send_Notification(void);

/* USER CODE BEGIN PFP */
void SendTestMessage(void);

/* USER CODE END PFP */

/* Functions Definition ------------------------------------------------------*/
void Custom_STM_App_Notification(Custom_STM_App_Notification_evt_t *pNotification)
{
  /* USER CODE BEGIN CUSTOM_STM_App_Notification_1 */

  /* USER CODE END CUSTOM_STM_App_Notification_1 */
  switch (pNotification->Custom_Evt_Opcode)
  {
    /* USER CODE BEGIN CUSTOM_STM_App_Notification_Custom_Evt_Opcode */

    /* USER CODE END CUSTOM_STM_App_Notification_Custom_Evt_Opcode */

    /* My_P2P_Server */
    case CUSTOM_STM_LED_C_READ_EVT:
      /* USER CODE BEGIN CUSTOM_STM_LED_C_READ_EVT */

      /* USER CODE END CUSTOM_STM_LED_C_READ_EVT */
      break;

    case CUSTOM_STM_LED_C_WRITE_NO_RESP_EVT:
      /* USER CODE BEGIN CUSTOM_STM_LED_C_WRITE_NO_RESP_EVT */
    	APP_DBG_MSG("\r\n\r** CUSTOM_STM_LED_C_WRITE_NO_RESP_EVT \n");
    	APP_DBG_MSG("\r\n\r** Write Data: 0x%02X %02X \n", pNotification->DataTransfered.pPayload[0], pNotification->DataTransfered.pPayload[1]);
    	if(pNotification->DataTransfered.pPayload[1] == 0x01) {
    		BSP_LED_On(LED_BLUE);
    	}
    	if(pNotification->DataTransfered.pPayload[1] == 0x00) {
    	    BSP_LED_Off(LED_BLUE);
    	}
      /* USER CODE END CUSTOM_STM_LED_C_WRITE_NO_RESP_EVT */
      break;

    case CUSTOM_STM_SWITCH_C_NOTIFY_ENABLED_EVT:
      /* USER CODE BEGIN CUSTOM_STM_SWITCH_C_NOTIFY_ENABLED_EVT */
    	APP_DBG_MSG("\r\n\r** CUSTOM_STM_BUTTON_C_NOTIFY_ENABLED_EVT \n");

    	Custom_App_Context.Switch_c_Notification_Status = 1;
      /* USER CODE END CUSTOM_STM_SWITCH_C_NOTIFY_ENABLED_EVT */
      break;

    case CUSTOM_STM_SWITCH_C_NOTIFY_DISABLED_EVT:
      /* USER CODE BEGIN CUSTOM_STM_SWITCH_C_NOTIFY_DISABLED_EVT */
    	APP_DBG_MSG("\r\n\r** CUSTOM_STM_BUTTON_C_NOTIFY_DISABLED_EVT \n");

    	Custom_App_Context.Switch_c_Notification_Status = 0;

      /* USER CODE END CUSTOM_STM_SWITCH_C_NOTIFY_DISABLED_EVT */
      break;

    case CUSTOM_STM_DATA_IN_C_READ_EVT:
      /* USER CODE BEGIN CUSTOM_STM_DATA_IN_C_READ_EVT */

      /* USER CODE END CUSTOM_STM_DATA_IN_C_READ_EVT */
      break;

    case CUSTOM_STM_DATA_IN_C_WRITE_NO_RESP_EVT:
      /* USER CODE BEGIN CUSTOM_STM_DATA_IN_C_WRITE_NO_RESP_EVT */
    	uint8_t* buf = pNotification->DataTransfered.pPayload;
    	uint16_t len = pNotification->DataTransfered.Length;
    	uint8_t  resp_hdr = buf[0];
    	uint16_t requested = (uint16_t)buf[2] | ((uint16_t)buf[1] << 8);
    	APP_DBG_MSG("Requested: %u\n", requested);
    	APP_DBG_MSG("Plain size: %u\n", sizeof(plain));
    	uint32_t t_start, t_stop;
    	uint32_t total_us = 0;
        switch (resp_hdr) {
          case M_CHA_CHA:
          {
            size_t offset = 0;
            while (offset < requested) {
              size_t chunk = MIN(MAX_CHUNK_SIZE_PC, requested - offset);
              uint8_t cipher[chunk];

              uint32_t t0 = get_micros();
              int rc = chacha20_encrypt(&plain[offset], chunk, 1, cipher);
              uint32_t t1 = get_micros();
              total_us += (t1 - t0);

              Custom_STM_App_Update_Char_Variable_Length(
                CUSTOM_STM_DATA_OUT_C, cipher, chunk);
              offset += chunk;
              HAL_Delay(DELAY);
            }
            break;
          }

          case M_CHA_POLY:
          {
            size_t offset = 0;
            while (offset < requested) {
              size_t chunk = MIN(MAX_CHUNK_SIZE_PC - TAG_SIZE, requested - offset);
              uint8_t cipher[chunk], tag[TAG_SIZE], outbuf[chunk + TAG_SIZE];

              uint32_t t0 = get_micros();
              int rc = chacha_encrypt_and_tag(
                         &plain[offset], chunk,
                         NULL, 0,
                         cipher, tag);
              uint32_t t1 = get_micros();
              total_us += (t1 - t0);

              memcpy(outbuf,            tag, TAG_SIZE);
              memcpy(outbuf + TAG_SIZE, cipher, chunk);
              Custom_STM_App_Update_Char_Variable_Length(
                CUSTOM_STM_DATA_OUT_C, outbuf, chunk + TAG_SIZE);
              offset += chunk;
              HAL_Delay(DELAY);
            }
            break;
          }

          case CMD_AES_GCM:
          {
            size_t offset = 0;
            while (offset < requested) {
              size_t chunk = MIN(MAX_CHUNK_SIZE_PC - TAG_SIZE, requested - offset);
              uint8_t outbuf[chunk + TAG_SIZE];

              uint32_t t0 = get_micros();
              int rc = aes_gcm_encrypt_and_tag(
                         &plain[offset], chunk,
                         NULL, 0,
                         outbuf);
              uint32_t t1 = get_micros();
              total_us += (t1 - t0);

              Custom_STM_App_Update_Char_Variable_Length(
                CUSTOM_STM_DATA_OUT_C, outbuf, chunk + TAG_SIZE);
              offset += chunk;
              HAL_Delay(DELAY);
            }
            break;
          }
    	    default:
    	    return;
    	    }

    	Custom_STM_App_Update_Char_Variable_Length(CUSTOM_STM_DATA_OUT_T_C, (uint8_t*)&total_us, sizeof(total_us));
    	APP_DBG_MSG("Casova delka sifrovani: %lu µs\n", (unsigned long)total_us);
      /* USER CODE END CUSTOM_STM_DATA_IN_C_WRITE_NO_RESP_EVT */
      break;

    case CUSTOM_STM_DATA_OUT_C_NOTIFY_ENABLED_EVT:
      /* USER CODE BEGIN CUSTOM_STM_DATA_OUT_C_NOTIFY_ENABLED_EVT */

      /* USER CODE END CUSTOM_STM_DATA_OUT_C_NOTIFY_ENABLED_EVT */
      break;

    case CUSTOM_STM_DATA_OUT_C_NOTIFY_DISABLED_EVT:
      /* USER CODE BEGIN CUSTOM_STM_DATA_OUT_C_NOTIFY_DISABLED_EVT */

      /* USER CODE END CUSTOM_STM_DATA_OUT_C_NOTIFY_DISABLED_EVT */
      break;

    case CUSTOM_STM_DATA_OUT_T_C_NOTIFY_ENABLED_EVT:
      /* USER CODE BEGIN CUSTOM_STM_DATA_OUT_T_C_NOTIFY_ENABLED_EVT */

      /* USER CODE END CUSTOM_STM_DATA_OUT_T_C_NOTIFY_ENABLED_EVT */
      break;

    case CUSTOM_STM_DATA_OUT_T_C_NOTIFY_DISABLED_EVT:
      /* USER CODE BEGIN CUSTOM_STM_DATA_OUT_T_C_NOTIFY_DISABLED_EVT */

      /* USER CODE END CUSTOM_STM_DATA_OUT_T_C_NOTIFY_DISABLED_EVT */
      break;

    case CUSTOM_STM_NOTIFICATION_COMPLETE_EVT:
      /* USER CODE BEGIN CUSTOM_STM_NOTIFICATION_COMPLETE_EVT */

      /* USER CODE END CUSTOM_STM_NOTIFICATION_COMPLETE_EVT */
      break;

    default:
      /* USER CODE BEGIN CUSTOM_STM_App_Notification_default */

      /* USER CODE END CUSTOM_STM_App_Notification_default */
      break;
  }
  /* USER CODE BEGIN CUSTOM_STM_App_Notification_2 */

  /* USER CODE END CUSTOM_STM_App_Notification_2 */
  return;
}

void Custom_APP_Notification(Custom_App_ConnHandle_Not_evt_t *pNotification)
{
  /* USER CODE BEGIN CUSTOM_APP_Notification_1 */

  /* USER CODE END CUSTOM_APP_Notification_1 */

  switch (pNotification->Custom_Evt_Opcode)
  {
    /* USER CODE BEGIN CUSTOM_APP_Notification_Custom_Evt_Opcode */

    /* USER CODE END P2PS_CUSTOM_Notification_Custom_Evt_Opcode */
    case CUSTOM_CONN_HANDLE_EVT :
      /* USER CODE BEGIN CUSTOM_CONN_HANDLE_EVT */
    	APP_DBG_MSG("Generate new data %d\n", genNewData);
    	if(useGenData && genNewData) {
    		plain[MAX_PLAIN_SIZE];
			for (size_t i = 0; i < MAX_PLAIN_SIZE; ++i) {
				plain[i] = 'A' + (i % 26);
			  }
			genNewData = false;
    	}
      /* USER CODE END CUSTOM_CONN_HANDLE_EVT */
      break;

    case CUSTOM_DISCON_HANDLE_EVT :
      /* USER CODE BEGIN CUSTOM_DISCON_HANDLE_EVT */

      /* USER CODE END CUSTOM_DISCON_HANDLE_EVT */
      break;

    default:
      /* USER CODE BEGIN CUSTOM_APP_Notification_default */

      /* USER CODE END CUSTOM_APP_Notification_default */
      break;
  }

  /* USER CODE BEGIN CUSTOM_APP_Notification_2 */

  /* USER CODE END CUSTOM_APP_Notification_2 */

  return;
}

void Custom_APP_Init(void)
{
  /* USER CODE BEGIN CUSTOM_APP_Init */
	UTIL_SEQ_RegTask(1<< CFG_TASK_SW1_BUTTON_PUSHED_ID, UTIL_SEQ_RFU, Custom_Switch_c_Send_Notification);
	//UTIL_SEQ_RegTask(1<< CFG_TASK_SEND_TEST_MSG_ID, UTIL_SEQ_RFU, SendTestMessage);

	Custom_App_Context.Switch_c_Notification_Status = 0;
	Custom_App_Context.SW1_Status = 0;
  /* USER CODE END CUSTOM_APP_Init */
  return;
}

/* USER CODE BEGIN FD */

/* USER CODE END FD */

/*************************************************************
 *
 * LOCAL FUNCTIONS
 *
 *************************************************************/

/* My_P2P_Server */
__USED void Custom_Switch_c_Update_Char(void) /* Property Read */
{
  uint8_t updateflag = 0;

  /* USER CODE BEGIN Switch_c_UC_1*/

  /* USER CODE END Switch_c_UC_1*/

  if (updateflag != 0)
  {
    Custom_STM_App_Update_Char(CUSTOM_STM_SWITCH_C, (uint8_t *)UpdateCharData);
  }

  /* USER CODE BEGIN Switch_c_UC_Last*/

  /* USER CODE END Switch_c_UC_Last*/
  return;
}

void Custom_Switch_c_Send_Notification(void) /* Property Notification */
{
  uint8_t updateflag = 0;

  /* USER CODE BEGIN Switch_c_NS_1*/
  if (Custom_App_Context.Switch_c_Notification_Status)
    {
      updateflag = 1;

      if (Custom_App_Context.SW1_Status == 0)
      {
    	NotifyCharData[0] = 0x00;
    	NotifyCharData[1] = 0x01;
      }
      else
      {
        Custom_App_Context.SW1_Status = 0;
        NotifyCharData[0] = 0x00;
        NotifyCharData[1] = 0x00;

      }

      APP_DBG_MSG("-- CUSTOM APPLICATION SERVER  : INFORM CLIENT BUTTON 1 PUSHED \n");
    }
    else
    {
      APP_DBG_MSG("-- CUSTOM APPLICATION : CAN'T INFORM CLIENT -  NOTIFICATION DISABLED\n");
    }

  /* USER CODE END Switch_c_NS_1*/

  if (updateflag != 0)
  {
    Custom_STM_App_Update_Char(CUSTOM_STM_SWITCH_C, (uint8_t *)NotifyCharData);
  }

  /* USER CODE BEGIN Switch_c_NS_Last*/

  /* USER CODE END Switch_c_NS_Last*/

  return;
}

__USED void Custom_Data_out_c_Update_Char(void) /* Property Read */
{
  uint8_t updateflag = 0;

  /* USER CODE BEGIN Data_out_c_UC_1*/

  /* USER CODE END Data_out_c_UC_1*/

  if (updateflag != 0)
  {
	Custom_STM_App_Update_Char_Ext(Connection_Handle, CUSTOM_STM_DATA_OUT_C, (uint8_t *)UpdateCharData);
  }

  /* USER CODE BEGIN Data_out_c_UC_Last*/

  /* USER CODE END Data_out_c_UC_Last*/
  return;
}

void Custom_Data_out_c_Send_Notification(void) /* Property Notification */
{
  uint8_t updateflag = 0;

  /* USER CODE BEGIN Data_out_c_NS_1*/

  /* USER CODE END Data_out_c_NS_1*/

  if (updateflag != 0)
  {
	Custom_STM_App_Update_Char_Ext(Connection_Handle, CUSTOM_STM_DATA_OUT_C, (uint8_t *)NotifyCharData);
  }

  /* USER CODE BEGIN Data_out_c_NS_Last*/

  /* USER CODE END Data_out_c_NS_Last*/

  return;
}

__USED void Custom_Data_out_t_c_Update_Char(void) /* Property Read */
{
  uint8_t updateflag = 0;

  /* USER CODE BEGIN Data_out_t_c_UC_1*/

  /* USER CODE END Data_out_t_c_UC_1*/

  if (updateflag != 0)
  {
    Custom_STM_App_Update_Char(CUSTOM_STM_DATA_OUT_T_C, (uint8_t *)UpdateCharData);
  }

  /* USER CODE BEGIN Data_out_t_c_UC_Last*/

  /* USER CODE END Data_out_t_c_UC_Last*/
  return;
}

void Custom_Data_out_t_c_Send_Notification(void) /* Property Notification */
{
  uint8_t updateflag = 0;

  /* USER CODE BEGIN Data_out_t_c_NS_1*/

  /* USER CODE END Data_out_t_c_NS_1*/

  if (updateflag != 0)
  {
    Custom_STM_App_Update_Char(CUSTOM_STM_DATA_OUT_T_C, (uint8_t *)NotifyCharData);
  }

  /* USER CODE BEGIN Data_out_t_c_NS_Last*/

  /* USER CODE END Data_out_t_c_NS_Last*/

  return;
}

/* USER CODE BEGIN FD_LOCAL_FUNCTIONS*/
void P2PS_APP_SW1_Button_Action(void)
  {
    UTIL_SEQ_SetTask(1<<CFG_TASK_SW1_BUTTON_PUSHED_ID, CFG_SCH_PRIO_0);

    /* --- teď navíc invokujeme task pro odeslání zprávy --- */
    //UTIL_SEQ_SetTask(1<< CFG_TASK_SEND_TEST_MSG_ID, CFG_SCH_PRIO_0);

    return;
  }
/* USER CODE END FD_LOCAL_FUNCTIONS*/
