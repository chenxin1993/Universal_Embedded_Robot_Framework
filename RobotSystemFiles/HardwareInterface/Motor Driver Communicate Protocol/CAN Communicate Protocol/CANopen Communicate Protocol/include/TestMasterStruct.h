/*
 * TestMasterStruct.h
 *
 *  Created on: 2016-10-24
 *      Author: e701
 */

#ifndef TESTMASTERSTRUCT_H_
#define TESTMASTERSTRUCT_H_

/** This are some structs which are neccessary for creating the entries
 *  of the object dictionary. */
typedef struct td_subindex
{
    unsigned char                    bAccessType;
    unsigned char                    bDataType; /* Defines of what datatype the entry is */
    unsigned long                   size;      /* The size (in Byte) of the variable */
    void*                   pObject;   /* This is the pointer of the Variable */
} subindex;


/** Struct for creating entries in the communictaion profile */
typedef struct td_indextable
{
    subindex*   pSubindex;   /* Pointer to the subindex */
    unsigned char   bSubCount;   /* the count of valid entries for this subindex
                         * This count here defines how many memory has been
                         * allocated. this memory does not have to be used.
                         */
    unsigned int   index;
} indextable;


typedef struct s_quick_index{
	unsigned int SDO_SVR;
	unsigned int SDO_CLT;
	unsigned int PDO_RCV;
	unsigned int PDO_RCV_MAP;
	unsigned int PDO_TRS;
	unsigned int PDO_TRS_MAP;
} quick_index;


struct CONTROLWORD_BITS
{
	unsigned int SwitchOn:1;
	unsigned int EnableVol:1;
	unsigned int QuickStop:1;
	unsigned int EnableOper:1;

	unsigned int OPperModeSpec1:1;
	unsigned int OPperModeSpec2:1;
	unsigned int OPperModeSpec3:1;

	unsigned int ResetFault:1;
	unsigned int Halt:1;
	unsigned int reserved1:1;
	unsigned int reserved2:1;
	unsigned int ManufSpec1:1;
	unsigned int ManufSpec2:1;
	unsigned int ManufSpec3:1;
	unsigned int ManufSpec4:1;
	unsigned int ManufSpec5:1;
};


union ControlWord
{
	unsigned int all;
	struct CONTROLWORD_BITS	bit;
};


struct STATUSWORD_BITS
{
	unsigned int ReadytoSwitchon:1;
	unsigned int Swichedon:1;
	unsigned int OperEnabled:1;
	unsigned int Fault:1;

	unsigned int VolEnabled:1;

	unsigned int QuickStop:1;
	unsigned int SwitchonDisabled:1;

	unsigned int Warning:1;
	unsigned int ManufSpec:1;
	unsigned int Remote:1;
	unsigned int TargetReached:1;
	unsigned int InterLimtActive:1;
	unsigned int OperModeSpec1:1;
	unsigned int OperModeSpec2:1;
	unsigned int ManufSpec1:1;
	unsigned int ManufSpec2:1;
};


union StatusWord
{
	unsigned int all;
	struct STATUSWORD_BITS bit;
};

struct FUNCCODE
{
/*$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$

                               OD relate funccode

$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$*/
	/* index 0x0000 :   NULL. */
	unsigned int 	obj0000;

	/* index 0x1000 :   Device Type. */
	unsigned long	obj1000;

	/* index 0x1001 :   Error Register. */
	unsigned char	obj1001;

	/* index 0x1003 :   Pre-defined Error Field. */
	unsigned char	highestSubIndex_obj1003;
	unsigned long	obj1003[4];

	/* index 0x1005 :   SYNC COB ID. */
	unsigned long	obj1005;

	/* index 0x1006 :   Communication / Cycle Period. */
	unsigned long	obj1006;

	/* index 0x1009 :   hardware version */
	unsigned int	obj1009;

	/* index 0x100A :   software version */
	unsigned int	obj100A;

	/* index 0x1014 :   Emergency COB ID. */
	unsigned long 	obj1014;

	/* index 0x1016 :   Consumer Heartbeat Count */
	unsigned char 	highestSubIndex_obj1016;

	/* index 0x1017 :   Producer Heartbeat Time. */
	unsigned int 	obj1017;

	/* index 0x1200 :   Client SDO 1 Parameter. */
	unsigned char 	highestSubIndex_obj1200;
    unsigned long 	obj1200_COB_ID_Client_to_Server_Transmit_SDO;
    unsigned long 	obj1200_COB_ID_Server_to_Client_Receive_SDO;

	/* index 0x1201 :   Client SDO 2 Parameter. */
	unsigned char 	highestSubIndex_obj1201;
    unsigned long 	obj1201_COB_ID_Client_to_Server_Transmit_SDO;
    unsigned long 	obj1201_COB_ID_Server_to_Client_Receive_SDO;

	/* index 0x1202 :   Client SDO 3 Parameter. */
	unsigned char 	highestSubIndex_obj1202;
    unsigned long 	obj1202_COB_ID_Client_to_Server_Transmit_SDO;
    unsigned long 	obj1202_COB_ID_Server_to_Client_Receive_SDO;

	/* index 0x1203 :   Client SDO 4 Parameter. */
	unsigned char 	highestSubIndex_obj1203;
    unsigned long 	obj1203_COB_ID_Client_to_Server_Transmit_SDO;
    unsigned long 	obj1203_COB_ID_Server_to_Client_Receive_SDO;

};

#endif /* TESTMASTERSTRUCT_H_ */
