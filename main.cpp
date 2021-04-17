// Programa que permite hallar las curvas de nivel de un terreno por el metodo de cuadrícula,
// a partir de los datos tomados en campo y además genera la nube de puntos lista para insertar en Autocad 

// 2021-04-17
// Cristian Santiago Tovar Bejarano <ctovar@unal.edu.co>

# include <iostream>    // Input/Output Stream:  cin, cout etc.
# include  <fstream>    // Para leer y escribir en archivos.
# include <iomanip>
# include <cmath>         // math.h: pow(x,y), fabs(x), abs(x), cos(x), sin(x), acos(x), exp(x), log(x), log10(x) etc.

# include <iomanip>     // Input/output manipulators - formateo de salida: setw etc.
# include <cstdio>         // standard input-output : printf: %d ó %i: integer, %f: float, %lf: double, %e - %E: exponente, %c: char, %s:string
# include <cstdlib>      // stdlib.h: standard library; para:  system ("pause") etc.;
# include <sstream>


#define PI 3.14159265
using namespace std;  // si no se usa --> usar extensión ".h" ej: # include <iostream.h>

// PARTE EDITABLE.........................

int const rows = 5; // Numero de filas
int const columns = 13; // Numero de columnas (abscisas)
float h_length = 20; // Longitud en el sentido horiuzontal
float v_length = 10; // Longitud en el sentido vertical
float intervalo = 0.2;
float start_point = 160; // Punto de partida de las abscisas

//  .......................................

////////// NO MODIFICAR ///////////
int contador = 0;
int columns_limit = columns - 1;
int rows_limit = rows - 1;
float const angle = atan(v_length/h_length)*180/PI;
float const d_length = sqrt((h_length * h_length) + (v_length * v_length));

float* getHigherFloat(float a, float b);
float getNextInteger(float f);
int countIntegers(float* a);

void generate_answer (float a, float b, float length_d);
void generate_points_h (float a, float b, float length_d, float coor_x, float coord_y, bool control);
void generate_points_v (float a, float b, float length_d, float coor_x, float coord_y, bool control);
void generate_points_r (float a, float b, float length_d, float coor_x, float coord_y, bool control);
void generate_points_l (float a, float b, float length_d, float coor_x, float coord_y, bool control);
void generate_horizontal (float array_float [rows][columns]);
void generate_horizontal_p (float array_float [rows][columns]);
void generate_vertical (float array_float [rows][columns]);
void generate_vertical_p (float array_float [rows][columns]);
void generate_diagonal_r (float array_float [rows][columns]);
void generate_diagonal_r_p (float array_float [rows][columns]);
void generate_diagonal_l (float array_float [rows][columns]);
void generate_diagonal_l_p (float array_float [rows][columns]);

ofstream ofs ("salida.txt");
ofstream cloud ("nube_de_puntos.txt");


int main()
{

    float arreglo [rows][columns] = {

    {589.71,591.72,592.7,593.64,593.91,594.28,596.07,596.02,595.96,595.31,594.96,595.86,593.53},
    {588.95,590.33,591.81,592.3,592.49,593.69,595.94,595.57,596.97,597.11,593.65,595.26,593.23},
    {587.87,589.72,590.17,591.96,591.49,591.76,595.24,595.78,597.31,599.51,599.86,594.97,592.67},
    {587.96,590.17,589.31,590.12,592.09,591.27,594.17,595.24,598.69,599.3,599.51,599.02,593.06},
    {588.29,591.72,590.48,589.49,591.32,591.91,593.14,596.5,599.71,599.93,599.66,598.3,597.96}

    };

    ofs.clear();
    cloud.clear();


    generate_horizontal(arreglo);
    generate_vertical(arreglo);
    generate_diagonal_r(arreglo);
    //generate_diagonal_l(arreglo);

    generate_horizontal_p(arreglo);
    generate_vertical_p(arreglo);
    generate_diagonal_r_p(arreglo);
    //generate_diagonal_l_p(arreglo);

    cout << "Total de operaciones realizadas " << contador << endl;
    cout << d_length << endl;

    return 0;
}



