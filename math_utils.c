/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   math_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ztoptas <ztoptas@student.42kocaeli.com.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/17 21:12:34 by ztoptas           #+#    #+#             */
/*   Updated: 2025/10/17 21:12:34 by ztoptas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "fractol.h"

// Julia iterasyonunu hesaplar.
// Z başlangıç değeri piksel koordinatlarıdır.
// C ise sabit parametredir (f->julia_c).
int julia_iter(t_complex z, t_complex c)
{
    int iter;

    iter = 0;
    while (iter < MAX_ITER) // MAX_ITER, fractol.h'de tanımlı
    {
        // |z|^2 > 4 ise kaçar
        if ((z.re * z.re + z.im * z.im) > 4.0)
            return (iter); // Kaçış süresi
        
        // z_next = z^2 + c
        z = complex_square(z);
        z.re += c.re;
        z.im += c.im;
        
        iter++;
    }
    return (MAX_ITER); // Kümenin içinde kaldı
}

t_complex complex_square(t_complex z)
{
    t_complex result;

    result.re = z.re * z.re - z.im * z.im; // x^2 - y^2
    result.im = 2.0 * z.re * z.im;          // 2xy
    return (result);
}
// Bir c karmaşık sayısı için Mandelbrot iterasyonunu hesaplar.
// Kaçış süresini (renk bilgisi) döndürür.
int mandelbrot_iter(t_complex c)
{
    t_complex z;
    int       iter;

    z.re = 0.0; // Mandelbrot için başlangıç z0 = 0
    z.im = 0.0;
    iter = 0;

    while (iter < MAX_ITER) // MAX_ITER bir sabit olmalı
    {
        // |z|^2 > 4 ise kaçar
        if ((z.re * z.re + z.im * z.im) > 4.0)
            return (iter); // Kaçış süresi
        
        // z_next = z^2 + c
        z = complex_square(z);
        z.re += c.re;
        z.im += c.im;
        
        iter++;
    }
    return (MAX_ITER); // Kümenin içinde kaldı (siyah renk olabilir)
}
