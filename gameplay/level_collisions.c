

#include "../includes/cub3D.h"

bool	level_collision(t_cub3d *cube, int x, int y, bool	player_collision)
{
	int	side_length;

	if (player_collision)
		side_length = 6;
	else
		side_length = 2;
	if ((x / MINIMAP_X >= 0 && y / MINIMAP_Y >= 0))
	{
		if (cube->level.map[y / MINIMAP_Y][x / MINIMAP_X] == '1')
			return (false);
		else if (cube->level.map[y / MINIMAP_Y][(x + side_length) / MINIMAP_X] == '1')
			return (false);
		else if (cube->level.map[(y + side_length) / MINIMAP_Y][x / MINIMAP_X] == '1')
			return (false);
		else if (cube->level.map[(y + side_length) / MINIMAP_Y][(x + side_length) / MINIMAP_X] == '1')
			return (false);
		else
			return (true);
	}
	return (true);
}
