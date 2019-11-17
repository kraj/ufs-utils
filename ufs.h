/* SPDX-License-Identifier: GPL-2.0-or-later */
/* Copyright (C) 2019 Western Digital Corporation or its affiliates */


#ifndef UFS_H_
#define UFS_H_
#include <asm-generic/int-ll64.h>
#include "ioctl.h"
#include "scsi_bsg_util.h"

#define BLOCK_SIZE 512

/*
 * Generally the max HW max chunk is 512KB,
 * but in order to be in safe side tool using 256KB as max chunk size
 * between user and kernel space
*/
#define MAX_IOCTL_BUF_SIZE (256L * 1024)

/* Flag idn for Query Requests*/
enum flag_idn {
	QUERY_FLAG_IDN_RESERVED1		= 0x00,
	QUERY_FLAG_IDN_FDEVICEINIT		= 0x01,
	QUERY_FLAG_IDN_PERMANENT_WPE		= 0x02,
	QUERY_FLAG_IDN_PWR_ON_WPE		= 0x03,
	QUERY_FLAG_IDN_BKOPS_EN			= 0x04,
	QUERY_FLAG_IDN_DEVICE_LIFE_SPAN_MODE_EN	= 0x05,
	QUERY_FLAG_IDN_PURGE_ENABLE		= 0x06,
	QUERY_FLAG_IDN_REFRESH_ENABLE		= 0x07,
	QUERY_FLAG_IDN_FPHYRESOURCEREMOVAL	= 0x08,
	QUERY_FLAG_IDN_BUSY_RTC			= 0x09,
	QUERY_FLAG_IDN_RESERVED4		= 0x0A,
	QUERY_FLAG_IDN_PERMANENTLYDISABLEFW	= 0x0B,
	QUERY_FLAG_IDN_MAX
};

/* Attribute idn for Query requests */
enum attr_idn {
	QUERY_ATTR_IDN_BOOT_LU_EN			= 0x00,
	QUERY_ATTR_IDN_RESERVED1			= 0x01,
	QUERY_ATTR_IDN_POWER_MODE			= 0x02,
	QUERY_ATTR_IDN_ACTIVE_ICC_LVL			= 0x03,
	QUERY_ATTR_IDN_OOO_DATA_EN			= 0x04,
	QUERY_ATTR_IDN_BKOPS_STATUS			= 0x05,
	QUERY_ATTR_IDN_PURGE_STATUS			= 0x06,
	QUERY_ATTR_IDN_MAX_DATA_IN			= 0x07,
	QUERY_ATTR_IDN_MAX_DATA_OUT			= 0x08,
	QUERY_ATTR_IDN_DYN_CAP_NEEDED			= 0x09,
	QUERY_ATTR_IDN_REF_CLK_FREQ			= 0x0A,
	QUERY_ATTR_IDN_CONF_DESC_LOCK			= 0x0B,
	QUERY_ATTR_IDN_MAX_NUM_OF_RTT			= 0x0C,
	QUERY_ATTR_IDN_EE_CONTROL			= 0x0D,
	QUERY_ATTR_IDN_EE_STATUS			= 0x0E,
	QUERY_ATTR_IDN_SECONDS_PASSED			= 0x0F,
	QUERY_ATTR_IDN_CNTX_CONF			= 0x10,
	QUERY_ATTR_IDN_OBSOLETE				= 0x11,
	QUERY_ATTR_IDN_RESERVED2			= 0x12,
	QUERY_ATTR_IDN_RESERVED3			= 0x13,
	QUERY_ATTR_IDN_DEVICE_FFU_STATUS		= 0x14,
	QUERY_ATTR_IDN_DEVICE_PSA_STATE			= 0x15,
	QUERY_ATTR_IDN_DEVICE_PSA_DATA_SIZE		= 0x16,
	QUERY_ATTR_IDN_CASE_REF_CLK_GATING_WAIT_TIME	= 0x17,
	QUERY_ATTR_IDN_CASE_ROUGH_TEMPERAURE		= 0x18,
	QUERY_ATTR_IDN_TOO_HIGH_TEMP_BOUNDARY		= 0x19,
	QUERY_ATTR_IDN_TOO_LOW_TEMP_BOUNDARY		= 0x1A,
	QUERY_ATTR_IDN_REFRESH_STATUS			= 0x2C,
	QUERY_ATTR_IDN_REFRESH_FREQ			= 0x2D,
	QUERY_ATTR_IDN_REFRESH_UNIT			= 0x2E,
	QUERY_ATTR_IDN_REFRESH_METHOD			= 0x2F,
	QUERY_ATTR_IDN_MAX
};

