#!/usr/bin/python
import mygameengine
import pygame
from pygame.locals import *
import threading
import time
import random
import sys
import os
import pygame.mixer
import pygame.time

## Create the engine as a object to be callable
game = mygameengine.Engine()

## The width of sprite sheet
sheet_width = 0

## The height of the sprite sheeet
sheet_height = 0

## Creates rectangle vectors for all the tiles in the sprite sheet
def load_grid_images(x_margin = 0, x_padding = 0, y_margin = 0, y_padding = 0):
    num_rows = 3
    num_cols = 3
    filename = 'assets/spritesheet.bmp'
    sheet = pygame.image.load(filename).convert()

    sheet_rect = sheet.get_rect()
    sheet_width, sheet_height = sheet_rect.size

    x_sprite_size = 128
    y_sprite_size = 128

    sprite_rects = []
    for row_num in range(num_rows):
        for col_num in range(num_cols):
            x = col_num * (x_sprite_size)
            y = row_num * (y_sprite_size)
            sprite_rect = (x, y, x_sprite_size, y_sprite_size)
            sprite_rects.append(sprite_rect)
    return sprite_rects

## Loads the images of the sprite sheet on two the GUI
def load_images(screen, sheet, Rectangles):
    tempX = 0
    tempY = 0
    for temprect in Rectangles:
        # print(temprect)
        if (tempX == 3):
            tempY += 1
            tempX = 0
        rect = pygame.Rect(temprect)
        screen.blit(sheet, (tempX * 128, tempY * 128), rect)
        tempX += 1

## The function of the GUI contains the main game loop for the GUI
## Also has the logic for what image should be displayed and sending the information to the engine
def GUI():
    DISPLAY_SIZE = (800, 800)
    GAME_TITLE = "Selection Lobby"
    DESIRED_FPS = 60
    # Setup preliminary pygame stuff
    pygame.init()
    screen = pygame.display.set_mode(DISPLAY_SIZE, 0 , 32)
    pygame.display.set_caption(GAME_TITLE)
    fps_clock = pygame.time.Clock()
    allRects = load_grid_images()
    filename1 = 'assets/spritesheet.bmp'
    filename2 = 'assets/itemSingle.bmp'
    filename3 = 'assets/enemySingle.bmp'
    sheet = pygame.image.load(filename1).convert()
    sheet = pygame.transform.scale(sheet, (384,384))
    singleSprite = pygame.image.load(filename2).convert()
    singleSprite = pygame.transform.scale(singleSprite, (128, 128))
    oneEnemy = pygame.image.load(filename3).convert()
    oneEnemy = pygame.transform.scale(oneEnemy, (128, 128))
    enemyRect = (0, 0, 128, 128)
    fruitRect = (0, 0, 128, 128)

    font = pygame.font.SysFont("comicsansms", 24)

    text = font.render("Press P to pause the game and go into editor mode.", True, (0, 0, 0))
    text1 = font.render("Left click on an object in the selection lobby to select it. Right click on an object to enter delete mode.", True, (0, 0, 0))
    text2 = font.render("Red deletes tiles, green deletes collectibles, and blue deletes enemies.", True, (0,0,0))
    text3 = font.render("Use the arrow keys in the game while paused to move the selection box.", True, (0,0,0))
    text4 = font.render("Press SPACE in the game while paused to place or delete the selected object.", True, (0,0,0))
    text5 = font.render("Press F5 to save the current state of the level.", True, (0,0,0))

    square = 0;
    game_run = False
    red_Rect = None
    selected = None

    while not game_run:
        game_run = game.getDoQuit()
        screen.fill((255, 255, 255))
        user_input = pygame.event.get()
        pressed_key = pygame.key.get_pressed()

        # Retrieves all user input
        for event in user_input:
            # Is the input mouse button pressed down?
            if event.type == pygame.MOUSEBUTTONDOWN:
                mouse_pos = pygame.mouse.get_pos()
                # print(mouse_pos)
                for aRect in allRects:
                    rect = pygame.Rect(aRect)
                    if pygame.Rect.collidepoint(rect, mouse_pos):
                        # print("Sprite sheet clicked.")
                        # print(aRect)
                        rMang.changePlaceWhat(0)
                        if (event.button == 1):
                            red_Rect = aRect
                            selected = sheet
                            tempX = (red_Rect[0] / 128)
                            tempY = (red_Rect[1] / 128)
                            rMang.changeBlock((int)((tempY * 3) + tempX))
                        elif (event.button == 3):
                            red_Rect = None
                            square = 1
                            rMang.changeBlock(-1)
                if pygame.Rect.collidepoint(pygame.Rect((128, 600, 128, 128)), mouse_pos):
                    if (event.button == 1):
                        # print("The fruit was clicked.")
                        rMang.changePlaceWhat(1)
                        red_Rect = fruitRect
                        selected = singleSprite
                    elif (event.button == 3):
                        red_Rect = None
                        rMang.changePlaceWhat(2)
                        square = 2

                elif pygame.Rect.collidepoint(pygame.Rect((512, 600, 128, 128)), mouse_pos):
                    if (event.button == 1):
                        #print("The enemy was clicked.")
                        rMang.changePlaceWhat(3)
                        red_Rect = enemyRect
                        selected = oneEnemy
                    elif(event.button == 3):
                        red_Rect = None
                        rMang.changePlaceWhat(4)
                        square = 3

        if (red_Rect != None):
            screen.blit(selected, (512, 128), red_Rect)
        else:
            if (square == 1):
                pygame.draw.rect(screen, (255, 0, 0), pygame.Rect(512, 128, 128, 128))
            elif (square == 2):
                pygame.draw.rect(screen, (0, 255, 0), pygame.Rect(512, 128, 128, 128))
            elif (square == 3):
                pygame.draw.rect(screen, (0, 0, 255), pygame.Rect(512, 128, 128, 128))

        # Render stuff
        load_images(screen, sheet, allRects)

        screen.blit(singleSprite, (128, 600), pygame.Rect(fruitRect))
        # pygame.draw.rect(screen, (0,0,0), pygame.Rect(512,600,128,128))
        screen.blit(oneEnemy, (512, 600), pygame.Rect(enemyRect))
        screen.blit(text, (10, 400))
        screen.blit(text1, (10, 425))
        screen.blit(text2, (10, 450))
        screen.blit(text3, (10, 475))
        screen.blit(text4, (10, 500))
        screen.blit(text5, (10, 525))

        pygame.display.flip()
        pygame.display.update()
        fps_clock.tick(DESIRED_FPS)
        if pressed_key[K_q]:
            game_run = True
            # print("GAME DONE")
            pygame.display.quit()
            pygame.quit()
            sys.exit()
            break
        # time.sleep(.2)

## Script main controller of game engine
## Checks to see if the game has quit
def runGame():
    quit = False;
    game_run = True # Global game_run
    FPS2 = 60 # Frames per second setting
    fpsClock2 = pygame.time.Clock()

    # While application is running
    while not quit:
        game.input(quit); # Get user input
        game.update(); # Update our scene
        game.render(); # Render using OpenGL
        quit = game.getDoQuit()
        fpsClock2.tick(FPS2)
    game.shutdown()

game.initializeGraphicsSubSystem()
game.start()
rMangTemp = mygameengine.ResourceManager()
rMang = mygameengine.ResourceManager.getInstance()

thread1 = threading.Thread(target = runGame)
thread1.start()
thread2 = threading.Thread(target = GUI)
thread2.start()

thread2.join()
thread1.join()
time.sleep(.1)
sys.exit()
exit()
