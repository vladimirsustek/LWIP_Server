/*
 * server_udp.h
 *
 *  Created on: Mar 17, 2022
 *      Author: z004f3nw
 */

#ifndef SERVER_UDP_H_
#define SERVER_UDP_H_

#include "udp.h"
#include "tcp.h"
#include "pbuf.h"
#include "snake_port.h"

void udp_server_init(uint16_t serverPort, uint16_t clientPort);

#endif /* SERVER_UDP_H_ */
