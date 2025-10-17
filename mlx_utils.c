/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ztoptas <ztoptas@student.42kocaeli.com.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/17 19:47:19 by ztoptas           #+#    #+#             */
/*   Updated: 2025/10/17 19:47:19 by ztoptas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

int init_mlx(t_fractol *f)
{
    // 1. mlx bağlantısını başlat
    f->mlx = mlx_init();
    if (f->mlx == NULL)
        return (0);
    f->win = mlx_new_window(f->mlx, WIDTH, HEIGHT, "fractol");
    if (f->win == NULL)
    {
        // Pencere oluşturulamazsa, mlx bağlantısını da temizle
        // MiniLibX'in mlx_destroy_display() fonksiyonu kullanılabilir (bazı MLX versiyonlarında vardır)
        return (0);
    }
    
    // 3. Görüntü (Image) oluşturma ve adresini alma (Piksel boyama için)
    f->img.img_ptr = mlx_new_image(f->mlx, WIDTH, HEIGHT);
    f->img.addr = mlx_get_data_addr(f->img.img_ptr, &f->img.bpp,
                                    &f->img.line_len, &f->img.endian);
    
    return (1);
}

// MiniLibX kaynaklarını temizler ve programdan çıkar.
int clean_exit(t_fractol *f)
{
    // Görüntüyü temizle
    if (f->img.img_ptr)
        mlx_destroy_image(f->mlx, f->img.img_ptr);

    // Pencereyi temizle
    if (f->win)
        mlx_destroy_window(f->mlx, f->win);

    // MLX bağlantısını temizle (bazı MLX versiyonlarında gereklidir)
    // mlx_destroy_display(f->mlx); 

    exit(EXIT_SUCCESS);
}

int key_hook(int keycode, t_fractol *f)
{
    if (keycode == 65307) 
        clean_exit(f);
    return (0);
}

void setup_mlx_hooks(t_fractol *f)
{
    mlx_key_hook(f->win, key_hook, f);
    mlx_hook(f->win, 17, 0, clean_exit, f); 
}

