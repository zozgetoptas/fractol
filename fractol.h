#ifndef FRACTOL_H
# define FRACTOL_H

#include <stdlib.h>
#include <unistd.h> 
#include <stdio.h>
#include <math.h>
#include "mlx.h"

#define WIDTH 800
#define HEIGHT 800
#define MAX_ITER 50

// mendelbrot
// z(n+1) = z(n)² + c
/* Her bir pikselin kümenin bir parçası olup olmadığını test etmek için,
z0 başlangıç değeri sıfır (0) olarak sabit tutulur.
Formüldeki c sabiti ise, test edilen pikselin karmaşık düzlemdeki koordinatlarını temsil eder
ve bu değer pikselden piksele değişir.
*/

// julia
// z(n+1) = z(n)² + c
/* burada, formüldeki c sabiti, tüm fraktal için dışarıdan belirlenen sabit bir parametre
olarak kullanılır ve fraktalın şeklini belirler.
İterasyonun başlangıç değeri olan z0 ise,
test edilen pikselin karmaşık düzlemdeki koordinatlarını temsil eder ve
bu değer pikselden piksele değişir.
*/

typedef struct s_complex
{
    double  real;
    double  imaginary;
}               t_complex;

typedef struct s_image
{
    void    *image_pointer;
    char    *addr;
    int     bpp;    // bits per pixel
    int     line_len;
    int     endian;
}               t_image;

typedef struct s_fractol
{
    void        *mlx;       // mlx_init() sonucu
    void        *win;       // mlx_new_window() sonucu
    t_image       img;        // Görüntü verileri
    char        *fractal_name; // Hangi fraktalın çizileceği
    // Harita ve Zoom Parametreleri
    double      min_re;
    double      max_re;
    double      min_im;
    double      max_im;
    // Julia için özel sabit (c) parametresi
    t_complex   julia_c;
}               t_fractol;

// Fonksiyon Prototipleri
// main.c
void    print_usage_and_exit(void);
int     parse_args(int argc, char **argv, t_fractol *f);

// mlx_utils.c
void    setup_mlx_hooks(t_fractol *f);
int     close_window(t_fractol *f);
int     key_hook(int keycode, t_fractol *f);

#endif