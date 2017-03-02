import System.Console.ANSI
import Control.Concurrent
import System.Random 
import SpaceX

takeoff = [Red, Yellow]

animate :: [[String]] ->  [Color] -> IO()
animate [] colors = putStrLn ""
animate frames colors = do 
	       threadDelay 500000
               setCursorPosition 0 0
               clearScreen
               setSGR[SetColor Foreground Vivid (head colors), SetColor Background Dull Blue]
               let next_colors = (tail colors) ++ [head colors]
               mapM_ putStrLn (head frames)
               let next = tail frames
               animate next next_colors
               

main = do
    setTitle "SpaceX Rocket Launch"
    setCursorPosition 0 0 
    animate movie takeoff
    setSGR[Reset]   
