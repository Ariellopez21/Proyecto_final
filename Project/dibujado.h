#pragma once
void DRAW_MAP_SINCE_MAPA
(
    char dibujado[SIZE][SIZE],
    ALLEGRO_BITMAP* sky,
    ALLEGRO_BITMAP* platform,
    ALLEGRO_BITMAP* dirt,
    ALLEGRO_BITMAP* power_up,
    ALLEGRO_BITMAP* profile,
    ALLEGRO_BITMAP* bar,
    ALLEGRO_BITMAP* jg_bitmap
)
{
    int i, j;
    for (i = 0; i < SIZE; i++)
    {
        for (j = 0; j < SIZE; j++)
        {
            if (dibujado[i][j] == '0')
            {
                al_draw_bitmap(sky, j * PXL_W, i * PXL_H, 0);
            }
            if (dibujado[i][j] == 'D')
            {
                al_draw_bitmap(dirt, j * PXL_W, i * PXL_H, 0);
            }
            if (dibujado[i][j] == 'p')
            {
                al_draw_bitmap(platform, j * PXL_W, i * PXL_H, 0);
            }
            if (dibujado[i][j] == 'O')
            {
                al_draw_bitmap(profile, j * PXL_W, i * PXL_H, 0);
            }
            if (dibujado[i][j] == 'U')
            {
                al_draw_bitmap(power_up, j * PXL_W, i * PXL_H, 0);
                al_convert_mask_to_alpha(jg_bitmap, al_map_rgb(120, 8, 249));
            }
            if (dibujado[i][j] == 'B')
            {
                al_draw_bitmap(bar, j * PXL_W, i * PXL_H, 0);
            }
        }
    }
}