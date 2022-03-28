#!/usr/bin/env python3

import pygame as pg

class Blah(pg.sprite.Sprite):
    def __init__(self):
        super().__init__()
        self.image = pg.surface
        self.image.fill( (0, 101, 164) )
        self.rect = self.image.get_rect()



class Game:
        def __init__(self):
            pg.init()
            self.running = False
            self.screen = pg.display.set_mode((800, 600))
            self.clock = pg.time.Clock()
            self.blahs = pg.sprite.Group()




        def run(self):
            while self.running:
                # Take events
                events = pg.event.get()
                for event in events:
                    if event.type == pg.QUIT:
                        pg.quit()
                        self.__running = False
                        exit()

                # Update updateable objects
                self.blahs.update()

                # Redraw screen
                self.screen.fill( (255, 255, 255) )
                blahs.draw()
                pg.display.flip()
                self.clock.tick(60)

        def setRunning(self, running):
            self.running = running

def main():
    game = Game()

    for _ in range(0, 100):
        game.addBlah( Blah() )

    game.setRunning(True)
    game.run()

    if __name__ == '__main__':
                main()
