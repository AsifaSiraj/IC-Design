#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/mman.h>
#include <time.h>
#include <termios.h>
#include <errno.h>
#include <string.h>

/* New Memory Map - 1280x720 8-bit framebuffer */
#define PIXEL_BUF_BASE 0x38000000
#define PIXEL_BUF_SPAN 921600          /* 1280 * 720 * 1 byte */

#define SCREEN_WIDTH   1280
#define SCREEN_HEIGHT  720

#define CELL_SIZE      20
#define MAX_LENGTH     512

/* 8-bit Color Format (3-3-2 RGB) */
/* Format: (R<<5) | (G<<2) | B where R,G = 0-7, B = 0-3 */
#define BLACK   ((0<<5)|(0<<2)|0)       /* 0x00 */
#define RED     ((7<<5)|(0<<2)|0)       /* 0xE0 */
#define GREEN   ((0<<5)|(7<<2)|0)       /* 0x1C */
#define WHITE   ((7<<5)|(7<<2)|3)       /* 0xFF */
#define BLUE    ((0<<5)|(0<<2)|3)       /* 0x03 */
#define YELLOW  ((7<<5)|(7<<2)|0)       /* 0xFC */
#define CYAN    ((0<<5)|(7<<2)|3)       /* 0x1F */
#define MAGENTA ((7<<5)|(0<<2)|3)       /* 0xE3 */

volatile unsigned char *pixel_buffer = NULL;

struct termios oldt, newt;

/* Snake */
int snakeX[MAX_LENGTH];
int snakeY[MAX_LENGTH];
int length = 5;

/* Food */
int foodX;
int foodY;

/*
Direction
0 = UP
1 = RIGHT
2 = DOWN
3 = LEFT
*/
int direction = 1;
int next_direction = 1;
int gameOver = 0;
int score = 0;

/*------------------------------------------------------------*/
/* Initialize Keyboard (Non-Blocking)                         */
/*------------------------------------------------------------*/
void init_keyboard()
{
    tcgetattr(STDIN_FILENO, &oldt);

    newt = oldt;
    newt.c_lflag &= ~(ICANON | ECHO);
    newt.c_cc[VMIN] = 0;
    newt.c_cc[VTIME] = 0;

    tcsetattr(STDIN_FILENO, TCSANOW, &newt);

    fcntl(STDIN_FILENO, F_SETFL, O_NONBLOCK);
}

/*------------------------------------------------------------*/
/* Restore Keyboard                                            */
/*------------------------------------------------------------*/
void restore_keyboard()
{
    tcsetattr(STDIN_FILENO, TCSANOW, &oldt);
}

/*------------------------------------------------------------*/
/* Plot Pixel - 8-bit format with 1280 byte stride            */
/*------------------------------------------------------------*/
void plot_pixel(int x, int y, unsigned char color)
{
    volatile unsigned char *pixel;

    if(x < 0 || x >= SCREEN_WIDTH || y < 0 || y >= SCREEN_HEIGHT)
        return;

    /* Stride is 1280 bytes per row */
    pixel = (volatile unsigned char *)((char *)pixel_buffer +
                                       (y * 1280) +
                                       x);

    *pixel = color;
}

/*------------------------------------------------------------*/
/* Draw Horizontal Line                                        */
/*------------------------------------------------------------*/
void draw_horizontal_line(int x, int y, int length, unsigned char color)
{
    int i;

    for(i = 0; i < length; i++)
        plot_pixel(x + i, y, color);
}

/*------------------------------------------------------------*/
/* Draw Vertical Line                                          */
/*------------------------------------------------------------*/
void draw_vertical_line(int x, int y, int length, unsigned char color)
{
    int i;

    for(i = 0; i < length; i++)
        plot_pixel(x, y + i, color);
}

/*------------------------------------------------------------*/
/* Draw Square Border                                          */
/*------------------------------------------------------------*/
void draw_square(int x, int y, int size, unsigned char color)
{
    draw_horizontal_line(x, y, size, color);
    draw_horizontal_line(x, y + size - 1, size, color);

    draw_vertical_line(x, y, size, color);
    draw_vertical_line(x + size - 1, y, size, color);
}

/*------------------------------------------------------------*/
/* Filled Square                                               */
/*------------------------------------------------------------*/
void fill_square(int x, int y, int size, unsigned char color)
{
    int i;

    for(i = 0; i < size; i++)
        draw_horizontal_line(x, y + i, size, color);
}

/*------------------------------------------------------------*/
/* Clear Screen                                                */
/*------------------------------------------------------------*/
void clear_screen(unsigned char color)
{
    int x, y;

    for(y = 0; y < SCREEN_HEIGHT; y++)
    {
        for(x = 0; x < SCREEN_WIDTH; x++)
        {
            plot_pixel(x, y, color);
        }
    }
}

