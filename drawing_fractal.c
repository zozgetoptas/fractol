#include "fractol.h"

// f->img.addr'a belirtilen x, y koordinatına 'color' değerini yazar.
static int get_color(int iter, int max_iter)
{
    int r;
    int g;
    int b;
    double t = (double)iter / max_iter;

    if (iter == max_iter)
        return (0x000000); // siyah
    // renk skalasını iterasyona göre haritala (0.0 ile 1.0 arası bir değer)
    r = (int)(9 * t * 255) % 256;
    g = (int)(15 * t * 255) % 256;
    b = (int)(30 * t * 255) % 256;

    // RGB formatına dönüştür: (R << 16) | (G << 8) | B
    return ((r << 16) | (g << 8) | b);
}
static void put_pixel(t_fractol *f, int x, int y, int color)
{
    char    *dst;

    // Hedef adres hesaplama formülü:
    // (satır numarası * bir satırın bayt cinsinden uzunluğu) + (sütun numarası * bir pikselin bayt cinsinden uzunluğu)
    dst = f->img.addr + (y * f->img.line_len + x * (f->img.bpp / 8));
    
    // Rengi bellek adresine yaz (MiniLibX'te genellikle 4 baytlık int kullanılır)
    *(unsigned int*)dst = color;
}

// Fraktalın başlangıç zoom ve konumunu ayarlar.
static void init_map_params(t_fractol *f)
{   
    f->min_re = -2.0;
    f->max_re = 2.0;
    f->min_im = -2.0;
    f->max_im = 2.0;
}

int draw_fractal(t_fractol *f)
{
    int         x;
    int         y;
    int         iter;
    t_complex   c;

    if (f->min_re == 0.0) 
        init_map_params(f);
    y = -1;
    while (++y < HEIGHT)
    {
        x = -1;
        while (++x < WIDTH)
        {
            c.re = f->min_re + (f->max_re - f->min_re) * x / WIDTH;
            c.im = f->min_im + (f->max_im - f->min_im) * y / HEIGHT;
            if (ft_strncmp(f->fractal_name, "mandelbrot", 11) == 0)
                iter = mandelbrot_iter(c);
            else if (ft_strncmp(f->fractal_name, "julia", 6) == 0)
                iter = julia_iter(c, f->julia_c);
            int final_color;
            final_color = get_color(iter, MAX_ITER);
            put_pixel(f, x, y, final_color);
        }
    }
    mlx_put_image_to_window(f->mlx, f->win, f->img.img_ptr, 0, 0);
    return (0);
}
