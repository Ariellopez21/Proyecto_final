#pragma once
bool func_menu(ranking rank[MAX_RANK])
{
    int mouseX = 10, mouseY = 10;
    bool click[] = { 0, 0, 0, 0 };
    click[0] = true;
    al_install_mouse();
    al_start_timer(timer);
    while (!done)
    {
        al_wait_for_event(queue, &event);
        switch (event.type)
        {
        case ALLEGRO_EVENT_DISPLAY_CLOSE:
            done = true;
            break;
        case ALLEGRO_EVENT_MOUSE_AXES:
            mouseX = event.mouse.x;
            mouseY = event.mouse.y;
            if (mouseX >= (106 * 2) && (mouseX <= 188 * 2) && mouseY >= (130 * 2) && (mouseY <= 162 * 2))    //START
                click[1] = true;                 //USAR BITMAP MENU_PRINCIPAL1                 
            else
                click[1] = false;

            if (mouseX >= (107 * 2) && mouseX <= (189 * 2) && mouseY >= (198 * 2) && mouseY <= (230 * 2))    //RANKING
                click[2] = true;                 //USAR BITMAP MENU_PRINCIPAL2
            else
                click[2] = false;

            if (mouseX >= (107 * 2) && mouseX <= (189 * 2) && mouseY >= (264 * 2) && mouseY <= (296 * 2))    //EXIT
                click[3] = true;                 //USAR BITMAP MENU_PRINCIPAL3
            else
                click[3] = false;

            if (!click[1] && !click[2] && !click[3])
                click[0] = true;
            else
                click[0] = false;
            break;
        case ALLEGRO_EVENT_MOUSE_BUTTON_DOWN:
            if (mouseX >= (106 * 2) && (mouseX <= 188 * 2) && mouseY >= (130 * 2) && (mouseY <= 162 * 2))    //START             
                if (event.mouse.button & 1)
                    return done;
            if (mouseX >= (107 * 2) && mouseX <= (189 * 2) && mouseY >= (198 * 2) && mouseY <= (230 * 2))    //RANKING
                if (event.mouse.button & 1)
                    func_rank(rank);
            if (mouseX >= (107 * 2) && mouseX <= (189 * 2) && mouseY >= (264 * 2) && mouseY <= (296 * 2))    //EXIT
                if (event.mouse.button & 1)
                    done = true;
            break;
        }
        if (al_is_event_queue_empty(queue) && (!done))
        {
            al_clear_to_color(al_map_rgb(0, 0, 0));
            if (click[0])
                al_draw_scaled_bitmap(menu_principal, 0, 0, 300, 400, 0, 0, WIDTH, HEIGHT, 0);
            else if (click[1])
                al_draw_scaled_bitmap(menu_principal1, 0, 0, 300, 400, 0, 0, WIDTH, HEIGHT, 0);
            else if (click[2])
                al_draw_scaled_bitmap(menu_principal2, 0, 0, 300, 400, 0, 0, WIDTH, HEIGHT, 0);
            else if (click[3])
                al_draw_scaled_bitmap(menu_principal3, 0, 0, 300, 400, 0, 0, WIDTH, HEIGHT, 0);
            al_flip_display();
        }
    }
    return done;
}
bool func_rank(ranking rank[MAX_RANK])
{
    ranking_bitmap = al_load_font("Font/sanes.TTF", 30, 0);
    int mouseX = 10, mouseY = 10, i=0, ALTO=142, ALTURA=0;
    al_install_mouse();
    al_start_timer(timer);
    while (!done)
    {
        al_wait_for_event(queue, &event);
        switch (event.type)
        {
        case ALLEGRO_EVENT_DISPLAY_CLOSE:
            done = true;
            break;
        case ALLEGRO_EVENT_MOUSE_AXES:
            mouseX = event.mouse.x;
            mouseY = event.mouse.y;
            break;
        case ALLEGRO_EVENT_MOUSE_BUTTON_DOWN:
            if (mouseX >= (35 * 2) && (mouseX <= 69 * 2) && mouseY >= (23 * 2) && (mouseY <= 52 * 2))    //BACK             
                if (event.mouse.button & 1)
                    return done;
            break;
        }
        if (al_is_event_queue_empty(queue) && (!done))
        {
            al_clear_to_color(al_map_rgb(0, 0, 0));
            al_draw_scaled_bitmap(menu_ranking, 0, 0, 300, 400, 0, 0, WIDTH, HEIGHT, 0);
            for(i=MAX_RANK-1; i>0; i--)
            {
                al_draw_textf(ranking_bitmap, al_map_rgb(255, 255, 255), 160, ALTO, 0, "%s", &rank[i].name);
                al_draw_textf(ranking_bitmap, al_map_rgb(255, 255, 255), 510, ALTO, 0, "%d", rank[i].points);
                ALTO = ALTO + 75;
            }
            ALTO = 142;

            al_flip_display();
        }
    }
    return done;
}
void func_instructions()
{
    int mouseX = 10, mouseY = 10;
    bool click = false;
    al_install_mouse();
    al_start_timer(timer);
    while (!done)
    {
        al_wait_for_event(queue, &event);
        switch (event.type)
        {
        case ALLEGRO_EVENT_DISPLAY_CLOSE:
            done = true;
            break;
        case ALLEGRO_EVENT_MOUSE_AXES:
            mouseX = event.mouse.x;
            mouseY = event.mouse.y;
            if (mouseX >= (232 * 2) && (mouseX <= 292 * 2) && mouseY >= (338 * 2) && (mouseY <= 390 * 2))    //START
                click = true;                 //USAR BITMAP MENU_INSTRUCTIONS1                 
            else
                click = false;
            break;
        case ALLEGRO_EVENT_MOUSE_BUTTON_DOWN:
            if (mouseX >= (232 * 2) && (mouseX <= 292 * 2) && mouseY >= (338 * 2) && (mouseY <= 390 * 2))    //BACK             
                if (event.mouse.button & 1)
                    return;
            break;
        }
        if (al_is_event_queue_empty(queue) && (!done))
        {
            al_clear_to_color(al_map_rgb(0, 0, 0));
            if (click)
                al_draw_scaled_bitmap(menu_instructions1, 0, 0, 300, 400, 0, 0, WIDTH, HEIGHT, 0);
            else
                al_draw_scaled_bitmap(menu_instructions, 0, 0, 300, 400, 0, 0, WIDTH, HEIGHT, 0);
            al_flip_display();
        }
    }
    return;
}
bool func_pause(bool pausa)
{
    int mouseX = 10, mouseY = 10;
    bool click[] = {0, 0, 0};
    click[0] = true;
    pausa = true;
    al_install_mouse();
    al_start_timer(timer);
    while (pausa)
    {
        al_wait_for_event(queue, &event);
        switch (event.type)
        {
        case ALLEGRO_EVENT_DISPLAY_CLOSE:
        {            
            done = true;
            pausa = false;
        }

            break;
        case ALLEGRO_EVENT_MOUSE_AXES:
            mouseX = event.mouse.x;
            mouseY = event.mouse.y;
            if (mouseX >= (94 + 150) && (mouseX <= 202 + 150) && mouseY >= (80 + 300) && (mouseY <= 116 + 300))    //CONTINUE
                click[1] = true;                 //USAR BITMAP PAUSE1                 
            else
                click[1] = false;
            if (mouseX >= (95 + 150) && (mouseX <= 201 + 150) && mouseY >= (124 + 300) && (mouseY <= 160 + 300))    //EXIT
                click[2] = true;                 //USAR BITMAP PAUSE2                 
            else
                click[2] = false;
            if (!click[1] && !click[2])
                click[0] = true;
            else
                click[0] = false;
            break;
        case ALLEGRO_EVENT_MOUSE_BUTTON_DOWN:
            if (mouseX >= (94 + 150) && (mouseX <= 202 + 150) && mouseY >= (80 + 300) && (mouseY <= 116 + 300))                     //CONTINUE
                if (event.mouse.button & 1)     //CONTINUE
                {
                    pausa = false;
                    done = false;
                }
            if (mouseX >= (95 + 150) && (mouseX <= 201 + 150) && mouseY >= (124 + 300) && (mouseY <= 160 + 300))                    //EXIT
                if (event.mouse.button & 1)     //EXIT
                {
                    pausa = false;
                    done = true;
                }
            break;
        }
        if (al_is_event_queue_empty(queue) && (!done))
        {
            if (click[0])
                al_draw_bitmap(pause, 150, 300, 0);
            else if (click[1])
                al_draw_bitmap(pause1, 150, 300, 0);
            else if (click[2])
                al_draw_bitmap(pause2, 150, 300, 0);
            al_flip_display();
        }
    }
    return done;
}