#ifndef _USBUTSDKH
#define _USBUTSDKH

/*******************************************************************************
*	USBUTSDK.h - USB-UT SDK Header File (c)2005 US Ultratek, Inc.
*
*
*******************************************************************************/

/*******************************************************************************
*	Constants
*******************************************************************************/

#define DEVICE_NOT_READY	-500
#define DIN		0
#define TFRC	1
#define TSEC	2
#define RPTX	3
#define RPTY	4
#define RPTZ	5
#define RPTW	6
#define RPTU	7
#define RPTV	8
#define CSCAN	9

//******************************************************************************
//******************************************************************************



/*******************************************************************************
*	Modes
*******************************************************************************/

//******************************************************************************
#define ISDATAREADY					1000	/*

	Description:	Checks the status of the data acquisition process.
	wParam:			Not Used
	lParam:			Not Used
	Return Value:	DEVICE_NOT_READY (-500) if the USB-UT is not present
					<0 if there is no data in the memory
					>0 if there is data in the memory
*******************************************************************************/

//******************************************************************************
#define SOFTWARETRIGGER				1001	/*

	Description:	Generates a software trigger which causes the device to emit
					a pulse and then digitize the response.  Note that in order
					to generate a software trigger the trigger source must be set
					to 'Software Trigger'.  Refer to SETADTRIGGERSOURCE in order
					to set the trigger source.
	wParam:			Not Used
	lParam:			Not Used
	Return Value:	1 if successful 
*******************************************************************************/

//******************************************************************************
#define SETSAMPLINGRATE				1002	/*

	Description:	Sets the sampling rate.
	wParam:			Index from 0 to 7.
					0: 50 MHz (default)
					1: 25 MHz
					2: 12.5 MHz
					3. 6.25 MHz
	lParam:			Not Used
	Return Value:	1														
*******************************************************************************/

//******************************************************************************
#define SETLOWPASSFILTER			1004	/*

	Description:	Sets the frequency of the high pass filter.
	wParam:			Frequency in Hz
	lParam:			Not Used
	Return Value:	1														
*******************************************************************************/

//******************************************************************************
#define SETHIGHPASSFILTER			1005	/*

	Description:	Sets the frequency of the high pass filter.
	wParam:			Frequency in Hz
	lParam:			Not Used
	Return Value:	1														
*******************************************************************************/

//******************************************************************************
#define SETRECTIFIER				1006	/*

	Description:	Sets the receiver signal type.
	wParam:			Index from 0 to 3:

					0: Full wave rectification
					1: Positive half rectification
					2: Negative half rectification
					3: RF signal (no rectification - default)
	lParam:			Not Used
	Return Value:	1														
*******************************************************************************/

//******************************************************************************
#define SETTRANSDUCERMODE	1008	
	// wParam: 0=pulse/echo, 1=through transmission
	// lParam: Not used

//******************************************************************************
#define SETBUFFERLENGTH				1009	/*

	Description:	Sets the length of the buffer to be taken during the next
					data acquisition cycle.
	wParam:			Number of samples ranging from 1 to 8190.  The default value
					is 2000.
	lParam:			Not Used
	Return Value:	1														
*******************************************************************************/

//******************************************************************************
#define SETTRIGGERDELAY				1010	/*

	Description:	Sets the number of samples to skip after the pulse is
					emitted before taking data.
	wParam:			Number of samples ranging from 1 to 16370.  The default
					value is 2.
	lParam:			Not Used
	Return Value:	1														
*******************************************************************************/

//******************************************************************************
#define SETPULSEVOLTAGE				1011	/*

	Description:	Sets the pulse voltage.
	wParam:			Index from 0 to 255.
					The formula for the voltage is:
						V = -(4 + 4000 / (0.392157 * Index + 13.5))
	lParam:			Not Used
	Return Value:	1														
*******************************************************************************/

//******************************************************************************
#define SETPULSEWIDTH				1012	/*

	Description:	Sets the pulse width for the normal pulser or the number of
					half cycles for the tone burst pulser.
	wParam:			Index from 0 to 255.  Default is 0 which is the minimum
					pulse width.
	lParam:			Not Used
	Return Value:	1														
*******************************************************************************/

//******************************************************************************
#define SETGAIN						1013	/*

	Description:	Sets the receiver gain.
	wParam:			Index from 0 to 1023.  The receiver gain can be set from
					-20dB to 80dB with approximately a 0.1dB resolution.
					Gain in dB = 0.0978 * (Index - 204)
	lParam:			Not Used
	Return Value:	1														
*******************************************************************************/

//******************************************************************************
#define SETDCOFFSET					1014	/*

	Description:	Sets the receiver DC offset.
	wParam:			Index from 0 to 1023.  The default is 511 which is 2.5V
	lParam:			Not Used
	Return Value:	1														
