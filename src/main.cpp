//Using SDL and standard IO
#include <SDL.h>
#include<iostream>
#include<ctime>
#include<iomanip>
using namespace std;

//Screen dimension constants
const int WIDTH = 1000;
const int HEIGHT = 600;
const int SIZE = 500;
SDL_Window* window = NULL;
SDL_Renderer* renderer;
SDL_Event event;
bool quit = false;

void GenerateArray(int* arr);
void Swap(int* arr, int i, int j);
void SelectionSort(int* arr);
void PrintArray(int* arr);
void draw(int* arr, int i, int j);

void setup()
{
	//Create window
	window = SDL_CreateWindow("Selection Sort", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, WIDTH, HEIGHT, 0);
	if (window == NULL)
	{
		std::cout << "Window could not be created! SDL_Error" << std::endl << SDL_GetError();
	}
	else
	{
		//Get window surface
		renderer = SDL_CreateRenderer(window, -1, 0);

		SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);

		SDL_RenderClear(renderer);

		//Update the surface
		SDL_UpdateWindowSurface(window);
	}
}
bool processEvent()
{
	while (SDL_PollEvent(&event))
	{
		switch (event.type)
		{
			// if window closed then quit the game
		case SDL_WINDOWEVENT_CLOSE:
		{
			if (window)
			{
				SDL_DestroyWindow(window);
				window = NULL;
				quit = true;
			}
		}
		break;
		// if escape keyboard passed then quit the game
		case SDL_KEYDOWN:
		{
			switch (event.key.keysym.sym)
			{
			case SDLK_ESCAPE:
				quit = true;
				break;
			}
		}
		break;
		// quit the game
		case SDL_QUIT:
			quit = 1;
			break;
		}
	}
	return quit;
}


void GenerateArray(int* arr)
{
	srand(time(NULL));
	for (int i = 0; i < SIZE; i++)
	{
		arr[i] = 1 + rand() % HEIGHT;
	}
}
// swapping i and j elements in array
void Swap(int* arr, int i, int j)
{
	int temp = arr[i];
	arr[i] = arr[j];
	arr[j] = temp;
}
void SelectionSort(int* arr)
{
	int i, j, index;
	for (i = 0; i < SIZE - 1; i++)
	{
		index = i;
		for (j = i + 1; j < SIZE; j++)
		{
			if (arr[j] < arr[index]) {
				index = j;
			}
		}
		draw(arr, i, index);
		Swap(arr, i, index);
		SDL_Delay(5);
	}
	SDL_Rect rect;
	SDL_SetRenderDrawColor(renderer, 0, 0, 255, 255);
	rect = { (SIZE - 1) * (WIDTH / SIZE),HEIGHT - arr[SIZE - 1],WIDTH / SIZE,HEIGHT };
	SDL_RenderFillRect(renderer, &rect);
	SDL_RenderPresent(renderer);
}
void PrintArray(int* arr)
{
	for (int i = 0; i < SIZE; i++)
	{
		cout << arr[i] << ' ';
	}
}
void draw(int* arr, int i, int j)
{
	SDL_Rect rect;

	SDL_SetRenderDrawColor(renderer, 0, 0, 255, 255);
	rect = { j * WIDTH / SIZE,HEIGHT - arr[j],WIDTH / SIZE,HEIGHT };
	SDL_RenderFillRect(renderer, &rect);
	SDL_RenderPresent(renderer);

	SDL_SetRenderDrawColor(renderer, 0, 0, 255, 255);
	rect = { i * WIDTH / SIZE,HEIGHT - arr[i],WIDTH / SIZE,HEIGHT };
	SDL_RenderFillRect(renderer, &rect);
	SDL_RenderPresent(renderer);

	//SDL_Delay(50);

	SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
	rect = { j * WIDTH / SIZE,HEIGHT - arr[j],WIDTH / SIZE,HEIGHT };
	SDL_RenderFillRect(renderer, &rect);

	SDL_SetRenderDrawColor(renderer, 255, 165, 0, 255);
	rect = { j * WIDTH / SIZE,HEIGHT - arr[i],WIDTH / SIZE,HEIGHT };
	SDL_RenderFillRect(renderer, &rect);
	SDL_RenderPresent(renderer);


	SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
	rect = { i * WIDTH / SIZE,HEIGHT - arr[i],WIDTH / SIZE,HEIGHT };
	SDL_RenderFillRect(renderer, &rect);

	SDL_SetRenderDrawColor(renderer, 0, 0, 255, 255);
	rect = { i * WIDTH / SIZE,HEIGHT - arr[j],WIDTH / SIZE,HEIGHT };
	SDL_RenderFillRect(renderer, &rect);
	SDL_RenderPresent(renderer);

}
int main(int argc, char* args[])
{
	time_t start, end;
	int arr[SIZE];
	GenerateArray(arr);

	if (SDL_Init(SDL_INIT_VIDEO) < 0)
	{
		std::cout<<"SDL could not initialize! SDL_Error" << std::endl << SDL_GetError();
	}
	else setup();


	SDL_SetRenderDrawColor(renderer, 255, 165, 0, 255);
	for (int i = 0; i < SIZE; i++)
	{
		SDL_Rect rect = { i * WIDTH / SIZE,HEIGHT - arr[i],WIDTH / SIZE,HEIGHT };
		SDL_RenderFillRect(renderer, &rect);
		SDL_RenderPresent(renderer);
	}
	time(&start);
	SelectionSort(arr);
	time(&end);
	// Calculating total time taken by the program. 
	double time_taken = double(end - start);
	std::cout << "Array size: " << SIZE << std::endl;
	std::cout << "Time taken by program is : " << std::fixed << time_taken << std::setprecision(5);
	std::cout << " sec " << std::endl;
	while (!quit)
	{
		quit = processEvent();
	}

	//Destroy renderer
	SDL_DestroyRenderer(renderer);
	//Destroy window
	SDL_DestroyWindow(window);
	//Quit SDL subsystems
	SDL_Quit();

	return 0;
}