/*
 * server_udp.c
 *
 *  Created on: Mar 17, 2022
 *      Author: z004f3nw
 */


#include "server_tcp.h"

/**
  ******************************************************************************
  * @file    udp_server.c
  * @author  MCD Application Team
  * @version V1.1.0
  * @date    07-October-2011
  * @brief   UDP  server
  ******************************************************************************
  * @attention
  *
  * THE PRESENT FIRMWARE WHICH IS FOR GUIDANCE ONLY AIMS AT PROVIDING CUSTOMERS
  * WITH CODING INFORMATION REGARDING THEIR PRODUCTS IN ORDER FOR THEM TO SAVE
  * TIME. AS A RESULT, STMICROELECTRONICS SHALL NOT BE HELD LIABLE FOR ANY
  * DIRECT, INDIRECT OR CONSEQUENTIAL DAMAGES WITH RESPECT TO ANY CLAIMS ARISING
  * FROM THE CONTENT OF SUCH FIRMWARE AND/OR THE USE MADE BY CUSTOMERS OF THE
  * CODING INFORMATION CONTAINED HEREIN IN CONNECTION WITH THEIR PRODUCTS.
  *
  * <h2><center>&copy; COPYRIGHT 2011 STMicroelectronics</center></h2>
  ******************************************************************************
  */

/* Includes ------------------------------------------------------------------*/
#include "main.h"
#include "lwip/pbuf.h"
#include "lwip/udp.h"
#include "lwip/tcp.h"
#include <string.h>
#include <stdio.h>

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
#define UDP_SERVER_PORT    8001   /* define the UDP local connection port */
#define UDP_CLIENT_PORT    8001   /* define the UDP remote connection port */


static uint16_t gClientPort = 0;
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/


/**
  * @brief This function is called when an UDP datagrm has been received on the port UDP_PORT.
  * @param arg user supplied argument (udp_pcb.recv_arg)
  * @param pcb the udp_pcb which received data
  * @param p the packet buffer that was received
  * @param addr the remote IP address from which the packet was received
  * @param port the remote port from which the packet was received
  * @retval None
  */

#if 0
void udp_server_receive_callback(void *arg,
		struct udp_pcb *upcb,
		struct pbuf *p,
		ip_addr_t *addr,
		u16_t port)
#endif
void udp_server_receive_callback(void *arg,
		struct udp_pcb *pcb,
		struct pbuf *p,
	    const ip_addr_t *addr,
		u16_t port)
{

  /* Connect to the remote client */
  udp_connect(pcb, addr, gClientPort);

  char *pReceived = (char*)mem_malloc((size_t)(p->len + 1));
  memcpy(pReceived, p->payload, p->len);
  memset(pReceived + p->len, 0, 1);

#ifdef SERVER_TCP_PRINTF_ENABLED
  printf("%s\n", pReceived);
#endif

  /* Binding with KeyBoard control */
  platform_snake_set_control(pReceived[0]);

  mem_free(pReceived);

  /* Tell the client that we have accepted it */
  udp_send(pcb, p);

  /* free the UDP connection, so we can accept new clients */
  udp_disconnect(pcb);

  /* Free the p buffer */
  pbuf_free(p);

}

/* Private functions ---------------------------------------------------------*/

/**
  * @brief  Initialize the server application.
  * @param  None
  * @retval None
  */
void udp_server_init(uint16_t serverPort, uint16_t clientPort)
{
   struct udp_pcb *upcb;
   err_t err;

   ip4_addr_t ipAddress;
   IP4_ADDR(&ipAddress, 192, 168, 100, 1);

   /* Create a new UDP control block  */
   upcb = udp_new();

   if (upcb)
   {
	   gClientPort = clientPort;
     /* Bind the upcb to the UDP_PORT port */
     /* Using IP_ADDR_ANY allow the upcb to be used by any local interface */
      err = udp_bind(upcb, &ipAddress, serverPort);

      if(err == ERR_OK)
      {
        /* Set a receive callback for the upcb */
        udp_recv(upcb, udp_server_receive_callback, NULL);
      }
      else
      {
        printf("can not bind pcb");
      }
   }
   else
   {
     printf("can not create pcb");
   }
}

/******************* (C) COPYRIGHT 2011 STMicroelectronics *****END OF FILE****/