*******************************************************************************/

//******************************************************************************
#define SETADTRIGGERSOURCE			1016	/*

	Description:	Sets the trigger source of the analog to digital converter.
	wParam:			Index from 0 to 2.
					0: +External Trigger
					1: Software Trigger
					2: -External Trigger
	lParam:			Not Used
	Return Value:	1														
*******************************************************************************/

//******************************************************************************
#define GETENCODERCOUNTER			1017	/*

	Description:	Gets the encoder counter value.
	wParam:			Index from 0 to 3.
					0: 1st encoder (X-axis)
					1: 2nd encoder (Y-axis)
					2: 3rd encoder (Z-axis)
					3: 4th encoder (W-axis)
	lParam:			Not Used
	Return Value:	Counter value from -8388608 to 8388607													
*******************************************************************************/

//******************************************************************************
#define SETENCODERCOUNTER			1018	/*

	Description:	Sets the encoder counter value.
	wParam:			Index from 0 to 3.
					0: 1st encoder (X-axis)
					1: 2nd encoder (Y-axis)
					2: 3rd encoder (Z-axis)
					3: 4th encoder (W-axis)
	lParam:			Counter value from -8388608 to 8388607
	Return Value:	1													
*******************************************************************************/

//******************************************************************************
#define GETDATA						1019	/*

	Description:	Gets the digitized data from memory after data acquisition.
	wParam:			Pointer to the buffer (unsigned char *) to receive the data.
	lParam:			Number of bytes to transfer
	Return Value:	Number of bytes received from the device													
*******************************************************************************/

//******************************************************************************
#define GETMODELNUMBER				1023	/*

	Description:	Gets the model number of the device.
	wParam:			Pointer to the buffer (char *) to receive the data.  Buffer
					must be at least 20 characters.
	lParam:			Not used
	Return Value:	1												
*******************************************************************************/

//******************************************************************************
#define GETSERIALNUMBER				1024	/*

	Description:	Gets the serial number of the device.
	wParam:			Pointer to the buffer (char *) to receive the data.  Buffer
					must be at least 20 characters.
	lParam:			Not used
	Return Value:	1												
*******************************************************************************/

//******************************************************************************
#define GETMEMORYSIZE				1025	/*
	Description:	Gets memory size.
	wParam:			Not used
	lParam:			Not used
	Return Value:	1												
*******************************************************************************/
	
//******************************************************************************
#define SETCHANNEL	1030
	// wParam: index of pulse channel; 0=Channel 1, 1=Channel 2...
	// lParam: index of receive channel; 0=Channel 1, 1=Channel 2...

//******************************************************************************
#define GETOPTIONBYTE1				1034	/*

	Description:	Gets option byte 1 which contains options present on the
					device.
	wParam:			Not used
	lParam:			Not used
	Return Value:	Option byte 1:			(0: Option not installed)
					Bit 7: DAC				(1: Option is installed)
					Bit 6: 1st Encoder
					Bit 5: 2nd Encoder
					Bit 4: Not used
					Bit 3: Sync Out
					Bit 2: Not Used
					Bit 1: Not Used
					Bit 0: Not Used
*******************************************************************************/

//******************************************************************************
#define GETOPTIONBYTE2				1035	/*

	Description:	Gets option byte 2 which contains options present on the
					device.
	wParam:			Not used
	lParam:			Not used
	Return Value:	Option byte 2:			(0: Option not installed)
					Bit 7: Not Used			(1: Option is installed)
					Bit 6: Not Used
					Bit 5: Not Used
					Bit 4: 3rd Encoder
					Bit 3: 4th Encoder
					Bit 2: Not Used
					Bit 1: Not Used
					Bit 0: Not Used
*******************************************************************************/

//******************************************************************************
#define GETREVNUMBER				1036	/*

	Description:	Gets the revsion number.
	wParam:			Index from 0 to 2:
					0: Driver revision
					1: Firmware revision
					2: Hardware revision
	lParam:			Not used
	Return Value:	Revision number based on the specified index.
*******************************************************************************/

//******************************************************************************
#define SETPRF						1038	/*

	Description:	Sets the PRF.
	wParam:			Frequency (0=Off)
	lParam:			Not used
	Return Value:	1
*******************************************************************************/

//******************************************************************************
#define SETIOPORT					1039	/*

	Description:	Sets the I/O port value.
	wParam:			I/O port to set:
					0: Port 0
					1: Port 1
	lParam:			Value for output port.  It will be ignored if the port is
					configured as an input port.
	Return Value:	1
*******************************************************************************/

