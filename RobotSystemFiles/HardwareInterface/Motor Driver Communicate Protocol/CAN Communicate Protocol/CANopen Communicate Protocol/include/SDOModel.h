/*
 * SDOStruct.h
 *
 *  Created on: 2016-10-24
 *      Author: e701
 */

#ifndef SDOMODEL_H_
#define SDOMODEL_H_

struct struct_s_transfer;
typedef struct struct_s_transfer s_transfer;

#include "DataParamPreDefine.h"
#include "FuncPointerModel.h"

struct struct_s_transfer {
  UNS8           CliServNbr; /**< The index of the SDO client / server in our OD minus 0x1280 / 0x1200 */

  UNS8           whoami;     /**< Takes the values SDO_CLIENT or SDO_SERVER */
  UNS8           state;      /**< state of the transmission : Takes the values SDO_... */
  UNS8           toggle;
  UNS32          abortCode;  /**< Sent or received */

  /**< index and subindex of the dictionary where to store */
  /**< (for a received SDO) or to read (for a transmit SDO) */
  UNS16          index;
  UNS8           subIndex;

  /**************************************
   *
   * 说明：	count 和 offset 决定了要写数据的
   * 			字节数目大小以及次数
   *
   **************************************/
  UNS32          count;      /**< Number of data received or to be sent. */
  UNS32          offset;     /**< stack pointer of data[]
                              * Used only to tranfer part of a line to or from a SDO.
                              * offset is always pointing on the next free cell of data[].
                              * WARNING s_transfer.data is subject to ENDIANISATION
                              * (with respect to CANOPEN_BIG_ENDIAN)
                              */
  /**************************************
   *
   * 说明：	data[] 只用于保存要传输的数据内容，
   * 		比如要向从机写 4个字节的数据，只存 4个字节的数据
   * 		不保存数据头信息
   *
   **************************************/
  UNS8           data [SDO_MAX_LENGTH_TRANSFERT];
  UNS8           peerCRCsupport;    /**< True if peer supports CRC */
  UNS8           blksize;           /**< Number of segments per block with 0 < blksize < 128 */
  UNS8           ackseq;            /**< sequence number of last segment that was received successfully */
  UNS32          objsize;           /**< Size in bytes of the object provided by data producer */
  UNS8           lastblockoffset;   /**< Value of offset before last block */
  UNS8           seqno;             /**< Last sequence number received OK or transmitted */
  UNS8           endfield;          /**< nbr of bytes in last segment of last block that do not contain data */
  rxStep_t       rxstep;            /**< data consumer receive step - set to true when last segment of a block received */
  UNS8           tmpData[8];        /**< temporary segment storage */

  UNS8           dataType;   /**< Defined in objdictdef.h Value is visible_string
                              * if it is a string, any other value if it is not a string,
                              * like 0. In fact, it is used only if client.
                              */
  TIMER_HANDLE   timer;      /**< Time counter to implement a timeout in milliseconds.
                              * It is automatically incremented whenever
                              * the line state is in SDO_DOWNLOAD_IN_PROGRESS or
                              * SDO_UPLOAD_IN_PROGRESS, and reseted to 0
                              * when the response SDO have been received.
                              */
  SDOCallback_t Callback;   /**< The user callback func to be called at SDO transaction end */
};

#define s_transfer_Initializer {\
		0,          /* nodeId */\
		0,          /* wohami */\
		SDO_RESET,  /* state */\
		0,          /* toggle */\
		0,          /* abortCode */\
		0,          /* index */\
		0,          /* subIndex */\
		0,          /* count */\
		0,          /* offset */\
		{0},        /* data (static use, so that all the table is initialize at 0)*/\
		0,          /* peerCRCsupport */\
		0,          /* blksize */\
		0,          /* ackseq */\
		0,          /* objsize */\
		0,          /* lastblockoffset */\
		0,          /* seqno */\
		0,          /* endfield */\
		RXSTEP_INIT,/* rxstep */\
		{0},        /* tmpData */\
		0,          /*  */\
		-1,         /*  */\
		NULL        /*  */\
	  }

#endif /* SDOSTRUCT_H_ */
