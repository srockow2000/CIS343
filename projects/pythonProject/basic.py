#!/usr/bin/env python3

import pygame as pg
from pygame import *
import random

"""
A constructor that creates a brick

@param xcoord - sets the x-coordinate of each brick
@param ycoord - sets the y-coordinate of each brick

"""
class Brick(pg.sprite.Sprite):
    def __init__(self, xcoord, ycoord):
        super().__init__()
        

        # set a random variable for the color
        r = random.randint

        # sets size of each brick
        self.image = pg.Surface((100, 50))
        self.rect = self.image.get_rect()

        # give each brick a random color
        self.__red = r(0, 255)
        self.__blue = r(0, 101)
        self.__green = r(0, 164)

        self.image.fill( (self.__red, self.__blue, self.__green) )
        
        # position bricks
        self.rect.x = xcoord * 100
        self.rect.y = ycoord * 50

        # health variable for each brick
        self.__health = 766 - self.__red - self.__blue - self.__green

    """
    a method to update brick health when hit
    Each brick will have a health score of 30
    and can take 3 hits before being destroyed
    """
    def update(self):
        ballCollision = pg.sprite.spritecollide(self, Game.balls, False)

        if ballCollision:
            self.__health -= 250

        if self.__health <= 0:
            # this will move the bricks off screen
            self.rect.x -= self.rect.x
            self.rect.y -= self.rect.y
            
    
    """
    a method to return brick health
    """
    def getHealth(self):
        return self.__health

    """
    a method to set brick health
    """
    def setHealth(self, value):
        self.__health -= value

"""
A constructor that creates a ball
"""
class Ball(pg.sprite.Sprite):
    def __init__(self):
        super().__init__()
        
        self.__lives = 5

         # a random variable for direction
        r = random.randint

        self.image = pg.Surface((15, 15))
        self.rect = self.image.get_rect()
        
        self.rect.x = 400
        self.rect.y = 300

        # copying from instructor sample code
        self.velocity = [4, 4]
        #self.velocity = [ r(1, 5) - 5, r(1, 5) - 5]

    def update(self):
        # copying from instructor sample code
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

        # check if ball hits the ground and take away a life
        if self.rect.y == 0:
            self.__lives -= 1
    
        # check for brick collision
        brickCollision = pg.sprite.spritecollide(self, Game.bricks, False)

        if brickCollision:
            self.velocity[1] = -self.velocity[1]

    
        # check for paddle collision
        paddleCollision = pg.sprite.spritecollide(self, Game.paddles, False)

        if paddleCollision:
            self.velocity[0] = -self.velocity[0]
            self.velocity[1] = -self.velocity[1]

    """
    a method to return the number of lives
    """
    def getLives(self):
        return self.__lives

    """
    a method to set the number of lives
    """
    def setLives(self, value):
        self.__lives = value


"""
The paddle class
"""
class Paddle(pg.sprite.Sprite):
    def __init__(self):
        super().__init__()

        # create paddle
        self.image = pg.Surface((300, 25))
        self.rect = self.image.get_rect()
        

        # position paddle
        self.rect.x = 400
        self.rect.y = 575

        # set initial velocity
        self.velocity = 15

    def update(self):
        keys = pg.key.get_pressed()

        self.rect.x += (keys[pg.K_RIGHT] - keys[pg.K_LEFT]) * 5
        
        if self.rect.x > 500:
            self.rect.x = 500
        if self.rect.x < 0:
            self.rect.x = 0


"""
This class updates the score and lives
"""
class Overlay:
    #Brick().getHealth()
    Ball().getLives()
    # need ball getter
    #return score

class Game:
    def __init__(self):
        pg.init()
        self.__running = False
        self.screen = pg.display.set_mode( (800, 600) )
        self.clock = pg.time.Clock()
        
        brick = None
        paddles = None
        balls = None

        # initialize the number of balls
        self.balls = pg.sprite.Group()
        self.balls.add(Ball()) 

        # initialize the number of bricks
        self.brick = pg.sprite.Group()

        for x in range (0, 8):
            for y in range(0, 5):
                self.brick.add ( Brick(x, y) )
        
        # initialize the paddle
        self.paddles = pg.sprite.Group()
        self.paddles.add(Paddle())

        # set titles
        pg.display.set_caption("Brick Game")

        #scoreText = pg.font.Font.render(pg.font.SysFont, "Score: ")
        # Player's paddle
        self.__paddle = Paddle()

    def run(self):
        while self.__running:
            events = pg.event.get()
            for event in events:
                if event.type == pg.QUIT:
                    self.__running = False
                    pg.quit()
                    exit()

                if event.type == pg.KEYDOWN:
                    if event.type == pg.K_DOWN:
                        #self.balls.add(Ball () )
                        print("added ball")

         # Take events

            # Update updateable objects
            self.balls.update()
            self.paddles.update()
            self.brick.update()
            # Redraw
            self.screen.fill( (255, 255, 255) ) 
            self.balls.draw(self.screen)
            self.brick.draw(self.screen)
            self.paddles.draw(self.screen)
          
            pg.display.flip()
            self.clock.tick(60)

    def setRunning(self, running):
        self.__running = running

    def addBrick(self, brick):
        self.brick.add(brick)

    def addPaddle(self, paddle):
        self.paddles.add(paddle)

    def addBall(self, ball):
        self.balls.add(ball)

    def getBricks(self):
        return self.brick

    def getPaddle(self):
        return self.paddles

    def getBall(self):
        return self.balls

def main():
    game = Game()

    # give attributes to Game class
    Game.bricks = game.getBricks()
    Game.paddles = game.getPaddle()
    Game.balls = game.getBall()

    # start game loop
    game.setRunning(True)
    game.run()

if __name__ == '__main__':
    main()

