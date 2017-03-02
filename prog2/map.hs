import System.Console.ANSI
import Map

-- Converts the directions to Coordinates
toCoord :: String -> (Int, Int) -> (Int, Int)
toCoord dir coords = 
        if dir == "north"       then north coords;
        else if  dir == "south" then south coords;
        else if  dir == "west"  then west  coords;
        else if  dir == "east"  then east  coords;
        else if  dir == "exit"  then (-1, -1)
        else coords;

-- Checks for a valid coordinate
isValid :: (Int, Int) -> Bool
isValid coords =
        if fst coords < 1 then False
        else if  fst coords > 16 then False;
        else if  snd coords < 1  then False;
        else if  snd coords > 8 then False;
        else True;  

-- Checks for an exit signal
isExit :: (Int, Int) -> Bool
isExit coords = 
              if fst coords == -1 && snd coords == -1 then True;
              else False;

-- Writes movement to the screen
move :: (Int, Int) -> IO()
move coords = do
              clearScreen;
              setCursorPosition 0 0;
              drawMap;
              setCursorPosition (fst coords) (snd coords);
              putStrLn "*";
              setCursorPosition 18 0;
              putStrLn "Enter north, south, east, west, or exit: "

-- Main loop
loop :: (Int, Int) -> IO()
loop coords = do
              nextDir <- getLine;
              let curPos = coords;
              let nextPos = toCoord nextDir curPos;
              if isExit nextPos then do
                 clearScreen;
                 putStrLn "Exiting Map";
              else if isValid $ nextPos then do
                 move nextPos;
                 loop nextPos;
              else do
                 move curPos;
                 loop curPos;

-- Main Execution 
main = do
       clearScreen;
       setCursorPosition 0 0;
       drawMap;
       setCursorPosition 1 1;
       putStrLn "*";
       setCursorPosition 18 0;
       putStrLn "Enter north, south, east, or west: ";
       loop (1, 1);
