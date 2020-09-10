#pragma once
#include <stdint.h>

class transaction;

typedef struct
{
	uint32_t crc32;
	uint16_t frame_id : 4;
	uint16_t packet_id : 12;
	uint16_t payload_count : 12;
	uint16_t parity_count : 12;		// might not used
	uint8_t payload[0];				// multiple of 16
} YAL2DownlinkFrame;

typedef struct
{
	uint32_t crc32;
	uint16_t ack_start:12;
	uint16_t ack_count:4;
	uint16_t ack_frame_id : 4;
	uint16_t uplink_count : 12;
	uint8_t realtime_payload_count;		// for stick data or anything else
	uint8_t feedback_count;				// count of downlink status feedback
	uint8_t ack_bitmap[16];
	uint8_t payload[0];					// realtime payload first, feedback latter, normal payload last
} YAL2UplinkFrame;

enum YAL_event
{
	sender_frame_done = 0,
	sender_frame_timeout = 1,
	sender_rate_change = 1,
	sender_MAX = 0xff,

	receiver_frame_ready = 0x102,
	receiver_realtime_poll = 0x103,
	receiver_MAX = 0x1ff,

	transaction_ack = 0x200,
	transaction_result = 0x201,
	transaction_request = 0x202,
	transaction_MAX = 0x2ff,
};

enum receiver_event
{
};

typedef void (*event_callback)(void *user_data, int event, transaction *trans);