float* getHigherFloat (float a, float b){
    float* X = new float [2];
    if(a < b){
        X[0]=a;
        X[1]=b;
    } else {
        X[0]=b;
        X[1]=a;
    }
    return X;
}

float getNextInteger(float f){
    float a = round(f);
    float comp = a - f;

    if (comp > 0){
       while (a > f){
            a = a - intervalo;
       }
       return a;
    } else {
        a++;
        while (a > f){
            a = a - intervalo;
       }
        return a;
    }
}

int countIntegers(float* a){

    float prueba = getNextInteger(a[0]);
    int cant=0;
    while (prueba < a[1]){
        prueba = prueba + intervalo;
        cant++;
    }
    return cant;
}

void generate_answer (float a, float b, float length_d){
    float* Y = getHigherFloat(a,b);
    float prueba = getNextInteger(Y[0]);

    float dif = Y[1]-Y[0];
    ofs << "   " <<length_d << "m --> " << dif << "\n";

    if (countIntegers(Y) != 0){
       while (prueba < Y[1]){

        float result_a = ((prueba-Y[0])*length_d)/dif;

        ofs << "   X" <<prueba << "       " << prueba-Y[0] << "=>" << fixed << setprecision(2) << result_a << "\n"; //Genera la respuesta en el archivo de

        prueba = prueba + 0.2;
        contador ++;
       }
    } else {
    ofs << "No hay valores en el intervalo" << "\n";
    }

}

void generate_points_h (float a, float b, float length_d, float coor_x, float coord_y, bool control){
    float* Y = getHigherFloat(a,b);
    float prueba = getNextInteger(Y[0]);

    float dif = Y[1]-Y[0];

    if (countIntegers(Y) != 0){
       while (prueba < Y[1]){

        float result_a = ((prueba-Y[0])*length_d)/dif;

            if (control){
                cloud << fixed << setprecision(2) << "  " << coor_x + result_a << "," << coord_y << "    " << prueba << "\n"; // genera la respuesta en el archivo de nube de puntos
            } else {
                cloud << fixed << setprecision(2) << "  " << coor_x - result_a << "," << coord_y << "    " << prueba << "\n"; // genera la respuesta en el archivo de nube de puntos
        }
        prueba = prueba + 0.2;
        contador ++;
       }
    } else {
    //NOOP
    }

}

void generate_points_v (float a, float b, float length_d, float coor_x, float coord_y, bool control){
    float* Y = getHigherFloat(a,b);
    float prueba = getNextInteger(Y[0]);

    float dif = Y[1]-Y[0];

    if (countIntegers(Y) != 0){
       while (prueba < Y[1]){

        float result_a = ((prueba-Y[0])*length_d)/dif;

            if (control){
                cloud << fixed << setprecision(2) << "  " << coor_x  << "," << coord_y + result_a << "    "<< prueba << "\n"; // genera la respuesta en el archivo de nube de puntos
            } else {
                cloud << fixed << setprecision(2) << "  " << coor_x  << "," << coord_y - result_a << "    "<< prueba << "\n"; // genera la respuesta en el archivo de nube de puntos
        }
        prueba = prueba + 0.2;
        contador ++;
       }
    } else {
    //NOOP
    }

}