/*------------------------------------------------------------*/
/* Draw Border                                                 */
/*------------------------------------------------------------*/
void draw_border()
{
    draw_horizontal_line(0, 0, SCREEN_WIDTH, WHITE);
    draw_horizontal_line(0, SCREEN_HEIGHT - 1, SCREEN_WIDTH, WHITE);

    draw_vertical_line(0, 0, SCREEN_HEIGHT, WHITE);
    draw_vertical_line(SCREEN_WIDTH - 1, 0, SCREEN_HEIGHT, WHITE);
}

/*------------------------------------------------------------*/
/* Draw Score as Pixel Blocks (No Character Buffer)           */
/*------------------------------------------------------------*/
void draw_score_display()
{
    int score_x = 30;
    int score_y = 30;
    int digit_width = 20;
    int digit_height = 30;
    
    /* Draw "Score: " label as simple blocks */
    fill_square(score_x, score_y, 100, CYAN);
    draw_square(score_x, score_y, 100, WHITE);
    
    /* Draw actual score value */
    char score_str[20];
    sprintf(score_str, "%d", score);
    
    /* Simple visual representation - draw colored blocks for score visualization */
    fill_square(score_x + 120, score_y, 80, GREEN);
    draw_square(score_x + 120, score_y, 80, WHITE);
}

/*------------------------------------------------------------*/
/* Initialize Snake                                            */
/*------------------------------------------------------------*/
void init_snake()
{
    int i;

    length = 5;
    direction = 1;
    next_direction = 1;
    gameOver = 0;
    score = 0;

    for(i = 0; i < length; i++)
    {
        snakeX[i] = (SCREEN_WIDTH / 2) - (i * CELL_SIZE);
        snakeY[i] = SCREEN_HEIGHT / 2;
    }
}

/*------------------------------------------------------------*/
/* Generate Food (Random Position)                             */
/*------------------------------------------------------------*/
void generate_food()
{
    int valid = 0;
    int i;

    while(!valid)
    {
        foodX = (rand() % ((SCREEN_WIDTH - CELL_SIZE) / CELL_SIZE)) * CELL_SIZE + CELL_SIZE;
        foodY = (rand() % ((SCREEN_HEIGHT - CELL_SIZE) / CELL_SIZE)) * CELL_SIZE + CELL_SIZE;

        valid = 1;

        /* Check if food spawns on snake */
        for(i = 0; i < length; i++)
        {
            if(foodX == snakeX[i] && foodY == snakeY[i])
            {
                valid = 0;
                break;
            }
        }
    }
}

/*------------------------------------------------------------*/
/* Draw Food                                                   */
/*------------------------------------------------------------*/
void draw_food()
{
    fill_square(foodX, foodY, CELL_SIZE, CYAN);
    draw_square(foodX, foodY, CELL_SIZE, WHITE);
}

/*------------------------------------------------------------*/
/* Draw Snake                                                  */
/*------------------------------------------------------------*/
void draw_snake()
{
    int i;

    for(i = 0; i < length; i++)
    {
        if(i == 0)
        {
            /* Head - Blue */
            fill_square(snakeX[i], snakeY[i], CELL_SIZE, BLUE);
            draw_square(snakeX[i], snakeY[i], CELL_SIZE, WHITE);
        }
        else
        {
            /* Body - Yellow */
            fill_square(snakeX[i], snakeY[i], CELL_SIZE, YELLOW);
            draw_square(snakeX[i], snakeY[i], CELL_SIZE, WHITE);
        }
    }
}

/*------------------------------------------------------------*/
/* Erase Snake                                                 */
/*------------------------------------------------------------*/
void erase_snake()
{
    int i;

    for(i = 0; i < length; i++)
    {
        fill_square(snakeX[i], snakeY[i], CELL_SIZE, BLACK);
    }
}

/*------------------------------------------------------------*/
/* Read Keyboard (W A S D)                                     */
/*------------------------------------------------------------*/
void read_keys()
{
    char ch;

    if(read(STDIN_FILENO, &ch, 1) > 0)
    {
        switch(ch)
        {
            case 'w':
            case 'W':
                if(direction != 2)
                    next_direction = 0;      /* UP */
                break;

            case 'd':
            case 'D':
                if(direction != 3)
                    next_direction = 1;      /* RIGHT */
                break;

            case 's':
            case 'S':
                if(direction != 0)
                    next_direction = 2;      /* DOWN */
                break;

            case 'a':
            case 'A':
                if(direction != 1)
                    next_direction = 3;      /* LEFT */
                break;

            default:
                break;
        }
    }
}

/*------------------------------------------------------------*/
/* Move Snake                                                  */
/*------------------------------------------------------------*/
void move_snake()
{
    int i;

    /* Update direction */
    direction = next_direction;

    /* Shift body */
    for(i = length - 1; i > 0; i--)
    {
        snakeX[i] = snakeX[i - 1];
        snakeY[i] = snakeY[i - 1];
    }

    /* Move head */
    switch(direction)
    {
        case 0:     /* UP */
            snakeY[0] -= CELL_SIZE;
            break;

        case 1:     /* RIGHT */
            snakeX[0] += CELL_SIZE;
            break;

        case 2:     /* DOWN */
            snakeY[0] += CELL_SIZE;
            break;

        case 3:     /* LEFT */
            snakeX[0] -= CELL_SIZE;
            break;
    }
}

