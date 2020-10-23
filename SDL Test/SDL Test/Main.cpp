#include <iostream>
#include <SDL.h>
#include <SDL_image.h>
using namespace std;

SDL_Surface* LoadBMP(const char* src)
{
    SDL_Surface *bmp = nullptr;
    bmp = SDL_LoadBMP(src);
    if (bmp == nullptr)
        cout << "Failled to load BMP : " << src << " : " << SDL_GetError() << endl;
    return bmp;
}

SDL_Surface *optimizedSurface(string src, SDL_Surface *windowSurface)
{
    SDL_Surface* optimizedSurface = nullptr;
    SDL_Surface* surface = SDL_LoadBMP(src.c_str());
    if (surface == NULL)
        cout << "Error::Failed to load BMP : " << src << " : " << SDL_GetError() << endl;
    else
    {
        optimizedSurface = SDL_ConvertSurface(surface, windowSurface->format, 0);
        if (optimizedSurface == NULL)
            cout << "Error::Failled to convert surface for BMP : " << src << " : " << SDL_GetError() << endl;
    }
    
    SDL_FreeSurface(surface);

    return optimizedSurface;
}

SDL_Texture* loadTexture(string src, SDL_Renderer *renderTarget)
{
    SDL_Texture* texture = nullptr;
    SDL_Surface* surface = SDL_LoadBMP(src.c_str());
    if (surface == NULL)
        cout << "Error::Failed to load BMP : " << src << " : " << SDL_GetError() << endl;
    else
    {
        texture = SDL_CreateTextureFromSurface(renderTarget, surface);
        if (texture == NULL)
            cout << "Error::Failled to create texture : " << src << " : " << SDL_GetError() << endl;
    }

    SDL_FreeSurface(surface);

    return texture;
}

SDL_Texture* loadImgTexture(string src, SDL_Renderer* renderTarget)
{
    SDL_Texture* texture = nullptr;
    SDL_Surface* surface = IMG_Load(src.c_str());
    if (surface == NULL)
        cout << "Error::Failed to load IMG : " << src << " : " << IMG_GetError() << endl;
    else
    {
        texture = SDL_CreateTextureFromSurface(renderTarget, surface);
        if (texture == NULL)
            cout << "Error::Failled to create texture : " << src << " : " << SDL_GetError() << endl;
    }

    SDL_FreeSurface(surface);

    return texture;
}