void generate_points_r (float a, float b, float length_d, float coor_x, float coord_y, bool control){
    float* Y = getHigherFloat(a,b);
    float prueba = getNextInteger(Y[0]);

    float dif = Y[1]-Y[0];

    float azimut;
    float coseno;
    float seno;

    if (countIntegers(Y) != 0){
       while (prueba < Y[1]){

        float result_a = ((prueba-Y[0])*length_d)/dif;

            if (control){
                azimut = 90 - angle;
                coseno = (cos(azimut * PI/180))*result_a;
                seno = (sin(azimut * PI/180))*result_a;

                cloud << fixed << setprecision(2) << "  " << coor_x + seno << "," << coord_y + coseno << "    " << prueba << "\n"; // genera la respuesta en el archivo de nube de puntos
            } else {
                azimut = 270 - angle;
                coseno = (cos(azimut * PI/180))*result_a;
                seno = (sin(azimut * PI/180))*result_a;

                cloud << fixed << setprecision(2) << "  " << coor_x + seno << "," << coord_y + coseno << "    " << prueba << "\n"; // genera la respuesta en el archivo de nube de puntos
        }
        prueba = prueba + 0.2;
        azimut = NULL;
        coseno = NULL;
        seno = NULL;
        contador ++;
       }
    } else {
    //NOOP
    }

}

void generate_points_l (float a, float b, float length_d, float coor_x, float coord_y, bool control){
    float* Y = getHigherFloat(a,b);
    float prueba = getNextInteger(Y[0]);

    float dif = Y[1]-Y[0];

    float azimut;
    float coseno;
    float seno;

    if (countIntegers(Y) != 0){
       while (prueba < Y[1]){

        float result_a = ((prueba-Y[0])*length_d)/dif;

            if (control){
                azimut = 90 + angle;
                coseno = (cos(azimut * PI/180))*result_a;
                seno = (sin(azimut * PI/180))*result_a;

                cloud << fixed << setprecision(2) << "  " << coor_x + seno << "," << coord_y + coseno << "    " << prueba << "\n"; // genera la respuesta en el archivo de nube de puntos
            } else {
                azimut = 270 + angle;
                coseno = (cos(azimut * PI/180))*result_a;
                seno = (sin(azimut * PI/180))*result_a;

                cloud << fixed << setprecision(2) << "  " << coor_x + seno << "," << coord_y + coseno << "    " << prueba << "\n"; // genera la respuesta en el archivo de nube de puntos
        }
        prueba = prueba + 0.2;
        azimut = NULL;
        coseno = NULL;
        seno = NULL;
        contador ++;
       }
    } else {
    //NOOP
    }

}

void generate_horizontal (float array_float [rows][columns]){ //Genera

    for (int i = 0; i < rows; i++){

      ofs << "Abscisa " << i << "\n";

        for (int j = 0; j < columns_limit; j++){

            float a = array_float[i][j];
            float b = array_float[i][j+1];

            ofs << "   " << a << "     "<< b << "\n";

            generate_answer(a,b,h_length);

            ofs << "_______________________" << "\n";
        }

       ofs << "======================================" << "\n";
    }

    float a = NULL;
    float b = NULL;
    array_float = NULL;
}

void generate_horizontal_p (float array_float [rows][columns]){ //Genera

    for (int i = 0; i < rows; i++){

        for (int j = 0; j < columns_limit; j++){

            int coor_x = (j * h_length) + start_point;//Halla la coordenada x de la cudricula
            int coor_i = (i * v_length);//Hallala coordenada y de la cudricula

            float a = array_float[i][j];
            float b = array_float[i][j+1];

            cloud << "  " << coor_x << "," << coor_i << "    " << a << "\n";//Imprime las coordenadas X,Y en el archivo de texto

            if (a < b){
                 generate_points_h(a,b,h_length, coor_x, coor_i, 1);
            } else {
                coor_x = ((j+1) * h_length) + start_point;
                generate_points_h(a,b,h_length, coor_x, coor_i, 0);
            }
        }
    }

    float a = NULL;
    float b = NULL;
    array_float = NULL;
}

void generate_vertical (float array_float [rows][columns]){
   for (int i = 0; i < columns; i++){

      ofs << "Transversal " << i << "\n";

        for (int j = 0; j < rows_limit; j++){
            float a = array_float[j][i];
            float b = array_float[j+1][i];

            ofs << "   " << a << "     "<< b << "\n";
            generate_answer(a,b,v_length);
            ofs << "_______________________" << "\n";
        }

       ofs << "======================================" << "\n";
    }

    float a = NULL;
    float b = NULL;
    array_float = NULL;
}