/*------------------------------------------------------------*/
/* Check Food Collision                                        */
/*------------------------------------------------------------*/
void check_food()
{
    if(snakeX[0] == foodX &&
       snakeY[0] == foodY)
    {
        /* Add new segment */
        if(length < MAX_LENGTH)
        {
            snakeX[length] = snakeX[length - 1];
            snakeY[length] = snakeY[length - 1];
            length++;
        }

        score += 10;
        generate_food();
    }
}

/*------------------------------------------------------------*/
/* Check Wall Collision                                        */
/*------------------------------------------------------------*/
void check_wall_collision()
{
    if(snakeX[0] <= 0)
        gameOver = 1;

    if(snakeX[0] >= SCREEN_WIDTH - CELL_SIZE)
        gameOver = 1;

    if(snakeY[0] <= 0)
        gameOver = 1;

    if(snakeY[0] >= SCREEN_HEIGHT - CELL_SIZE)
        gameOver = 1;
}

/*------------------------------------------------------------*/
/* Check Self Collision                                        */
/*------------------------------------------------------------*/
void check_self_collision()
{
    int i;

    for(i = 1; i < length; i++)
    {
        if((snakeX[0] == snakeX[i]) &&
           (snakeY[0] == snakeY[i]))
        {
            gameOver = 1;
            return;
        }
    }
}

/*------------------------------------------------------------*/
/* Main                                                        */
/*------------------------------------------------------------*/
int main()
{
    int fd;
    void *pixel_virtual_base;

    srand(time(NULL));

    /* Initialize keyboard */
    init_keyboard();

    /* Open physical memory */
    fd = open("/dev/mem", O_RDWR | O_SYNC);

    if(fd < 0)
    {
        perror("open /dev/mem failed");
        restore_keyboard();
        return 1;
    }

    /* Map pixel buffer (1280x720 8-bit) */
    pixel_virtual_base = mmap(NULL,
                              PIXEL_BUF_SPAN,
                              PROT_READ | PROT_WRITE,
                              MAP_SHARED,
                              fd,
                              PIXEL_BUF_BASE);

    if(pixel_virtual_base == MAP_FAILED)
    {
        perror("mmap pixel buffer failed");
        restore_keyboard();
        close(fd);
        return 1;
    }
    pixel_buffer = (volatile unsigned char *)pixel_virtual_base;

    /* Initialize Game */
    clear_screen(BLACK);
    draw_border();

    init_snake();
    generate_food();

    printf("\n");
    printf("========================================\n");
    printf("   SNAKE GAME - 1280x720 HD VERSION\n");
    printf("========================================\n");
    printf("Memory Map:\n");
    printf("  Base: 0x38000000\n");
    printf("  Size: 921600 bytes (1280x720x1)\n");
    printf("  Color: 8-bit (3-3-2 RGB)\n");
    printf("  Stride: 1280 bytes/row\n");
    printf("\n");
    printf("Controls:\n");
    printf("   W = UP\n");
    printf("   A = LEFT\n");
    printf("   S = DOWN\n");
    printf("   D = RIGHT\n");
    printf("\n");
    printf("Game Features:\n");
    printf("   - Eat CYAN food to grow (+10 score)\n");
    printf("   - Blue head, Yellow body\n");
    printf("   - Avoid walls and yourself!\n");
    printf("   - Screen: 1280x720 pixels\n");
    printf("   - Cell Size: 20 pixels\n");
    printf("\n");
    printf("Press Ctrl+C to quit.\n\n");

    /*================ GAME LOOP ================*/
    while(!gameOver)
    {
        /* Erase previous snake */
        erase_snake();

        /* Read keyboard (non-blocking) */
        read_keys();

        /* Move snake */
        move_snake();

        /* Check collisions */
        check_wall_collision();
        check_self_collision();

        /* Check food collision and eat */
        check_food();

        /* Draw everything */
        draw_border();
        draw_food();
        draw_snake();

        /* Display score */
        draw_score_display();

        /* Game speed */
        usleep(150000);     /* 150ms delay */
    }

    /*================ GAME OVER ================*/

    clear_screen(BLACK);

    /* Draw game over box */
    fill_square(400, 300, 480, RED);
    draw_square(400, 300, 480, WHITE);

    /* Display game over message using pixel blocks */
    fill_square(450, 350, 380, BLACK);

    /* Display score info */
    fill_square(480, 380, 320, YELLOW);
    fill_square(480, 420, 320, GREEN);
    fill_square(480, 460, 320, CYAN);

    printf("\n");
    printf("========================================\n");
    printf("              GAME OVER!\n");
    printf("========================================\n");
    printf("Final Score:  %d\n", score);
    printf("Final Length: %d\n", length);
    printf("========================================\n\n");

    /* Wait 5 seconds before exit */
    sleep(5);

    /* Cleanup */
    restore_keyboard();
    munmap(pixel_virtual_base, PIXEL_BUF_SPAN);
    close(fd);

    printf("Game ended. Thank you for playing!\n");

    return 0;
}
