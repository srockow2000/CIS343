#!/usr/bin/env python3

"""
A version of the Brick Breaker game (https://www.coolmathgames.com/0-brick-breaker)
that allows a user to play with one or more balls at different speeds using
hidden keystrokes. To win, the user must defeat a grid of 48 bricks with varying
health levels.

@author             Sarah Rockow
@collaborator       Amaka Ezuruonye
@version            Winter 2022

Notes:

    The overlay and sound are not working.

    Hidden keystrokes:
        f - speeds up the ball(s)
        j - slows down the ball(s)
        down_arrow - adds another ball (unlimited amount)
"""



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

        # checks if the ball has hit a brick and updates the health of the brick
        ballCollision = pg.sprite.spritecollide(self, Game.balls, False)

        if ballCollision:
            self.__health -= 250
            self.image.fill( (self.__red, self.__blue, self.__green) )

        # removes brick when health is depleted
        if self.__health <= 0:
            # this will move the bricks off screen
            self.rect.x = -100
            self.rect.y = -100
            
    
    """
    a method to return brick health
    """
    def getHealth(self):
        return self.__health


"""
A constructor that creates a ball
"""
class Ball(pg.sprite.Sprite):
    def __init__(self):
        super().__init__()
        
        # the number of lives that each ball has
        self.__lives = 5
        self.__points = 0

        # creates the ball
        self.image = pg.Surface((15, 15))
        self.rect = self.image.get_rect()
        
        # positions the ball in the middle of the screen
        self.rect.x = 400
        self.rect.y = 300

        # initial velocity of the ball
        self.velocity = [4, 4]

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


        # change ball speed when 'f' is pressed
        if pg.key.get_pressed()[pg.K_f]:
            self.velocity = [10, 10]

        # slow down ball speed when 'j' is pressed
        if pg.key.get_pressed()[pg.K_j]:
            self.velocity = [2, 2]
        
        # check if ball hits the ground and take away a life
        if self.rect.y == 0:
            self.__lives -= 1

        # remove ball if lives are gone
        if self.__lives == 0:
            self.rect.x = -100
            self.rect.y = -100
            self.velocity = [0, 0]
            
        # check for brick collision
        brickCollision = pg.sprite.spritecollide(self, Game.bricks, False)

        if brickCollision:
            self.velocity[1] = -self.velocity[1]
            Ball.getPoints(self)
            Ball.setPoints(self, 250)
    
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
    a method to return the number of total points
    """
    def getPoints(self):
        return self.__points

    """
    a method to set/update the number of points
    """
    def setPoints(self, value):
        self.__points += value

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
        
        """
        mixer.init()
        mixer.music.load('big-impact-7054.mp3')
        #self.boom = mixer.music.play()
        """

    def update(self):
        keys = pg.key.get_pressed()

        # move the paddle based on key binding
        self.rect.x += (keys[pg.K_RIGHT] - keys[pg.K_LEFT]) * 15
        
        # limits the paddle's movement; plays music if boundaries are hit
        if self.rect.x > 500:
            self.rect.x = 500
        #    self.boom.play()

        if self.rect.x < 0:
            self.rect.x = 0
        #   self.boom.play()
        


"""
This class updates the score and lives
"""
class Overlay(pg.sprite.Sprite):
    def __init__(self):
        super().__init__()
        print(Ball().getPoints())

    def update(self):
        Ball().getPoints()
        print(Ball().getPoints())

class Game:
    def __init__(self):
        pg.init()
        self.__running = False
        self.screen = pg.display.set_mode( (800, 600) )
        self.clock = pg.time.Clock()
        
        # assign attributes to Game() Class
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

        # set title
        pg.display.set_caption("Brick Game")







        #scoreText = pg.font.Font.render(pg.font.SysFont, "Score: ")
        # Player's paddle





        # initialize the overlay
        self.overlay = pg.sprite.Group()
        self.overlay.add( Overlay() )

    def run(self):
        while self.__running:
            events = pg.event.get()
            for event in events:
                if event.type == pg.QUIT:
                    self.__running = False
                    pg.quit()
                    exit()

                # adds a new ball when the down arrow is pressed; no limit
                if pg.key.get_pressed()[pg.K_DOWN]:
                    self.balls.add( Ball() )

            # Update updateable objects
            self.balls.update()
            self.paddles.update()
            self.brick.update()
            self.overlay.update()

            # Redraw
            self.screen.fill( (255, 255, 255) ) 
            self.balls.draw(self.screen)
            self.brick.draw(self.screen)
            self.paddles.draw(self.screen)
#            self.overlay.draw(self.screen)

            pg.display.flip()
            self.clock.tick(60)
    
    # setter for Game loop
    def setRunning(self, running):
        self.__running = running

    # method to add a Brick
    def addBrick(self, brick):
        self.brick.add(brick)

    # method to add a Paddle
    def addPaddle(self, paddle):
        self.paddles.add(paddle)

    # method to add a Ball
    def addBall(self, ball):
        self.balls.add(ball)

    # method to return a Brick from the Game() Class
    def getBricks(self):
        return self.brick

    # method to return a Paddle from the Game() Class
    def getPaddle(self):
        return self.paddles

    # method to return a Ball from the Game() Class
    def getBall(self):
        return self.balls

def main():
    # initialize the Game() Class
    game = Game()

    # give attributes to Game class for other classes to access
    Game.bricks = game.getBricks()
    Game.paddles = game.getPaddle()
    Game.balls = game.getBall()

    # start game loop
    game.setRunning(True)
    game.run()

# run main method
if __name__ == '__main__':
    main()

