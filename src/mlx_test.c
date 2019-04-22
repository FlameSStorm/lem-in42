#include <mlx.h>
#include <stdlib.h>

#define WINDOW_SIZE 1000
#define MARGIN (WINDOW_SIZE / 10)

void	draw_line(int x1, int x2, int y1, int y2, void *mlx, void *win, int color)
{
	const int deltaX = abs(x2 - x1);
    const int deltaY = abs(y2 - y1);
    const int signX = x1 < x2 ? 1 : -1;
    const int signY = y1 < y2 ? 1 : -1;
    int error = deltaX - deltaY;
    while(x1 != x2 || y1 != y2) 
   {
		mlx_pixel_put(mlx, win, x1, y1, color);
        const int error2 = error * 2;
        if(error2 > -deltaY) 
        {
            error -= deltaY;
            x1 += signX;
        }
        if(error2 < deltaX) 
        {
            error += deltaX;
            y1 += signY;
        }
    }
}

// char 	**read_map(void)
// {
// 	char 	**map;
// 	int 	i;

// 	map = (char**)malloc(sizeof(char*) * 1000000);
// 	i = 0;
// 	while (get_next_line(0, &map[i]) > 0)
// 	{
// 		i++;
// 	}
// 	return (map);
// }

int 	main(void)
{

	void *mlx_ptr = mlx_init();
	void *win_ptr = mlx_new_window(mlx_ptr, 1000, 1000, "main");
	for (int i = 0;i < WINDOW_SIZE;i++)
		draw_line(i, i, WINDOW_SIZE / 2, 0, mlx_ptr, win_ptr, 250);
	for (int k = 0;k < WINDOW_SIZE;k++)
		draw_line(k, k, WINDOW_SIZE / 2, WINDOW_SIZE, mlx_ptr, win_ptr, 0xfaff00);
	for (int k = 0;k < WINDOW_SIZE;k++)
		draw_line(k, k, WINDOW_SIZE / 2, WINDOW_SIZE, mlx_ptr, win_ptr, 0xfaff00);
	draw_line(100, 100, 100, 100, mlx_ptr, win_ptr, 0xfaff00);

	mlx_loop(mlx_ptr);
	return (0);
}

