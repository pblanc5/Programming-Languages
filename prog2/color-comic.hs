import System.Console.ANSI
import Control.Concurrent
import System.Random 

frame2 =["                                         ",
         "  |\\ | /|                    |\\ | /|   ",
         "  \\_\\|/_/                    \\_\\|/_/ ",
         "    |_|                        |_|       ",
         "    |_|                        |_|       ",
         "    |_|                        |_|       ",
         "    |_|                        |_|       ",
         "    |_|                        |_|       ",
         "____|_|________________________|_|_______"];

frame3 =["                                         ",
         "   /| /                       /| /       ",
         "   \\|/ _ _                    \\|/ _ _  ",
         "    |_|\\_/                     |_|\\_/  ",
         "    |_|                        |_|       ",
         "    |_|                        |_|       ",
         "    |_|                        |_|       ",
         "    |_|                        |_|       ",
         "____|_|________________________|_|_______"];

frame1 =["                                         ",
         "   \\  |\\                      \\  |\\  ",
         " _ _\\ |/                    _ _\\ |/    ",
         " \\_/|_|                     \\_/|_|     ",
         "    |_|                        |_|       ",
         "    |_|                        |_|       ",
         "    |_|                        |_|       ",
         "    |_|                        |_|       ",
         "____|_|________________________|_|_______"];

movie = [frame1, frame2, frame3, frame2, frame1];
colors = [Red, Blue, Green, Yellow, Magenta, Cyan, White];


animate :: [[String]] -> [Color] -> IO()
animate frames cl = do
                    setCursorPosition 0 0 
	            threadDelay 100000
                    clearScreen
                    setSGR[SetColor Foreground Vivid (head cl)]
                    let next_cl = tail cl ++ [head cl]
                    mapM_ putStrLn (head frames)
                    let next = ((tail frames) ++ [head frames])
                    animate next next_cl
               

main = do 
    animate movie colors   
