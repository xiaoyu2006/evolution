#!/usr/bin/env python3
# -*- coding: utf-8 -*-
"""
Utilities for visualization. Pip simulation output from the C++ progeam to this script.
"""

from tkinter import *


# EXAMPLE: Prey,0.741356,0.569952
class Parser:
    def __init__(self):
        self.now = []

    def parse(self, line):
        line = line.rstrip()
        if ',' not in line:
            if line != '':
                print(line)
            result = self.now
            self.now = []
            return result
        line = line.split(',')
        new_item = [line[0], float(line[1]), float(line[2])]
        self.now.append(new_item)
        return None


def tick(parser, canvas):
    try:
        line = input()
    except EOFError:
        print('End of file.')
        return True
    result = parser.parse(line)
    if result is None:
        return False
    canvas.delete('all')
    for item in result:
        if item[0] == 'Prey':
            color = 'green'
        else:
            color = 'red'
        canvas.create_oval(item[1] * 800 - 5, item[2] * 600 - 5, item[1] * 800 + 5, item[2] * 600 + 5, fill=color)
    return True


def main():
    ui = Tk()
    ui.title('Simulation Visualization')
    ui.geometry('800x600')
    canvas = Canvas(ui, width=800, height=600)
    canvas.pack()

    parser = Parser()
    while True:
        update = tick(parser, canvas)
        if update:
            ui.update_idletasks()
            ui.update()


if __name__ == '__main__':
    main()
