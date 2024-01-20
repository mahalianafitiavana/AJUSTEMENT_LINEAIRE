#include <stdio.h>
#include <math.h>
#include <string.h>

float f (float x);
float df(float x);
void gplot (float x0, float alpha, float xmin , float xmax, float ymin, float ymax);
int main(){

    printf("Trouver le point minimal par la méthode de la descente du gradiant\n");
    float x0 = 6, alpha = 0.2 , xmin = -6,xmax= 8, ymin = -2,ymax = 4;
        gplot(x0,alpha,xmin,xmax,ymin,ymax);
    /* char rep[2] = "o";
    while (1) {
        printf("Entrez alpha : ");
        scanf("%f ", &alpha);
        printf("Faure un autre essai? (o/n) : ");scanf("%s",rep);
        if (strcmp(rep,"o") != 0 ) break;        

    } */
    

    return 0;
}

void gplot (float x0, float alpha, float xmin , float xmax, float ymin, float ymax){
    FILE *GP = popen("gnuplot -persist","w");
    float x = x0;
    int np = 50;
    if(GP){
        //plot setup
        fprintf(GP,"set term wxt size 640 , 480\n" );
        fprintf(GP,"set title 'Descnte du gradiant' \n" );
        fprintf(GP, "set xlabel 'x'\n");
        fprintf(GP, "set ylabel 'y'\n");
        fprintf(GP,"set xzeroaxis\n" );
        fprintf(GP,"set xrange [%f:%f]\n",xmin,xmax );
        fprintf(GP,"set yrange [%f:%f]\n",ymin, ymax );

        //put data in a reusable internal data blocks
        fprintf(GP,"$data  << EOF\n");
        fprintf(GP,"%f %f\n",x, f(x));
        for(int i = 0 ; i < np ;i++){
            x = x0 - alpha * df(x0);
            fprintf(GP,"%f %f\n",x,f(x));   //data
            x0 = x;
        }
        fprintf(GP,"EOF\n");

        fprintf(GP,"$dataf << EOF\n ");
        float dx = (xmax - xmin)/200;
        x = xmin;
        for (int i = 0; i < 200; i++) {
            fprintf(GP, "%f %f\n", x, f(x));
            x += dx;
        }
        fprintf(GP, "EOF\n");

        // plot now
        fprintf(GP, "plot \"$data\" with lines title 'Gradient Descent' linecolor rgb 'black' linewidth 4, \\\n");
        fprintf(GP, "     \"$dataf\" with lines title 'Fonction f(x)' \n");

        // send commands to gnuplot and close pipe
        
        fflush(GP);
        pclose(GP);
        
    }
    else printf("gnuplot not found ...\n ");
}
float df(float x){  
    return (-x*x *sin(x)+ 2 * x*cos(x)-1)/10;
}
float f (float x){
    return (x*x*cos(x)-x)/10;
}
