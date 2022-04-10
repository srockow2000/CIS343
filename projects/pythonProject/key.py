import pygame

pygame.init()
window = pygame.display.set_mode((800, 600))
clock = pygame.time.Clock()

#Shared variables

vel = 10

class Item(pygame.sprite.Sprite):
    def __init__(self):
        super().__init__()
        self.image = pg.Surface((64, 64))
        


"""
A constructor that creates the paddle

Function: move - allows the paddle to move
from left to right using keybindings. Movement
is restricted within the screen.
"""

class Paddle(pygame.sprite.Sprite):
    def __init__(self):
        super().__init__()
        self.rect = pygame.Rect(150, 580, 250, 20)

    def move(self):
        run = True
        while run:
            for event in pygame.event.get():
                if event.type == pygame.QUIT:
                    run = False
                if event.type == pygame.KEYDOWN:
                    print(pygame.key.name(event.key))

        keys = pygame.key.get_pressed()

        self.rect.x += (keys[pygame.K_RIGHT] - keys[pygame.K_LEFT]) * vel
        self.rect.centerx = self.rect.centerx % window.get_width()
        self.rect.centery = self.rect.centery % window.get_height()

        if self.rect.x > 550:
            self.rect.x = 545
        if self.rect.x < 0:
            self.rect.x = 5

class Game:
    def __init__(self):
        pygame.init()
        self.run = False
        self.screen = pygame.display.set_mode( (800, 600) )
        self.clock = pygame.time.Clock()
        self.items = pygame.sprite.Group()

    def running(self):
        while self.__run:
            events = pygame.event.get()
            for event in events:
                if event.type == pygame.QUIT:
                    self.__run = False
                    pygame.quit()
                    exit()

            self.screen.fill ( (255, 255, 255) )
            pygame.display.flip()
            self.clock.tick(60)
    def setRunning(self, run):
        self.__run = run
    def addItem(self, item):
        self.items.add(item)

def main():
    game = Game()

    game.addItem(Paddle())
    game.setRunning(True)
    game.running()

    
if __name__ == '__main__':
    main()
