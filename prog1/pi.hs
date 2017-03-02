-- Author: Patrick Blanchard
-- Date: 1-27-17
-- Description:  Approximate PI using the Nilakantha series.

-- Calculates one instance of the Nilakantha series
nilakantha :: Int -> Float
nilakantha n  =  if (mod n 4 == 0) then 
                      (-4 / (fromIntegral n * (fromIntegral n+1) * (fromIntegral n+2) ) ) 
                 else ( 4 / (fromIntegral n * (fromIntegral n+1) * (fromIntegral n+2) ) )

-- Approximates PI 
my_pi :: Float
my_pi = 3 + ( foldl (+) 0 $ map (nilakantha) [2,4 ..100] )

main = do
       print (my_pi)