/* Descriptor idn for Query requests */
enum desc_idn {
	QUERY_DESC_IDN_DEVICE		= 0x0,
	QUERY_DESC_IDN_CONFIGURAION	= 0x1,
	QUERY_DESC_IDN_UNIT		= 0x2,
	QUERY_DESC_IDN_RFU_0		= 0x3,
	QUERY_DESC_IDN_INTERCONNECT	= 0x4,
	QUERY_DESC_IDN_STRING		= 0x5,
	QUERY_DESC_IDN_RFU_1		= 0x6,
	QUERY_DESC_IDN_GEOMETRY		= 0x7,
	QUERY_DESC_IDN_POWER		= 0x8,
	QUERY_DESC_IDN_HEALTH		= 0x9,
	QUERY_DESC_IDN_RFU_3		= 0xA,
	QUERY_DESC_IDN_MAX = 0xFF,
};

/* UTP QUERY Transaction Specific Fields OpCode */
enum query_opcode {
	UPIU_QUERY_OPCODE_NOP		= 0x0,
	UPIU_QUERY_OPCODE_READ_DESC	= 0x1,
	UPIU_QUERY_OPCODE_WRITE_DESC	= 0x2,
	UPIU_QUERY_OPCODE_READ_ATTR	= 0x3,
	UPIU_QUERY_OPCODE_WRITE_ATTR	= 0x4,
	UPIU_QUERY_OPCODE_READ_FLAG	= 0x5,
	UPIU_QUERY_OPCODE_SET_FLAG	= 0x6,
	UPIU_QUERY_OPCODE_CLEAR_FLAG	= 0x7,
	UPIU_QUERY_OPCODE_TOGGLE_FLAG	= 0x8,
	UPIU_QUERY_OPCODE_MAX,
};

enum ufs_desc_max_size {
	QUERY_DESC_DEVICE_MAX_SIZE		= 0x40,
	QUERY_DESC_CONFIGURAION_MAX_SIZE	= 0x90,
	QUERY_DESC_UNIT_MAX_SIZE		= 0x23,
	QUERY_DESC_INTERCONNECT_MAX_SIZE	= 0x06,
	/*
	 * Max. 126 UNICODE characters (2 bytes per character) plus 2 bytes
	 * of descriptor header.
	 */
	QUERY_DESC_STRING_MAX_SIZE		= 0xFE,
	QUERY_DESC_GEOMETRY_MAX_SIZE		= 0x48,
	QUERY_DESC_POWER_MAX_SIZE		= 0x62,
	QUERY_DESC_HEALTH_MAX_SIZE		= 0x2d
};

/* UPIU Read/Write flags */
enum {
	UPIU_CMD_FLAGS_NONE	= 0x00,
	UPIU_CMD_FLAGS_WRITE	= 0x20,
	UPIU_CMD_FLAGS_READ	= 0x40,
};

/* UPIU Query request function */
enum {
	UPIU_QUERY_FUNC_STANDARD_READ_REQUEST	= 0x01,
	UPIU_QUERY_FUNC_STANDARD_WRITE_REQUEST	= 0x81,
};

enum ufs_cong_type {
	DESC_TYPE = 0,
	ATTR_TYPE,
	FLAG_TYPE,
	ERR_HIST_TYPE,
	UIC_TYPE,
	FFU_TYPE,
	VENDOR_BUFFER_TYPE,
	RPMB_CMD_TYPE,
	HMR_TYPE
};

/* UTP UPIU Transaction Codes Initiator to Target */
enum {
	UPIU_TRANSACTION_NOP_OUT	= 0x00,
	UPIU_TRANSACTION_COMMAND	= 0x01,
	UPIU_TRANSACTION_DATA_OUT	= 0x02,
	UPIU_TRANSACTION_TASK_REQ	= 0x04,
	UPIU_TRANSACTION_QUERY_REQ	= 0x16,
};

int write_file(const char *name, const void *buffer, int length);
void print_error(const char *msg, ...);
long str_to_long(char *nptr, int base, long *result);
#ifdef DEBUG
	#define WRITE_LOG(format, ...) fprintf(stderr, format"\n", __VA_ARGS__)
	#define WRITE_LOG0(text) fprintf(stderr, "%s\n", text)
#else
	#define WRITE_LOG(...)
	#define WRITE_LOG0(...)
#endif

#endif /* UFS_H_ */
