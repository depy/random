-- Need to sort list of points depending on angle between each of them and another point and axis x.

import Data.Monoid

data Point = Point { x :: Float, y :: Float} deriving (Show, Eq)
data Dir = DL | DR | DS deriving (Show)

instance Ord Point where
  compare (Point x y) (Point x' y') = mappend (compare y y') (compare x x')

distance :: Point -> Point -> Float
distance p0 p1 = sqrt ((x p0 - x p1)**2 + (y p0 - y p1)**2)

angle p0 p1 p2 = let a = Point (x p0 - x p1) (y p0 - y p1)
                     b = Point (x p0 - x p2) (y p0 - y p2)
                     f0 = (x a)*(x b)+(y a)*(y b)
                     f1 = sqrt ((x a)**2 + (y a)**2) * sqrt((x b)**2 + (y b)**2)
                     f = f0/f1
                 in (acos f) * 180 / pi

direction p0 p1 p2
  | cross p0 p1 p2 < 0  = DR
  | cross p0 p1 p2 > 0  = DL
  | cross p0 p1 p2 == 0 = DS
  where cross (Point x0 y0) (Point x1 y1) (Point x2 y2) =
          (x1-x0) * (y2-y0) - (y1 - y0) * (x2 - x0)

dirList [] = []
dirList (a:b:[]) = []
dirList (p0:p1:p2:ps) = let d = direction p0 p1 p2
                        in d : dirList(p1:p2:ps)

lowestPoint ps = minimum ps

angleWithXaxis p0 p1 = angle p0 xAxisPoint p1
  where xAxisPoint = Point ((x p0)-1) (y p0)

