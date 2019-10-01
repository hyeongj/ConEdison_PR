#pragma once
#ifndef Usbut


#include "USBUTSDK.h"
#include "usbasdk.h"

#define TOTALTESTS		2

using namespace std;



class Usbut {

private:

    double** ary;
    double** auto_ary;
    double* tm;
    double* tof;



public:

    int _speed;
    int _chs;
    int _channel;
    int _buffer;
    int _gain;
    int _delay;
    int _rate;
    int _rectifier;
    double _time_in;
    double _maxth;
    double _offset;


    Usbut()
    {
        _chs = 0;
        _channel = 4;
        _buffer = 500;
        _gain = 700;
        _delay = 1;
        _rate = 0;
        _rectifier = 0;
        _time_in = 2.0;
        _maxth = 0.3;
        _speed = 1500;
        _offset = 0.4;

        //constructor  -initialized
        ary = new double* [_channel];//row  -channel
        for (int i = 0; i < _channel; i++)
        {
            ary[i] = new double[_buffer];// column - buffer
        }

        auto_ary = new double* [_channel];//row  -channel
        for (int i = 0; i < _channel; i++)
        {
            auto_ary[i] = new double[_buffer];// column - buffer
        }


        tm = new double[_buffer + 1];

        tof = new double[_channel];
        //MessageBox(NULL, TEXT("Start ON"), L"Simple Message", NULL);

    }

    ~Usbut()
    {
        //Free each sub-array
        for (int i = 0; i < _channel; i++) // delete row
        {
            delete[] ary[i];
        }

        delete[] ary;


        for (int i = 0; i < _channel; i++) // delete row
        {
            delete[] auto_ary[i];
        }

        delete[] auto_ary;



        delete[] tof;

        delete[] tm;

        //MessageBox(NULL, TEXT("Closed header file"), L"Simple Message", NULL);

    }


    bool connected()
    {
        int firmVer = USBUTParms(GETREVNUMBER, 0, 1, 0);

        if (firmVer < 220)
        {

            return false;
        }

        return true;
    }

    void setchannel(int _chnselect)
    {
        _chs = _chnselect;

        USBUTParms(ASDK_SETRXN, 0, 0, _chs);	// receiver chan: 1
        USBUTParms(ASDK_SETTXN, 0, 0, _chs);	// transmit chan: 1

        USBUTParms(ASDK_SETRXN, 0, 1, _chs);	// receiver chan: 2
        USBUTParms(ASDK_SETTXN, 0, 1, _chs);	// transmit chan: 2

    }

    void setgain(int _gainselect)
    {
        _gain = _gainselect;

        for (int i = 0; i < TOTALTESTS; i++)
        {
            USBUTParms(ASDK_SETGAIN, 0, i, _gain);

        }

    }
    void setrate(int _rateselect)
    {
        _rate = _rateselect;


        USBUTParms(SETSAMPLINGRATE, 0, 0, _rate);

    }



    void setrectifier(int _rectif)
    {
        _rectifier = _rectif;

        for (int i = 0; i < TOTALTESTS; i++)
        {
            USBUTParms(ASDK_SETREC, 0, i, _rectifier);

        }

    }

    void setbuffer(int _bufferselect)
    {
        _buffer = _bufferselect;

        for (int i = 0; i < TOTALTESTS; i++)
        {
            USBUTParms(ASDK_SETBUFFERLENGTH, 0, 0, _buffer);

        }

    }



    void init();
    double* timedata(int, int);
    double** waveform(int);
    double* get_tof(double*, double**, double, double);

    double** autocorr(int, double**);




};





double* Usbut::get_tof(double* tm, double** ary, double _time_in_x, double _maxth_x) {


    _time_in = _time_in_x;
    _maxth = _maxth_x;


    int index = 0;


    for (int i = 0; i < _buffer; i++) {
        if (_time_in < tm[i]) {
            if (_time_in + 2 * 0.02 > tm[i])
            {
                index = i;
            }
        }

    }

    for (int j = 0; j < _channel; j++)
    {

        double max = 0.0;
        int ind = 0;
        for (int i = index; i < _buffer; i++) {
            if (ary[j][i] > max)
            {

                max = ary[j][i];
                //ind = i;


                if (max > _maxth)
                {
                    ind = i;
                }
                else {
                    ind = 0;
                }


            }

        }


        tof[j] = tm[ind];


    }




    return tof;

}



