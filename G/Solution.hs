module Main where

import Control.Applicative
import Control.Monad
import Data.Ratio

solve :: Rational -> Rational -> Rational -> Rational
solve a b c
  | c <= 0 = 0
  | 0 <= c && c <= b = c*c / (2*a*b)
  | b <= c && c <= a = (c*c - (c-b)*(c-b)) / (2*a*b)
  | a <= c && c <= a + b =
      (1/b) * (a/2 - (c-b)*(c-b) / (2*a) + c - a)
  | c >= a + b = 1

solveIt a b c = solve (max a b) (min a b) c

main =
  do i <- read <$> getLine
     replicateM_ i $ do
        [a,b,c] <- map (fromIntegral . read) . words <$> getLine
        putStrLn $ showRatio $ solveIt a b c
  where showRatio x = show (numerator x) ++ "/" ++ show (denominator x)
