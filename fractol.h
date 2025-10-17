/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractol.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ztoptas <ztoptas@student.42kocaeli.com.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/17 20:29:36 by ztoptas           #+#    #+#             */
/*   Updated: 2025/10/17 20:29:36 by ztoptas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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
    double  re;
    double  im;
}               t_complex;

typedef struct s_image
{
    void    *img_ptr;
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
void    print_right_usage_and_exit(void);
int     parse_arguments(int argc, char **argv, t_fractol *f);
int	ft_strncmp(const char *s1, const char *s2, size_t n);
double  ft_atof(const char *str);
int draw_fractal(t_fractol *f);
int julia_iter(t_complex z, t_complex c);
t_complex complex_square(t_complex z);
int mandelbrot_iter(t_complex c);
int init_mlx(t_fractol *f);
int clean_exit(t_fractol *f);
int key_hook(int keycode, t_fractol *f);
void setup_mlx_hooks(t_fractol *f);
int     close_window(t_fractol *f);

#endif