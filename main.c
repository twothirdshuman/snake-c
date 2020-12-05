#include <stdio.h>
#include <stdbool.h>

#ifdef _WIN32
#include <Windows.h>
#else
#include <unistd.h>
#endif

//documentation for sdl: https://wiki.libsdl.org/
#include <SDL2/SDL.h>

void game(const char* settings);


SDL_Window* window;//the window
SDL_Renderer* renderer;//the render target

const Uint16 width = 1080;
const Uint16 height = 720;

int main(int argc, char* args[]){

    //init sdl



    if (SDL_Init(SDL_INIT_EVERYTHING) > 0){
        printf("SDL_Init FAILED. SDL_ERROR: ");
        printf(SDL_GetError());
        printf("\n");
        return -1;
    }

    //init sdl with images
    if (!(IMG_Init(IMG_INIT_PNG))){
       printf("IMG_INIT HAS FAILED. IMG_ERROR: ");
       printf(SDL_GetError());
       printf("\n");
       return -1;
    }
   
    //create a window



    window = SDL_CreateWindow("Snake!", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, width, height, SDL_WINDOW_SHOWN);//create the window

    //if faield
    if (window == NULL){
        printf("WINDOW FAILED TO INIT. ERROR: ");
        printf(SDL_GetError());
        printf("\n");
        return -1;
    }

    //create the render target
    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

    printf(SDL_GetError());



    //make a event
    SDL_Event event;



    //game loop

    Uint16 mousePosX;
    Uint16 mousePosY;

    while (1){


        const Uint16 sizeX = width / 15;
        const Uint16 sizeY = height / 10;

        //do all the events that occur
        while (SDL_PollEvent(&event)){

            //if you pressed the exit button exit
            switch (event.type){
                case SDL_QUIT:

                    goto quit;
                    break;
                case SDL_MOUSEMOTION:
                    mousePosX = event.button.x;
                    mousePosY = event.button.y;
                    break;
                case SDL_MOUSEBUTTONDOWN:
                    if (event.button.button == SDL_BUTTON_LEFT){
                        SDL_Rect rect;

                        rect.x = width / 2 - 100;
                        rect.w = 200;
                        rect.y = height / 2 - 50;
                        rect.h = 100;


                        if (mousePosX > rect.x && mousePosX < rect.x + rect.w && mousePosY > rect.y && mousePosY < rect.y + rect.h){
                            game(NULL);
                        }
                    }


            }
        }



        



        SDL_RenderClear(renderer);


        //-----------background-----------------


        for (int n = 0; n < 15; n++){
            for (int i = 0; i < 10; i++){

                SDL_Rect area;

                area.x = sizeX * n;
                area.y = sizeY * i;
                area.w = sizeX * (n + 1);
                area.h = sizeY * (i + 1);

                if ((n + (i % 2)) % 2 == 0)
                    SDL_SetRenderDrawColor(renderer, 142, 204, 57, 255);
                else
                    SDL_SetRenderDrawColor(renderer, 167, 217, 72, 255);

                SDL_RenderFillRect(renderer, &area);
            }
        }

        SDL_Rect rect;

        rect.x = width / 2 - 100;
        rect.w = 200;
        rect.y = height / 2 - 50;
        rect.h = 100;

        SDL_SetRenderDrawColor(renderer, 10, 70, 255, 255);
        SDL_RenderFillRect(renderer, &rect);



        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);

        SDL_RenderDrawLine(renderer, width / 2 + 25, height / 2, width / 2 - 25, height / 2 + 25);
        SDL_RenderDrawLine(renderer, width / 2 + 25, height / 2, width / 2 - 25, height / 2 - 25);



        SDL_RenderDrawLine(renderer, width / 2 - 25, height / 2 + 25, width / 2 - 25, height / 2 - 25);



        //------------------end------------------



        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);

        SDL_RenderPresent(renderer);

    }
    quit:


    //cleanup
    SDL_DestroyWindow(window);
    //quit
    SDL_Quit();

    return 0;
}

char OppositeDirection(char direction){
    switch (direction){
        case 'L':
        return 'R';
        case 'R':
        return 'L';
        case 'U':
        return 'D';
        case 'D':
        return 'U';
    }
    return ' ';
}

