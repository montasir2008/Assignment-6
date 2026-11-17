/*
 * File: Labyrinth.cpp
 * -------------------
 * Name:Montasir Mahir
 * Course: CS106B
 * Section: Thu 7:30 pm
 * Description: This file checks whether a given path through a maze
 * leads to escape. It follows the specified directions, keeps track
 * of the items collected along the way, and returns whether the path
 * is valid and all three required items have been collected.
 */
#include "Labyrinth.h"
using namespace std;

/*
 * This function checks whether a sequence of moves successfully
 * collects the items. It starts at the given
 * maze cell and follows each direction, returning false if a move
 * leads into a wall. It tracks the items found along the path,
 * including the starting cell, and returns true only if all three
 * items have been collected.
 */
bool isPathToFreedom(MazeCell* start, const string& moves) {
    MazeCell* current = start;
    bool items[3] = {};

    if (start->whatsHere != Item::NOTHING) {
        if (start->whatsHere == Item::POTION) items[0] = true;
        else if (start->whatsHere == Item::SPELLBOOK) items[1] = true;
        else if (start->whatsHere == Item::WAND) items[2] = true;
    }

    for (char c : moves) {
        if (c == 'N') {
            current = current->north;
        }
        else if (c == 'W') {
            current = current->west;
        }
        else if (c == 'E') {
            current = current->east;
        }
        else if (c == 'S') {
            current = current->south;
        }
        if (current == nullptr) return false;
        if (current->whatsHere != Item::NOTHING) {
            if (current->whatsHere == Item::POTION) items[0] = true;
            else if (current->whatsHere == Item::SPELLBOOK) items[1] = true;
            else if (current->whatsHere == Item::WAND) items[2] = true;
        }
    }
    for (bool i : items) {
        if (i == false) return false;
    }
    return true;
}


/* * * * * * Test Cases Below This Point * * * * * */
#include "GUI/SimpleTest.h"
#include "Demos/MazeGenerator.h"

/* Optional: Add your own custom tests here! */



/* * * * * Provided Tests Below This Point * * * * */

/* Utility function to free all memory allocated for a maze. */
void deleteMaze(const Grid<MazeCell*>& maze) {
    for (auto* elem: maze) {
        delete elem;
    }
    /* Good question to ponder: why don't we write 'delete maze;'
     * rather than what's shown above?
     */
}

PROVIDED_TEST("Checks paths in the sample maze.") {
    auto maze = toMaze({"* *-W *",
                        "| |   |",
                        "*-* * *",
                        "  | | |",
                        "S *-*-*",
                        "|   | |",
                        "*-*-* P"});

    /* These paths are the ones in the handout. They all work. */
    EXPECT(isPathToFreedom(maze[2][2], "ESNWWNNEWSSESWWN"));
    EXPECT(isPathToFreedom(maze[2][2], "SWWNSEENWNNEWSSEES"));
    EXPECT(isPathToFreedom(maze[2][2], "WNNEWSSESWWNSEENES"));

    /* These paths don't work, since they don't pick up all items. */
    EXPECT(!isPathToFreedom(maze[2][2], "ESNW"));
    EXPECT(!isPathToFreedom(maze[2][2], "SWWN"));
    EXPECT(!isPathToFreedom(maze[2][2], "WNNE"));

    /* These paths don't work, since they aren't legal paths. */
    EXPECT(!isPathToFreedom(maze[2][2], "WW"));
    EXPECT(!isPathToFreedom(maze[2][2], "NN"));
    EXPECT(!isPathToFreedom(maze[2][2], "EE"));
    EXPECT(!isPathToFreedom(maze[2][2], "SS"));

    deleteMaze(maze);
}

PROVIDED_TEST("Can't walk through walls.") {
    auto maze = toMaze({"* S *",
                        "     ",
                        "W * P",
                        "     ",
                        "* * *"});

    EXPECT(!isPathToFreedom(maze[1][1], "WNEES"));
    EXPECT(!isPathToFreedom(maze[1][1], "NWSEE"));
    EXPECT(!isPathToFreedom(maze[1][1], "ENWWS"));
    EXPECT(!isPathToFreedom(maze[1][1], "SWNNEES"));

    deleteMaze(maze);
}

PROVIDED_TEST("Works when starting on an item.") {
    auto maze = toMaze({"P-S-W"});

    EXPECT(isPathToFreedom(maze[0][0], "EE"));
    EXPECT(isPathToFreedom(maze[0][1], "WEE"));
    EXPECT(isPathToFreedom(maze[0][2], "WW"));

    deleteMaze(maze);
}

/* Printer for items. */
ostream& operator<< (ostream& out, Item item) {
    if (item == Item::NOTHING) {
        return out << "Item::NOTHING";
    } else if (item == Item::WAND) {
        return out << "Item::WAND";
    } else if (item == Item::POTION) {
        return out << "Item::POTION";
    } else if (item == Item::SPELLBOOK) {
        return out << "Item::SPELLBOOK";
    } else {
        return out << "<unknown item type>";
    }
}
