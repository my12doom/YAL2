#pragma once

#include <HAL/Interface/IBlockDevice.h>
#include <stdint.h>
#include "YAL2_types.h"
#include "YAL2_config.h"

namespace YAL2
{

// helper functions
int wifi_frame_time_us(int data_size, float Mbps);


// classes
class sender;
class receiver;

// packet transaction
class transaction
{
public:
	//
	transaction(uint8_t *data, int size, uint8_t *out = NULL, int out_size = 0);
	~transaction();

	int cancel();
	bool finished();
	bool is_transaction();

	// data pointers
	void *data_out;
	int data_out_size;
	void *data_in;
	int data_in_size;

protected:
	sender *tx;
	receiver *rx;
};

class sender
{
public:
	sender();
	~sender();

	// 
	int set_device(HAL::IBlockDevice *tx_device, HAL::IBlockDevice *rx_device = NULL);
	int set_callback(event_callback cb, void *user_data);
	int set_timeout(int streaming_timeout, int packet_timeout, int transaction_timeout);

	// video streaming
	transaction *send_frame(uint8_t *data, int size);

	// packet transaction
	transaction *do_transaction(uint8_t *data, int size, uint8_t *out = NULL, int out_size = 0);

protected:

	// 
	virtual int update_downlink_setting(uint8_t *metadata, int size, float over_send_ratio);
};

class receiver
{
public:
	receiver();
	~receiver();

	int set_device(HAL::IBlockDevice *tx_device, HAL::IBlockDevice *rx_device = NULL);
	int set_timeout(int streaming_timeout, int packet_timeout, int transaction_timeout);
	int set_callback(event_callback cb, void *user_data);

	// 
	int get_frame();

	// packet transaction
	transaction *do_transaction(uint8_t *data, int size, uint8_t *out = NULL, int out_size = 0);

protected:
};



};