void Usbut::init() {


    // initialize global parameters
    USBUTParms(ASDK_SETNUMBERTEST, 0, TOTALTESTS, 0);
    USBUTParms(SETSAMPLINGRATE, 0, 0, _rate);	// 50MHz sampling rate
    USBUTParms(SETPULSEVOLTAGE, 0, 0, 0);	// Power: 300 volts	//Index from 0 to 255 (40V).
    USBUTParms(SETADTRIGGERSOURCE, 0, 1, 0);		//Set the trigger source to software trigger

    for (int i = 0; i < TOTALTESTS; i++)
    {

        USBUTParms(ASDK_SETPULSEWIDTH, 0, i, 1);	// Index from 1 to 25 for 50 to 530 ns.
        USBUTParms(ASDK_SETDLY, 0, i, _delay);	// delay
        USBUTParms(ASDK_SETBUFFERLENGTH, 0, i, _buffer);	// # of samples
        USBUTParms(ASDK_SETGAIN, 0, i, _gain);	// gain 0 to 1023 for -20 to 80 dB.
        USBUTParms(ASDK_SETREC, 0, i, _rectifier);	//  RF wave rectify, 0 to 3 where 0=Full rectified, 1=+half, 2=-half, or 3=RF.
        USBUTParms(ASDK_SETDCOFFSET, 0, i, 511);	// center
        USBUTParms(ASDK_SETHARDWAREHPF, 0, i, 1);	// HPF:0.6 MHz

        if (i == 0)
        {
            USBUTParms(ASDK_SETTRANSDUCERMODE, 0, i, 0);	// pulse/echo
        }
        else
        {
            USBUTParms(ASDK_SETTRANSDUCERMODE, 0, i, 1);	// pulse/echo
        }

    }



}


double* Usbut::timedata(int _rate_x1, int _buffer_x2)
{
    _rate = _rate_x1;
    _buffer = _buffer_x2;

    float srate = 50;


    if (_rate == 0)
    {
        srate = 50;
    }
    else if (_rate == 1) {
        srate = 25;
    }
    else if (_rate == 2) {
        srate = 12.5;
    }
    else if (_rate == 3) {
        srate = 6.25;
    }



    double dt = 1 / srate;
    tm[0] = 0.0;
    double x0 = 0.0;

    for (int i = 0; i < _buffer; i++)
    {
        x0 = tm[i];
        tm[i + 1] = x0 + dt;
    }

    char str2[200];

    //for (int i = 0; i < _buffer; i++)

    //{
    //     
    //     sprintf(str2, "%lf\n", tm[i]);
    //     OutputDebugString(str2);
    //}

    return tm;
}

double** Usbut::waveform(int _buffer_x)
{

    _buffer = _buffer_x;

    unsigned long* dwptr;
    unsigned char* bptr;



    for (int jj = 0; jj < _channel; jj++)
    {
        setchannel(jj);

        USBUTParms(ASDK_STARTSCAN, 0, 0, 0);	// stop first
        USBUTParms(ASDK_STARTSCAN, 10,	// 10 Hz
            1,		// time base scan mode
            0);




        do {
            dwptr = (unsigned long*)USBUTParms(ASDK_GETDATAPOINTER, 0, 0, 0);
            Sleep(1);	// give CPU a break
        } while (dwptr == NULL);



        dwptr += (_buffer / 4) + 8;
        bptr = (unsigned char*)dwptr;	// beginning of the data



        USBUTParms(ASDK_STARTSCAN, 0, 0, 0);	// stop scan mode


        for (int kk = 0; kk < _buffer; kk++)
        {
            int kj = bptr[kk];

            ary[jj][kk] = kj;// rows (channel) and columns (buffer)

            //char str2[200];
            //sprintf(str2, "%d\n", kj);
            //OutputDebugString(str2);
        }



    }



    for (int jj = 0; jj < _channel; jj++)
    {
        for (int kk = 0; kk < _buffer; kk++)
        {
            ary[jj][kk] = ary[jj][kk] / 255;
            /*	if (ary[jj][kk]<0.2 && ary[jj][kk]>-0.2)
                {
                    ary[jj][kk] = 0.0;
                }*/

        }
    }

    //offset -----------------------------
    int index = 0;

    for (int i = 0; i < _buffer; i++) {
        if (_offset < tm[i]) {
            if (_offset + 2 * 0.02 > tm[i])
            {
                index = i;
            }
        }

    }

    for (int jj = 0; jj < _channel; jj++)
    {
        for (int m = 0; m < _buffer - index; m++)
        {

            ary[jj][m] = ary[jj][m + index];
        }
    }
    //offset -----------------------------
    return ary;
}


double** Usbut::autocorr(int _buffer_a, double** farr)
{


    _buffer = _buffer_a;

    for (int jj = 0; jj < _channel; jj++)
    {
        for (int m = 0; m < _buffer; m++)
        {

            auto_ary[jj][m] = 0.0;
        }
    }


    for (int jj = 0; jj < _channel; jj++)
    {

        for (int m = 0; m < _buffer; m++)
        {
            for (int n = 0; n < _buffer - m; n++)
            {



                auto_ary[jj][m] = auto_ary[jj][m] + farr[jj][n] * farr[jj][n + m];


            }

        }

    }




    return auto_ary;
}




#endif