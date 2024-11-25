#include "../include/common.h"
#include "SDL3/SDL_main.h"

SDL_AppResult SDL_AppInit(void** appData, int argc, char* argv[])
{
    Chip8_t* pChip8 = initializeComponents();

    if (pChip8 == NULL)
    {
        return SDL_APP_FAILURE;
    }

    AppData_t* data = malloc(sizeof(AppData_t));
    *appData = (void*)data;
    WindowData_t* windowData = malloc(sizeof(WindowData_t));
    UpdateTracker_t* updateTracker = malloc(sizeof(UpdateTracker_t));
    unsigned char* fontData = initializeFont();

    windowData->updateTracker = updateTracker;
    data->windowData = windowData;
    data->pChip8 = pChip8;
    data->fontData = fontData;

    if (data->windowData == NULL)
    {
        SDL_LogError(SDL_LOG_CATEGORY_ERROR, "windowdata is null\n");
    }

    if (!SDL_CreateWindowAndRenderer("Chip8-Interpreter", WIDTH * DEFAULT_RENDER_SCALE, HEIGHT * DEFAULT_RENDER_SCALE, 0, &windowData->window, &windowData->renderer))
    {
        SDL_LogError(SDL_LOG_CATEGORY_ERROR, "Unable to create Window and Renderer\n");
        return SDL_APP_FAILURE;
    }

    clearScreen(data);

    loadMenu(data);

    return SDL_APP_CONTINUE;
}

SDL_AppResult SDL_AppIterate(void* appData)
{
    AppData_t* data = (AppData_t*) appData;

    //framerate
    Uint64 frameStart = SDL_GetTicks();
    drawDisplay(data->windowData);
    Uint64 frameEnd = SDL_GetTicks();

    Uint64 frameTime = frameEnd - frameStart;

    int timeLeft = DESIRED_DELTA_TIME - (float) frameTime;

    if (timeLeft < 0)
    {
        timeLeft = 0;
    }

    SDL_Delay(timeLeft);

    return SDL_APP_CONTINUE;
}

SDL_AppResult SDL_AppEvent(void* appData, SDL_Event* event)
{
    AppData_t* data = (AppData_t*) appData;

    switch (event->type) {
        case SDL_EVENT_QUIT:
        return SDL_APP_SUCCESS;
    }

    switch (data->windowData->currentScreen) {
        case CHIP8:
            break;
        case OPTION:
            break;
        case MENU:
            return MenuEventHandler(data, event);
    }

    return SDL_APP_CONTINUE;
}

void SDL_AppQuit(void* appData, SDL_AppResult result)
{
    AppData_t* data = (AppData_t*) appData;

    SDL_DestroyWindow(data->windowData->window);
    SDL_DestroyRenderer(data->windowData->renderer);

    free(data->windowData->updateTracker);
    free(data->windowData);
    free(data->pChip8);
    free(data);

}
