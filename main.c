/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ztoptas <ztoptas@student.42kocaeli.com.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/13 23:11:20 by ztoptas           #+#    #+#             */
/*   Updated: 2025/10/13 23:11:20 by ztoptas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

void    print_right_usage_and_exit(void)
{
    write(1, "Usage: ./fractol <fractal_name> [julia_re] [julia_im]\n", 54);
    write(1, "Available fractals:\n", 20);
    write(1, "  - mandelbrot\n", 15);
    write(1, "  - julia <C_re> <C_im>\n", 24);
    exit(1);
}

int parse_arguments(int argc, char **argv, t_fractol *f)
{
    if (argc < 2)
        print_right_usage_and_exit();
    f->fractal_name = argv[1];
    if (strcmp(f->fractal_name, "mandelbrot") == 0)
        return (1);
    else if (ft_strcmp(f->fractal_name, "julia") == 0)
    {
        if (argc < 4)
            print_right_usage_and_exit();
        f->julia_c.re = ft_atof(argv[2]);
        f->julia_c.im = ft_atof(argv[3]);
        return (1);
    }
    else
        print_usage_and_exit();
    return (0);
}

// main.c dosyanızın ana akışı
int main(int argc, char **argv)
{
    t_fractol   f;

    if (!parse_args(argc, argv, &f))
        return (EXIT_FAILURE);

    // 2. MiniLibX'i Başlatma, Pencere ve Görüntü Oluşturma
    if (!init_mlx(&f))
        return (EXIT_FAILURE);

    // 3. Olayları Bağlama (ESC ve X düğmesi için)
    setup_mlx_hooks(&f);

    // 4. Fraktal çizimini başlat (Sonraki gün yapılacak)
    // draw_fractal(&f); 

    // 5. MiniLibX Ana Döngüsünü Başlatma
    // Bu fonksiyon tüm olayları dinlemeye başlar
    mlx_loop(f.mlx); 

    return (EXIT_SUCCESS);
}