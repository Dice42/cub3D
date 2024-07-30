

// #include "../includes/cub3D.h"


// //send rx and ry of each ray to the function
// void    cast_ray(t_cub3d *cube)
// {
//     float     quotient;
//     float   atan = -1/tan(cube->player.rays.angle);
//     float   x_offset;
//     float   y_offset;
//     int     dof; //depth of field
//     int     mx = 0;
//     int     my = 0;
//     int     map_index;
//     int     rx;
//     int     ry;

//     rx = cube->player.rays.rx;
//     ry = cube->player.rays.ry;
//     y_offset = 0;
//     x_offset = 0;
//     dof = 0;
//     //check the direction where the player is looking
//     if (cube->player.rays.angle > PI) //looking down
//     {
//         //find the closest grid line from the player relative to his y position
//         //player y position 
//         y_offset = -64;
//         quotient = cube->player.transform.y0 / 64;
//         ry = (quotient * 64 )- 0.0001;
//         rx = (cube->player.transform.y0 - cube->player.rays.ry) * atan + cube->player.transform.x0;
//         x_offset = -y_offset * atan;
//     }
//     if (cube->player.rays.angle < PI)
//     {
//         y_offset = 64;
//         quotient = cube->player.transform.y0 / 64;
//         ry = (quotient * 64) + 64;
//         rx = (cube->player.transform.y0 - cube->player.rays.ry) * atan + cube->player.transform.x0;
//         x_offset = -y_offset * atan;
//      }
//     if (cube->player.rays.angle == PI || cube->player.rays.angle == 0) //will never hit a vertical line
//     {
//         rx = cube->player.transform.x0;
//         ry = cube->player.transform.y0;
//         dof = 8;
//     }

//     while (dof < 8)
//     {
//         mx = rx / 64;
//         my = ry / 64;
//         map_index = my * (cube->level.num_of_columns + mx);
//         if (map_index < cube->level.num_of_columns * cube->level.num_of_rows && cube->level.map[my][mx] == '1')
//             break ;
//         else
//         {
//             rx += x_offset;
//             ry += y_offset;
//         }
//         my_mlx_pixel_put(&cube->data.img, rx, ry, 0x00FF00);
//         dof ++;
//     }
// }