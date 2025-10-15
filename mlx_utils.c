// Başlatma ve Hata Kontrolü
int init_mlx(t_fractol *f)
{
    // 1. mlx bağlantısını başlat
    f->mlx = mlx_init();
    if (f->mlx == NULL)
    {
        // Hata durumunda bellek temizliği yap ve çık
        return (0);
    }
    
    // 2. Pencereyi oluştur (WIDTH ve HEIGHT daha önce #define edilmiş olmalı)
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
    // ESC tuşu genellikle 53 (MacOS) veya 65307 (Linux/X11) keycode'udur.
    if (keycode == 53 || keycode == 65307) 
    {
        clean_exit(f);
    }
    // Diğer tuşlar için (bonus kısımda kullanılacak)
    return (0);
}

void setup_mlx_hooks(t_fractol *f)
{
    // ESC tuşu olayını bağlama (Klavye yönetimi)
    // mlx_key_hook(window_ptr, function, param);
    mlx_key_hook(f->win, key_hook, f);

    // Pencere kapatma düğmesi (X) olayını bağlama
    // mlx_hook(window_ptr, event, mask, function, param);
    // Pencere kapatma olayı: 17 (DestroyNotify)
    mlx_hook(f->win, 17, 0, clean_exit, f); 
}

