#pragma once
void DRAW_MAP_SINCE_MAPA
(
    char dibujado[SIZE][SIZE],
    ALLEGRO_BITMAP* sky,
    ALLEGRO_BITMAP* platform,
    ALLEGRO_BITMAP* dirt
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
            /*if (dibujado[i][j] == 'E')
            {
                al_draw_bitmap_region(futbol_img, 0, 0, PXL_W, PXL_H, j * PXL_W, i * PXL_H, 0);
                al_convert_mask_to_alpha(futbol_img, al_map_rgba(255, 0, 0, 255));
            }*/
        }
    }
}