void game(const char* settings){

    const Uint8 width = 15;
    const Uint8 height = 10;

    SDL_Event event;


//--------------OnStart-----------------
    Uint16 window_width = 1080;
    Uint16 window_height = 720;
    Uint16 Snake_length = 5;
    Uint16 game_field[width * height];
    char currentDirection = 'R';
    char buttonQue[3] = {' ', ' ', ' '};
    bool SaveFrame = false;

    char Frame = 0;


    Snake_length = 5;


	for (Uint16 n = 5; n < width * height; n++) {
		game_field[n] = 0;
	}


	for (Uint16 n = 0; n < 5; n++) {
		game_field[n] = n + 1;
	}
	game_field[137] = 255;

	Uint16 x = 5;
    Uint16 y = 0;
//--------------------------------------



    while (1){

        usleep(10000);

        while (SDL_PollEvent(&event)){

            switch (event.type){
                case SDL_QUIT:

                    exit(0);
                    break;
                case SDL_KEYDOWN:
                   char newDirection = 0;

                   switch (event.key.keysym.sym){

                        case SDLK_UP:
                        newDirection = 'U';
                        break;
                        case SDLK_DOWN:
                        newDirection = 'D';
                        break;
                        case SDLK_RIGHT:
                        newDirection = 'R';
                        break;
                        case SDLK_LEFT:
                        newDirection = 'L';
                        break;
                   }

                   for (Uint8 n = 0; n < 3; n++){
                       if (buttonQue[n] == ' ' && newDirection != 0){
                           buttonQue[n] = newDirection;
                           break;
                       }
                   }



                   break;
            }
        }

        SDL_RenderClear(renderer);



        Frame++;
        if (Frame % 9 == 0) {

            Frame = 0;
            for (int n = 0; n < width * height; n++) {

                if (game_field[n] == Snake_length) {

                    if (buttonQue[0] != ' '){

                        if (buttonQue[0] != OppositeDirection(currentDirection))
                            currentDirection = buttonQue[0];

                        buttonQue[0] = buttonQue[1];
                        buttonQue[1] = buttonQue[2];
                        buttonQue[2] = ' ';
                    }

                    x = n % 15;
                    y = n / 15;

                    switch (currentDirection)
                    {
                    case 'R':
                        x++;
                        break;
                    case 'L':
                        x--;
                        break;
                    case 'U':
                        y--;
                        break;
                    case 'D':
                        y++;
                        break;
                    default:
                        break;
                    }
                    if (x > 16000) {
                        x = 14;
                    }
                    if (y > 16000) {
                        y = 9;
                    }
                    y %= 10;
                    x %= 15;



                    if (game_field[y * 15 + x] == 255) {
                        Snake_length++;
                        game_field[y * 15 + x] = Snake_length;
                        for (int n = 0; n < width * height; n++) {
                            if (game_field[n] != 0) {
                                game_field[n]++;
                            }
                        }
                        srand(x + y + Snake_length + currentDirection + (long int)window);
                        Uint16 new_apple;
                        do {
                            new_apple = rand() % width * height;
                        } while (game_field[new_apple] != 0);
                        game_field[new_apple] = 255;
                        break;
                    }

                    if (game_field[y * 15 + x] != 0 && game_field[y * 15 + x] != 1) {
                        for (Uint16 n = 0; n < width * height; n++)
                            if (game_field[n] != 0)
                                if (game_field[n] != 255)
                                    game_field[n] += 1;

                        if (SaveFrame)
                            goto out;
                        SaveFrame = true;


                        usleep(200000);
                        break;

                    }
                    else {
                        game_field[y * 15 + x] = Snake_length + 1;
                        SaveFrame = false;
                    }

                }


            }
            for (Uint16 n = 0; n < width * height; n++)
                if (game_field[n] != 0)
                    if (game_field[n] != 255)
                        game_field[n] -= 1;
        }
        //render
        const Uint16 sizeX = window_width / width;
        const Uint16 sizeY = window_height / height;

        SDL_SetRenderDrawColor(renderer, 128, 128, 128, 255);

        SDL_RenderFillRect(renderer, NULL);

        for (int n = 0; n < 15; n++) {
            for (int i = 0; i < 10; i++) {

                SDL_Rect area;

                area.x = sizeX * n;
                area.y = sizeY * i;
                area.w = sizeX * (n + 1);
                area.h = sizeY * (i + 1);

                if (game_field[i * 15 + n] == 0)
                    if ((n + (i % 2)) % 2 == 0)
                        SDL_SetRenderDrawColor(renderer, 142, 204, 57, 255);
                    else
                        SDL_SetRenderDrawColor(renderer, 167, 217, 72, 255);
                   
                else if (game_field[i * 15 + n] == 255)
                    SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
   
                else
                   
                    SDL_SetRenderDrawColor(renderer, 0, 255 - ((((float)game_field[i * 15 + n] / Snake_length) * 128) + 70), 255, 255);

                SDL_RenderFillRect(renderer, &area);
            }
        }

        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);

        SDL_RenderPresent(renderer);

    }
    out:



    return;
}