void generate_vertical_p (float array_float [rows][columns]){
   for (int i = 0; i < columns; i++){

        for (int j = 0; j < rows_limit; j++){

            int coor_x = (i * h_length)+start_point;//Halla la coordenada x de la cudricula
            int coor_i = (j * v_length);//Hallala coordenada y de la cudricula

            float a = array_float[j][i];
            float b = array_float[j+1][i];

            if(a < b){
                generate_points_v(a,b,v_length,coor_x,coor_i,1);
            } else {
                coor_i=((j+1)*10);
                generate_points_v(a,b,v_length,coor_x,coor_i,0);
            }
        }

    }

    float a = NULL;
    float b = NULL;
    array_float = NULL;
}

void generate_diagonal_r (float array_float [rows][columns]){
   for (int i = 0; i < columns_limit; i++){

      ofs << "Diagonales en la columna " << i << "\n";

        for (int j = 0; j < rows_limit; j++){

            float a = array_float[j][i];
            float b = array_float[j+1][i+1];

            ofs << "   " << a << "     "<< b << "\n";

            generate_answer(a,b,d_length);
            ofs << "_______________________" << "\n";
        }

       ofs << "======================================" << "\n";
    }

    float a = NULL;
    float b = NULL;
    array_float = NULL;
}

void generate_diagonal_r_p (float array_float [rows][columns]){

   for (int i = 0; i < columns_limit; i++){

        for (int j = 0; j < rows_limit; j++){

            int coor_x = (i * h_length)+ start_point;//Halla la coordenada x de la cudricula
            int coor_i = (j * v_length);//Hallala coordenada y de la cudricula

            float a = array_float[j][i];
            float b = array_float[j+1][i+1];

            if(a < b){
                generate_points_r(a,b,d_length,coor_x,coor_i,1);
            } else {
                int coor_x = ((i + 1) * h_length)+start_point;//Halla la coordenada x de la cudricula
                int coor_i = ((j + 1) * v_length);//Hallala coordenada y de la cudricula
                generate_points_r(a,b,d_length,coor_x,coor_i,0);
            }

            coor_x = NULL;
            coor_i = NULL;
        }

    }

    float a = NULL;
    float b = NULL;
    array_float = NULL;
}

void generate_diagonal_l (float array_float [rows][columns]){
   for (int i = 0; i < columns_limit; i++){

      ofs << "Diagonales en la columna " << i << "\n";

        for (int j = 0; j < rows_limit; j++){
            float a = array_float[j][i+1];
            float b = array_float[j+1][i];

            ofs << "   " << a << "     "<< b << "\n";

            generate_answer(a,b,d_length);
            ofs << "_______________________" << "\n";
        }

       ofs << "======================================" << "\n";
    }

    float a = NULL;
    float b = NULL;
    array_float = NULL;
}

void generate_diagonal_l_p (float array_float [rows][columns]){

   for (int i = 0; i < columns_limit; i++){

        for (int j = 0; j < rows_limit; j++){

            int coor_x = (i * h_length) + start_point;//Halla la coordenada x de la cudricula
            int coor_y = ((j + 1) * v_length);//Halla la coordenada y de la cudricula

            float a = array_float[j][i+1];
            float b = array_float[j+1][i];

            if(a > b){
                generate_points_l(a,b,d_length,coor_x,coor_y,1);
            } else {

            coor_x = ((i + 1) * h_length)+start_point;//Halla la coordenada x de la cudricula
            coor_y = (j * v_length);//Halla la coordenada y de la cudricula

                generate_points_l(a,b,d_length,coor_x,coor_y,0);
            }

            coor_x = NULL;
            coor_y = NULL;
        }

    }

    float a = NULL;
    float b = NULL;
    array_float = NULL;
}
//....... FIN ...............