//******************************************************************************
#define CONFIGUREIOPORT				1040	/*

	Description:	Configures the I/O port.
	wParam:			I/O port to configure:
					0: Input Port
					1: Output Port
	lParam:			I/O Port configuration byte
					Bit				7	6	5	4	3	2	1	0
					Configuration	x	x	x	x	x	x	x	x
					x: 0 for Input
					x: 1 for Output
	Return Value:	1
*******************************************************************************/

//******************************************************************************
#define READIOPORT					1044	/*

	Description:	Reads the I/O port value.
	wParam:			I/O port to set:
					0: Port 0
					1: Port 1
	lParam:			Not used
	Return Value:	The value of the port.
*******************************************************************************/

//******************************************************************************
#define SETTONEBURSTFREQUENCY		1046	/*

	Description:	Sets the frequency of the tone burst pulser.
	wParam:			Frequency in kHz from 20 to 10,000
	lParam:			Polarity: 0 = Positive, 1 = Negative
	Return Value:	1
*******************************************************************************/

//******************************************************************************
#define SETHARDWAREHPF				1047	/*
	Description:	Sets the hardware high pass filter.
	wParam:			0=12 kHz, 1=600 kHz
	lParam:			not used
	Return Value:	1
*******************************************************************************/


//******************************************************************************
#define SETAVERAGING				1075	/*

	Description:	Configures averaging.
	wParam:			Not used
	lParam:			Number of waveforms to average for each waveform returned.
	Return Value:	1
*******************************************************************************/

//******************************************************************************
#define SETFILTER				1076	/*

	Description:	Sets the filter specified by wParam.
	wParam:			Index from 0 to 1:
					0: Low Pass Filter
					1: High Pass Filter
	lParam:			Filter frequency in Hz.
	Return Value:	1
*******************************************************************************/

//******************************************************************************
#define INITIALIZE					5000	/*

	Description:	Initializes the device.
	wParam:			Not used
	lParam:			Not used
	Return Value:	1
*******************************************************************************/

//******************************************************************************
#define REGISTERARRIVALFUNCTION		5010	/*

	Description:	Registers a function to be called when the device is plugged
					in to the computer.
	wParam:			Address of the function to be called.
	lParam:			Not used
	Return Value:	1
*******************************************************************************/

//******************************************************************************
#define REGISTERREMOVALFUNCTION		5011	/*

	Description:	Registers a function to be called when the device is
					unplugged from the computer.
	wParam:			Address of the function to be called.
	lParam:			Not used
	Return Value:	1
*******************************************************************************/

//******************************************************************************
#define SETENCODERMODE				5050	/*

	Description:	Sets the encoder pins to function either as encoder pins or
					digital I/O.  When these pins are set to function as digital
					I/O port 1, the encoders will be disabled.
	wParam:			Not used
	lParam:			0: Encoder pins function as encoder pins.
					1: Encoder pins function as digital I/O port 1.
	Return Value:	1
*******************************************************************************/

//******************************************************************************
#define SETSPEAKER					5051	/*

	Description:	Sets the encoder pins to function either as encoder pins or
					digital I/O.  When these pins are set to function as digital
					I/O port 1, the encoders will be disabled.
	wParam:			Not used
	lParam:			0: Encoder pins function as encoder pins.
					1: Encoder pins function as digital I/O port 1.
	Return Value:	1
*******************************************************************************/

//******************************************************************************
#define GETDATAPOINTER				5500	/*

	Description:	Gets the data pointer of the data set after data acquisition.
	wParam:			Not Used
	lParam:			Not used
	Return Value:	Pointer to the data set, or NULL if there is no data set
					available.
*******************************************************************************/

//******************************************************************************
#define SETPOSITIONACQUISITION		5510	/*

	Description:	Sets the position acquisition configuration.  Position
					acquisition samples data based on the position of the
					encoder.
	wParam:			Index from 0 to 3.
					0: 1st encoder (X-axis)
					1: 2nd encoder (Y-axis)
					2: 3rd encoder (Z-axis)
					3: 4th encoder (W-axis)
	lParam:			Encoder count interval multiplied by 1000.
					Data will be sampled at each interval.  For example, if
					the desired interval is 23.569 encoder counts, specify
					23569.  This value must be positive.
	Return Value:	1
*******************************************************************************/

//******************************************************************************
#define GETEXTVOLTAGE		5520	/*

	Description:	Get the voltage of external power such as battery
	wParam:			Not used
	lParam:			Not used
	Return Value:	Returns 0 to 25000 mV or -2 if the option is not installed.
*******************************************************************************/


#if defined(__cplusplus)
extern "C" {
#endif  //  __cplusplus

__declspec(dllimport) int _stdcall USBUTParms(int mode, int device, 
	unsigned int wParam, int lParam);

#if defined(__cplusplus)
}
#endif  //  __cplusplus

//******************************************************************************
//******************************************************************************

#endif