int main(int argc, char *argv[])
{
    const int FPS = 60;
    int frameTime = 0;

    bool running = true;

    if (SDL_Init(SDL_INIT_EVERYTHING) < 0) 
    {
        cout << "SDL_Init Failed: " << SDL_GetError() << endl;
    }
    SDL_Window* window = SDL_CreateWindow("SDL Test", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 1280, 720, SDL_WINDOW_SHOWN);

    SDL_Surface* windowSurface = nullptr;
    windowSurface = SDL_GetWindowSurface(window);

    SDL_Renderer* rendererTarget = nullptr;
    //rendererTarget = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    rendererTarget = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    
    /*SDL_Surface* imageRed = LoadBMP("BMP\\red.bmp");
    SDL_Surface* imageGreen = LoadBMP("BMP\\green.bmp");
    SDL_Surface* imageBlue = LoadBMP("BMP\\blue.bmp");
    SDL_Surface* imageBlack = LoadBMP("BMP\\black.bmp");*/

    /*SDL_Surface* imageRed = optimizedSurface("BMP\\red.bmp", windowSurface);
    SDL_Surface* imageGreen = optimizedSurface("BMP\\green.bmp", windowSurface);
    SDL_Surface* imageBlue = optimizedSurface("BMP\\blue.bmp", windowSurface);
    SDL_Surface* imageBlack = optimizedSurface("BMP\\black.bmp", windowSurface);
    SDL_Surface* imageSurface = imageBlack;*/
    
    /*SDL_Rect drawingRect;
    drawingRect.x = drawingRect.y = 0;
    drawingRect.w = 1280;
    drawingRect.h = 720;*/

    int imgFlags = IMG_INIT_PNG;
    if (!(IMG_Init(imgFlags) & imgFlags))
    {
        cout << "Error : " << IMG_GetError() << endl;
    }

    SDL_Texture* imageRed = loadTexture("BMP\\red.bmp", rendererTarget);
    SDL_Texture* imageGreen = loadTexture("BMP\\green.bmp", rendererTarget);
    SDL_Texture* imageBlue = loadTexture("BMP\\blue.bmp", rendererTarget);
    SDL_Texture* imageBlack = loadTexture("BMP\\black.bmp", rendererTarget);
    SDL_Texture* imagePNG = loadImgTexture("PNG.png", rendererTarget);
    SDL_Texture* imageSurface = imageBlack;

    // Sprite
    SDL_Rect playerRect, playerPos;
    int frameWidth, frameHeight;
    int textureWidth, textureHeight;

    /*SDL_Texture* spriteImg = loadImgTexture("SpriteSheets\\SpriteSheet1.png", rendererTarget);
    SDL_QueryTexture(spriteImg, NULL, NULL, &textureWidth, &textureHeight);
    cout << textureHeight << " " << textureHeight << endl;
    frameWidth = textureWidth / 3;
    frameHeight = textureHeight / 4;*/

    SDL_Texture* spriteImg = loadImgTexture("SpriteSheets\\SpriteSheet2.png", rendererTarget);
    SDL_QueryTexture(spriteImg, NULL, NULL, &textureWidth, &textureHeight);
    cout << textureHeight << " " << textureHeight << endl;
    frameWidth = textureWidth / 5;
    frameHeight = textureHeight / 2;

    playerRect.x = playerRect.y = 0;
    playerRect.w = frameWidth;
    playerRect.h = frameHeight;

    playerPos.x = playerPos.y = 0;
    playerPos.w = playerPos.h = 256;

    SDL_Event ev;
    //SDL_SetRenderDrawColor(rendererTarget, 0, 255, 0, 255);
    while (running) 
    {
        while (SDL_PollEvent(&ev))
        {
            if (ev.type == SDL_QUIT)
            {
                running = false;
            }
            else if (ev.type == SDL_KEYDOWN)
            {
                switch (ev.key.keysym.sym)
                {
                case SDLK_1:
                    imageSurface = imageRed;
                    break;
                case SDLK_2:
                    imageSurface = imageGreen;
                    break;
                case SDLK_3:
                    imageSurface = imageBlue;
                    break;
                    /*case SDLK_w:
                        cout << "W is pressed!" << endl;
                        break;*/
                default:
                    imageSurface = imageBlack;
                }
            }
            else if (ev.type == SDL_MOUSEBUTTONUP)
            {
                switch (ev.button.button)
                {
                case SDL_BUTTON_LEFT:
                    imageSurface = imageRed;
                    break;
                case SDL_BUTTON_RIGHT:
                    imageSurface = imageBlue;
                    break;
                }

                if (ev.button.clicks == 2)
                {
                    imageSurface = imageGreen;
                }
            }
            else if (ev.type == SDL_MOUSEMOTION)
            {
                cout << ev.button.x << "  " << ev.motion.x << "         ";
                cout << ev.button.y << "  " << ev.motion.y << endl;
            }
        }

        frameTime++;
        if (/*FPS / frameTime == 4*/ frameTime == 5)
        {
            frameTime = 0;
            playerRect.x += frameWidth;
            if (playerRect.x >= textureWidth)
                playerRect.x = 0;
        }

        //SDL_BlitSurface(imageSurface, NULL, windowSurface, NULL);
        //SDL_BlitScaled(imageSurface, NULL, windowSurface, &drawingRect);
        //SDL_UpdateWindowSurface(window);

        SDL_RenderClear(rendererTarget);
        SDL_RenderCopy(rendererTarget, imageSurface, NULL, NULL);
        SDL_RenderCopy(rendererTarget, imagePNG, NULL, NULL);
        SDL_RenderCopy(rendererTarget, spriteImg, &playerRect, &playerPos);
        SDL_RenderPresent(rendererTarget);

    }

    //SDL_Delay(2000);
    
    /*SDL_FreeSurface(imageBlack);
    SDL_FreeSurface(imageBlue);
    SDL_FreeSurface(imageGreen);
    SDL_FreeSurface(imageRed);*/
    
    SDL_DestroyTexture(imageBlack);
    SDL_DestroyTexture(imageBlue);
    SDL_DestroyTexture(imageRed);
    SDL_DestroyTexture(imageGreen);
    SDL_DestroyTexture(imagePNG);
    SDL_DestroyTexture(spriteImg);

    SDL_DestroyWindow(window);

    imageSurface = imageBlack = imageRed = imageBlue = imageGreen = nullptr;
    window = nullptr;
    windowSurface = nullptr;
    SDL_Quit();

    return 0;
}