SELECT R.r3,S.s3,T.t3,x.u3,y.u3,x.u1,y.u2
FROM R,S,T,U as x, U as y
WHERE R.r1 == S.s1
  AND S.s1 == T.t1
  AND R.r1 == T.t1
  AND x.u2 == R.r2
  AND x.u1 == y.u2