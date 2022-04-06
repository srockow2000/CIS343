#!/usr/bin/env python3

import pygame as pg
from pygame import *
import random

MOVE_LEFT = -10
MOVE_RIGHT = 10

"""
A constructor that creates a brick

"""
class Brick(pg.sprite.Sprite):
    def __init__(self):
        super().__init__()
        self.image = pg.Surface((64, 64))
        self.rect = self.image.get_rect()
       # pg.draw.circle(self.image, (0, 101, 164), (32, 32), 32)
        self.rect.x = 400
        self.rect.y = 300

"""
A constructor that creates a ball
"""
class Ball(pg.sprite.Sprite):
    def __init__(self):
        super().__init__()
        self.image = pg.Surface((64, 64))
        pg.draw.circle(self.image, BLUE, (0, 101, 164), (32, 32), 32)


"""
The paddle class
"""
class Paddle(pg.sprite.Sprite):
    def __init__(self):
        super().__init__()

        # set window size to get screen dimensions
        window = pg.display.set_mode((800, 800))
        width, height = window.get_size()

        # create paddle
        self.image = pg.Surface((64, 64))
        self.rect = self.image.get_rect()

        def move(self):
            keys = pg.key.get_pressed()

            if keys[K_a]:
                self.state = MOVE_LEFT
                self.accel.x += 5
                
            if keys[K_d]:
                self.state = MOVE_RIGHT
                self.accel.x += 5
        # position paddle
        self.rect.x = move(self)
        self.rect.y = 700


class Blah(pg.sprite.Sprite):
    explodifiers = None
    def __init__(self):
        super().__init__()
        r = random.randint
        self.image = pg.Surface((r(0,64),r(0,64)))
        self.image.fill( (r(0,255), r(0,101), r(0,164)) )
        self.rect = self.image.get_rect()
        self.rect.x = random.randint(0,800)
        self.rect.y = random.randint(0,600)
        self.velocity = [r(0,3) - 3, r(0,3) - 3]
        self.explodifiers = None
#        self.boom = pg.mixer.Sound("./boom.mp3")

    def update(self):
        self.rect.x += self.velocity[0]
        self.rect.y += self.velocity[1]
        if self.rect.x < 0:
            self.velocity[0] = -self.velocity[0]
        if self.rect.x > 800:
            self.velocity[0] = -self.velocity[0]
        if self.rect.y < 0:
            self.velocity[1] = -self.velocity[1]
        if self.rect.y > 600:
            self.velocity[1] = -self.velocity[1]
        collisions = pg.sprite.spritecollide(self, Blah.explodifiers, False)
        if collisions:
            self.velocity[0] = 0
            self.velocity[1] = 0
            self.rect.x = -100
#         self.boom.play()

    def setExplodifiers(self, explodifiers):
        self.explodifiers = explodifiers




class Game:
    def __init__(self):
        pg.init()
        self.__running = False
        self.screen = pg.display.set_mode( (800, 600) )
        self.clock = pg.time.Clock()
        self.blahs = pg.sprite.Group()
        self.exploders = pg.sprite.Group()
        self.brick = pg.sprite.Group()

    def run(self):
        while self.__running:
            events = pg.event.get()
            for event in events:
                if event.type == pg.QUIT:
                    self.__running = False
                    pg.quit()
                    exit()
            # Take events

            # Update updateable objects
            self.blahs.update()
            # Redraw
            self.screen.fill( (255, 255, 255) )
            self.blahs.draw(self.screen)
            self.exploders.draw(self.screen)
            pg.display.flip()
            self.clock.tick(60)

    def setRunning(self, running):
        self.__running = running

    def addBrick(self, brick):
        self.brick.add(brick)

    def addBlah(self, blah):
        self.blahs.add(blah)

    def addExplodifier(self, exploder):
        self.exploders.add(exploder)

    def getExplodifiers(self):
        return self.exploders

def main():
    game = Game()
    
    for _ in range(0,50):
        game.addBrick(Blah())
        #game.addBlah( Blah() )


    game.addExplodifier(Paddle())
    Blah.explodifiers = game.getExplodifiers()
    game.setRunning(True)
    game.run()

if __name__ == '__main__':
    main()

