#ifndef GRAPH1010
#define GRAPH1010
#include <stdio.h>
#include <stdlib.h>
#include <vector>

using namespace std;
#define GRAPH_ENABLED true

class plot {

public:
    FILE* gp;
    bool enabled, persist;
    plot(bool _persist = false, bool _enabled = GRAPH_ENABLED) {
        enabled = _enabled;
        persist = _persist;
        if (enabled) {
            if (persist)
            {
                gp = _popen("gnuplot -persist", "w");
                fprintf(gp, "set terminal windows size 600, 250\n");

            }
            else
            {
                gp = _popen("gnuplot", "w");
                fprintf(gp, "set terminal windows size 600, 250\n");

            }

        }
    }



    void rplot_data(vector<double> x) {
        if (!enabled)
            return;
        //fprintf(gp, "set title '%s' \n", title);
        fprintf(gp, "plot '-' w points \n");
        for (int k = 0; k < x.size(); k++) {
            fprintf(gp, "%f\n", x[k]);
        }
        fprintf(gp, "e\n");
        fflush(gp);
    }

    void rplot_data(vector<double> x, vector<double> y) {
        if (!enabled)
            return;
        //fprintf(gp, "set title '%s' \n", title);
        fprintf(gp, "set xlabel 'Time'\n");
        fprintf(gp, "set ylabel 'Height (mm)'\n");
        fprintf(gp, "plot '-' w lines \n");

        for (int k = 0; k < x.size(); k++) {
            fprintf(gp, "%f %f \n", x[k], y[k]);
        }
        fprintf(gp, "e\n");
        fflush(gp);
    }


    void plot_data(const int N, int* x, int* y) {
        if (!enabled)
            return;


        fprintf(gp, "plot '-' w lines\n");
        for (int k = 0; k < N; k++) {
            fprintf(gp, "%d %d \n", x[k], y[k]);
        }
        fprintf(gp, "e\n");
        fflush(gp);
    }


    void mplot_data(const int N, double* x, double** y, int chn) {
        if (!enabled)
            return;

        fprintf(gp, "set key right box\n");
        fprintf(gp, "set xlabel 'Time (us)'\n");
        fprintf(gp, "set ylabel 'Amplitude'\n");


        fprintf(gp, "plot");
        for (int j = 0; j < chn; j++)
        {
            fprintf(gp, "'-' with lines title 'Ch #%d',", j);
        }
        fprintf(gp, "\n");


        for (int j = 0; j < chn; j++)
        {


            for (int i = 0; i < N; i++)
            {

                //if (i >= 0 && i < 20)
                //{
                //	y[j][i] = 0.0;
                //}

                fprintf(gp, "%f %f\n", x[i], y[j][i]);

            }

            fprintf(gp, "e\n");
            fflush(gp);

        }



    }



    ~plot() {
        if (enabled)
            _pclose(gp);
    }

};



#endif
